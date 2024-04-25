#ifndef HASH_INCLUDE_HASH_H
#define HASH_INCLUDE_HASH_H

#include <iostream>
#include <vector>
#include<list>
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
	std::vector<std::list<Pair>> _data;
	size_t _size;

	size_t hash_function(const K& key) {
		double w = 64;
		double a = 8589934583; //взаимно простое число к 64 (2^33-1)
		double result = _data.size()*std::fmod(((a/w) * key), 1); // Вычисляем K((a / w) * k) mod 1
		return result;
	}

	Pair* find(const K& key) {
		size_t index = hash_function(key);
		for (const auto& pair : _data[index]) {
			if (pair.key == key && pair.not_empty) {
				return &pair;
			}
		}
		return nullptr;
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
		for (size_t i = 0; i < _data.size(); ++i) {
			std::cout << i << ": ";
			for (const auto& pair : _data[i]) {
				std::cout << "{" << pair.key << " : " << pair.value << "} ";
			}
			std::cout << std::endl;
		}
	}

	V operator[](const K& key) const {
		Pair* find_pair = find(key);
		if (find_pair)
			return find_pair->value;
		throw std::out_of_range("Key not found");
	}

	V& operator[](const K& key) {
		Pair* find_pair = find(key);
		if (find_pair)
			return find_pair->value;
		throw std::out_of_range("Key not found");
	}


	void insert(K key, V value){
		size_t index = hash_function(key);
		_data[index].push_back({ key, value });
		_size++;
	}


	/*void insert_or_assign(K key, V value) {
		size_t index = hash_function(key);
		for (auto& pair : _data[index]) {
			if (pair.key == key) {
				pair.value = value;
				return;
			}
		}
		insert(key, value);
	}*/

	void insert_or_assign(K key, V value) {
		size_t index = hash_function(key);
		auto& bucket = _data[index];
		bool found = false;
		for (auto& pair : bucket) {
			if (pair.key == key) {
				pair.value = value;
				found = true;
			}
		}
		if (!found) {
			bucket.push_back({ key, value });
			_size++;
		}
	}

	bool contains(const V& value) const {
		for (const auto& list : _data) {
			for (const auto& pair : list) {
				if (pair.not_empty && pair.value == value) {
					return true;
				}
			}
		}
		return false;
	}

	bool erase(K key) {
		size_t index = hash_function(key);
		auto& bucket = _data[index];
		for (auto it = bucket.begin(); it != bucket.end(); ++it) {
			if (it->key == key) {
				bucket.erase(it);
				_size--;
				return true;
			}
		}
		return false;
	}

	size_t count(K key) {
		size_t index = hash_function(key);
		size_t cnt = 0;
		for (const auto& pair : _data[index]) {
			if (pair.key == key) {
				cnt++;
			}
		}
		return cnt;
	}

	V* search(const K& key) {
		size_t index = hash_function(key);
		for (auto& pair : _data[index]) {
			if (pair.key==key) {
				return &pair.value;
			}
		}
		return nullptr;
	}

};
#endif