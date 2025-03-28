cmake_minimum_required(VERSION 3.10)
project(cProgram)

set(SOURCES
    src/farmsql.c
    src/pthread.c
    src/main.c
    src/serial.c
)

add_executable(cProgram ${SOURCES})
target_include_directories(cProgram PRIVATE include)

# library setting
target_include_directories(cProgram PRIVATE /usr/include/mysql)
target_link_directories(cProgram PRIVATE /usr/lib/mysql)
target_link_libraries(cProgram PRIVATE mysqlclient)