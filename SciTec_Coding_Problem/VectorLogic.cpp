//
// Created by Cameron Rosenberger on 4/20/23.
//
#include "VectorLogic.hpp"
#include "ECEF.hpp"
#include <iostream>
#include <vector>
using namespace std;

void VectorLogic::requestedTimePair(int idx, double time, vector<ECEF> &data) {
    ECEF p1 = data[idx];
    ECEF p2;
    if(p1.time < time && data[idx+1].time > time){
        cout << "Requested time is between two points in dataset..." << endl;
    }
    //time is either: before all points -- at first point -- between two points -- at last point -- greater than all points
    if (time == p1.time) {//p1 print statements
        cout <<"Requested point in dataset: \n\t" << p1 << endl;
    }else if(time < p1.time){// time requested is between two points in dataset
        cout<<"Closest point above time: \n\t"<<p1<<endl;
    }else{// time requested is less than all points in dataset
        cout<<"Closest point below time: \n\t"<<p1<<endl;
    }
    //p2 print statements
    if (idx == data.size()-1) {// time requested is last point or is greater than all points in dataset
        p2 = data[idx - 1];
        cout << "Second closest point below time: \n\t" << p2 << endl;
    } else {
        p2 = data[idx + 1];
        if(time < p1.time){//time requested is either first in dataset or less than all points in dataset
            cout << "Second closest point above time: \n\t" << p2 << endl;
        }else{//time requested is between two points
            cout << "Closest point above time: \n\t" << p2 << endl;
        }
    }
    vector<double> velocity_vector = VectorLogic::getVelocityVector(p1, p2);
    string velocity = "V = " + to_string(velocity_vector[0]) + "i " +
                  (velocity_vector[1] >= 0 ? "+" : "") + to_string(velocity_vector[1]) + "j " +
                  (velocity_vector[2] >= 0 ? "+" : "") + to_string(velocity_vector[2]) + "k";
    cout << "Velocity vector between closest two points: \n\t" << velocity<<endl;

    double speed = VectorLogic::calculateVelocityMagnitude(velocity_vector);
    cout << "Constant speed between points: \n\t" << int(speed) << " m/s"<<endl;
}
void VectorLogic::requestedTimeTrio(int idx, vector<ECEF> &data) {
    //find velocity of higher plus velocity of lower then avg
    ECEF p1 = data[idx];
    cout << "Requested point in dataset. \nAveraging velocity between next point higher, requested point, and previous point in dataset" << endl;
    //  p2 < p1 < p3
    //begin higher point
    ECEF p2 = data[idx + 1];
    ECEF p3 = data[idx - 1];
    cout << "Closest point above time: \n\t" << p2 << endl;
    cout << "Requested point: \n\t" << p1 << endl;
    cout << "Closest point below time: \n\t" << p3 << endl;

    vector<double> velocity_vector1 = VectorLogic::getVelocityVector(p1, p2);
    string velocity = "V = " + to_string(velocity_vector1[0]) + "i " +
                      (velocity_vector1[1] >= 0 ? "+" : "") + to_string(velocity_vector1[1]) + "j " +
                      (velocity_vector1[2] >= 0 ? "+" : "") + to_string(velocity_vector1[2]) + "k";
    cout << "Velocity vector between requested point and higher point: \n\t" << velocity << endl;
    double speed1 = VectorLogic::calculateVelocityMagnitude(velocity_vector1);
    cout << "Constant speed between first points: \n\t" << int(speed1) << " m/s" << endl;
    //end higher point
    //begin lower point
    vector<double> velocity_vector2 = VectorLogic::getVelocityVector(p1, p3);
    string velocity2 = "V = " + to_string(velocity_vector2[0]) + "i " +
                       (velocity_vector2[1] >= 0 ? "+" : "") + to_string(velocity_vector2[1]) + "j " +
                       (velocity_vector2[2] >= 0 ? "+" : "") + to_string(velocity_vector2[2]) + "k";
    cout << "Velocity vector between requested point and lower point: \n\t" << velocity2 << endl;
    double speed2 = VectorLogic::calculateVelocityMagnitude(velocity_vector2);
    cout << "Constant speed between second points: \n\t" << speed2 << " m/s" << endl;
    //end lower point
    double avg_speed = (speed1 + speed2) / 2;
    cout << "Average speed of particle across 3 points: \n\t" << int(avg_speed) << " m/s" << endl;
}
vector<double> VectorLogic::getVelocityVector(ECEF p1, ECEF p2){
    //f(t) = a+bt where a and b are constants, t is time
    vector<double> position_vector(3);
    vector<double> p1_coordinates{p1.x, p1.y, p1.z};
    vector<double> p2_coordinates{p2.x, p2.y, p2.z};

    for (int i = 0; i < 3; i++) {
        double t1 = p1.time;
        double t2 = p2.time;
        if(t1 == t2){
            throw runtime_error("\n\tgetVelocityVector: t1 == t2. Vector is infinite between points");
        }
        double x1 = p1_coordinates[i];
        double x2 = p2_coordinates[i];
        //f(x1) = a + bt1 = x1    a always cancels out when you take the derivative because it is a constant
        //f(x2) = a + bt2 = x2
        double lhs = t1 - t2;       // left hand side
        double rhs = x1 - x2;       //right hand side

        double b = rhs / lhs;       //possible error from t1 == t2
        double a = 0;
        //f(x) = a+bt
        double f = a + b;           //f(x) = a + bt
        if(isnan(f)){// resolves t1 == t2 problem
            f = 0;
        }
        position_vector[i] = f;
    }
    return position_vector;
    //position vector is same as velocity vector here
    //v(x) = d'(x) + d'(y) + d'(z)
    //v(x) = '(a+bt) + '(a+bt) + '(a+bt)
    //'(a+bt) = b since a is constant and the t drops out
}
double VectorLogic::calculateVelocityMagnitude(vector<double> velocity) {
    //speed = square root(v(x)^2+v(y)^2+v(z)^2)
    double speed = sqrt(pow(velocity[0], 2) + pow(velocity[1], 2) + pow(velocity[2], 2));
    return speed;
}
int VectorLogic::findLowerNeighbor(double time, vector<ECEF> &data) {
    //time given is either:
    //                      less than all times in dataset,
    //                      between two points,
    //                      equal to a point,
    //                      or greater than all times in dataset
    for (int i = 0; i < data.size(); i++) {
        if (data[i].time > time) {
            if (i == 0) {
                cout << "Time requested is before any points in dataset..." << endl;
                return 0;
            } else {
                return i - 1;
            }
        }
    }
    cout << "Time requested greater than all points in dataset..."<<endl;
    return data.size() - 1;     //last element in dataset
}
