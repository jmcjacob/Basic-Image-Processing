#include <iostream>
#pragma once
using namespace std;

template <class t>
class Matrix
{
protected:
	int M, N;
	t* data;
public:
	Matrix(){};
	Matrix(int sizeR, int sizeC, t val);
	Matrix(int sizeR, int sizeC, t* input_data);
	Matrix(const Matrix& m);
	~Matrix();

	t get(int i, int j) const{ return data[i*N + j]; };
	void set(int i, int j, t val) { data[i*N + j] = val; };
	int getM() const{ return M; };
	int getN() const{ return N; };
	t* getData() { return data; };
	Matrix getBlock(int startRow, int endRow, int startColumn, int endColumn) const;
	void setBlock(int startRow, int startColumn, Matrix<t> m);

	Matrix operator+ (const Matrix& m);
	Matrix operator- (const Matrix& m);
	Matrix operator* (const Matrix& m);
	Matrix operator/ (const Matrix& m);

	Matrix& operator= (const Matrix& m);
	void operator++ ();
	void operator-- ();
	t operator()(int i, int j);

	double SSD(Matrix T);
	double NC(Matrix T);
	void print();
	double mean();
};

// Constructor with rows, columns and a value for every element.
template <class t> Matrix<t>::Matrix(int sizeR, int sizeC, t val)
{
	M = sizeR;
	N = sizeC;
	data = new t[M*N];
	for (int i = 0; i < M*N; i++)
		data[i] = val;
}

// Constructor with rows, columns and a array to be inputted.
template <class t>  Matrix<t>::Matrix(int sizeR, int sizeC, t* input_data)
{
	M = sizeR;							// Sets the value of M to the number of rows.
	N = sizeC;							// Sets the value of N to the number of columns.
	data = new t[M*N];					// Allocates the memory of data to rows*columns.
	for (int i = 0; i < M*N; i++)		// Goes through the loop and sets the values of the inputted array to data.
		data[i] = input_data[i];
}

// Copy Constructor that will create a temporary Matrix object for copying data.
template <class t>  Matrix<t>::Matrix(const Matrix& m)
{
	M = m.getM();
	N = m.getN();
	data = new t[M*N];
	for (int i = 0; i < M*N; i++)
		data[i] = m.data[i];
}

// Destructor that will delete the data that has been created by the object.
template <class t> Matrix<t>::~Matrix()
{
	delete[] data;
	data = 0;
}

// Get block will return a matrix extracted from a matrix.
template <class t> Matrix<t> Matrix<t>::getBlock(int startRow, int endRow, int startColumn, int endColumn) const
{
	int A = endRow - startRow + 1;
	int B = endColumn - startColumn + 1;
	t *block = new t[A*B];

	for (int i = 0; i < A; i++)
		for (int j = 0; j < B; j++)
			block[i*B + j] = get((i + startRow), (j + startColumn));
	Matrix<t> result(A, B, block);
	delete[] block;
	block = 0;
	return result;
}

// Function that sets an inputted matrix to the specified matrix.
template <class t> void Matrix<t>::setBlock(int startRow, int startColumn, Matrix<t> m)
{
	for (int i = 0; i < m.M; i++)
		for (int j = 0; j < m.N; j++)
			data[(startRow + i) * N + (startColumn + j)] = m.get(i, j);
}

// Prints the matrix to the console used for testing purposes.
template <class t> void Matrix<t>::print()
{
	cout << "Rows: " << M << endl;
	cout << "Columns: " << N << endl;
	for (int i = 0; i < M; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
			cout << data[i*M + j] << ", ";
	}
	cout << endl;
}

// Overloads the + operator adding each element of two matrices.
template <class t> virtual Matrix<t> Matrix<t>::operator+ (const Matrix& m)
{
	t* result = new t[M*N];
	for (int i = 0; i < M*N; i++)
		result[i] = data[i] + m.data[i];
	Matrix<t> answer(M, N, result);
	delete[] result;
	return answer;
}

// Overloads the - operator subtracking each element of two matrices.
template <class t> virtual Matrix<t> Matrix<t>::operator- (const Matrix& m)
{
	t* result = new t[M*N];
	for (int i = 0; i < M*N; i++)
		result[i] = data[i] - m.data[i];
	Matrix<t> answer(M, N, result);
	delete[] result;
	return answer;
}

// Overloads the * operator multiplying each element of two matrices.
template <class t> virtual Matrix<t> Matrix<t>::operator* (const Matrix& m)
{
	t* resultArray = new t[M*N];
	for (int i = 0; i < M*N; i++)
		result[i] = data[i] * m.data[i];
	Matrix<t> result(M, N, resultArray);
	delete[] resultArray;
	return result;
}

// Overloads the / operator divide each element of two matrices.
template <class t> virtual Matrix<t> Matrix<t>::operator/ (const Matrix& m)
{
	t* resultArray = new t[M*N];
	for (int i = 0; i < M*N; i++)
		result[i] = data[i] / m.data[i];
	Matrix<t> result(M, N, resultArray);
	delete[] resultArray;
	return result;
}

// Overloads the = operator and sets one matrix to the value of another.
template <class t> Matrix<t>& Matrix<t>::operator= (const Matrix& m)
{
	delete[] data;
	M = m.M; N = m.N;
	data = new t[M*N];
	for (int i = 0; i < M*N; i++)
		data[i] = m.data[i];
	return *this;
}

// Overloads the ++ operator and increments all the values in the matrix by 1.
template <class t> void Matrix<t>::operator++ ()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			this->set(i, j, get(i, j) + 1);
}

// Overloads the -- operator and decrements all the values in the matrix by 1.
template <class t> void Matrix<t>::operator-- ()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			this->set(i, j, get(i, j) - 1);
}

// Overloads the () with two parameters and will return the value at that position.
template <class t> t Matrix<t>::operator()(int i, int j)
{
	return data[i*N + j];
}

// Function for preforming the Normalised Correlation NNS check with another inputted matrix.
template <class t> double Matrix<t>::NC(Matrix T)
{
	double meanA = mean(); double meanB = T.mean();
	t part1 = 0; t part2 = 0; t part3 = 0;
	for (int i = 0; i < M*N; i++)
	{
		double A = data[i] - meanA;
		double B = T.data[i] - meanB;
		part1 += A * B;
		part2 += pow(A, 2);
		part3 += pow(B, 2);
	}
	return part1 / sqrt(part2*part3);
}

// Function for preforming the Sum of the Squares Diffrence NNS check.
template <class t> double Matrix<t>::SSD(Matrix T)
{
	double answer = 0;
	for (int i = 0; i < M*N; i++)
		if (T.data[i] != (double)255)
			answer += pow((data[i] - T.data[i]), 2);
	return answer;
}

// Method for finding the mean of a matrix.
template <class t> double Matrix<t>::mean()
{
	double sum = 0;
	for (int i = 0; i < M*N; i++)
		sum += data[i];
	return sum / (M*N);
}