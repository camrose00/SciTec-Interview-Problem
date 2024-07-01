//
// Created by Cam Rosenberger
//

#include "LLA.hpp"

LLA::LLA() {
    this->time = 0;
    this->altitude = 0;
    this->latitude = 0;
    this->longitude = 0;
}

LLA::LLA(double time, double lat, double longi, double alt) {
    //converting deg to rad
    const double PI = 2 * acos(0.0);
    this->time = time;
    this->latitude = PI * lat / 180;
    this->longitude = PI * longi / 180;
    this->altitude = alt * 1000;//km to m
}
