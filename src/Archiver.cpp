    #include "Archiver.h"
    #include <assert.h>
    #include <fstream>
    #include "FileReader.h"
    #include "FileWriter.h"
    #include <filesystem>
    #include <algorithm>
    #include "FilePathManager.h"

/*
    Методът Archiver::compress взима като входни параметри име на архив, в който да се запази компресирания файл, и масив от стойности от
    тип string, които са пътища към директории и файлове за компресия.

    Компресията се случва в следната последователност:
    1. Имената на пътищата се обработват в зависимост от това дали съответния string е път към файл или към директория. Ако е път към директория,
    то рекурсивно се генерират релативни пътища от директорията до всички файлове вътре в нея. Ако е път към файл, то пътят се обработва, така че да остане
    само името на файла и той се поставя на най-горно ниво в структурата на архива.
    Пример: Ако входните пътища са {"dir/dir1/file1", "dir2"}, структурата на архива ще бъде:
        -file1
        -dir2
        -a
        -b
    , където a и b са произволни файлове/папки в директорията dir2 

    2. Сканират се всички файлове байт по байт, за да се създадат Хъфман кодовете. Те се запазват в CodeTable - асоциативен контейнер, който асоциира
    байт към Хъфман код. Освен CodeTable се създава и един допълнителен код, който служи като специален символ за отбелязване на ключови места в архивния файл.
    Класът Encoder е интерфейс, който осигурява специалния символ и Хъфман кодовете, използвайки класа HTree за създаване на Хъфман дърво.

    3. В архивния файл се записва дължината в битове на специалния символ. За нея са фиксирани 4 байта, за да може 
    при декомпресия да се прочете лесно с променлива от тип int. След дължината се записва самият специален символ. Той може да е с произволна дължина в битове и
    презентацията му се поддържа от класа Bitset. Във файла се запазва като последователност от променливи с тип unsigned long long. За да се прочете успешно трябва
    предварително да знаем дължината му.

    4. След специалния се кодира таблицата с кодове (CodeTable). Подобно на специалния символ, тя представлява поредица от int за дължина на код (в битове)
    и след това последователност от unsigned long long, модерирани чрез Bitset класа. Това е наложително, тъй като, както специалния символ, така и кодовете,
    могат да имат произволна дължина между 1 и 256 бита.

    5. След таблицата с кодове се записва броя файлове, които се съдържат в архивния файл.

    6. Следва кодирането на самите файлове. Файл се кодира като последователност от:
        - Дължина на името на файла (int). Името на файла може да е само име, а може и да е релативен път, в зависимост от ситуацията, описана в т. 1.
        - Името на файла, кодирано като string. По един байт за символ. Байтовете на имената на файлове НЕ са кодирани и се четат директно като char.
        - Самият файл. Файлът се обхожда байт по байт и всеки байт се замества със съответния Хъфман код. Последователността от битове се запазва в Bitset обект
        и накрая целия Bitset обект се записва във файла. Битовете на компресирания файл са разпределени из множество unsigned long long-ове.
        - Накрая на файла се поставя специалния символ. Той също е уникален Хъфман код и при неговото прочитане знаем, че сме стигнали край на файл в рамките на архивния файл.
        След специалния символ се ДОПЪЛВАТ празни байтове (0000000), така че след последния байт, в който се попада специалния символ да остават точно 8 празни байта.
        Обяснението за това е, че архивният файл се чете байт по байт. За всеки прочетен байт се прави проверка дали съдържа Хъфман код, който да бъде декодиран.
        Ако не съдържа, се прочита следващ байт и се конкатенира към първия. Отново се прави проверка дали се съдържа Хъфман код и т.н. Имайки това предвид, искаме да
        сме сигурни, че последния байт, който прочетем, за да парснем специалния символ не съдържа информация за някой код който идва след него. 
        Освен това искаме да знаем точно на кое положение във файла трябва отново да започнем да декодираме файлове. 
        Затова след специалния символ има  ФИКСИРАНО разстояние от точно 8 байта, които се прочитат преди да продължи разархивирането.
    
    7. След записването на специалния символ и на 8 празни байта, следва или нов int за дължина на име на компресиран файл или EOF, 
    който сигнализира край на архивния файл. 
*/
void Archiver::compress(const std::string& archive_name, const std::vector<std::string>& files){


    FileWriter writer;
    FileReader reader;
    FilePathManager filepath_manager;
    std::ifstream f;
    
    std::vector<std::string> archive_filenames;
    filepath_manager.filepaths_to_archive_names(files, archive_filenames);

    std::vector<std::string> readable_filenames;
    filepath_manager.filepaths_to_readable_files(files, readable_filenames);

    for(int i=0; i<readable_filenames.size(); i++){

        std::string file = readable_filenames[i];
        f.open(file);
        assert(f.good());   

        std::vector<byte> bytes;
        bool success = true;
        while(success){

            success = reader.read_byte_sequence(f, bytes);
            encoder.update_freq_table(bytes);
            bytes.clear();
        }
        f.close();
    }

    encoder.create_codes();
    Bitset special;
    encoder.get_special(special);
    CodeTable code_table;
    encoder.get_codes(code_table);
    std::ofstream of(archive_name);
    std::ofstream codes("codes");
    for(const std::pair<byte, Bitset>& code : code_table){
        codes << "key: " << (byte) code.first << std::endl;
        codes << "value: " << (std::string) code.second << std::endl;
    }
    codes.close();

    std::ofstream archive(archive_name, std::ios::binary);
    assert(archive.good());

    writer.write_code_table(archive, code_table, special);

    writer.write_bytes(archive, (int)readable_filenames.size());
    for(int i=0; i<readable_filenames.size(); i++){

        std::string file = readable_filenames[i];
        std::string archive_filename = archive_filenames[i];

        f.open(file);
        assert(f.good());
        int filename_size = archive_filename.size();
        writer.write_bytes(archive, (int)filename_size);
        //assert(file != files[1]);
        writer.write_string(archive, archive_filename);
        writer.write_file(archive, f, encoder, special);
        //if(i > 0)assert(readable_filenames[i-1] != "CMakeFiles/Bytesmack.dir/compiler_depend.make");
        f.close();
        
    }

    std::cout << "Compression OK\n";
    std::cout << "Special " << (std::string) special << std::endl;
}

