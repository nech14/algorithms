
#include <iostream>
#include <iomanip>

#ifndef _ARRAY_H
#define _ARRAY_H

const int DEFAULT_CAPACITY = 10;

class ArrayException {};

template <class T> class Array{
	T* arr;
	int size, capacity;
public:
	explicit Array(int startCapacity);
	Array(int startCapacity, T fill);
	Array(int startCapacity, char fill);
	~Array();

	T& operator[] (int index);
	Array& operator +=(const T n);
	Array& operator -=(const T n);
	Array& operator *=(const T n);
	Array& operator /=(const T n);

	Array transposition(const Array* matr);
};

template <class T>Array<T>::Array(int startCapacity) {
	if (startCapacity <= 0)
		capacity = DEFAULT_CAPACITY;
	else
		capacity = startCapacity;
	arr = new T[capacity];
	size = capacity;
}

template <class T>Array<T>::~Array() {

	delete[] arr;

}


template <class T>Array<T>::Array(int startCapacity, T fill) {
	arr = new T[startCapacity];
	capacity = startCapacity;
	size = startCapacity;
	for (int i = 0; i < capacity; i++) {
		arr[i] = fill;
	}
}


template <class T>Array<T>::Array(int startCapacity, char fill) {
	
	arr = new T[startCapacity];
	capacity = startCapacity;
	size = startCapacity;

	if (fill == 'r' || fill == 'R') { // Random
		int* rMas = new int[startCapacity];	
		for (int i = 0; i < startCapacity; i++)
			rMas[i] = i+1;

		int r = 0;
		int n = startCapacity;

		for (int i = 0; i < startCapacity; i++) {
			srand(time(0));
			r = int(rand() % n);

			arr[i] = T(rMas[r]);
			rMas[r] = rMas[n - 1];
			n--;
		}

		delete rMas;
		
	}
	else if (fill == 'f' || fill == 'F') { // Full Random
		T r = 0;
		for (int i = 0; i < startCapacity; i++) {
			srand(time(NULL));
			r = rand();
			arr[i] = (r);
		}
	}
	
}


template <class T> T& Array<T>::operator [](int index) {
	
	if (index >= size || index < 0)
		throw ArrayException();
	else
		return arr[index];
}

template <class T> Array<T>& Array<T>::operator +=(const T n) {

	for (int i = 0; i < size; i++) {
		arr[i] += T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator -=(const T n) {

	for (int i = 0; i < size; i++) {
		arr[i] -= T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator *=(const T n) {

	for (int i = 0; i < size; i++) {
		arr[i] *= T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator /=(const T n) {

	for (int i = 0; i < size; i++) {
		arr[i] /= T(n);
	}
	return *this;
}



#endif