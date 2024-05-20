#include <iostream>
#include <cmath>

using namespace std;

// Структура для комплексного числа
struct Complex {
	double real; // Вещественная часть
	double imag; // Мнимая часть
};

// Функция для создания комплексного числа по вещественной и мнимой частям
Complex createComplex(double real, double imag) {
	Complex c;
	c.real = real;
	c.imag = imag;
	return c;
}

// Сложения комплексных чисел
Complex operator+(const Complex& c1, const Complex& c2) {
	return createComplex(c1.real + c2.real, c1.imag + c2.imag);
}

// Вычитания комплексных чисел
Complex operator-(const Complex& c1, const Complex& c2) {
	return createComplex(c1.real - c2.real, c1.imag - c2.imag);
}

// Умножения комплексных чисел
Complex operator*(const Complex& c1, const Complex& c2) {
	double real = c1.real * c2.real - c1.imag * c2.imag;
	double imag = c1.real * c2.imag + c1.imag * c2.real;
	return createComplex(real, imag);
}

// Деления комплексных чисел
Complex operator/(const Complex& c1, const Complex& c2) {
	double denominator = c2.real * c2.real + c2.imag * c2.imag;
	if (denominator == 0) {
		cerr << "Ошибка: деление на ноль!" << endl;
		return createComplex(0, 0);
	}
	double real = (c1.real * c2.real + c1.imag * c2.imag) / denominator;
	double imag = (c1.imag * c2.real - c1.real * c2.imag) / denominator;
	return createComplex(real, imag);
}

// Функция для вычисления модуля комплексного числа
double abs(const Complex& c) {
	return sqrt(c.real * c.real + c.imag * c.imag);
}

// Функция для вычисления аргумента комплексного числа
double arg(const Complex& c) {
	return atan2(c.imag, c.real);
}

// Функция для вывода комплексного числа на экран
void print(const Complex& c) {
	cout << c.real << (c.imag >= 0 ? " + " : " - ") << abs(c.imag) << "i\n";
}

int main() {
	setlocale(0, "");

	Complex result = createComplex(0, 0);
	Complex c;
	char choice;
	double real, imag;
	cout << "Добро пожаловать в программу для работы с комплексными числами!" << endl;
	do {
		cout << endl << "Меню:" << endl << "1. Сложение" << endl << "2. Вычитание" << endl << "3. Умножение" << endl << "4. Деление" << endl;
		cout << "5. Модуль" << endl << "6. Аргумент" << endl << "7. Вывод результата" << endl << "Q. Выход" << endl;
		cout << "Выберите действие: ";
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "Введите вещественную часть: ";
			cin >> real;
			cout << "Введите мнимую часть: ";
			cin >> imag;
			c = createComplex(real, imag);
			result = result + c;
			break;
		case '2':
			cout << "Введите вещественную часть: ";
			cin >> real;
			cout << "Введите мнимую часть: ";
			cin >> imag;
			c = createComplex(real, imag);
			result = result - c;
			break;
		case '3':
			cout << "Введите вещественную часть: ";
			cin >> real;
			cout << "Введите мнимую часть: ";
			cin >> imag;
			c = createComplex(real, imag);
			result = result * c;
			break;
		case '4':
			cout << "Введите вещественную часть: ";
			cin >> real;
			cout << "Введите мнимую часть: ";
			cin >> imag;
			c = createComplex(real, imag);
			result = result / c;
			break;
		case '5':
			cout << "Модуль числа: " << abs(result) << endl;
			break;
		case '6':
			cout << "Аргумент числа: " << arg(result) << endl;
			break;
		case '7':
			cout << "Результат: ";
			print(result);
			break;
		case 'Q':
		case 'q':
			cout << "Программа завершена.\n";
			break;
		default:
			cout << "Неизвестная команда.\n";
		}
	} while (choice != 'Q' && choice != 'q');
	return 0;
}