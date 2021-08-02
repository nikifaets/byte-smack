set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 3.19)

set (CMAKE_CXX_STANDARD 17)
project (Bytesmack)

file(GLOB_RECURSE Bytesmack_SRC

	"src/*.h"
	"src/*.cpp"
)
add_executable(Bytesmack ${Bytesmack_SRC})