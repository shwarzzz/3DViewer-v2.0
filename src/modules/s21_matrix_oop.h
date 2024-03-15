#ifndef S21_MATRIX_OOP_H_

#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <stdexcept>
namespace s21 {
class S21Matrix {
 public:
  // Конструкторы
  S21Matrix();
  S21Matrix(size_t rows, size_t cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // Деструктор
  ~S21Matrix();

  // Аксесор и мутатор
  size_t GetRows() const noexcept;
  size_t GetColumns() const noexcept;

  void SetRows(size_t row);
  void SetColumns(size_t column);

  // Операции над матрицами
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Перегрузка операторов
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);

  bool operator==(const S21Matrix& other) const noexcept;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);

  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);

  S21Matrix& operator*=(const double num) noexcept;
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix operator*(const S21Matrix& other);

  friend S21Matrix operator*(const double& num,
                             const S21Matrix& other) noexcept;
  friend S21Matrix operator*(const S21Matrix& other,
                             const double& num) noexcept;

  double& operator()(size_t i, size_t j);
  const double& operator()(size_t i, size_t j) const;

 private:
  size_t rows_ = 0;
  size_t cols_ = 0;
  double** matrix_ = nullptr;

  double FindDet();
  double MinorDet(size_t i, size_t j);
};
}  // namespace s21
#endif
