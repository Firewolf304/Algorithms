//
// Created by firewolf on 03.12.24.
//

#ifndef K_MEANS_POINT_HXX
#define K_MEANS_POINT_HXX
#include "../libs.hpp"
class Point {
    double x, y;

public:
    int cluster; // Номер кластера, к которому принадлежит точка
    Point(const double & x, const double & y) : x(x), y(y), cluster(-1) {}
    Point(double & x, double & y) : x(x), y(y), cluster(-1) {}
    double distance(const Point & b) {
        return std::sqrt((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y));
    }
    ~Point(){
        this->x = 0;
        this->y = 0;
    }
    double & get_x() {
        return this->x;
    }
    double & get_y() {
        return  this->y;
    }
    void set_x(int set_x) {
        this->x = set_x;
    }
    void set_x(const int &set_x) {
        this->x = set_x;
    }

    void set_x(int &set_x) {
        this->x = set_x;
    }

    void set_y(int set_y) {
        this->y = set_y;
    }

    void set_y(const int &set_y) {
        this->y = set_y;
    }

    void set_y(int &set_y) {
        this->y = set_y;
    }
};

#endif //K_MEANS_POINT_HXX
