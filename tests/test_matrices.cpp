// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_mathvector/mathvector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_trianglematrix/trianglematrix.h"

TEST(MathVectorTest, DefaultConstructor) {
  MathVector<int> vec;
  EXPECT_EQ(vec.size(), 0);
}

TEST(MathVectorTest, SizedConstructor) {
  MathVector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
  for (size_t i = 0; i < 5; i++) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(MathVectorTest, InitializerListConstructor) {
  MathVector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(MathVectorTest, CopyConstructor) {
  MathVector<int> original{1, 2, 3};
  MathVector<int> copy(original);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy[0], 1);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);
}

TEST(MathVectorTest, Addition) {
  MathVector<int> a{1, 2, 3};
  MathVector<int> b{4, 5, 6};
  MathVector<int> result = a + b;

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 5);
  EXPECT_EQ(result[1], 7);
  EXPECT_EQ(result[2], 9);
}

TEST(MathVectorTest, Subtraction) {
  MathVector<int> a{10, 20, 30};
  MathVector<int> b{1, 2, 3};
  MathVector<int> result = a - b;

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 9);
  EXPECT_EQ(result[1], 18);
  EXPECT_EQ(result[2], 27);
}

TEST(MathVectorTest, ScalarMultiplication) {
  MathVector<int> vec{1, 2, 3};
  MathVector<int> result = vec * 3;

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 6);
  EXPECT_EQ(result[2], 9);
}

TEST(MathVectorTest, DotProduct) {
  MathVector<int> a{1, 2, 3};
  MathVector<int> b{4, 5, 6};
  int result = a * b;  // 1*4 + 2*5 + 3*6

  EXPECT_EQ(result, 32);
}

TEST(MathVectorTest, CompoundAddition) {
  MathVector<int> a{1, 2, 3};
  MathVector<int> b{4, 5, 6};
  a += b;

  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(a[1], 7);
  EXPECT_EQ(a[2], 9);
}

TEST(MathVectorTest, CompoundSubtraction) {
  MathVector<int> a{10, 20, 30};
  MathVector<int> b{1, 2, 3};
  a -= b;

  EXPECT_EQ(a[0], 9);
  EXPECT_EQ(a[1], 18);
  EXPECT_EQ(a[2], 27);
}

TEST(MathVectorTest, CompoundScalarMultiplication) {
  MathVector<int> a{1, 2, 3};
  a *= 4;

  EXPECT_EQ(a[0], 4);
  EXPECT_EQ(a[1], 8);
  EXPECT_EQ(a[2], 12);
}

TEST(MathVectorTest, AdditionSizeMismatchThrows) {
  MathVector<int> a{1, 2, 3};
  MathVector<int> b{1, 2};

  EXPECT_THROW(a + b, std::logic_error);
  EXPECT_THROW(a += b, std::logic_error);
}

TEST(MathVectorTest, SubtractionSizeMismatchThrows) {
  MathVector<int> a{1, 2, 3, 4};
  MathVector<int> b{1, 2, 3};

  EXPECT_THROW(a - b, std::logic_error);
  EXPECT_THROW(a -= b, std::logic_error);
}

TEST(MathVectorTest, DotProductSizeMismatchThrows) {
  MathVector<int> a{1, 2, 3};
  MathVector<int> b{1, 2};

  EXPECT_THROW(a * b, std::logic_error);
}

TEST(MathVectorTest, OutputStream) {
  MathVector<int> vec{1, 2, 3};
  std::stringstream ss;
  ss << vec;
  EXPECT_EQ(ss.str(), "[1 2 3]");
}

TEST(MatrixTest, ConstructorWithDimensions) {
  Matrix<int> mat(2, 3);
  EXPECT_EQ(mat.get_rows(), 2);
  EXPECT_EQ(mat.get_cols(), 3);

  // Проверяем, что все элементы инициализированы 0
  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 3; j++) {
      EXPECT_EQ(mat[i][j], 0);
    }
  }
}

