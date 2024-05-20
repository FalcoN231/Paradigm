#include <iostream>

using namespace std;

// Определение структуры узла двунаправленного списка
struct Node {
	int data;
	Node* prev;
	Node* next;

	// Конструктор для удобного создания узлов
	Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Класс двунаправленного списка
class DoublyLinkedList {
protected:
	Node* head;
	Node* tail;
	int size;

	void clear() {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		head = tail = nullptr;
	}

public:
	// Конструктор и деструктор
	DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Конструктор копирования
	DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
		// Создаем глубокую копию списка other
		Node* current = other.head;
		while (current != nullptr) {
			append(current->data);
			current = current->next;
		}
	}

	// Конструктор перемещения
	DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
		// Перехватываем ресурсы у другого списка
		other.head = nullptr;
		other.tail = nullptr;
	}

	// Деструктор
	~DoublyLinkedList() {
		clear();
	}

	// Метод для возврата длины списка
	int getSize() const {
		return size;
	}

	// Метод для проверки на пустоту списка
	bool isEmpty() const {
		return head == nullptr;
	}

	// Метод для добавления элемента в конец списка
	void append(int value) {
		Node* newNode = new Node(value);
		if (tail == nullptr) {
			// Если список пустой
			head = tail = newNode;
		}
		else {
			// Иначе добавляем в конец
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	// Метод для добавления элемента в начало списка
	void prepend(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			// Если список пустой
			head = tail = newNode;
		}
		else {
			// Иначе добавляем в начало
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		size++;
	}

	// Метод для удаления первого элемента списка
	void removeFirst() {
		if (head == nullptr) {
			cerr << "Error" << endl;
			return;
		}
		Node* temp = head;
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		delete temp;

		size--;
	}

	// Метод для удаления первого заданного элемента списка
	void removeFirst(int value) {
		if (head == nullptr) {
			cerr << "Error" << endl;
			return;
		}

		Node* curr = head;
		while (curr != nullptr) {
			if (curr->data == value) {
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				delete curr;
				size--;
				return;
			}
			curr = curr->next;
		}
	}

	// Метод для удаления последнего элемента списка
	void removeLast() {
		if (tail == nullptr) {
			cerr << "Error" << endl;
			return;
		}
		Node* temp = tail;
		tail = tail->prev;
		if (tail != nullptr)
			tail->next = nullptr;
		delete temp;

		size--;
	}

	// Метод для удаления первого заданного элемента списка
	void removeLast(int value) {
		if (head == nullptr) {
			cerr << "Error" << endl;
			return;
		}

		Node* curr = tail;
		while (curr != nullptr) {
			if (curr->data == value) {
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				delete curr;
				size--;
				return;
			}
			curr = curr->prev;
		}
	}

	// Перегрузка оператора + для конкатенации списков
	DoublyLinkedList operator+(const DoublyLinkedList& other) const {
		DoublyLinkedList result;

		// Копируем элементы из первого списка
		Node* current = this->head;
		while (current != nullptr) {
			result.append(current->data);
			current = current->next;
		}

		// Копируем элементы из второго списка
		current = other.head;
		while (current != nullptr) {
			result.append(current->data);
			current = current->next;
		}

		return result;
	}

	// Перегрузка оператора [] для доступа к элементам по индексу
	int& operator[](int index) {
		if (index < 0) {
			throw out_of_range("Индекс должен быть неотрицательным");
		}

		Node* current = head;
		int currentIndex = 0;
		while (current != nullptr) {
			if (currentIndex == index) {
				return current->data;
			}
			current = current->next;
			currentIndex++;
		}

		throw out_of_range("Индекс выходит за пределами списка");
	}

	// Метод для проверки наличия элемента в списке
	bool contains(int value) const {
		Node* current = head;
		while (current != nullptr) {
			if (current->data == value) {
				return true; // Найдено значение в списке
			}
			current = current->next;
		}
		return false; // Значение не найдено в списке
	}

	// Метод для вывода списка на экран
	void display() const {
		Node* current = head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
};

// Пример использования
int main() {
	setlocale(0, "");

	DoublyLinkedList list1;
	list1.append(10);
	list1.append(20);
	cout << "Список 1: ";
	list1.display();

	DoublyLinkedList list2;
	list2.append(30);
	list2.append(40);
	cout << "Список 2: ";
	list2.display();

	// Используем оператор + для объединения списков
	DoublyLinkedList concatenatedList = list1 + list2;
	cout << "Результат конкатенации: ";
	concatenatedList.display();

	DoublyLinkedList list3 = move(concatenatedList);
	list3.display();

	return 0;
}
