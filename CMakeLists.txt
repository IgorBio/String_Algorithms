cmake_minimum_required(VERSION 3.5)

project(DNA_Analizer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/view
  ${CMAKE_SOURCE_DIR}/dna
)

set(HEADERS
  dna/dna.h
  view/console.h
)

set(SOURCES
  dna/dna.cc
  view/console.cc
)

add_executable(
  ${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  main.cc
)