TEST(MatrixTest, InitializerListConstructor) {
  Matrix<int> mat{{1, 2, 3}, {4, 5, 6}};

  EXPECT_EQ(mat.get_rows(), 2);
  EXPECT_EQ(mat.get_cols(), 3);

  EXPECT_EQ(mat[0][0], 1);
  EXPECT_EQ(mat[0][1], 2);
  EXPECT_EQ(mat[0][2], 3);
  EXPECT_EQ(mat[1][0], 4);
  EXPECT_EQ(mat[1][1], 5);
  EXPECT_EQ(mat[1][2], 6);
}

TEST(MatrixTest, InvalidInitializerListThrows) {
  EXPECT_THROW(
      Matrix<int>({{1, 2}, {3, 4, 5}}),  // Дополнительные скобки вокруг всего
      std::invalid_argument);
}


TEST(MatrixTest, MatrixAddition) {
  Matrix<int> A{{1, 2}, {3, 4}};
  Matrix<int> B{{5, 6}, {7, 8}};
  Matrix<int> C = A + B;

  EXPECT_EQ(C[0][0], 6);   // 1+5
  EXPECT_EQ(C[0][1], 8);   // 2+6
  EXPECT_EQ(C[1][0], 10);  // 3+7
  EXPECT_EQ(C[1][1], 12);  // 4+8
}

TEST(MatrixTest, MatrixCompoundAddition) {
  Matrix<int> A{{1, 2}, {3, 4}};
  Matrix<int> B{{5, 6}, {7, 8}};
  A += B;

  EXPECT_EQ(A[0][0], 6);
  EXPECT_EQ(A[0][1], 8);
  EXPECT_EQ(A[1][0], 10);
  EXPECT_EQ(A[1][1], 12);
}

TEST(MatrixTest, MatrixSubtraction) {
  Matrix<int> A{{10, 20}, {30, 40}};
  Matrix<int> B{{1, 2}, {3, 4}};
  Matrix<int> C = A - B;

  EXPECT_EQ(C[0][0], 9);   // 10-1
  EXPECT_EQ(C[0][1], 18);  // 20-2
  EXPECT_EQ(C[1][0], 27);  // 30-3
  EXPECT_EQ(C[1][1], 36);  // 40-4
}

TEST(MatrixTest, MatrixScalarMultiplication) {
  Matrix<int> A{{1, 2}, {3, 4}};
  Matrix<int> B = A * 3;

  EXPECT_EQ(B[0][0], 3);   // 1*3
  EXPECT_EQ(B[0][1], 6);   // 2*3
  EXPECT_EQ(B[1][0], 9);   // 3*3
  EXPECT_EQ(B[1][1], 12);  // 4*3
}

TEST(MatrixTest, MatrixCompoundScalarMultiplication) {
  Matrix<int> A{{1, 2}, {3, 4}};
  A *= 2;

  EXPECT_EQ(A[0][0], 2);
  EXPECT_EQ(A[0][1], 4);
  EXPECT_EQ(A[1][0], 6);
  EXPECT_EQ(A[1][1], 8);
}

TEST(MatrixTest, MatrixMultiplication) {
  Matrix<int> A{{1, 2, 3}, {4, 5, 6}};       // 2x3
  Matrix<int> B{{7, 8}, {9, 10}, {11, 12}};  // 3x2
  Matrix<int> C = A * B;                     // Должно быть 2x2

  EXPECT_EQ(C.get_rows(), 2);
  EXPECT_EQ(C.get_cols(), 2);

  // C[0][0] = 1*7 + 2*9 + 3*11 = 58
  EXPECT_EQ(C[0][0], 58);
  // C[0][1] = 1*8 + 2*10 + 3*12 = 64
  EXPECT_EQ(C[0][1], 64);
  // C[1][0] = 4*7 + 5*9 + 6*11 = 139
  EXPECT_EQ(C[1][0], 139);
  // C[1][1] = 4*8 + 5*10 + 6*12 = 154
  EXPECT_EQ(C[1][1], 154);
}

