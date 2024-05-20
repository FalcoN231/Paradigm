#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


// Функция для проверки симметричности матрицы
bool isSymmetric(double** matrix, int n) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (matrix[i][j] != matrix[j][i])
				return false;

	return true;
}

// Функция для освобождения памяти, выделенной под матрицу
void freeMatrix(double** matrix, int n) {
	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// Функция для вычисления длины вектора
double calculateVectorLength(double* x, double** G, int n) {
	double result = 0.0;

	// Умножение вектора на матрицу G
	double* temp = new double[n];
	for (int i = 0; i < n; ++i) {
		temp[i] = 0.0;
		for (int j = 0; j < n; ++j) {
			temp[i] += G[i][j] * x[j];
		}
	}

	// Умножение полученного вектора на транспонированный вектор x
	for (int i = 0; i < n; ++i) {
		result += temp[i] * x[i];
	}

	delete[] temp;

	// Взятие корня из результата
	result = sqrt(result);

	return result;
}

int main() {
	setlocale(LC_ALL, "");

	ifstream inFile("input.txt");

	//Проверка наличия файла
	if (!inFile) {
		wcout << L"Невозможно прочесть файл" << endl;
		return 1;
	}

	int n; // Размерность пространства
	inFile >> n;

	// Иницализаия матрицы тензора
	double** G = new double* [n];
	for (int i = 0; i < n; ++i) {
		G[i] = new double[n];
		for (int j = 0; j < n; ++j) {
			inFile >> G[i][j];
		}
	}

	// Проверка симметричности матрицы тензора
	if (!isSymmetric(G, n)) {
		wcout << L"Матрица не симметрична" << endl;
		freeMatrix(G, n);
		return 1;
	}

	// Инициализация вектора x
	double* x = new double[n];
	for (int i = 0; i < n; ++i) {
		inFile >> x[i];
	}

	inFile.close();

	// Вычисление длины вектора
	double length = calculateVectorLength(x, G, n);

	// Вывод результата
	wcout << L"Длина вектора: " << length << endl;

	// Освобождение выделенной памяти
	freeMatrix(G, n);
	delete[] x;

	return 0;
}