//
// Created by Cam Rosenberger
//

#include "ECEF.hpp"

ECEF::ECEF() {
    this->time = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

ECEF::ECEF(double time, double x_coord, double y_coord, double z_coord)
{
    this->time = time;
    this->x = x_coord;
    this->y = y_coord;
    this->z = z_coord;
}
