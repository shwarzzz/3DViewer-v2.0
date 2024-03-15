#include "s21_matrix_oop.h"
namespace s21 {
// Констркутор без парметров
S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_];
  for (size_t i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      throw;
    }
  }
}

// Деструктор
S21Matrix::~S21Matrix() {
  for (size_t i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  cols_ = 0;
  rows_ = 0;
}
// Констркутор с параметрами
S21Matrix::S21Matrix(size_t row, size_t col) : rows_(row), cols_(col) {
  if (rows_ == 0 || cols_ == 0) {
    throw std::length_error(
        "Error: The number of rows and columns must be greater than zero!");
  }
  matrix_ = new double *[rows_];
  for (size_t i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      throw;
    }
  }
}
// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (size_t i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      throw;
    }
    std::memcpy(this->matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}
// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
// Оператор перемещения
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    for (size_t i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
// Оператор копирования
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix tmp(other);
    *this = std::move(tmp);
  }
  return *this;
}

// Getters
size_t S21Matrix::GetRows() const noexcept { return rows_; }

size_t S21Matrix::GetColumns() const noexcept { return cols_; }
// Setters
void S21Matrix::SetRows(size_t row) {
  if (rows_ != row) {
    if (row == 0) {
      throw std::length_error("Error: Rows must be > 0");
    }
    double **new_matrix = new double *[row];
    for (size_t i = rows_; i < row; i++) {
      try {
        new_matrix[i] = new double[cols_]();
      } catch (...) {
        for (size_t j = rows_; j < i; j++) {
          delete[] new_matrix[j];
          delete[] new_matrix;
          throw;
        }
      }
    }
    for (size_t i = 0; i < rows_; i++) {
      if (i < row) {
        new_matrix[i] = matrix_[i];
      } else {
        delete[] matrix_[i];
      }
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    rows_ = row;
  }
}

void S21Matrix::SetColumns(size_t column) {
  S21Matrix newMatrix(rows_, column);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < column && j < cols_; j++) {
      newMatrix.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = std::move(newMatrix);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool res = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    res = false;
  } else {
    for (size_t i = 0; i < this->rows_ && res; i++) {
      for (size_t j = 0; j < this->cols_ && res; j++) {
        if (this->matrix_[i][j] - other.matrix_[i][j] > 0.0000001) {
          res = false;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error("Error: Different matrix length!");
  } else {
    for (size_t i = 0; i < this->rows_; i++) {
      for (size_t j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error("Error: Different matrix length!");
  } else {
    for (size_t i = 0; i < this->rows_; i++) {
      for (size_t j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw std::logic_error(
        "Error: The number of columns of the first matrix must be equal to "
        "the "
        "number of rows of the second matrix");
  } else {
    S21Matrix result(this->rows_, other.cols_);
    for (size_t k = 0; k < result.rows_; k++) {
      for (size_t i = 0; i < result.cols_; i++) {
        for (size_t j = 0; j < this->cols_; j++) {
          result.matrix_[k][i] += this->matrix_[k][j] * other.matrix_[j][i];
        }
      }
    }
    *this = result;
  }
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix res(cols_, rows_);
  for (size_t i = 0; i < res.rows_; i++) {
    for (size_t j = 0; j < res.cols_; j++) {
      res.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix res(cols_, rows_);
  if (rows_ != cols_) {
    throw std::logic_error(
        "Error: The number of columns must be equal to the rows number!");
  } else {
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        res(i, j) = pow(-1, i + j) * MinorDet(i, j);
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  double res = 0;
  if (rows_ != cols_) {
    throw std::logic_error(
        "Error: The number of columns must be equal to the rows number!");
  } else {
    res = FindDet();
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 0.0000001) {
    throw std::logic_error(
        "Error: The determinant of the matrix is ​​zero!");
  }
  det = 1.0 / det;
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = det;
  } else {
    result = (this->CalcComplements().Transpose()) * det;
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator*=(const double num) noexcept {
  this->MulNumber(num);
  return *this;
}

S21Matrix operator*(const double &num, const S21Matrix &other) noexcept {
  S21Matrix res = other;
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(const S21Matrix &other, const double &num) noexcept {
  S21Matrix res = num * other;
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

double &S21Matrix::operator()(size_t i, size_t j) {
  if (i >= rows_ || j >= cols_) {
    throw std::out_of_range("Error: Index out of bounds");
  } else {
    return this->matrix_[i][j];
  }
}

const double &S21Matrix::operator()(size_t i, size_t j) const {
  if (i >= rows_ || j >= cols_) {
    throw std::out_of_range("Error: Index out of bounds");
  } else {
    return this->matrix_[i][j];
  }
}

double S21Matrix::FindDet() {
  double d = 0;
  if (rows_ == 1) {
    d = matrix_[0][0];
  } else if (rows_ == 2) {
    d = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix tmp(rows_ - 1, cols_ - 1);
    for (size_t k = 0; k < rows_; k++) {
      for (size_t i = 1; i < rows_; i++) {
        int t = 0;
        for (size_t j = 0; j < rows_; j++) {
          if (j != k) {
            tmp.matrix_[i - 1][t] = matrix_[i][j];
            t++;
          }
        }
      }
      d += pow(-1, k) * matrix_[0][k] * tmp.FindDet();
    }
  }
  return d;
}

double S21Matrix::MinorDet(size_t i, size_t j) {
  double det = 0;
  if (cols_ == 1) {
    det = this->matrix_[0][0];
  } else {
    S21Matrix tmp(rows_ - 1, cols_ - 1);
    int q = 0;
    for (size_t x = 0; x < rows_; x++) {
      int t = 0;
      if (x == i) continue;
      for (size_t y = 0; y < cols_; y++) {
        if (y != j) {
          tmp.matrix_[q][t] = this->matrix_[x][y];
          t++;
        }
      }
      q++;
    }
    det = tmp.FindDet();
  }
  return det;
}
}  // namespace s21
