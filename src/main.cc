#include "../include/hash.h"

int main() {
	// Создаем хеш-таблицу
	HashTable<int, int> hashTable(10);

	// Вставляем значения
	hashTable.insert(1, 3);
	hashTable.insert(2, 8);
	hashTable.insert(3, 9);
	hashTable.insert(3, 8);
	hashTable.insert(3, 10);
	//hashTable.insert_or_assign(3, 6);


	hashTable.print();
	std::cout << "count: " << std::endl;
	std::cout << hashTable.count(3) << std::endl;
	std::cout << std::endl;
	//std::cout << hashTable.contains(8);
	std::cout << "erase: "<< std::endl;
	std::cout << hashTable.erase(1);

	std::cout << std::endl;
	hashTable.print();

	int* value = hashTable.search(2);
	if (value) {
		std::cout << "Value of '2': " << *value << std::endl;
	}
	else {
		std::cout << "Key '2' not found" << std::endl;
	}

	return 0;
}
