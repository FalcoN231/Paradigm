#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix {
private:
	int rows_, cols_;
	std::vector<int> data_;

	// Проверка индексов на допустимость
	void check_indices(int row, int col) const {
		if (row < 1 || row > rows_ || col < 1 || col > cols_) {
			throw std::out_of_range("Matrix indices out of range");
		}
	}

public:
	// Конструктор по умолчанию
	Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows* cols) {}

	// Конструктор копирования
	Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

	// Конструктор перемещения
	Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(move(other.data_)) {
		other.rows_ = 0;
		other.cols_ = 0;
	}

	// Перегрузка оператора () для доступа к элементам (для чтения)
	const int& operator()(int row, int col) const {
		check_indices(row, col);
		return data_[(row - 1) * cols_ + (col - 1)];
	}

	// Перегрузка оператора () для доступа к элементам (для записи)
	int& operator()(int row, int col) {
		check_indices(row, col);
		return data_[(row - 1) * cols_ + (col - 1)];
	}

	// Вывод значений элементов матрицы
	void print() {
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				std::cout << data_[i * cols_ + j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	Matrix mat(3, 3);

	// Установка значений элементов матрицы
	mat(1, 1) = 1;
	mat(1, 2) = 2;
	mat(1, 3) = 3;
	mat(2, 1) = 4;
	mat(2, 2) = 5;
	mat(2, 3) = 6;
	mat(3, 1) = 7;
	mat(3, 2) = 8;
	mat(3, 3) = 9;

	mat.print();

	return 0;
}
