project("mouse")

add_executable(${PROJECT_NAME} "test_mouse.c")

target_link_libraries(${PROJECT_NAME} ${lpw_all_dependencies})