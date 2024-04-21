#include "../include/hash.h"

int main() {
	// Создаем хеш-таблицу
	HashTable<int, int> hashTable;

	// Вставляем значения
	hashTable.insert(1, 3);
	hashTable.insert(2, 8);
	hashTable.insert(3, 9);

	// Печатаем содержимое
	hashTable.print();

	return 0;
}
