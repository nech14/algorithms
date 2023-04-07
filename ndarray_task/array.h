
#include <iostream>
#include <iomanip>
#include <time.h>
#include <type_traits>

#ifndef _ARRAY_H
#define _ARRAY_H

const int DEFAULT_CAPACITY = 10;

class ArrayException {};

template <class T> class Array {
	T* arr;
	int* sizeArray;
	int capacity, dimension;
public:

	Array();
	Array(int dim, int* sizeArr);
	Array(int dim, int* sizeArr, T* buf);
	Array(const Array<T>& n);

	~Array();

	T& operator[] (int index);
	Array& operator =(const Array& buf);

	Array& operator +=(const T n);
	Array& operator -=(const T n);
	Array& operator *=(const T n);
	Array& operator /=(const T n);

	Array& fill(T fill);
	Array& fillZero(); 
	Array& fillOne();
	Array& fillOrder();
	Array& fillRandom();

	Array& transposition();
	Array matmul(Array<T>& matr);

	int giveDimension();
	int* giveSizeArray();

	T min();
	T* min(int n);

	T max();
	T* max(int n);

	T mean();
	T* mean(int n);
};

template <class T> T Array<T>::min() {

	T minimum = arr[0];
	for (int i = 0; i < capacity; i++)
		if (minimum > arr[i])
			minimum = arr[i];

	return minimum;
}


template <class T> T* Array<T>::min(int n) {
	
	if( n >= dimension)
		throw ArrayException();

	T* minimum = new T[sizeArray[dimension - n - 1]];
	for (int m = 0; m < sizeArray[dimension - n - 1]; m++) {
		minimum[m] = arr[m * n * sizeArray[1] + n + (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)];
		for (int i = 0; i < sizeArray[0]; i++) {
			for (int j = 0; j < sizeArray[1]; j++) {

				if (minimum[m] > arr[m * n * sizeArray[1] + j*n + i * (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)])
					minimum[m] = arr[m * n * sizeArray[1] + j*n + i * (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)];

			}
		}

	}	

	return minimum;
}


template <class T> T Array<T>::max() {

	T maximum = arr[0];
	for (int i = 0; i < capacity; i++)
		if (maximum < arr[i])
			maximum = arr[i];

	return maximum;
}

template <class T> T* Array<T>::max(int n) {

	if (n >= dimension)
		throw ArrayException();

	T* maximum = new T[sizeArray[dimension - n - 1]];
	for (int m = 0; m < sizeArray[dimension - n - 1]; m++) {
		maximum[m] = arr[m * n * sizeArray[1] + n + (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)];
		for (int i = 0; i < sizeArray[0]; i++) {
			for (int j = 0; j < sizeArray[1]; j++) {

				if (maximum[m] < arr[m * n * sizeArray[1] + j * n + i * (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)])
					maximum[m] = arr[m * n * sizeArray[1] + j * n + i * (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)];

			}
		}

	}

	return maximum;
}

template <class T> T Array<T>::mean() {

	T m = 0;
	for (int i = 0; i < capacity; i++)
		m += arr[i];

	return m/capacity;
}


template <class T> T* Array<T>::mean(int n) {

	if (n >= dimension)
		throw ArrayException();

	T* medium = new T[sizeArray[dimension - n - 1]];
	for (int m = 0; m < sizeArray[dimension - n - 1]; m++) {
		medium[m] = 0;
		for (int i = 0; i < sizeArray[0]; i++) {
			for (int j = 0; j < sizeArray[1]; j++) {

				medium[m] += arr[m * n * sizeArray[1] + j * n + i * (dimension - n - 1) * sizeArray[1] + m * (dimension - n - 1)];

			}
		}

		medium[m] /= sizeArray[1] * sizeArray[0];
	}

	return medium;
}


template <class T>  int Array<T>::giveDimension() {
	return dimension;
}

template <class T> int* Array<T>::giveSizeArray() {
	return sizeArray;
}

template <class T>Array<T>::Array() {
	capacity = DEFAULT_CAPACITY;
	arr = new T[capacity];
	dimension = 1;
	sizeArray = new int[1];
	sizeArray[0] = capacity;
}

template <class T>Array<T>::Array(int dim, int* sizeArr) {
	capacity = 1;
	dimension = dim;
	
	sizeArray = new int[dimension];
	for (int i = 0; i < dimension; i++) {
		capacity *= sizeArr[i];
		sizeArray[i] = sizeArr[i];
	}
	arr = new T[capacity];
}

