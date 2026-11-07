cmake_minimum_required(VERSION 4.4)
project(redis_clone)

set(CMAKE_CXX_STANDARD 20)

add_executable(redis_clone main.cpp)
add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(servertest exercise/server.cpp)

