#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include "Vector.h"

#include <iostream>
using namespace std;    // TODO: Remove this when finalized.

/* General Specifications:
 *  - Coordinate system starts at (1,1), referring to the upper-rightmost
 *    entry.
 */

/* TODO:
 * Change implementation to use row vectors.
 */

template <typename T>
class Matrix
{
public:
    // Empty Matrix of [r,c] dimensions.
	Matrix(const int r = 5, const int c = 5)
        : m_rows(r), m_cols(c)
    {
        // Create an array of pointers to column vectors.
        m_matrix = new Vector<T>*[c];

        // Create each column vector to be of size r (rows).
        for (int k = 0; k < c; k++)
            m_matrix[k] = new Vector<T>(r);
    }

    // Matrix constructed from preexisting one.
    Matrix(const T* src, const int r, const int c)
        : m_rows(r), m_cols(c)
    {
        // TODO
    }

    // Construct from column vectors.
    Matrix(const Vector<T>* src, const int nVectors);
    
    // Copy constructor.
    Matrix(const Matrix& m);

    ~Matrix()
    {
        // Delete each column vector.
        for (int k = 0; k < cols(); k++)
            delete m_matrix[k];

        // Delete the array of pointers to column vectors.
        delete [] m_matrix;
    }

	// Operators.
	Matrix& operator=(const Matrix& m);		// Assignment
	Matrix& operator*(const Matrix& m);		// Multiplication
	Matrix& operator^(const int e);			// Exponentiation

    // Row operations. Return whether r, r1, r2 are in bounds or not.
    bool addRows(const int r1, const int r2);   // r1 += r2
    bool subRows(const int r1, const int r2);   // r1 -= r2
    bool divRow(const int r, const T& t);       // r /= t
    bool multRow(const int r, const T& t);      // r *= t
    bool swapRows(const int r1, const int r2);  // r1 = r2, r2 = r1

    // Getter functions.
    int rows() const { return m_rows; }             // Return the number of rows.
    int cols() const { return m_cols; }             // Return the number of cols.
	int rank() const { return m_rank; }			    // Return the number of leading ones in rref(this).

    // Properties.
	bool invertible() const;      // Is this Matrix invertible?

    // Managing content.
    // Replace a value. Returns if value changed or (r,c) is OOB.
    bool mod(const int r, const int c, const T& value)
    {
        if (r > rows() || r < 1 || c > cols() || c < 1)
            return false;
        
        // Access the column vector 'c' and set 'r' to value.
        m_matrix[c - 1]->m_vector[r - 1] = value;
        
        return true;
    }

    // Basic operations, properties of the Matrix, etc.
    Matrix rref() const
    {
        // Copy the current Matrix.
        Matrix<T> mat(*this);

        // Divide the first row by (1,1)
        // Perform operations so all other rows' (x,1) = 0
        // Do so for the second row and (2, 2)
    }

    Matrix identity() const
    {
        Matrix<T> mat(rows(), cols());
        int i = 0;
        for (int k = 0; k < rows(); k++)
        {
            mat.mod(k, i, 1);
            i++;
        }
        return mat;
    }

    Matrix inverse() const;     // Return inverse(this).
    Vector<T>* image() const;    // Return the image of this Matrix as a span of its column vectors.

    void print() const
    {
        for (int k = 0; k < rows(); k++)
        {
            cerr << '[';
            int i = 0;
            for (i = 0; i < cols() - 1; i++)
                cerr << m_matrix[i]->m_vector[k] << ',';
            cerr << m_matrix[i]->m_vector[k] << ']' << endl;
        }
    }

private:
    Vector<T>** m_matrix;    // Source matrix. Pointers to column vectors.
	int m_rows;
    int m_cols;
    int m_rank;
};

#endif  // MATRIX_INCLUDED