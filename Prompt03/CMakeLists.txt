
find_package(Curses REQUIRED)

add_executable(Prompt03 main.cpp)
target_link_libraries(Prompt03 curses)