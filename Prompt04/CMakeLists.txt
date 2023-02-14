
find_package(Curses REQUIRED)

add_executable(Prompt04 main.cpp)
target_link_libraries(Prompt04 curses)