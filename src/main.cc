#include "../include/hash.h"

int main() {
	// ������� ���-�������
	HashTable<int, int> hashTable;

	// ��������� ��������
	hashTable.insert(1, 3);
	hashTable.insert(2, 8);
	hashTable.insert(3, 9);

	// �������� ����������
	hashTable.print();

	return 0;
}
