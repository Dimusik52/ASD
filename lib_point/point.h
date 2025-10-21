// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
 private:
  int _x;
  int _y;

 public:
  Point();
  Point(int x_inp, int y_inp);
  Point(const Point& other);
  ~Point();
  int get_x();
  int get_y();
};

int calculate_destination(Point p1, Point p2);

#endif  // !LIB_POINT_POINT_H_