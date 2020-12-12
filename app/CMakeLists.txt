set(elf_file ${CMAKE_PROJECT_NAME}.elf)
add_executable(${elf_file} main.cpp)


target_link_libraries(${elf_file} idf::esp32 idf::freertos idf::spi_flash)
# Attach additional targets to the executable file for flashing,
# linker script generation, partition_table generation, etc.
idf_build_executable(${elf_file})