set(CMAKE_BUILD_TYPE Debug)

project (Bytesmack)

file(GLOB_RECURSE Bytesmack_SRC

	"src/*.h"
	"src/*.cpp"
)

add_executable(Bytesmack ${Bytesmack_SRC})