#pragma once

#include <iostream>
#include <fstream>
#include <assert.h>


template<class T>
class Arr1D {
public:
	int numElements; //element number
	T *values;

	/*constructor*/
	Arr1D()
		: numElements(0), values(nullptr)
	{}

	Arr1D(const int numElementsInput)
		: numElements(0), values(nullptr)
	{
		initialize(numElementsInput);
	}

	Arr1D(const int numElementsInput, const T& valuesInput)
		: numElements(0), values(nullptr)
	{
		initialize(numElementsInput, valuesInput);
	}

	Arr1D(const Arr1D<T>& arrInput)
		: numElements(0), values(nullptr)
	{
		initialize(arrInput);
	}

	/*destructor*/
	~Arr1D() {
		if (values != nullptr) { delete[] values; values = nullptr; }

		numElements = 0;
	}

	/*template initialize*/
	void initialize(const int numElementsInput) {
		numElements = numElementsInput;

		if (values != nullptr) { delete[] values; values = nullptr; }

		if (numElements > 0)
			values = new T[numElements];
	}

	void initialize(const int numElementsInput, const T& valuesInput) {
		numElements = numElementsInput;

		if (values != nullptr) { delete[] values; values = nullptr; }

		if (numElements > 0) {
			values = new T[numElements];

			assignAllValues(valuesInput);
		}
	}

	void initialize(const Arr1D<T>& arrInput) {
		initialize(arrInput.numElements);

		copyFrom(arrInput);
	}

	//assign all values to input 
	void assignAllValues(const T& input) {
		for (int i = 0; i < numElements; i++) values[i] = input;
	}

	//assign values to inputs
	void assignValues(const int startIndex, const int endIndex, const T& input)
	{
		for (int i = startIndex; i <= endIndex; i++) values_[i] = input;
	}

	//copy array
	void copyFrom(const Arr1D<T>& from) {
		assert(numElements == from.numElements);

		T *fromVal = from.values;

		for (int i = 0; i < numElements; i++) values[i] = fromVal[i];
	}

	void freeMemory() {
		numElements = 0;

		if (values != nullptr) { delete[] values; values = nullptr; }
	}

	T& operator [] (const int i) const
	{
		assert(i >= 0);
#ifndef NDEBUG
		if (!(i < numElements)) {
			const int doSomething = (int)3.141592;
		}
#endif // !NDEBUG
		assert(i < numElements);

		return values[i];
	}

	const int getSizeOfData() const {
		return numElements * sizeof(T);
	}
	/*
	const int getSizeOfType() const {
		return sizeof(T);
	}*/

	friend std::ostream& operator<< (std::ostream& stream, const Arr1D<T>& arr) {
		for (int i = 0; i < arr.numElements; i++)
			stream << arr[i] << " ";

		return stream;
	}

	//void read(std::ifstream& is) {
	//	int numElements;

	//	is.read((char*)&numElements, sizeof(numElements));

	//	initialize(numElements);

	//	for (int i = 0; i < numElements; i++)
	//		is.read((char*)&values[i], sizeof(T));
	//}

	//void write(std::ofstream& os) const {
	//	os.write((char*)&numElements, sizeof(numElements));

	//	for (int i = 0; i < numElements; i++) {
	//		os.write((char*)&values[i], sizeof(T));
	//	}
	//}

	/*Array operator*/
	void operator *= (const T& constant) {
		for (int i = 0; i < numElements; i++)
			values[i] *= constant;
	}

	void operator += (const T& constant) {
		for (int i = 0; i < numElements; i++)
			values[i] += constant;
	}

	void operator -= (const T& constant) {
		for (int i = 0; i < numElements; i++)
			values[i] -= constant;
	}
};