TEST(MatrixTest, MatrixVectorMultiplication) {
  Matrix<int> A{{1, 2, 3}, {4, 5, 6}};  // 2x3
  MathVector<int> v{7, 8, 9};           // 3 элемента
  MathVector<int> result = A * v;  // Должно быть 2 элемента

  EXPECT_EQ(result.size(), 2);
  // result[0] = 1*7 + 2*8 + 3*9 = 50
  EXPECT_EQ(result[0], 50);
  // result[1] = 4*7 + 5*8 + 6*9 = 122
  EXPECT_EQ(result[1], 122);
}

TEST(MatrixTest, VectorMatrixMultiplication) {
  MathVector<int> v{1, 2, 3};             // 3 элемента
  Matrix<int> A{{4, 5}, {6, 7}, {8, 9}};  // 3x2
  MathVector<int> result = v * A;  // Должно быть 2 элемента

  EXPECT_EQ(result.size(), 2);
  // result[0] = 1*4 + 2*6 + 3*8 = 40
  EXPECT_EQ(result[0], 40);
  // result[1] = 1*5 + 2*7 + 3*9 = 46
  EXPECT_EQ(result[1], 46);
}

TEST(MatrixTest, InvalidMultiplicationThrows) {
  Matrix<int> A{{1, 2}, {3, 4}};  // 2x2
  Matrix<int> B{{1, 2, 3}};       // 1x3

  EXPECT_THROW(A * B, std::logic_error);  // 2x2 * 1x3 - несовместимо
}

TEST(MatrixTest, InvalidAdditionThrows) {
  Matrix<int> A{{1, 2}, {3, 4}};        // 2x2
  Matrix<int> B{{1, 2, 3}, {4, 5, 6}};  // 2x3

  EXPECT_THROW(A + B, std::logic_error);
}

TEST(MatrixTest, Transpose) {
  Matrix<int> A{{1, 2, 3}, {4, 5, 6}};  // 2x3
  Matrix<int> T = A.transpose();        // Должно быть 3x2

  EXPECT_EQ(T.get_rows(), 3);
  EXPECT_EQ(T.get_cols(), 2);

  EXPECT_EQ(T[0][0], 1);
  EXPECT_EQ(T[0][1], 4);
  EXPECT_EQ(T[1][0], 2);
  EXPECT_EQ(T[1][1], 5);
  EXPECT_EQ(T[2][0], 3);
  EXPECT_EQ(T[2][1], 6);
}

TEST(MatrixTest, EqualityOperator) {
  Matrix<int> A{{1, 2}, {3, 4}};
  Matrix<int> B{{1, 2}, {3, 4}};
  Matrix<int> C{{1, 2}, {3, 5}};

  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A == C);
}

TEST(MatrixTest, InequalityOperator) {
  Matrix<int> A{{1, 2}, {3, 4}};
  Matrix<int> B{{1, 2}, {3, 5}};

  EXPECT_TRUE(A != B);
}

TEST(MatrixTest, OutputStream) {
  Matrix<int> mat{{1, 2}, {3, 4}};
  std::stringstream ss;
  ss << mat;
  EXPECT_EQ(ss.str(), "[ 1 2 ]\n[ 3 4 ]");
}

TEST(TriangleMatrixTest, Constructor) {
    TriangleMatrix<int> mat(4);
    EXPECT_EQ(mat.get_dimension(), 4);
}

TEST(TriangleMatrixTest, AccessValidElements) {
    TriangleMatrix<int> mat(3);
    
    // Заполняем верхний треугольник
    mat.at(0, 0) = 1;
    mat.at(0, 1) = 2;
    mat.at(0, 2) = 3;
    mat.at(1, 1) = 4;
    mat.at(1, 2) = 5;
    mat.at(2, 2) = 6;
    
    EXPECT_EQ(mat.at(0, 0), 1);
    EXPECT_EQ(mat.at(0, 1), 2);
    EXPECT_EQ(mat.at(0, 2), 3);
    EXPECT_EQ(mat.at(1, 1), 4);
    EXPECT_EQ(mat.at(1, 2), 5);
    EXPECT_EQ(mat.at(2, 2), 6);
}

