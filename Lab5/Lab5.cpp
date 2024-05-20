#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14
#endif

using namespace std;

// Абстрактный класс 3D-фигура
class Shape3D {
public:
    // Виртуальные функции для нахождения площади поверхности и объема
    virtual double surfaceArea() const = 0;
    virtual double volume() const = 0;
    virtual ~Shape3D() = default;
};

// Сфера
class Sphere : public Shape3D {
private:
    double radius;

public:
    // Конструктор
    Sphere(double r) : radius(r) {}

    // Переопределение виртуальных функций
    double surfaceArea() const override {
        return 4 * M_PI * radius * radius;
    }

    double volume() const override {
        return (4.0 / 3.0) * M_PI * radius * radius * radius;
    }
};

// Прямой конус
class Cone : public Shape3D {
private:
    double radius;
    double height;

public:
    // Конструктор
    Cone(double r, double h) : radius(r), height(h) {}

    // Переопределение виртуальных функций
    double surfaceArea() const override {
        double slantHeight = sqrt(radius * radius + height * height);
        return M_PI * radius * (radius + slantHeight);
    }

    double volume() const override {
        return (1.0 / 3.0) * M_PI * radius * radius * height;
    }
};

// Прямая прямоугольная пирамида
class RectangularPyramid : public Shape3D {
private:
    double length;
    double width;
    double height;

public:
    // Конструктор
    RectangularPyramid(double l, double w, double h)
        : length(l), width(w), height(h) {}

    // Переопределение виртуальных функций
    double surfaceArea() const override {
        double slantHeightL = sqrt((length / 2) * (length / 2) + height * height);
        double slantHeightW = sqrt((width / 2) * (width / 2) + height * height);
        return length * width + length * slantHeightW + width * slantHeightL;
    }

    double volume() const override {
        return (1.0 / 3.0) * length * width * height;
    }
};

// Цилиндр
class Cylinder : public Shape3D {
private:
    double radius;
    double height;

public:
    Cylinder(double r, double h) : radius(r), height(h) {}

    double surfaceArea() const override {
        return 2 * M_PI * radius * (radius + height);
    }

    double volume() const override {
        return M_PI * radius * radius * height;
    }
};

// Правильный тетраэдр
class RegularTetrahedron : public Shape3D {
private:
    double side;

public:
    RegularTetrahedron(double a) : side(a) {}

    double surfaceArea() const override {
        return sqrt(3) * side * side;
    }

    double volume() const override {
        return (pow(side, 3) / (6 * sqrt(2)));
    }
};

// Прямоугольный параллелепипед
class RectangularParallelepiped : public Shape3D {
protected:
    double length;
    double width;
    double height;

public:
    RectangularParallelepiped(double l, double w, double h)
        : length(l), width(w), height(h) {}

    double surfaceArea() const override {
        return 2 * (length * width + width * height + height * length);
    }

    double volume() const override {
        return length * width * height;
    }
};

// Куб
class Cube : public RectangularParallelepiped {
public:
    Cube(double a) : RectangularParallelepiped(a, a, a) {}

    double surfaceArea() const override {
        return 6 * length * length;
    }

    double volume() const override {
        return length * length * length;
    }
};

int main() {
    setlocale(0, "");

    ifstream inputFile("shapes.txt"); // Открытие файла для чтения
    if (!inputFile) {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    int numShapes;
    inputFile >> numShapes; // Чтение количества фигур из файла

    vector<unique_ptr<Shape3D>> shapes; // Вектор указателей на 3D-фигуры

    // Чтение информации о фигурах из файла
    char shapeType;
    for (int i = 0; i < numShapes; ++i) {
        inputFile >> shapeType;
        switch (shapeType) {
        case 's': {
            double radius;
            inputFile >> radius;
            shapes.push_back(std::make_unique<Sphere>(radius));
            break;
        }
        case 'c': {
            double radius, height;
            inputFile >> radius >> height;
            shapes.push_back(std::make_unique<Cone>(radius, height));
            break;
        }
        case 'r': {
            double length, width, height;
            inputFile >> length >> width >> height;
            shapes.push_back(std::make_unique<RectangularPyramid>(length, width, height));
            break;
        }
        case 'd': {
            double radius, height;
            inputFile >> radius >> height;
            shapes.push_back(std::make_unique<Cylinder>(radius, height));
            break;
        }
        case 't': {
            double side;
            inputFile >> side;
            shapes.push_back(std::make_unique<RegularTetrahedron>(side));
            break;
        }
        case 'p': {
            double length, width, height;
            inputFile >> length >> width >> height;
            shapes.push_back(std::make_unique<RectangularParallelepiped>(length, width, height));
            break;
        }
        case 'q': {
            double side;
            inputFile >> side;
            shapes.push_back(std::make_unique<Cube>(side));
            break;
        }
        default:
            cerr << "Неизвестный код фигуры: " << shapeType << endl;
            return 1;
        }
    }

    inputFile.close(); // Закрытие файла

    ofstream output("results.txt"); // Открытие файла для записи результатов
    if (!output) {
        cerr << "Unable to open file for writing." << endl;
        return 1;
    }

    // Вывод информации о площади поверхности и объеме каждой фигуры в файл
    for (const auto& shape : shapes) {
        output << shape->surfaceArea() << " " << shape->volume() << endl;
    }

    output.close(); // Закрытие файла

    std::cout << "Results written to results.txt." << endl;

    return 0;
}