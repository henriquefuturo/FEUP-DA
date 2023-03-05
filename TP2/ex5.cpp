#include "exercises.h"

#include <cmath>


Result nearestPointsBF(std::vector<Point> &vp) {
    Result res;
    long long int d = INT64_MAX;

    for (Point point : vp) {
        for (Point p : vp) {
            if(!(point.operator==(p)) && p.distance(point) < d) {
                d = p.distance(point);
                res.dmin = p.distance(point);
                res.p1 = p;
                res.p2 = point;
            }
        }
    }
    return res;
}

/// TESTS ///
#include "gtest/gtest.h"

TEST(TP2_Ex5, testNPBF) {
    testNearestPoints(nearestPointsBF, "Brute force");
}