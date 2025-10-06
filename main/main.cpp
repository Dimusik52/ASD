// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#define MATRIX
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
  }
}

template <typename T>
TriangleMatrix<T> trianglematrix_user_input() {
  int m, n;

  std::cout << "Please enter the size of matrix (m n): ";
  std::cin >> m;
  std::cin >> n;
  try {
    TriangleMatrix<T> tr_matrix(m, n);
    std::cout << "Input matrix: " << std::endl;
    std::cin >> tr_matrix;
    return tr_matrix;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

template <typename T>
MathVector<T> mathvector_user_input() {
  int m;

  std::cout << "Please enter the size of mathvector (m): ";
  std::cin >> m;
  try {
    MathVector<T> vector(m);
    std::cout << "Input vector: " << std::endl;
    std::cin >> vector;
    return vector;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
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
          std::cout << "Answer:\n" << matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 2:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = matrix_1 * mathvector_1;
          std::cout << "Answer:\n" << mathvector_2;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 3:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = mathvector_1 * matrix_1;
          std::cout << "Answer:\n" << mathvector_2;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 4:
        system("cls");
        try {
          mathvector_1 = mathvector_user_input<int>();
          mathvector_2 = mathvector_user_input<int>();
          int number = mathvector_1 * mathvector_2;
          std::cout << "Answer:\n" << number;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 5:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          matrix_2 = matrix_user_input<int>();
          matrix_3 = matrix_1 + matrix_2;
          std::cout << "Answer:\n" << matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 6:
        system("cls");
        try {
          matrix_1 = matrix_user_input<int>();
          matrix_2 = matrix_user_input<int>();
          matrix_3 = matrix_1 - matrix_2;
          std::cout << "Answer:\n" << matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 7:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 + tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 8:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 - tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      case 9:
        system("cls");
        try {
          tr_matrix_1 = trianglematrix_user_input<int>();
          tr_matrix_2 = trianglematrix_user_input<int>();
          tr_matrix_3 = tr_matrix_1 * tr_matrix_2;
          std::cout << "Answer:\n" << tr_matrix_3;
          system("pause");
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      default:
        std::cout << "Wrong Input. Try again!" << std::endl;
        break;
    }
  }
}
#endif // MATRIX