TEST(TriangleMatrixTest, AccessBelowDiagonalThrows) {
    TriangleMatrix<int> mat(3);
    
    EXPECT_THROW(mat.at(1, 0), std::logic_error);
    EXPECT_THROW(mat.at(2, 0), std::logic_error);
    EXPECT_THROW(mat.at(2, 1), std::logic_error);
}

TEST(TriangleMatrixTest, ConstructorWithData) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TriangleMatrix<int> mat(4, data, 10);
    
    // Проверяем, что правильно разложилось
    // Для 4x4: 10 элементов (1+2+3+4)
    EXPECT_EQ(mat.at(0, 0), 1);
    EXPECT_EQ(mat.at(0, 1), 2);
    EXPECT_EQ(mat.at(0, 2), 3);
    EXPECT_EQ(mat.at(0, 3), 4);
    EXPECT_EQ(mat.at(1, 1), 5);
    EXPECT_EQ(mat.at(1, 2), 6);
    EXPECT_EQ(mat.at(1, 3), 7);
    EXPECT_EQ(mat.at(2, 2), 8);
    EXPECT_EQ(mat.at(2, 3), 9);
    EXPECT_EQ(mat.at(3, 3), 10);
}

TEST(TriangleMatrixTest, Addition) {
    TriangleMatrix<int> A(3);
    TriangleMatrix<int> B(3);
    
    // A = [[1,2,3],[0,4,5],[0,0,6]]
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3;
    A.at(1, 1) = 4; A.at(1, 2) = 5;
    A.at(2, 2) = 6;
    
    // B = [[2,3,4],[0,1,2],[0,0,3]]
    B.at(0, 0) = 2; B.at(0, 1) = 3; B.at(0, 2) = 4;
    B.at(1, 1) = 1; B.at(1, 2) = 2;
    B.at(2, 2) = 3;
    
    TriangleMatrix<int> C = A + B;
    
    EXPECT_EQ(C.at(0, 0), 3);  // 1+2
    EXPECT_EQ(C.at(0, 1), 5);  // 2+3
    EXPECT_EQ(C.at(0, 2), 7);  // 3+4
    EXPECT_EQ(C.at(1, 1), 5);  // 4+1
    EXPECT_EQ(C.at(1, 2), 7);  // 5+2
    EXPECT_EQ(C.at(2, 2), 9);  // 6+3
}

TEST(TriangleMatrixTest, CompoundAddition) {
    TriangleMatrix<int> A(2);
    TriangleMatrix<int> B(2);
    
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 1) = 3;
    
    B.at(0, 0) = 4; B.at(0, 1) = 5;
    B.at(1, 1) = 6;
    
    A += B;
    
    EXPECT_EQ(A.at(0, 0), 5);  // 1+4
    EXPECT_EQ(A.at(0, 1), 7);  // 2+5
    EXPECT_EQ(A.at(1, 1), 9);  // 3+6
}

TEST(TriangleMatrixTest, Subtraction) {
    TriangleMatrix<int> A(2);
    TriangleMatrix<int> B(2);
    
    A.at(0, 0) = 10; A.at(0, 1) = 20;
    A.at(1, 1) = 30;
    
    B.at(0, 0) = 1; B.at(0, 1) = 2;
    B.at(1, 1) = 3;
    
    TriangleMatrix<int> C = A - B;
    
    EXPECT_EQ(C.at(0, 0), 9);   // 10-1
    EXPECT_EQ(C.at(0, 1), 18);  // 20-2
    EXPECT_EQ(C.at(1, 1), 27);  // 30-3
}

