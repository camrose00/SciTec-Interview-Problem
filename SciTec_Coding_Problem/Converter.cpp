//
// Created by Cameron Rosenberger on 4/20/23.
//

#include "Converter.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Converter * Converter::getInstance()
{
    static Converter gConverter;
    return &gConverter;
}

Converter::Converter() {

}

ECEF Converter::LLA_to_ECEF(LLA src) {
    //WGS84 formulae from pdf given
    const double A = 6378137;
    const double F = 1 / 298.257224;
    double b = A * (1 - F);
    const double E = sqrt((pow(A,2) - pow(b,2)) / pow(A,2)); // sqrt((a^2-b^2)/a^2)
    double N = A / (sqrt(1 - E*E*pow(sin(src.latitude), 2)));

    ECEF dest;
    dest.x = (N + src.altitude) * cos(src.latitude) * cos(src.longitude);
    dest.y = (N + src.altitude) * cos(src.latitude) * sin(src.longitude);
    dest.z =  (N*pow(b,2)/pow(A,2)+src.altitude) * sin(src.latitude);
    dest.time = src.time;

    return dest;
}

void Converter::read_convert(std::string fName, vector<ECEF> &data) {
    //open file
    //read in data
    //convert LLA to ECEF
    //close file
    ifstream input(fName);
    if (!input.is_open()) {
        cout << "Input file not found..." << endl;
        exit(1);
    }
    while (!input.eof()) {
        char time[50], latitude[50], longitude[50], height[50];
        input.getline(time, 50, ',');
        input.getline(latitude, 50, ',');
        input.getline(longitude, 50, ',');
        input.getline(height, 50);
        try {//stod throws error if incompatible types given
            LLA row(std::stod(time), std::stod(latitude), std::stod(longitude), std::stod(height));
            ECEF converted = LLA_to_ECEF(row);
            data.push_back(converted);
        } catch (exception e) {
            break;
        }
    }
    input.close();
}
