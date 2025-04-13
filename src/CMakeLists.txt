add_compile_options(-Wall -Wextra -pedantic -fdiagnostics-color)

add_executable(${PROJECT_NAME} main.cpp parser.cpp scanner.cpp)
# Find the libraries that correspond to the LLVM components
# that we wish to use
# llvm_map_components_to_libnames(llvm_libs support core irreader)
#
# target_link_libraries(${PROJECT_NAME} LLVM)
