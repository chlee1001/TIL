#pragma once

#include <assert.h>
#include <iostream>

template<class T>
class VectorND {
public:
	int numDimension;
	T *values;

	/*constructor*/
	VectorND()
		: numDimension(0), values(nullptr)
	{}

	VectorND(const int num) {
		values = 0;

		initialize(num);
	}

	VectorND(const VectorND<T>& vector)
	{
		values = 0;

		initialize(vector.numDimension, false);

		for (int i = 0; i < numDimension; i++)	values[i] = vector[i];
	}

	/*destructor*/
	~VectorND() {
		if (values != 0) delete[] values;
		numDimension = 0;
	}

	/*initialize*/
	void initialize(const int num, const bool initialize = false) {
		numDimension = num;

		if (values != nullptr) { delete[] values; values = nullptr; }

		if (numDimension > 0) {
			values = new T[numDimension];
			if (initialize == true)
				for (int i = 0; i < numDimension; i++)
					values[i] = T();
		}
	}

	/*overriding operator*/
	void operator = (const VectorND<T>& from) {
		if (from.numDimension != numDimension) {
			numDimension = from.numDimension;

			if (values != nullptr) { delete[] values; values = nullptr; }

			values = new T[numDimension];
		}

		for (int i = 0; i < numDimension; i++) values[i] = from[i];
	}

	T& operator[](const int i) const {
		assert(i >= 0);
		assert(i < numDimension);

		return values[i];
	}

	T& operator()(const int i) const {
		assert(i >= 0);
		assert(i < numDimension);

		return values[i];
	}

	VectorND<T> operator + (const VectorND& vector) const {
		assert(numDimension == vector.numDimension);

		VectorND<T> result(numDimension);

		for (int i = 0; i < numDimension; i++) result[i] = values[i] + vector.values[i];

		return result;
	}

	VectorND<T> operator - (const VectorND & vector)const {
		assert(numDimension == vector.numDimension);

		VectorND<T> result(numDimension);

		for (int i = 0; i < numDimension; i++) result[i] = values[i] - vector.values[i];

		return result;
	}

	void operator += (const T& s) {
		for (int i = 0; i < numDimension; i++) values[i] += s;
	}

	void operator -= (const T& s) {
		for (int i = 0; i < numDimension; i++) values[i] -= s;
	}

	void operator *= (const T& s) {
		for (int i = 0; i < numDimension; i++) values[i] *= s;
	}

	void operator *= (const int s) {
		for (int i = 0; i < numDimension; i++) values[i] *= s;
	}

	void operator /= (const T& s) {
		for (int i = 0; i < numDimension; i++) values[i] /= s;
	}

	void operator += (const VectorND<T>& s) {
		assert(numDimension == s.numDimension);

		for (int i = 0; i < numDimension; i++) values[i] += s.values;
	}

	void operator -= (const VectorND<T>& s) {
		assert(numDimension == s.numDimension);

		for (int i = 0; i < numDimension; i++) values[i] -= s.values;
	}

	void operator *= (const VectorND<T>& s) {
		assert(numDimension == s.numDimension);

		for (int i = 0; i < numDimension; i++) values[i] *= s.values;
	}

	void operator /= (const VectorND<T>& s) {
		assert(numDimension == s.numDimension);

		for (int i = 0; i < numDimension; i++) values[i] /= s.values;
	}

	VectorND <T> operator*(const T& s) const {
		VectorND <T> V(numDimension);

		for (int i = 0; i < numDimension; i++) V.values = values[i] * s;

		return V;
	}

	/*copy vector partial*/
	void copyPartial(const VectorND<T>& source, const int startIndexThis, const int startIndexSrc, const int num) {
		assert(startIndexThis >= 0);
		assert(startIndexThis + num <= numDimension);

		assert(startIndexSrc >= 0);
		assert(startIndexSrc + num <= source.numDimension);

		for (int i = 0; i < num; i++)
			values[startIndexThis + i] = source.values[startIndexSrc + i];
	}
};

//template<class T>
///*Vector dot product*/
//void dotProduct(const VectorND<T>& v1, const VectorND<T>& v2, T& sum) {
//	assert(v1.numDimension == v2.numDimension);
//
//	sum = 0;
//
//	for (int i = 0; i < v1.numDimension; i++)
//		sum += v1.values[i] * v2.values[i];
//}

template<class T>
std::ostream& operator<<(std::ostream& output, const VectorND<T>& v) {
	for (int i = 0; i < v.numDimension; i++) output << v.values[i] << " ";
	output << std::flush;

	return output;
}