// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <iostream>
#include "../lib_point/point.h"

#include "cmath"
#include "algorithm"

Point::Point() {
  _x = 0;
  _y = 0;
}

Point::Point(int x, int y) {
  _x = x;
  _y = y;
}
int Point::get_x() { return _x; }

int Point::get_y() { return _y; }

int calculate_destination(Point p1, Point p2) {
  return int(sqrt(pow((p2.get_x() - p1.get_x()), 2) +
                  pow((p2.get_y() - p1.get_y()), 2)));
}

Point::Point(const Point& other) {
  if (&other != NULL) {
    _x = other._x;
    _y = other._y;
  }
}

Point::~Point() {}