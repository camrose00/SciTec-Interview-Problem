//
// Created by Cameron Rosenberger on 4/20/23.
//

#ifndef SCITEC_CODING_PROBLEM_LLA_H
#define SCITEC_CODING_PROBLEM_LLA_

#include <cmath> // acos() for PI value
#include <ostream>

class LLA {
public:
    double time;            //seconds
    double latitude;        //radians
    double longitude;       //radians
    double altitude;        //meters

    LLA();

    LLA(double a, double b, double c, double d) {
        //converting degrees to radians for use with trig functions
        const double PI = 2 * acos(0.0);
        time = a;               //s
        latitude = PI * b / 180;    //degrees
        longitude = PI * c / 180;   //degrees
        altitude = d * 1000;           //km to m
    }

    friend std::ostream &operator<<(std::ostream &send, const LLA &point) {
        send << std::fixed << "Time: " << point.time << "s Latitude: " << point.latitude << "rad. Longitude: "
             << point.longitude << "rad. Altitude: " << point.altitude<<"m";
        return send;
    }
};


#endif //SCITEC_CODING_PROBLEM_LLA_H