template <class T>Array<T>::Array(int dim, int* sizeArr, T* buf) : Array(dim, sizeArr) {
	
	for (int i = 0; i < capacity; i++) {
		arr[i] = buf[i];
	}
}

template <class T>Array<T>::Array(const Array<T>& n) : Array(n.dimension, n.sizeArray) {

	for (int i = 0; i < capacity; i++) {
		arr[i] = n.arr[i];
	}
	
}


template <class T>Array<T>::~Array() {

	delete[] arr;
	delete[] sizeArray;

}


template <class T> Array<T>& Array<T>::fill(T fill) {

	for (int i = 0; i < capacity; i++) {
		arr[i] = fill;
	}
	return *this;
}


template <class T> Array<T>& Array<T>::fillZero() {

	fill(0);

	return *this;
}


template <class T> Array<T>& Array<T>::fillOne() {

	fill(1);

	return *this;
}

template <class T> Array<T>& Array<T>::fillOrder() {

	for (int i = 0; i < capacity; i++) {
		arr[i] = i;
	}

	return *this;
}



template <class T> Array<T>& Array<T>::fillRandom() {
	srand((unsigned)time(0));
	for (int i = 0; i < capacity; i++) {
		arr[i] = rand();
	}

	return *this;
}



template <class T>
Array<T>& Array<T>::transposition() {
	int* bufSize = new int[dimension];
	for (int i = dimension - 1; i >= 0; i--) {
		bufSize[i] = sizeArray[dimension - 1 - i];
	}

	int* buf1 = new int[capacity];
	std::cout << 'k' << sizeArray[0] << " - " << sizeArray[1] << '\n';
	for (int i = 0; i < sizeArray[0]; i++) {
		for (int j = 0; j < sizeArray[1]; j++) {
			buf1[j * bufSize[1] + i] = arr[i * sizeArray[1] + j];
		}
	}
	sizeArray = bufSize;

	for (int i = 0; i < capacity; i++) {
		arr[i] = buf1[i];
	}

	return *this;
}

template <class T> Array<T> Array<T>::matmul(Array<T>& matr) {

	int* bufSize = new int[dimension];
	int a[] = { sizeArray[0], matr.sizeArray[1] };
	bufSize = a;
	
	int newCapacity = 1;
	for (int i = 0; i < dimension; i++)
		newCapacity *= bufSize[i];

	int minCapacity;
	sizeArray[1] < matr.sizeArray[0] ? minCapacity = sizeArray[1] : minCapacity = matr.sizeArray[0];
	

	T* newMatr = new T[newCapacity];
	T buf;
	for (int i = 0; i < bufSize[0]; i++) {

		for (int j = 0; j < bufSize[1]; j++) {

			buf = 0;
			for (int c = 0; c < minCapacity; c++) {
				buf += arr[i * sizeArray[1] + c] * matr.arr[c * matr.sizeArray[1] + j];
			}
			newMatr[i * bufSize[1] + j] = buf;

		}

	}

	
	Array<T> a1(dimension, bufSize, newMatr);



	return a1;
}


template <class T> T& Array<T>::operator [](int index) {

	if (index >= capacity || index < 0)
		throw ArrayException();
	else
		return arr[index];
}

template <class T> Array<T>& Array<T>::operator =(const Array& buf) {

	if (this == &buf)
		return *this;
	if (capacity != buf.capacity) {
		delete[] arr;
		arr = new T[buf.capacity];
		capacity = buf.capacity;
	}

	dimension = buf.dimension;
	delete[] sizeArray;
	sizeArray = new int[dimension];

	for (int i = 0; i < dimension; i++)
		sizeArray[i] = buf.sizeArray[i];

	for (int i = 0; i < capacity; i++)
		arr[i] = buf.arr[i];

	return *this;
}




template <class T> Array<T>& Array<T>::operator +=(const T n) {

	for (int i = 0; i < capacity; i++) {
		arr[i] += T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator -=(const T n) {

	for (int i = 0; i < capacity; i++) {
		arr[i] -= T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator *=(const T n) {

	for (int i = 0; i < capacity; i++) {
		arr[i] *= T(n);
	}
	return *this;
}

template <class T> Array<T>& Array<T>::operator /=(const T n) {

	for (int i = 0; i < capacity; i++) {
		arr[i] /= T(n);
	}
	return *this;
}



#endif
