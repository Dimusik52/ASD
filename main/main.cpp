// Copyright 2024 Marina Usova

#define CIRCLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

#ifdef CIRCLE
#include <iostream>
#include "circle.h"
#include "point.h"

void main() {
  Point point1 = Point(2, 5);
  Point point2 = Point(7, 5);
  std::cout << point1.get_x() << " " << point1.get_y() << std::endl;
  std::cout << calculate_destination(point1, point2) << std::endl;

  // 1. Ќе пересекаютс€ (положительные координаты)
  Circle c1 = Circle(2, 3, 5);
  Circle c2 = Circle(15, 3, 3);
  std::cout << positionToString(calculate_pos(c1, c2)) << std::endl;

  // 2. Ќе пересекаютс€ (отрицательные координаты)
  Circle c3 = Circle(-5, -2, 4);
  Circle c4 = Circle(-20, -2, 3);
  std::cout << positionToString(calculate_pos(c3, c4)) << std::endl;

  // 3. ѕересекаютс€ в двух точках
  Circle c9 = Circle(1, 2, 5);
  Circle c10 = Circle(9, 2, 4);
  std::cout << positionToString(calculate_pos(c9, c10)) << std::endl;
  // 4.  асаютс€ внешним образом (положительные координаты)
  Circle c5 = Circle(4, 7, 5);
  Circle c6 = Circle(12, 7, 3);
  std::cout << positionToString(calculate_pos(c5, c6)) << std::endl;
  // 5.  асаютс€ внутренним образом (отрицательные координаты)
  Circle c15 = Circle(-6, -4, 8);
  Circle c16 = Circle(-3, -4, 5);
  std::cout << positionToString(calculate_pos(c15, c16)) << std::endl;
  // 6. ќдна внутри другой (положительные координаты)
  Circle c17 = Circle(3, 5, 10);
  Circle c18 = Circle(4, 5, 2);
  std::cout << positionToString(calculate_pos(c17, c18)) << std::endl;
  // 7. —овпадение (отрицательные координаты)
  Circle c23 = Circle(-5, -3, 3);
  Circle c24 = Circle(-5, -3, 6);
  std::cout << positionToString(calculate_pos(c23, c24)) << std::endl;
}

#endif  // CIRCLE
