//
// Created by Cameron Rosenberger on 4/20/23.
//

#ifndef SCITEC_CODING_PROBLEM_VECTORLOGIC_H
#define SCITEC_CODING_PROBLEM_VECTORLOGIC_H

#include "ECEF.hpp"
#include <vector>

class VectorLogic {
public:
    /*  findLowerNeighbor
     * input: double time, vector<ECEF> dataset
     * findLowerNeighbor traverses vector and returns the closest point before the time requested
     * output:
     *  if time requested is less than all points in dataset, returns 0
     *  if time requested falls between the first and last point in the dataset, returns index of closest time point less than time requested
     *  if time requested is greater than all points in dataset, returns index of last element
     */
    static int findLowerNeighbor(double, std::vector<ECEF> &);

    /*getVelocityVector
     * input: ECEF p1, ECEF p2
     * calculates distance traveled divided by time
     * throws an error is p1.time == p2.time
     * output: vector<double> [dx/dt, dy/dt, dz/dt]
     */
    static std::vector<double> getVelocityVector(ECEF, ECEF);

    /*calculateVelocityMagnitude
     * input: vector<double> dx/dt, dy/dt, dz/dt from getVelocityVector
     * square root( (dx/dt)^2 + (dy/dt)^2 + (dz/dt)^2 )
     * returns the magnitude of the velocity vector aka speed
     * output: double
     */
    static double calculateVelocityMagnitude(std::vector<double>);

    /* requestedTimeTrio
     * input: int idx, vector<double>& dataset
     * function used when time requested is a point in the dataset
     * idx is the index of the time value requested
     * calculates the velocity vector of the point requested with the point above it,
     *      and then the point requested with the point below
     * averages speed across all 3 points
     * output: void
     */
    static void requestedTimeTrio(int, std::vector<ECEF> &);

    /* requestedTimePair
     * input: int idx, vector<double>& dataset
     * calculates the velocity vector of two points
     * if time requested is:
     *          - less than the first point in the dataset, uses first two points in dataset
     *          - equal to the first point in dataset, uses the first two points in dataset
     *          - between two points, uses the points above and below requested time
     *          - equal to the last point's time in dataset, uses the last two points
     *          - greater than all points in dataset, uses last point in dataset
     * calculates speed from velocity vector
     * output: void
     */
    static void requestedTimePair(int, double, std::vector<ECEF> &);
};


#endif //SCITEC_CODING_PROBLEM_VECTORLOGIC_H
