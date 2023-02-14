
find_package(Curses REQUIRED)

add_executable(Prompt02 main.cpp)
target_link_libraries(Prompt02 curses)