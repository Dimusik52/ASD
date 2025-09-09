#include <iostream>
#include "../lib_point/point.h"


#ifndef _LIB_CIRCLE_CIRCLE_H_
#define _LIB_CIRCLE_CIRCLE_H_

enum Position { OUTSIDE, INTERSECTS, EQUALS, TOUCH, INSIDE };

class Circle {
 private:
  Point _center;
  int _radius;

 public:
  Circle();
  Circle(int x, int y, int r);
  Circle(Point point, int r);
  int get_r();
  Point get_point();
  ~Circle();

 private:
};

template <typename T>
Position calculate_pos(T obj1, T obj2) {
  int destination = calculate_destination(obj1.get_point(), obj2.get_point());
  if ((destination == (std::max(obj1.get_r(), obj2.get_r()) -
                       std::min(obj1.get_r(), obj2.get_r()))) ||
      (destination == (std::max(obj1.get_r(), obj2.get_r()) +
                       std::min(obj1.get_r(), obj2.get_r())))) {
    return Position::TOUCH;
  } else if (destination > (std::max(obj1.get_r(), obj2.get_r()) +
                            std::min(obj1.get_r(), obj2.get_r()))) {
    return Position::OUTSIDE;
  } else if (destination == 0) {
    return Position::EQUALS;
  } else if (destination < (std::max(obj1.get_r(), obj2.get_r()) -
                            std::min(obj1.get_r(), obj2.get_r()))) {
    return Position::INSIDE;
  } else if ((std::max(obj1.get_r(), obj2.get_r()) -
              std::min(obj1.get_r(), obj2.get_r())) < destination <
             (std::max(obj1.get_r(), obj2.get_r()) +
              std::min(obj1.get_r(), obj2.get_r()))) {
    return Position::INTERSECTS;
  }
}
std::string positionToString(Position pos);

#endif  // !_LIB_CIRCLE_CIRCLE_H_