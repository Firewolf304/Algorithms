//
// Created by firewolf on 03.12.24.
//

#ifndef K_MEANS_POINT_HXX
#define K_MEANS_POINT_HXX
#include "../libs.hpp"
struct Point {
    float x, y;
    int cluster;
    __device__ __host__ Point(const float & x, const float & y) : x(x), y(y), cluster(-1) {}
    __device__ __host__ Point(float & x, float & y) : x(x), y(y), cluster(-1) {}
};

#endif //K_MEANS_POINT_HXX
