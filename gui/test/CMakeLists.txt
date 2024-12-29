cmake_minimum_required(VERSION 3.16)
project(runTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar módulos de Qt
find_package(Qt6 REQUIRED COMPONENTS Core Test)

# Incluir GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# Include _deps directory for gtest
include_directories(_deps/googletest-src/googletest/include)

# Incluir directorios de encabezados de Qt
include_directories(${CMAKE_SOURCE_DIR})

enable_testing()

# Agregar ejecutable para las pruebas
add_executable(
  runTests
  runTest.cpp
  utils_test.cpp
  ../src/utils.cpp
)

# Vincular bibliotecas de Google Test y Qt
target_link_libraries(
  runTests
  Qt6::Core
  Qt6::Test
  GTest::gtest_main
)

# Establecer el CRT compartido para Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Descubrir y registrar pruebas de GoogleTest
include(GoogleTest)
gtest_discover_tests(runTests)

