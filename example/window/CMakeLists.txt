project("window")

add_executable(${PROJECT_NAME} "create_window.c")

target_link_libraries(${PROJECT_NAME} ${lpw_all_dependencies})