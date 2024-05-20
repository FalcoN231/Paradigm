#include <iostream>
#include <vector>

using namespace std;

// Функция для нахождения всех подмножеств множества
void findSubsets(vector<int>& nums, vector<int>& subset, int index, vector<vector<int>>& subsets) {
	// Добавляем текущее подмножество в общий список подмножеств
	subsets.push_back(subset);

	// Рекурсивно находим все подмножества, начиная с текущего индекса
	for (int i = index; i < nums.size(); ++i) {
		// Добавляем элемент в текущее подмножество
		subset.push_back(nums[i]);

		// Рекурсивно находим подмножества, начиная со следующего индекса
		findSubsets(nums, subset, i + 1, subsets);

		// Удаляем последний добавленный элемент для создания нового подмножества
		subset.pop_back();
	}
}

int main() {
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7 };
	vector<vector<int>> subsets;
	vector<int> subset;

	findSubsets(nums, subset, 0, subsets);

	// Выводим все подмножества
	for (const auto& subset : subsets) {
		cout << "{ ";
		for (const auto& num : subset) {
			cout << num << " ";
		}
		cout << "}" << endl;
	}

	return 0;
}