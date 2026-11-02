include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(TY1500_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(TY1500_default_default_XC8_FILE_TYPE_assemble)
add_library(TY1500_default_default_XC8_assemble OBJECT ${TY1500_default_default_XC8_FILE_TYPE_assemble})
    TY1500_default_default_XC8_assemble_rule(TY1500_default_default_XC8_assemble)
    list(APPEND TY1500_default_library_list "$<TARGET_OBJECTS:TY1500_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(TY1500_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(TY1500_default_default_XC8_assemblePreprocess OBJECT ${TY1500_default_default_XC8_FILE_TYPE_assemblePreprocess})
    TY1500_default_default_XC8_assemblePreprocess_rule(TY1500_default_default_XC8_assemblePreprocess)
    list(APPEND TY1500_default_library_list "$<TARGET_OBJECTS:TY1500_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(TY1500_default_default_XC8_FILE_TYPE_compile)
add_library(TY1500_default_default_XC8_compile OBJECT ${TY1500_default_default_XC8_FILE_TYPE_compile})
    TY1500_default_default_XC8_compile_rule(TY1500_default_default_XC8_compile)
    list(APPEND TY1500_default_library_list "$<TARGET_OBJECTS:TY1500_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(TY1500_default_image_8Q6Wlkgq ${TY1500_default_library_list})

set_target_properties(TY1500_default_image_8Q6Wlkgq PROPERTIES
    OUTPUT_NAME "default-production"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${TY1500_default_output_dir}")
target_link_libraries(TY1500_default_image_8Q6Wlkgq PRIVATE ${TY1500_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
TY1500_default_link_rule( TY1500_default_image_8Q6Wlkgq)


