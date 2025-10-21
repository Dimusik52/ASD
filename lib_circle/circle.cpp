// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <iostream>
#include "circle.h"


Circle::Circle() {
  _radius = 0;
  _center = Point();
}

Point Circle::get_point() { return _center; }
int Circle::get_r() { return _radius; }

Circle::Circle(int x, int y, int r) {
  _center = Point(x, y);
  _radius = r;
}

Circle::Circle(Point point, int r) {
  _center = point;
  _radius = r;
}

Circle::~Circle() {}

std::string positionToString(Position pos) {
  switch (pos) {
    case OUTSIDE:
      return "Outside";
      break;
    case INTERSECTS:
      return "Intersects";
      break;
    case EQUALS:
      return "Equals";
      break;
    case TOUCH:
      return "Touch";
      break;
    case INSIDE:
      return "Inside";
      break;
    default:
      break;
  }
} 