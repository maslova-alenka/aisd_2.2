#ifndef HASH_INCLUDE_HASH_H
#define HASH_INCLUDE_HASH_H

#include <iostream>
#include <vector>
#include <functional>

template<typename K, typename V>
class HashTable {
	struct Pair {
		K key;
		V value;
		bool not_empty;

		Pair(): key(0), value(0), not_empty(false){}
		Pair(const K& key, const V& value) : key(key), value(value), not_empty(true) {}
	};
	std::vector<Pair> _data;
	size_t _size;

	/*size_t hashFunction(const K& key) {
		size_t h = std::hash<K>{}(key);
		return (h * 2654435761u) % _data.size();
	}*/

	size_t hashFunction(const K& key) {
		double A = 0.6180339887;  //  онстанта A, котора€ €вл€етс€ приближенным значением ((sqrt(5) - 1) / 2)
		double fractional_part = key * A - int(key * A);  // ¬ычисл€ем дробную часть от умножени€ ключа на константу A
		return size_t(_data.size() * fractional_part);  // ”множаем дробную часть на размер таблицы и возвращаем целую часть результата
	}

public:
	HashTable() : _data(0), _size(0) {}

	HashTable(size_t capacity) {
		_data.resize(capacity);
		_size = 0;
	}
	
	HashTable(const HashTable& other) : _data(other._data), _size(other._size) {}

	HashTable& operator=(const HashTable& other) {
		{
			if (this != &other) {
				_data = other._data;
				_size = other._size;
			}
			return *this;
		}
	}

	~HashTable() {
		_data.clear();
		_size = 0;
	}

	size_t size() const {
		return _size;
	}

	size_t capacity() const {
		return _data.size();
	}

	void print() const {
		for (const Pair& pair : _data) {
			std::cout << "{" << pair.key << " : " << pair.value << "} ";
		}
		std::cout << std::endl;
	}

	void insert(K key, V value){
		size_t index = hashFunction(key);
		_data[index] = Pair(key, value);
		_size++;
	}

	void insert_or_assign(K key, V value) {
		size_t index = hashFunction(key);
		for (auto& pair : _data) {
			if (pair.key == key) {
				pair.value = value;
				return;
			}
		}
		_data[index]= Pair(key, value);
	}

	bool contains(V value) const {
		for (const auto& pair : _data) {
			if (pair.value == value) {
				return true;
			}
		}
		return false;
	}

	bool erase(K key) {
		size_t index = hashFunction(key);
		for (auto& pair : _data) {
			if (pair.key == key) {
				pair.not_empty = false;
				_size--;
				return true;
			}
		}
		return false;
	}

	size_t count(K key) const {
		size_t index = hashFunction(key);
		size_t cnt = 0;
		for (const auto& pair : _data) {
			if (pair.key == key) {
				cnt++;
			}
		}
		return cnt;
	}

	V* search(K key) {
		size_t index = hashFunction(key);
		for (auto& pair : _data) {
			if (pair.key == key) {
				return &pair.value;
			}
		}
		return nullptr;
	}

};
#endif