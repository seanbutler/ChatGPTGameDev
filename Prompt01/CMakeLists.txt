

find_package(Curses REQUIRED)

add_executable(Prompt01 main.cpp)
target_link_libraries(Prompt01 curses)