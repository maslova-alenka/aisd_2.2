#include "../include/hash.h"

int main() {
	// Создаем хеш-таблицу
	HashTable<int, int> hashTable(10);

	// Вставляем значения
	hashTable.insert(1, 3);
	hashTable.insert(2, 8);
	hashTable.insert(3, 9);
	hashTable.insert_or_assign(3, 8);
	//hashTable.insert(3, 6);

	hashTable.print();
	std::cout << hashTable.count(3) << std::endl;
	std::cout << std::endl;
	std::cout << hashTable.contains(8);
	std::cout << std::endl;
	std::cout<<hashTable.erase(1);
	std::cout << std::endl;
	hashTable.print();

	return 0;
}
