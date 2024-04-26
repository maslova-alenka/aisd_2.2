#include "../include/hash.h"

#include <random>

int main() {
	std::cout << "Check" << std::endl;
	HashTable<int, int> hashTable(5);

	hashTable.insert(1, 3);
	hashTable.insert(2, 8);
	hashTable.insert(3, 9);
	hashTable.insert(3, 8);
	hashTable.insert(3, 10);
	//hashTable.insert_or_assign(2, 9);


	hashTable.print();
	std::cout << std::endl;
	std::cout << "count 3: ";
	std::cout << hashTable.count(3) << std::endl;
	std::cout << "contains 8: ";
	std::cout << hashTable.contains(10)<< std::endl;
	std::cout << "contains 1: ";
	std::cout << hashTable.contains(1) << std::endl;
	std::cout << "erase 1: ";
	std::cout << hashTable.erase(1);

	std::cout << std::endl;
	std::cout << std::endl;
	hashTable.print();

	std::vector<int> values = hashTable.search(3);
	std::cout << "Search 3: ";
	for (int value : values) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Task 3." << std::endl;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);

	const int size = 100;
	int arr[size];
	for (int i = 0; i < size; i++) {
		arr[i] = dis(gen);
	}

	// Подсчет количества одинаковых чисел с помощью хэш-таблицы
	HashTable<int, int> table(size);
	for (int num : arr) {
		table.insert(num, table.count(num) + 1);
	}

	table.print();

	std::cout << "The number of identical numbers:" << std::endl;
	for (int i = 0; i < 100; i++) {
		size_t count = table.count(i);
		if (count > 1) {
			std::cout << "Number " << i << " meets " << count << " once" << std::endl;
		}
	}


	return 0;
}
