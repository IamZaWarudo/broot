cmake_minimum_required(VERSION 3.16)
project(broot VERSION 1.0.0 LANGUAGES CXX)

find_package(ROOT REQUIRED)

set(CMAKE_CXX_STANDARD ${ROOT_CXX_STANDARD})
set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

add_library(BLib src/Banalyzer.cxx src/HistoScanner.cxx)
target_link_libraries(BLib ROOT::Core ROOT::Hist ROOT::Tree ROOT::RIO ROOT::Gpad ROOT::Gui) 

add_executable(broot app/main.cxx)
target_link_libraries(broot BLib ROOT::Core ROOT::Gpad ROOT::Gui)
