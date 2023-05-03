SciTec_Coding_Problem created by Cameron Rosenberger 4/20/23

To run the program, give three arguments:
    1 - dataset file name,
    2 - first time value,
    3 - second time value

ex - navigate to 'cmake-build-debug' folder then enter the following text into mac terminal:
> ./SciTec_Coding_Problem SciTec_code_problem_data.csv TIME1 TIME2

where TIME1 and TIME2 are requested times. 

For Linux environments enter the following text: 
> g++ main.cpp Converter.h Converter.cpp VectorLogic.h VectorLogic.cpp ECEF.h LLA.h -o SciTec_Program_Executable
 
then
> ./SciTec_Program_Executable cmake-build-debug/SciTec_code_problem_data.csv TIME1 TIME2

C++14 and newer required

Program reads in data from the file given,
    converts points from LLA to ECEF, 
    calculates velocity vectors for the two times given as program arguments,
    calculates speed from velocity vector

A catch2 testing file is included as TestCases.cpp.
