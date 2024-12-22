cmake_minimum_required(VERSION 3.16)
project(ActualizarMapa)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

add_executable(ActualizarMapa main2.cpp)

target_link_libraries(ActualizarMapa Qt6::Core Qt6::Gui)
