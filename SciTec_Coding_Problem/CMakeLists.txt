cmake_minimum_required(VERSION 3.22)
project(SciTec_Coding_Problem)

set(CMAKE_CXX_STANDARD 14)

add_executable(SciTec_Coding_Problem main.cpp ECEF.h LLA.h Converter.cpp Converter.h VectorLogic.cpp VectorLogic.h )
add_executable(TestCases ECEF.h LLA.h Converter.cpp Converter.h VectorLogic.cpp VectorLogic.h TestCases.cpp)
