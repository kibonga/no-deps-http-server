cmake_minimum_required(VERSION 3.26)
project(no_deps_http_server C)

set(CMAKE_C_STANDARD 17)

add_executable(server server.c)
add_executable(client client.c)
