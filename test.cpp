#include "test.h"

TEST(Constructor, Without_param) {
  S21Matrix A;
  EXPECT_EQ(A.get_cols(), 1);
  EXPECT_EQ(A.get_rows(), 1);
  EXPECT_EQ(A(0, 0), 0.0);
}
TEST(Constructor, Throw_1) { EXPECT_ANY_THROW(S21Matrix(-1, 23)); }

TEST(Constructor, Throw_2) { EXPECT_ANY_THROW(S21Matrix(4, -1)); }

TEST(Constructor, Throw_3) { EXPECT_ANY_THROW(S21Matrix(-1, -1)); }

TEST(Constructor, Throw_4) { EXPECT_ANY_THROW(S21Matrix(0, 4)); }

TEST(Constructor, Param) {
  S21Matrix A(3, 3);
  EXPECT_EQ(A.get_cols(), 3);
  EXPECT_EQ(A.get_rows(), 3);
  EXPECT_EQ(is_mat_fill_numb(A, 0.0), 1);
}
TEST(Constructor, Copy) {
  S21Matrix B(3, 3);
  S21Matrix A(B);
  EXPECT_EQ(A.get_cols(), 3);
  EXPECT_EQ(A.get_rows(), 3);
  EXPECT_EQ(is_mat_fill_numb(A, 0.0), 1);
}
TEST(Constructor, Move) {
  S21Matrix B(3, 3);
  S21Matrix A((std::move(B)));
  EXPECT_EQ(A.get_cols(), 3);
  EXPECT_EQ(A.get_rows(), 3);
  EXPECT_EQ(is_mat_fill_numb(A, 0.0), 1);
}
TEST(Operator, Copy) {
  S21Matrix B(2, 2);
  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;
  S21Matrix A(3, 3);
  A = B;
  EXPECT_EQ(A.get_cols(), 2);
  EXPECT_EQ(A.get_rows(), 2);
  EXPECT_EQ(is_mat_fill_numb(A, 1.0), 1);
}
TEST(Operator, Move) {
  S21Matrix B(2, 2);
  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;
  S21Matrix A(3, 3);
  A = std::move(B);
  EXPECT_EQ(A.get_cols(), 2);
  EXPECT_EQ(A.get_rows(), 2);
  EXPECT_EQ(is_mat_fill_numb(A, 1.0), 1);
}
TEST(Function, EqMatrix_1) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  B(1, 0) = 1.0;
  EXPECT_FALSE(A.EqMatrix(B));
}
TEST(Function, EqMatrix_2) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_FALSE(A.EqMatrix(B));
}
TEST(Function, EqMatrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  fill_mat_numb(A, 3.0);
  fill_mat_numb(B, 3.0);
  EXPECT_TRUE(A.EqMatrix(B));
}
TEST(Function, EqMatrix_4) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  EXPECT_TRUE(A.EqMatrix(B));
}
TEST(Function, SumMatrix_1) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_ANY_THROW(A.SumMatrix(B));
}
TEST(Function, SumMatrix_2) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 3.0);
  fill_mat_numb(C, 4.0);
  A.SumMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, SumMatrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, -1.0);
  fill_mat_numb(B, 1.0);
  A.SumMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, SumMatrix_4) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix C(2, 2);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;
  fill_mat_numb(C, 5.0);
  A.SumMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, SubMatrix_1) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_ANY_THROW(A.SubMatrix(B));
}
TEST(Function, SubMatrix_2) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, SubMatrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 1.0);
  A.SubMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, SubMatrix_4) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix C(2, 2);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;
  C(0, 0) = 3.0;
  C(0, 1) = 1.0;
  C(1, 0) = -1.0;
  C(1, 1) = -3.0;
  A.SubMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulNumber_1) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A.MulNumber(4.0);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulNumber_2) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 5.0);
  A.MulNumber(0.0);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulNumber_3) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 5.0);
  fill_mat_numb(C, 20.0);
  A.MulNumber(4.0);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulNumber_4) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  C(0, 0) = 8.0;
  C(0, 1) = 6.0;
  C(1, 0) = 4.0;
  C(1, 1) = 2.0;
  A.MulNumber(2.0);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulMatrix_1) {
  S21Matrix A(4, 3);
  S21Matrix B(4, 4);
  EXPECT_ANY_THROW(A.MulMatrix(B));
}
TEST(Function, MulMatrix_2) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix C(4, 4);
  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulMatrix_3) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 4.0;
  A(1, 0) = 2.0, A(1, 1) = 5.0;
  A(2, 0) = 3.0, A(2, 1) = 6.0;

  B(0, 0) = 1.0, B(0, 1) = -1.0, B(0, 2) = 1.0;
  B(1, 0) = 2.0, B(1, 1) = 3.0, B(1, 2) = 4.0;

  C(0, 0) = 9.0, C(0, 1) = 11.0, C(0, 2) = 17.0;
  C(1, 0) = 12.0, C(1, 1) = 13.0, C(1, 2) = 22.0;
  C(2, 0) = 15.0, C(2, 1) = 15.0, C(2, 2) = 27.0;
  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, MulMatrix_4) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 0.0, A(0, 1) = 1.0;
  A(1, 0) = 3.0, A(1, 1) = 4.0;
  A(2, 0) = 6.0, A(2, 1) = 7.0;

  B(0, 0) = 9.0, B(0, 1) = 8.0, B(0, 2) = 7.0;
  B(1, 0) = 6.0, B(1, 1) = 5.0, B(1, 2) = 4.0;

  C(0, 0) = 6.0, C(0, 1) = 5.0, C(0, 2) = 4.0;
  C(1, 0) = 51.0, C(1, 1) = 44.0, C(1, 2) = 37.0;
  C(2, 0) = 96.0, C(2, 1) = 83.0, C(2, 2) = 70.0;
  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Function, Transpose_1) {
  S21Matrix A(3, 2);
  S21Matrix C(2, 3);
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, Transpose_2) {
  S21Matrix A(3, 2);
  S21Matrix C(2, 3);
  fill_mat_numb(A, 5.0);
  fill_mat_numb(C, 5.0);
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, Transpose_3) {
  S21Matrix A(3, 2);
  S21Matrix C(2, 3);
  A(0, 0) = 1.0, A(0, 1) = 4.0;
  A(1, 0) = 2.0, A(1, 1) = 5.0;
  A(2, 0) = 3.0, A(2, 1) = 6.0;

  C(0, 0) = 1.0, C(0, 1) = 2.0, C(0, 2) = 3.0;
  C(1, 0) = 4.0, C(1, 1) = 5.0, C(1, 2) = 6.0;
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, CalcComplements_1) {
  S21Matrix A(3, 2);
  EXPECT_ANY_THROW(A.CalcComplements());
}
TEST(Function, CalcComplements_2) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, CalcComplements_3) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 2.0, A(0, 2) = 3.0;
  A(1, 0) = 0.0, A(1, 1) = 4.0, A(1, 2) = 2.0;
  A(2, 0) = 5.0, A(2, 1) = 2.0, A(2, 2) = 1.0;

  C(0, 0) = 0.0, C(0, 1) = 10.0, C(0, 2) = -20.0;
  C(1, 0) = 4.0, C(1, 1) = -14.0, C(1, 2) = 8.0;
  C(2, 0) = -8.0, C(2, 1) = -2.0, C(2, 2) = 4.0;
  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, CalcComplements_4) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 5.0, A(0, 1) = -1.0, A(0, 2) = 1.0;
  A(1, 0) = 2.0, A(1, 1) = 3.0, A(1, 2) = 4.0;
  A(2, 0) = 1.0, A(2, 1) = 0.0, A(2, 2) = 3.0;

  C(0, 0) = 9.0, C(0, 1) = -2.0, C(0, 2) = -3.0;
  C(1, 0) = 3.0, C(1, 1) = 14.0, C(1, 2) = -1.0;
  C(2, 0) = -7.0, C(2, 1) = -18.0, C(2, 2) = 17.0;
  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, CalcComplements_5) {
  S21Matrix A(1, 1);
  S21Matrix C(1, 1);
  C(0, 0) = 1;
  A(0, 0) = 198;
  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, Determinant_1) {
  S21Matrix A(3, 2);
  EXPECT_ANY_THROW(A.Determinant());
}
TEST(Function, Determinant_2) {
  S21Matrix A(1, 1);
  double c = 198.0;
  A(0, 0) = 198.0;
  double b = A.Determinant();
  EXPECT_TRUE(equel_double(b, c));
}
TEST(Function, Determinant_3) {
  S21Matrix A(2, 2);
  A(0, 0) = 5.0, A(0, 1) = -1.0;
  A(1, 0) = 2.0, A(1, 1) = 3.0;
  double c = 17.0;
  double b = A.Determinant();
  EXPECT_TRUE(equel_double(b, c));
}
TEST(Function, Determinant_4) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 2.0, A(0, 2) = 3.0;
  A(1, 0) = 4.0, A(1, 1) = 5.0, A(1, 2) = 6.0;
  A(2, 0) = 7.0, A(2, 1) = 8.0, A(2, 2) = 9.0;
  double c = 0.0;
  double b = A.Determinant();
  EXPECT_TRUE(equel_double(b, c));
}
TEST(Function, Determinant_5) {
  S21Matrix A(4, 4);
  A(0, 0) = 3.0, A(0, 1) = -3.0, A(0, 2) = -5.0, A(0, 3) = 8.0;
  A(1, 0) = -3.0, A(1, 1) = 2.0, A(1, 2) = 4.0, A(1, 3) = -6.0;
  A(2, 0) = 2.0, A(2, 1) = -5.0, A(2, 2) = -7.0, A(2, 3) = 5.0;
  A(3, 0) = -4.0, A(3, 1) = 3.0, A(3, 2) = 5.0, A(3, 3) = -6.0;
  double c = 18.0;
  double b = A.Determinant();
  EXPECT_TRUE(equel_double(b, c));
}
TEST(Function, InverseMatrix_1) {
  S21Matrix A(3, 2);
  EXPECT_ANY_THROW(A.InverseMatrix());
}
TEST(Function, InverseMatrix_2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 2.0, A(0, 2) = 3.0;
  A(1, 0) = 4.0, A(1, 1) = 5.0, A(1, 2) = 6.0;
  A(2, 0) = 7.0, A(2, 1) = 8.0, A(2, 2) = 9.0;
  EXPECT_ANY_THROW(A.InverseMatrix());
}
TEST(Function, InverseMatrix_3) {
  S21Matrix A(1, 1);
  S21Matrix C(1, 1);
  A(0, 0) = 21.0;
  C(0, 0) = 1.0 / 21.0;
  S21Matrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Function, InverseMatrix_4) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 2.0, A(0, 1) = 5.0, A(0, 2) = 7.0;
  A(1, 0) = 6.0, A(1, 1) = 3.0, A(1, 2) = 4.0;
  A(2, 0) = 5.0, A(2, 1) = -2.0, A(2, 2) = -3.0;

  C(0, 0) = 1.0, C(0, 1) = -1.0, C(0, 2) = 1.0;
  C(1, 0) = -38.0, C(1, 1) = 41.0, C(1, 2) = -34.0;
  C(2, 0) = 27.0, C(2, 1) = -29.0, C(2, 2) = 24.0;
  S21Matrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(C));
}
TEST(Operator, Plus_1) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 3.0);
  fill_mat_numb(C, 4.0);
  S21Matrix D = A + B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, Plus_2) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, -1.0);
  fill_mat_numb(B, 1.0);
  S21Matrix D = A + B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, Plus_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 3.0);
  fill_mat_numb(C, 4.0);
  A += B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, Plus_4) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, -1.0);
  fill_mat_numb(B, 1.0);
  A += B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, Minus_1) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  S21Matrix D = A - B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, Minus_2) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 1.0);
  S21Matrix D = A - B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, Minus_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  A -= B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, Minus_4) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  fill_mat_numb(A, 1.0);
  fill_mat_numb(B, 1.0);
  A -= B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, MulMatrix_1) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix C(4, 4);
  S21Matrix D = A * B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulMatrix_2) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 4.0;
  A(1, 0) = 2.0, A(1, 1) = 5.0;
  A(2, 0) = 3.0, A(2, 1) = 6.0;

  B(0, 0) = 1.0, B(0, 1) = -1.0, B(0, 2) = 1.0;
  B(1, 0) = 2.0, B(1, 1) = 3.0, B(1, 2) = 4.0;

  C(0, 0) = 9.0, C(0, 1) = 11.0, C(0, 2) = 17.0;
  C(1, 0) = 12.0, C(1, 1) = 13.0, C(1, 2) = 22.0;
  C(2, 0) = 15.0, C(2, 1) = 15.0, C(2, 2) = 27.0;
  S21Matrix D = A * B;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulMatrix_3) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  S21Matrix C(4, 4);
  A *= B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, MulMatrix_4) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1.0, A(0, 1) = 4.0;
  A(1, 0) = 2.0, A(1, 1) = 5.0;
  A(2, 0) = 3.0, A(2, 1) = 6.0;

  B(0, 0) = 1.0, B(0, 1) = -1.0, B(0, 2) = 1.0;
  B(1, 0) = 2.0, B(1, 1) = 3.0, B(1, 2) = 4.0;

  C(0, 0) = 9.0, C(0, 1) = 11.0, C(0, 2) = 17.0;
  C(1, 0) = 12.0, C(1, 1) = 13.0, C(1, 2) = 22.0;
  C(2, 0) = 15.0, C(2, 1) = 15.0, C(2, 2) = 27.0;
  A *= B;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, MulNumber_1) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  double b = 5.0;
  S21Matrix D = A * b;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulNumber_2) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  C(0, 0) = 8.0;
  C(0, 1) = 6.0;
  C(1, 0) = 4.0;
  C(1, 1) = 2.0;
  double b = 2.0;
  S21Matrix D = A * b;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulNumber_3) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  double b = 5.0;
  S21Matrix D = b * A;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulNumber_4) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  C(0, 0) = 8.0;
  C(0, 1) = 6.0;
  C(1, 0) = 4.0;
  C(1, 1) = 2.0;
  double b = 2.0;
  S21Matrix D = b * A;
  EXPECT_TRUE(D.EqMatrix(C));
}
TEST(Operator, MulNumber_5) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  double b = 5.0;
  A *= b;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, MulNumber_6) {
  S21Matrix A(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;
  A(1, 0) = 2.0;
  A(1, 1) = 1.0;
  C(0, 0) = 8.0;
  C(0, 1) = 6.0;
  C(1, 0) = 4.0;
  C(1, 1) = 2.0;
  double b = 2.0;
  A *= b;
  EXPECT_TRUE(A.EqMatrix(C));
}
TEST(Operator, EqMatrix_1) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  B(1, 0) = 1.0;
  EXPECT_FALSE(A == B);
}
TEST(Operator, EqMatrix_2) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_FALSE(A == B);
}
TEST(Operator, EqMatrix_3) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  fill_mat_numb(A, 3.0);
  fill_mat_numb(B, 3.0);
  EXPECT_TRUE(A == B);
}
TEST(Operator, Skobok_1) {
  S21Matrix A(3, 3);
  fill_mat_numb(A, 3.0);
  double temp = A(0, 0);
  EXPECT_TRUE(equel_double(temp, 3.0));
}
TEST(Operator, Skobok_2) {
  S21Matrix A(3, 3);
  A(1, 1) = 1.0;
  double temp = A(1, 1);
  EXPECT_TRUE(equel_double(temp, 1.0));
}
TEST(Operator, Skobok_3) {
  S21Matrix A(3, 3);
  EXPECT_ANY_THROW(A(4, 4));
}
TEST(Function, Accessor_1) {
  S21Matrix A(6, 3);
  EXPECT_EQ(A.get_rows(), 6);
}
TEST(Function, Accessor_2) {
  S21Matrix A(6, 3);
  EXPECT_EQ(A.get_cols(), 3);
}
TEST(Operator, Mutator_1) {
  S21Matrix A(3, 3);
  EXPECT_ANY_THROW(A.set_rows(-2));
}
TEST(Operator, Mutator_2) {
  S21Matrix A(3, 3);
  EXPECT_ANY_THROW(A.set_cols(-2));
}
TEST(Operator, Mutator_3) {
  S21Matrix A(3, 3);
  A.set_cols(5);
  EXPECT_EQ(A.get_cols(), 5);
}
TEST(Operator, Mutator_4) {
  S21Matrix A(3, 3);
  A.set_rows(5);
  EXPECT_EQ(A.get_rows(), 5);
}
TEST(Operator, Mutator_5) {
  S21Matrix A(3, 3);
  A.set_cols(2);
  EXPECT_EQ(A.get_cols(), 2);
}
TEST(Operator, Mutator_6) {
  S21Matrix A(3, 3);
  A.set_rows(2);
  EXPECT_EQ(A.get_rows(), 2);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

bool is_mat_fill_numb(const S21Matrix& mat, double num) {
  bool res = true;
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      if (!(std::fabs(mat(i, j) - num) <
            std::numeric_limits<double>::epsilon())) {
        res = false;
      }
    }
  }
  return res;
}
void fill_mat_numb(S21Matrix& mat, double num) {
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      mat(i, j) = num;
    }
  }
}
bool equel_double(double a, double b) {
  bool res = true;
  if (!(std::fabs(a - b) < std::numeric_limits<double>::epsilon())) {
    res = false;
  }
  return res;
}