/* 
    След запознаване с метода compress, методът decompress би следвало да е сравнително тривиален. Случват се почти същите неща, но в обратен ред:
    1. Прочитане на таблицата с кодове.
    2. Създаване на таблица, която асоциира код с байт (обратното на таблица с кодове) - DecodeTable.
    3. Прочитане на броя файлове, които се съдържат в архива.
    4. Следва прочитане на самите файлове - последователност от четене на дължина на името на файла; четене на string със съответната дължина;
    четене и декодиране на самия файл байт по байт. За всеки прочетен байт се проверява дали няма подмасив от битове, който започва от началото на последователността
    и съдържа Хъфман код. Четенето продължава до прочитане на специалния символ.
    5. След прочитане на специалния символ се прочитат точно 8 байта, след което се продължава или със следващ файл или край на архива.
    
    Методът compress съдържа също и функционалността да се извлече информация за архива. При подаване на get_info=true, методът ще разпечата
    на конзолата имената на файловете в архива, размерът на оригиналните файлове, размерът на архива и колко процента от сумата на размерите на 
    оригиналните файлове е архивния файл.

    Приема като параметри път към архивния файл, път директория, в която да се разархивира съдържанието на архива, вектор от файлове, които да бъдат разархивирани и get_info.
*/
bool Archiver::decompress(const std::string& archive_name, const std::string& out_dir, const std::vector<std::string>& files, bool get_info){

    std::ifstream archive(archive_name, std::ios::binary);
    assert(archive.good());

    bool extract_all = (std::find(files.begin(), files.end(), std::string("all")) != files.end());
    
    FileReader reader;
    FileWriter writer;

    Bitset special;
    CodeTable code_table;

    reader.read_code_table(archive, code_table, special);
    
    DecodeTable decode_table;
    encoder.decode_table_from_code_table(decode_table, code_table);

    int num_files;
    reader.read_bytes(num_files, archive);


    int sum_file_sizes = 0;
    std::vector<std::string> files_in_archive;
    
    for(int i=0; i<num_files; i++){
        std::cout << "START FILE " << i << std::endl;
        int strlen=0;
        reader.read_bytes(strlen, archive);

        //assert(i<1);
        std::string filename;
        reader.read_string(filename, strlen, archive);

        if(get_info){
            files_in_archive.push_back(filename);
        }      
        
        std::string filepath = out_dir + "/" + filename;
        bool file_requested = (std::find(files.begin(), files.end(), filename) != std::end(files));
        std::filesystem::path p(filepath);
        std::ofstream of;
        if(file_requested || extract_all){
            
            std::cout << "Creating dir: " << p.parent_path() << std::endl;
            if(!std::filesystem::exists(p.parent_path())) std::filesystem::create_directories(p.parent_path());
            of.open(filepath);
            assert(of.good());                
        } 

        std::vector<byte> bytes;
        bool success = true;
        while(success){

            success = reader.read_and_decode(archive, bytes, decode_table, special);
            if(file_requested) writer.append_bytes(of, bytes);
            sum_file_sizes += bytes.size();
            bytes.clear();
        }
        if(file_requested) of.close();

        std::cout << "file ready \n";
    }

    if(get_info){
            
        unsigned long long arch_size = std::filesystem::file_size(archive_name);
        print_info(arch_size, sum_file_sizes, files_in_archive);
    }
}

