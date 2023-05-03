//
// Created by Cameron Rosenberger on 4/22/23.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include "VectorLogic.h"
#include "ECEF.h"
#include "Converter.h"

TEST_CASE("findLowerNeighbor") {
    ECEF a(1, 1, 2, 3);
    ECEF b(2, 2, 3, 4);
    ECEF c(4, 3, 4, 5);
    std::vector<ECEF> points{a, b, c};
    SECTION("requested time is less than all points in dataset") {
        int result = VectorLogic::findLowerNeighbor(0, points);
        REQUIRE(result == 0);
    }SECTION("Requested time is greater than all points in dataset") {
        int result = VectorLogic::findLowerNeighbor(10, points);
        REQUIRE(result == 2);
    }
}
TEST_CASE("getVelocityVector") {
    ECEF a(1, 1, 2, 3);
    ECEF b(2, 2, 3, 4);
    ECEF c(4, 3, 4, 5);
    SECTION("(1,1,2,3) -> (2,2,3,4)") {// time @ p1 < p2
        std::vector<double> position = VectorLogic::getVelocityVector(a, b);
        REQUIRE(position[0] == 1);
        REQUIRE(position[1] == 1);
        REQUIRE(position[2] == 1);
    }SECTION("(2,2,3,4) -> (1,1,2,3)") {// time @ p2 > p1
        std::vector<double> position = VectorLogic::getVelocityVector(b, a);
        REQUIRE(position[0] == 1);
        REQUIRE(position[1] == 1);
        REQUIRE(position[2] == 1);
    }
}
TEST_CASE("getComponentTime") {
    ECEF a(2, 1, 2, 3); //time==2, x==1, y==2, z==3
    ECEF b(4, 2, 3, 4); //time==4, x==2, y==3, z==4
    ECEF c(5, 3, 4, 5); //time==4, x==3, y==4, z==5
    SECTION("(2,1,2,3) -> (4,2,3,4)") {// time @ p1 < p2
        std::vector<double> result = VectorLogic::getVelocityVector(a, b);
        //x,y,z points all move 1 unit in 2 seconds, 1m/2sec == 0.5
        REQUIRE(result[0] == .5);
        REQUIRE(result[1] == .5);
        REQUIRE(result[2] == .5);
    }SECTION("(4,2,3,4) -> (2,1,2,3)") {// time @ p2 > p1
        std::vector<double> result = VectorLogic::getVelocityVector(b, a);
        //x,y,z points all move 1 unit in 2 seconds, 1m/2sec == .5
        REQUIRE(result[0] == .5);
        REQUIRE(result[1] == .5);
        REQUIRE(result[2] == .5);
    }
}
TEST_CASE("calculateVelocityMagnitude") {
    SECTION(".5,.5,.5 == sqrt(3/4)") {
        double speed = VectorLogic::calculateVelocityMagnitude(std::vector<double>(3, .5));
        REQUIRE(speed == sqrt(3) / 2);
    }
}
TEST_CASE("Converting LLA to ECEF") {
    SECTION("(0,0,0)") {
        LLA a(0,0,0,0);
        ECEF b = Converter::LLA_to_ECEF(a);
        REQUIRE(int(b.x) == 6378137);//value of WGS 'a'
        REQUIRE(int(b.y) == 0);
        REQUIRE(int(b.z) == 0);
    }
    SECTION("(-50,-50,1)") {//test came from using online conversion tool
        LLA a(0,-50,-50,1);
        ECEF b = Converter::LLA_to_ECEF(a);
        REQUIRE(int(b.x) == 2640897);
        REQUIRE(int(b.y) == -3147298);
        REQUIRE(int(b.z) == -4863555);
    }
    SECTION("(53.3498,-6.2603,6.096)") {//test came from using online conversion tool
        LLA a(0,53.3498,-6.2603,6.096);
        ECEF b = Converter::LLA_to_ECEF(a);
        REQUIRE(int(b.x) == 3796382);
        REQUIRE(int(b.y) == -416462);
        REQUIRE(int(b.z) == 5098767);
    }
}