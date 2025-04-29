cmake_minimum_required(VERSION 3.14)
project(ServidorBoost)

find_package(Boost REQUIRED)
add_executable(servidor main.cpp)
target_link_libraries(servidor Boost::boost boost_system pthread)