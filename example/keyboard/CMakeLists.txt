project("keyboard")

add_executable(${PROJECT_NAME} "test_keyboard.c")

target_link_libraries(${PROJECT_NAME} ${lpw_all_dependencies})