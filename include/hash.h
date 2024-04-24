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

	size_t hashFunction(const K& key) {
		double w = 64;
		double a = 8589934583; //взаимно простое число к 64 (2^33-1)
		double result = _data.size()*std::fmod(((a/w) * key), 1); // Вычисляем ((a / w) * k) mod 1
		return result;
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
		//_data[index]= Pair(key, value);
		insert(key, value);
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

	size_t count(K key) {
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