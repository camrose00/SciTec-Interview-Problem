#include <iostream>
#include "ECEF.hpp"
#include "VectorLogic.hpp"
#include "Converter.hpp"
#include <vector>
using namespace std;

int main(int argc, char **argv) {
    //argv[1] == dataset file name
    //argv[2] == first time requested
    //argv[3] == second time requested
    double requested_times[2];
    try {
        requested_times[0] = stod(argv[2]);
        requested_times[1] = stod(argv[3]);
    }catch(exception e){
        throw runtime_error("Incorrect arguments given");
        exit(99);
    }

    vector<ECEF> data;
    Converter::read_convert(argv[1], data);
    for (int i = 0; i < 2; i++) {
        double time = requested_times[i];
        cout << fixed << "Time #" << i + 1 << " requested: " << int(time) << "s" << endl;
        cout << string(30, '-') << endl;
        int idx = VectorLogic::findLowerNeighbor(time, data);
        ECEF p1 = data[idx];

        if (p1.time == time & idx != 0) {// if requested time is in the dataset average the velocity with its two closest neighbors
            VectorLogic::requestedTimeTrio(idx, data);
        } else {                //index will either be 0, the index of the closest lower point, or the end of dataset
            VectorLogic::requestedTimePair(idx, time, data);
        }
        cout << endl;
    }
    cout << "Finished calculations..goodbye" << endl;
    return 0;
}
