#ifndef S21_MATRIX_OPP_H
#define S21_MATRIX_OPP_H
#include <cmath>
#include <limits>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  const double& get_num(int i, int j) const;
  double s21_minor(int row_del, int column_del) const;
  bool s21_eq_matrix_fun(const S21Matrix& other) const;

 public:
  S21Matrix() noexcept;
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  S21Matrix& operator=(S21Matrix const& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const noexcept;
  friend S21Matrix operator*(double num, const S21Matrix& other) noexcept;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator+=(S21Matrix const& other);
  S21Matrix& operator-=(S21Matrix const& other);
  S21Matrix& operator*=(S21Matrix const& other);
  S21Matrix& operator*=(double num);
  double& operator()(int i, int j) &;
  double& operator()(int i, int j) && = delete;
  const double& operator()(int i, int j) const&;
  const double& operator()(int i, int j) const&& = delete;

  int get_rows() const;
  int get_cols() const;
  void set_rows(int new_rows);
  void set_cols(int new_cols);
};

#endif