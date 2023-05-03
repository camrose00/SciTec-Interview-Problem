//
// Created by Cameron Rosenberger on 4/20/23.
//

#ifndef SANDBOX_ECEF_H
#define SANDBOX_ECEF_H
#include <ostream>
#include <iomanip>
#include <math.h>

class ECEF {
public:
    double time;        //seconds
    double x;           //meters
    double y;           //meters
    double z;           //meters

    ECEF() {}

    ECEF(double a, double b, double c, double d) {
        time = a;
        x = b;
        y = c;
        z = d;
    }
    friend std::ostream &operator<<(std::ostream &send, const ECEF &point) {
        send <<std::fixed<< "Time: " << int(point.time) << "s X: " <<int(point.x) << "m Y: " << int(point.y) << "m Z: " << int(point.z)<<"m";
        return send;
    }
};


#endif //SANDBOX_ECEF_H