TEST(TriangleMatrixTest, ScalarMultiplication) {
    TriangleMatrix<int> A(2);
    
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 1) = 3;
    
    TriangleMatrix<int> B = A * 3;
    
    EXPECT_EQ(B.at(0, 0), 3);  // 1*3
    EXPECT_EQ(B.at(0, 1), 6);  // 2*3
    EXPECT_EQ(B.at(1, 1), 9);  // 3*3
}

TEST(TriangleMatrixTest, MatrixMultiplication) {
    TriangleMatrix<int> A(3);
    TriangleMatrix<int> B(3);
    
    // A = [[1,2,3],[0,4,5],[0,0,6]]
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3;
    A.at(1, 1) = 4; A.at(1, 2) = 5;
    A.at(2, 2) = 6;
    
    // B = [[2,3,4],[0,1,2],[0,0,3]]
    B.at(0, 0) = 2; B.at(0, 1) = 3; B.at(0, 2) = 4;
    B.at(1, 1) = 1; B.at(1, 2) = 2;
    B.at(2, 2) = 3;
    
    TriangleMatrix<int> C = A * B;
    
    // Проверяем только верхний треугольник
    // C[0][0] = 1*2 = 2
    EXPECT_EQ(C.at(0, 0), 2);
    // C[0][1] = 1*3 + 2*1 = 3 + 2 = 5
    EXPECT_EQ(C.at(0, 1), 5);
    // C[0][2] = 1*4 + 2*2 + 3*3 = 4 + 4 + 9 = 17
    EXPECT_EQ(C.at(0, 2), 17);
    // C[1][1] = 4*1 = 4
    EXPECT_EQ(C.at(1, 1), 4);
    // C[1][2] = 4*2 + 5*3 = 8 + 15 = 23
    EXPECT_EQ(C.at(1, 2), 23);
    // C[2][2] = 6*3 = 18
    EXPECT_EQ(C.at(2, 2), 18);
}

TEST(TriangleMatrixTest, AdditionDimensionMismatchThrows) {
    TriangleMatrix<int> A(3);
    TriangleMatrix<int> B(4);
    
    EXPECT_THROW(A + B, std::logic_error);
    EXPECT_THROW(A += B, std::logic_error);
}

TEST(TriangleMatrixTest, MultiplicationDimensionMismatchThrows) {
    TriangleMatrix<int> A(3);
    TriangleMatrix<int> B(2);
    
    EXPECT_THROW(A * B, std::logic_error);
}

TEST(TriangleMatrixTest, EqualityOperator) {
    TriangleMatrix<int> A(2);
    TriangleMatrix<int> B(2);
    TriangleMatrix<int> C(2);
    
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 1) = 3;
    
    B.at(0, 0) = 1; B.at(0, 1) = 2;
    B.at(1, 1) = 3;
    
    C.at(0, 0) = 1; C.at(0, 1) = 2;
    C.at(1, 1) = 4;  // Отличие здесь
    
    EXPECT_TRUE(A == B);
    EXPECT_FALSE(A == C);
}

TEST(TriangleMatrixTest, AssignmentOperator) {
    TriangleMatrix<int> A(2);
    TriangleMatrix<int> B(3);
    
    A.at(0, 0) = 1; A.at(0, 1) = 2;
    A.at(1, 1) = 3;
    
    B = A;
    
    EXPECT_EQ(B.get_dimension(), 2);
    EXPECT_EQ(B.at(0, 0), 1);
    EXPECT_EQ(B.at(0, 1), 2);
    EXPECT_EQ(B.at(1, 1), 3);
}

TEST(TriangleMatrixTest, OutputStreamShowsFullMatrix) {
    TriangleMatrix<int> mat(2);
    mat.at(0, 0) = 1;
    mat.at(0, 1) = 2;
    mat.at(1, 1) = 3;
    
    std::stringstream ss;
    ss << mat;
    // Должно показать полную матрицу с нулями
    EXPECT_EQ(ss.str(), "1 2\n0 3");
}