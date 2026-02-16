// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#define ASD
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

  Circle c1 = Circle(2, 3, 5);
  Circle c2 = Circle(15, 3, 3);
  std::cout << positionToString(calculate_pos(c1, c2)) << std::endl;

  Circle c3 = Circle(-5, -2, 4);
  Circle c4 = Circle(-20, -2, 3);
  std::cout << positionToString(calculate_pos(c3, c4)) << std::endl;

  Circle c9 = Circle(1, 2, 5);
  Circle c10 = Circle(9, 2, 4);
  std::cout << positionToString(calculate_pos(c9, c10)) << std::endl;

  Circle c5 = Circle(4, 7, 5);
  Circle c6 = Circle(12, 7, 3);
  std::cout << positionToString(calculate_pos(c5, c6)) << std::endl;

  Circle c15 = Circle(-6, -4, 8);
  Circle c16 = Circle(-3, -4, 5);
  std::cout << positionToString(calculate_pos(c15, c16)) << std::endl;

  Circle c17 = Circle(3, 5, 10);
  Circle c18 = Circle(4, 5, 2);
  std::cout << positionToString(calculate_pos(c17, c18)) << std::endl;

  Circle c23 = Circle(-5, -3, 3);
  Circle c24 = Circle(-5, -3, 6);
  std::cout << positionToString(calculate_pos(c23, c24)) << std::endl;
}

#endif  // CIRCLE


#ifdef MATRIX
#include <iostream>
#include "../lib_matrix/matrix.h"
#include "../lib_mathvector/mathvector.h"
#include "../lib_trianglematrix/trianglematrix.h"

template <typename T>
Matrix<T> matrix_user_input() {
  int m,n;
  
  std::cout << "Please enter the size of matrix (m n): ";
  std::cin >> m;
  std::cin >> n;
  try {
    Matrix<T> matrix(m, n);
    std::cout << "Input matrix: " << std::endl;
    std::cin >> matrix;
    return matrix;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    system("pause");
  }
}

template <typename T>
TriangleMatrix<T> trianglematrix_user_input() {
  int m, n;
  bool is_upper;

  std::cout << "Please enter the size of matrix (m n): ";
  std::cin >> m;
  std::cin >> n;

  char input_char;
  std::cout << "Please enter is this matrix upper? (y/n): ";
  std::cin >> input_char;

  is_upper = (input_char == 'y');

  try {
    TriangleMatrix<T> tr_matrix(m, n, is_upper);
    std::cout << "Input matrix: " << std::endl;
    std::cin >> tr_matrix;
    return tr_matrix;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    system("pause");
  }
}

template <typename T>
MathVector<T> mathvector_user_input() {
  int m;

  std::cout << "Please enter the size of mathvector (m): ";
  std::cin >> m;
  MathVector<T> vector(m);
  try {
    std::cout << "Input vector: " << std::endl;
    std::cin >> vector;
    return vector;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return vector;
  }
}

void main() {
  while (true) {
    system("cls");
    std::cout << "1. Matrix*Matrix;\n"
              << "2. Matrix*Vector;\n"
              << "3. Vector*Matrix;\n"
              << "4. Vector*Vector;\n"
              << "5. Matrix+Matrix;\n"
              << "6. Matrix-Matrix;\n"
              << "7. TriangleMatrix+TriangleMatrix;\n"
              << "8. TriangleMatrix-TriangleMatrix;\n"
              << "9. TriangleMatrix*TriangleMatrix;\n"
              << "0. Exit." << std::endl;
    std::cout << "Please choose an action: ";
    int user_choice;
    std::cin >> user_choice;

    if (user_choice == 0) {
      break;
    }

    Matrix<int> matrix_1;
    Matrix<int> matrix_2;
    Matrix<int> matrix_3;
    TriangleMatrix<int> tr_matrix_1;
    TriangleMatrix<int> tr_matrix_2;
    TriangleMatrix<int> tr_matrix_3;
    MathVector<int> mathvector_1;
    MathVector<int> mathvector_2;

    switch (user_choice) {
      case 1:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          matrix_2 = matrix_user_input<int>();
          matrix_3 = matrix_1 * matrix_2;
          std::cout << "Answer:\n" << matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 2:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = matrix_1 * mathvector_1;
          std::cout << "Answer:\n" << mathvector_2 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 3:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = mathvector_1 * matrix_1;
          std::cout << "Answer:\n" << mathvector_2 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 4:
        system("cls");
        try {
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = mathvector_user_input<int>();
          int number = mathvector_1 * mathvector_2;
          std::cout << "Answer:\n" << number << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 5:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          matrix_2 = matrix_user_input<int>();
          matrix_3 = matrix_1 + matrix_2;
          std::cout << "Answer:\n" << matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 6:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          matrix_2 = matrix_user_input<int>();
          matrix_3 = matrix_1 - matrix_2;
          std::cout << "Answer:\n" << matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 7:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 + tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 8:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 - tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      case 9:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 * tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3 << std::endl;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          system("pause");
        }
        break;
      default:
        std::cout << "Wrong Input. Try again!" << std::endl;
        system("pause");
        break;
    }
  }
}
#endif // MATRIX

#ifdef ALGORITHMS

#include <iostream>
#include "../lib_algorithms/algorithms.h"


void main() {
  //Matrix<int> matrix(3, 3);
  //std::cin >> matrix;
  //std::cout << matrix_get_local_min(matrix);

  //std::string str = "() ())";
  //std::cout << check_brackets(str);
  //try {
  //  read_expression("1+2*(1x*(x+y))");
  //} catch (std::exception& e) {
  //  std::cerr << e.what();
  //}

  generateAndPrintLabyrinth(10, 10);
 
}

#endif