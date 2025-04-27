cmake_minimum_required(VERSION 3.10)
project(VHashTable C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries)

# Lib estática
add_library(vhash_static STATIC src/VHashTable.c)
target_compile_options(vhash_static PRIVATE -g)
set_target_properties(vhash_static PROPERTIES OUTPUT_NAME "vhash")
target_include_directories(vhash_static PUBLIC src)

# Lib compartilhada
add_library(vhash_shared SHARED src/VHashTable.c)
target_compile_options(vhash_shared PRIVATE -g)
set_target_properties(vhash_shared PROPERTIES OUTPUT_NAME "vhash")
target_include_directories(vhash_shared PUBLIC src)

# Executável de teste (linkando com a versão estática por padrão)
add_executable(test_vhash test/Test.c)
target_compile_options(test_vhash PRIVATE -g)
target_link_libraries(test_vhash PRIVATE vhash_static)
