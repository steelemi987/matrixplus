#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept {
  this->rows_ = 1;
  this->cols_ = 1;
  this->matrix_ = new double*[1];
  this->matrix_[0] = new double[1];
  this->matrix_[0][0] = 0;
}
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::length_error("Matrix side must be greater than 0");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  this->matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    this->matrix_[i] = new double[cols];
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      this->matrix_[i][j] = 0;
    }
  }
}
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}
S21Matrix& S21Matrix::operator=(S21Matrix const& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
  }
  return *this;
}
S21Matrix::~S21Matrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) {
    res = false;
  } else {
    res = s21_eq_matrix_fun(other);
  }
  return res;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) {
    throw std::logic_error("Incorrect matrix size for Sum");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        (*this)(i, j) += other(i, j);
      }
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) {
    throw std::logic_error("Incorrect matrix size for Sub");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        (*this)(i, j) -= other(i, j);
      }
    }
  }
}
void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.get_rows()) {
    throw std::logic_error("Incorrect matrix size for Mul");
  }
  S21Matrix res(rows_, other.get_cols());
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      for (int k = 0; k < cols_; k++) {
        res(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = res;
}
S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      res(i, j) = (*this)(j, i);
    }
  }
  return res;
}
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Calc");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < res.get_rows() && (res.get_rows() > 1); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      res(i, j) = s21_minor(i, j);
      if ((i + j) % 2) {
        res(i, j) = -res(i, j);
      }
    }
  }
  if (res.get_rows() == 1) {
    res(0, 0) = 1.0;
  }
  return res;
}
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Determinant");
  }
  double res = 0;
  if (rows_ > 2) {
    for (int j = 0; j < cols_; j++) {
      if ((j % 2)) {
        res += (*this)(0, j) * s21_minor(0, j) * (-1.0);
      } else {
        res += (*this)(0, j) * s21_minor(0, j);
      }
    }
  } else if (rows_ == 1) {
    res = (*this)(0, 0);
  } else if (rows_ == 2) {
    res = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }
  return res;
}
S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Inverse");
  }
  double determinant = Determinant();
  if (std::fabs(determinant) < std::numeric_limits<double>::epsilon()) {
    throw std::logic_error("Determinant is 0");
  }
  return Transpose().CalcComplements() * (1.0 / determinant);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator*(double num) const noexcept {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}
S21Matrix operator*(double num, const S21Matrix& other) noexcept {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}
S21Matrix& S21Matrix::operator+=(S21Matrix const& other) {
  SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(S21Matrix const& other) {
  SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(S21Matrix const& other) {
  MulMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}
double& S21Matrix::operator()(int i, int j) & {
  return const_cast<double&>(get_num(i, j));
}
const double& S21Matrix::operator()(int i, int j) const& {
  return get_num(i, j);
}

const double& S21Matrix::get_num(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[i][j];
}
int S21Matrix::get_rows() const { return rows_; }
int S21Matrix::get_cols() const { return cols_; }
void S21Matrix::set_rows(int new_rows) {
  if (new_rows <= 0) {
    throw std::length_error("Matrix side must be greater than 0");
  }
  if (new_rows != rows_) {
    S21Matrix temp(new_rows, cols_);
    int rows = new_rows < rows_ ? new_rows : rows_;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        temp(i, j) = (*this)(i, j);
      }
    }
    *this = temp;
  }
}
void S21Matrix::set_cols(int new_cols) {
  if (new_cols <= 0) {
    throw std::length_error("Matrix side must be greater than 0");
  }
  if (new_cols != cols_) {
    S21Matrix temp(rows_, new_cols);
    int cols = new_cols < cols_ ? new_cols : cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        temp(i, j) = (*this)(i, j);
      }
    }
    *this = temp;
  }
}
bool S21Matrix::s21_eq_matrix_fun(const S21Matrix& other) const {
  bool res = true;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (!(std::fabs((*this)(i, j) - other(i, j)) <
            std::numeric_limits<double>::epsilon())) {
        res = false;
      }
    }
  }
  return res;
}
double S21Matrix::s21_minor(int row_del, int column_del) const {
  S21Matrix M(rows_ - 1, cols_ - 1);
  int k_row = 0;
  int k_col = 0;
  for (int i = 0; i < M.get_rows(); i++) {
    if (row_del == i) {
      k_row = 1;
    }
    for (int j = 0; j < M.get_cols(); j++) {
      if (column_del == j) {
        k_col = 1;
      }
      M(i, j) = (*this)(i + k_row, j + k_col);
    }
    k_col = 0;
  }
  return M.Determinant();
}