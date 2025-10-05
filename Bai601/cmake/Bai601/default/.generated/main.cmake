# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Bai601_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(Bai601_default_default_XC8_FILE_TYPE_assemble)
add_library(Bai601_default_default_XC8_assemble OBJECT ${Bai601_default_default_XC8_FILE_TYPE_assemble})
    Bai601_default_default_XC8_assemble_rule(Bai601_default_default_XC8_assemble)
    list(APPEND Bai601_default_library_list "$<TARGET_OBJECTS:Bai601_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(Bai601_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(Bai601_default_default_XC8_assemblePreprocess OBJECT ${Bai601_default_default_XC8_FILE_TYPE_assemblePreprocess})
    Bai601_default_default_XC8_assemblePreprocess_rule(Bai601_default_default_XC8_assemblePreprocess)
    list(APPEND Bai601_default_library_list "$<TARGET_OBJECTS:Bai601_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(Bai601_default_default_XC8_FILE_TYPE_compile)
add_library(Bai601_default_default_XC8_compile OBJECT ${Bai601_default_default_XC8_FILE_TYPE_compile})
    Bai601_default_default_XC8_compile_rule(Bai601_default_default_XC8_compile)
    list(APPEND Bai601_default_library_list "$<TARGET_OBJECTS:Bai601_default_default_XC8_compile>")
endif()

add_executable(Bai601_default_image_6rV8TbQy ${Bai601_default_library_list})

set_target_properties(Bai601_default_image_6rV8TbQy PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Bai601_default_output_dir})
set_target_properties(Bai601_default_image_6rV8TbQy PROPERTIES OUTPUT_NAME "default")
set_target_properties(Bai601_default_image_6rV8TbQy PROPERTIES SUFFIX ".elf")

target_link_libraries(Bai601_default_image_6rV8TbQy PRIVATE ${Bai601_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
Bai601_default_link_rule(Bai601_default_image_6rV8TbQy)



