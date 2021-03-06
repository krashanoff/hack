#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include "Vector.h"

#include <iostream>
#include <type_traits>

/* General Specifications:
 *  - Coordinate system starts at (1,1), referring to the upper-rightmost
 *    entry.
 */

/* TODO:
 * Comment everywhere
 * Fix row operations
 * Clarify implementations
 * Exceptions.
 */

template<typename T>
class Matrix
{
public:
	static_assert(std::is_arithmetic<T>::value, "Matrices can only be used with arithmetic types.");

    // Empty Matrix of [r,c] dimensions.
	Matrix<T>(const int& r = 5, const int& c = 5);

	// Copy constructors:
	Matrix(const T* src, const int& r, const int& c);   // Using a preexisting 2D array
    Matrix(const Vector<T>* src, const int& nVectors);  // Using an array of row vectors
	Matrix(const Matrix<T>& m);                         // Using an existing matrix

	~Matrix();

	// Operators.
	Matrix<T>& operator=(const Matrix<T>& m);		// Assignment
	Matrix<T>& operator*(const Matrix<T>& m);		// Multiplication
	Matrix<T>& operator^(const int& e);				// Exponentiation

    // Row operations. Return whether r, r1, r2 are in bounds or not.
    bool addRows(const int r1, const int r2);
    bool subRows(const int r1, const int r2);
    bool swapRows(const int r1, const int r2);

    // Arithmetic row operations. Return whether the row is in bounds or
    // not.
    bool divRow(const int r, const T& t);
    bool multRow(const int r, const T& t);

    // Getter functions.
    int rows() const { return m_rows; }             // Return the number of rows.
    int cols() const { return m_cols; }             // Return the number of cols.
	int rank() const { return m_rank; }			    // Return the number of leading ones in rref(this).

    // Properties.
	bool invertible() const;      // Is this Matrix invertible?

    // Managing content.
    // Replace a value. Returns if value changed or (r,c) is OOB.
    bool mod(const int r, const int c, const T& value);

    // Basic operations, properties of the Matrix, etc.
	// TODO: Implement this.
    Matrix<T> rref() const;         // Returns the basic RREF of the matrix.
    Matrix<T> identity() const;    // Returns the NxN identity matrix.

    Matrix<T> inverse() const;     // Return inverse(this).
    Vector<T>* image() const;    // Return the image of this Matrix as a span of its column vectors.

    void print() const;

private:
    Vector<T>** m_matrix;    // Source matrix. Pointers to row vectors.
	int m_rows;
    int m_cols;
    int m_rank;
};

template<typename T>
Matrix<T>::Matrix(const int& r, const int& c)
	: m_rows(r), m_cols(c)
{
	// Create an array of pointers to row vectors.
	m_matrix = new Vector<T> * [r];

	// Create each row vector to be of size c (cols).
	for (int k = 0; k < r; k++)
		m_matrix[k] = new Vector<T>(c);
}

template<typename T>
Matrix<T>::Matrix(const T* src, const int& r, const int& c)
	: m_rows(r), m_cols(c)
{
	m_matrix = new Vector<T>* [r];

	for (int k = 0; k < r; k++)
	{
		m_matrix[k] = new Vector<T>(c);
		for (int i = 0; i < c; i++)
			m_matrix[k]->m_vector[i] = *(src + r*c + i);
	}
}

template<typename T>
Matrix<T>::Matrix(const Vector<T>* src, const int& nVectors)
{
    // TODO
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
	m_rows = m.rows();
	m_cols = m.cols();

	m_matrix = new Vector<T> * [m_rows];

	for (int k = 0; k < m_rows; k++)
	{
		m_matrix[k] = new Vector<T>(m_cols);
		for (int i = 0; i < m_cols; i++)
			m_matrix[k]->m_vector[i] = m.m_matrix[k]->m_vector[i];
	}
}

template<typename T>
Matrix<T>::~Matrix<T>()
{
	// Delete each row vector.
	for (int k = 0; k < rows(); k++)
		delete m_matrix[k];

	// Delete the array of pointers to row vectors.
	delete[] m_matrix;
}

template<typename T>
bool Matrix<T>::addRows(const int r1, const int r2)
{
    if (r1 < 1 || r2 < 1 || r1 > rows() || r2 > rows())
        return false;

    *m_matrix[r1 - 1] += *m_matrix[r2 - 1];

    return true;
}   // r1 += r2

template<typename T>
bool Matrix<T>::subRows(const int r1, const int r2)
{
    if (r1 < 1 || r2 < 1 || r1 > rows() || r2 > rows())
        return false;

    m_matrix[r1 - 1] -= m_matrix[r2 - 1];

    return true;
}   // r1 -= r2

template<typename T>
bool Matrix<T>::divRow(const int r, const T& t)
{
    if (r < 1 || r > rows())
        return false;

    m_matrix[r - 1] /= t;

    return true;
}       // r /= t

template<typename T>
bool Matrix<T>::multRow(const int r, const T& t)
{
    if (r < 1 || r > rows())
        return false;

    m_matrix[r - 1] *= t;

    return true;
}      // r *= t

template<typename T>
bool Matrix<T>::swapRows(const int r1, const int r2)
{
    // OOB check.
    if (r1 < 1 || r2 < 1 || r1 > rows() || r2 > rows())
        return false;

    // Swap rows r1 and r2.
    Vector<T>* temp = new Vector<T>(*m_matrix[r1]);
    delete m_matrix[r1];
    m_matrix[r1] = m_matrix[r2];
    m_matrix[r2] = temp;

    return true;
}  // r1 = r2, r2 = r1

template<typename T>
bool Matrix<T>::mod(const int r, const int c, const T& value)
{
    if (r > rows() || r < 1 || c > cols() || c < 1)
        return false;
    
    // Access the row vector 'r' and set 'c' to value.
    m_matrix[r - 1]->m_vector[c - 1] = value;
    
    return true;
}

template<typename T>
Matrix<T> Matrix<T>::rref() const
{
    // Copy the current Matrix.
    Matrix<T> mat(*this);

	// For every row:
    for (int k = 0; k < rows(); k++)
    {
        // Divide the first row by (1,1)
        *mat.m_matrix[k] /= mat.m_matrix[k]->m_vector[k];
		mat.m_matrix[k]->print();

        // Subtract proper multiples from each row to reach rref.
        for (int i = k; i > 0; i--)
            *mat.m_matrix[i] -= *mat.m_matrix[k]*m_matrix[i]->m_vector[k];
        for (int i = k; i < rows(); i++)
            *mat.m_matrix[i] -= *mat.m_matrix[k]*m_matrix[i]->m_vector[k];
    }

    return mat;
}

template<typename T>
Matrix<T> Matrix<T>::identity() const
{
    Matrix<T> mat(rows(), cols());
    int i = 1;
    
    for (int k = 1; k <= rows(); k++)
    {
        mat.mod(k, i, 1);
        i++;
    }

    return mat;
}

template<typename T>
void Matrix<T>::print() const
{
    for (int k = 0; k < rows(); k++)
        m_matrix[k]->print();

    std::cerr << std::endl;
}

#endif