/*
    Метод за ъпдейтване на вече съществуващ файл в архива. Приема като параметри името на архива, името, с което търсеният файл е записан в архива,
    и път към файла, с който да се замести търсения файл. 

    Процедурата на изпълнение е следната:

    1. Сканиране на новия файл, прочитане и създаване на таблица с кодове и таблица за декодиране. Тъй като вкарваме нов файл в архива, 
    вече съществуващата таблица с кодове трябва да се актуализира. В момента това става като се променя честотата на срещане на различните байтове,
    като просто се прибавят тези на новия файл и на база това се преизчисляват Хъфман кодовете. Така ще се създаде вярна таблица, но не много ефективна, 
    тъй като все още ще съдържа кодовете на стария, неизползван файл.
    След множество такива операции Хъфман кодовете няма да бъдат релевантни и ефективни. 

    Ако се очаква тази операция да се използва често си струва да се помисли за друго решение, например напълно да се преизчисли таблицата, сканирайки всички файлове. 
    Това, обаче, би било по-бавно.

    2. Създаване на нов, временен архивен файл.
    
    3. Сканиране на стария архивен файл и презаписване на всички данни от него към новия. Щом стигнем до файла, който търсим, 
    го изпускаме и не го пишем в новия, временен архив. Новият файл се добавя на края на архива със същото име като стария.

    4. Старият архив се изтрива и новият се преименува да е с името на стария.

    Накратко: Актуализация на таблицата с кодове, декомпресия и после пак компресия.
*/
void Archiver::modify_archived_file(const std::string& archive_filepath, const std::string& old_filename, const std::string& modified_filepath){

    std::ifstream archive(archive_filepath);
    assert(archive.good());

    FileReader reader;
    FileWriter writer;

    // Read code table and special symbol

    Bitset special;
    CodeTable code_table;
    reader.read_code_table(archive, code_table, special);
    
    DecodeTable decode_table;
    encoder.decode_table_from_code_table(decode_table, code_table);

    int num_files;
    reader.read_bytes(num_files, archive);

    std::ifstream modified_file(modified_filepath);
    std::vector<byte> modified_bytes;
    reader.read_byte_sequence(modified_file, modified_bytes, 100000);

    // Update the code table
    encoder.set_code_table(code_table);
    encoder.update_freq_table(modified_bytes);
    encoder.create_codes();

    CodeTable updated_code_table;
    encoder.get_codes(updated_code_table);
    Bitset updated_special;
    encoder.get_special(updated_special);

    std::ofstream temp_arch("temp", std::ios::binary);
    writer.write_code_table(temp_arch, updated_code_table, updated_special);
    writer.write_bytes(temp_arch, num_files);

    for(int i=0; i<num_files; i++){

        
        int strlen = 0;
        std::string filename;

        reader.read_bytes(strlen, archive);
        reader.read_string(filename, strlen, archive);

        std::vector<byte> file_bytes;
        reader.read_and_decode(archive, file_bytes, decode_table, special);

        std::cout << " curr name " << old_filename << " target name " << modified_filepath << " curr_name " << filename << std::endl; 
        if(filename == old_filename){
            std::cout << "Found old filename " << std::endl;
            continue;
        } 

        Bitset encoded;
        encoder.encode(file_bytes, encoded);

        writer.write_bytes(temp_arch, (int)filename.size());
        writer.write_string(temp_arch, filename);
        encoded += updated_special;
        writer.append_archive(temp_arch, encoded);
        writer.write_byte_remainder(temp_arch, encoded);

    }

    Bitset new_file_encoded;
    encoder.encode(modified_bytes, new_file_encoded);
    writer.write_bytes(temp_arch, (int)old_filename.size());
    writer.write_string(temp_arch, old_filename);
    new_file_encoded += updated_special;
    std::cout << " new file encoded " << (std::string) new_file_encoded << std::endl;
    writer.append_archive(temp_arch, new_file_encoded);
    writer.write_byte_remainder(temp_arch, new_file_encoded);
    
    std::filesystem::rename("temp", archive_filepath);
    


}
void Archiver::print_info(const int arch_size, const int sum_file_sizes, const std::vector<std::string>& files_in_archive){

    std::cout << "Size of original files: " << sum_file_sizes << std::endl;
    std::cout << "Size of archive " << arch_size << std::endl;
    std::cout << "Compression level: " << std::setprecision(4) << (1.0 * arch_size / sum_file_sizes) * 100.0 << "%" << std::endl;

    std::cout << "\nCompressed files: \n \n";
    for(const std::string& s : files_in_archive){

        std::cout << s << std::endl;
    }
}