#pragma once

#include "VectorND.h"

template<class T>
class Matrix {
public:
	int rows;
	int cols;
	T *values;

	/*constructor*/
	Matrix()
		: values(nullptr), rows(0), cols(0)
	{}
	//initialize matrix
	void initialize(const int m, const int n, const bool init = true);

	/*matrix multiply*/
	void multiply(const VectorND<T>& vector, VectorND<T>& result) const;
	void multiplyTransposed(const VectorND<T>& vector, VectorND<T>& result) const;

	/*convert 1D array into 2D array*/
	int get1DIndex(const int row, const int col)const;
	/*getter*/
	T& getValue(const int row, const int col) const;

	//override cout
	void cout();
};