#include <iostream>
#include "Matrix.h"
#pragma once
using namespace std;

template <class t>
class BinaryImage : public Matrix<t>
{
public:
	BinaryImage(){};
	BinaryImage(int sizeR, int sizeC, t* input_data) : Matrix(sizeR, sizeC, input_data) {};
	BinaryImage(int sizeR, int sizeC, t* input_data, t threshold);
	BinaryImage(const BinaryImage& b) : Matrix(b) {};
	~BinaryImage();

	BinaryImage getBlock(int startRow, int endRow, int startColumn, int endColumn) const;
	bool operator+ (const BinaryImage& b);
	bool operator- (const BinaryImage& b);
	bool operator* (const BinaryImage& b);
	bool operator/ (const BinaryImage& b);
};

// Constructor with rows, columns, array to be inputted and threshold for binary conversion that inherits from the matrix constructor.
template <class t> BinaryImage<t>::BinaryImage(int sizeR, int sizeC, t* input_data, t threshold) : Matrix(sizeR, sizeC, input_data)
{
	for (int i = 0; i < M*N; i++)
		if (data[i] > threshold)
			data[i] = 1;
		else
			data[i] = 0;
}

// Destructor that will delete memory that is declared within BinaryImage.
template <class t> BinaryImage<t>::~BinaryImage()
{
	delete[] data;
	data = 0;
}

// Get block will return a BinaryImage extracted from a BinaryImage.
template <class t> BinaryImage<t> BinaryImage<t>::getBlock(int startRow, int endRow, int startColumn, int endColumn) const
{
	int A = endRow - startRow + 1;
	int B = endColumn - startColumn + 1;
	t *block = new t[A*B];
	for (int i = 0; i < A; i++)
		for (int j = 0; j < B; j++)
			block[i*B + j] = this->data[(startRow + i) * N + (startColumn + j)];
	BinaryImage<t> result(A, B, block, 0.5);
	delete[] block;
	return result;
}

// Overloads the + operator applying the OR operation to two matrices.
template <class t> bool BinaryImage<t>::operator+ (const BinaryImage& b)
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (get(i, j) == b.get(i, j))
				return true;
	return false;
}

// Overloads the - operator applying the XOR operation to two matrices.
template <class t> bool BinaryImage<t>::operator- (const BinaryImage& b)
{
	bool one = false;
	bool two = false;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			if (get(i, j) == b.get(i, j))
				one = true;
			else
				two = true;
		}
	if (one&&two)
		return true;
	else
		return false;
}

// Overloads the * operator applying the AND operation to two matrices.
template <class t> bool BinaryImage<t>::operator* (const BinaryImage& b)
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (get(i, j) != b.get(i, j))
				return false;
	return true;
}

// Overloads the / operator applying the NOR operation to two matrices.
template <class t> bool BinaryImage<t>::operator/ (const BinaryImage& b)
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (get(i, j) == b.get(i, j))
				return false;
	return true;
}