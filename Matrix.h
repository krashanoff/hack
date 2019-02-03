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
 * Comment everywhere
 * Fix row operations
 * Clarify implementations
 */

template <typename T>
class Matrix
{
public:
    // Empty Matrix of [r,c] dimensions.
	Matrix(const int r = 5, const int c = 5)
        : m_rows(r), m_cols(c)
    {
        // Create an array of pointers to row vectors.
        m_matrix = new Vector<T>*[r];

        // Create each row vector to be of size c (cols).
        for (int k = 0; k < r; k++)
            m_matrix[k] = new Vector<T>(c);
    }

    // Matrix constructed from preexisting one.
    Matrix(const T src[][5], const int r, const int c)
        : m_rows(r), m_cols(c)
    {
        m_matrix = new Vector<T>*[r];

        for (int k = 0; k < r; k++)
        {
            m_matrix[k] = new Vector<T>(c);
            for (int i = 0; i < c; i++)
                m_matrix[k]->m_vector[i] = src[k][i];
        }
    }

    // Construct from row vectors.
    Matrix(const Vector<T>* src, const int nVectors);
    
    // Copy constructor.
    Matrix(const Matrix& m);

    ~Matrix()
    {
        // Delete each row vector.
        for (int k = 0; k < rows(); k++)
            delete m_matrix[k];

        // Delete the array of pointers to row vectors.
        delete [] m_matrix;
    }

	// Operators.
	Matrix& operator=(const Matrix& m);		// Assignment
	Matrix& operator*(const Matrix& m);		// Multiplication
	Matrix& operator^(const int e);			// Exponentiation

    // Row operations. Return whether r, r1, r2 are in bounds or not.
    bool addRows(const int r1, const int r2)
    {
        if (r1 < 1 || r2 < 1 || r1 > rows() || r2 > rows())
            return false;
        *m_matrix[r1] += *m_matrix[r2];
        return true;
    }   // r1 += r2

    bool subRows(const int r1, const int r2)
    {
        if (r1 < 1 || r2 < 1 || r1 > rows() || r2 > rows())
            return false;
        m_matrix[r1] -= m_matrix[r2];
        return true;
    }   // r1 -= r2

    bool divRow(const int r, const T& t)
    {
        if (r < 1 || r > rows())
            return false;
        m_matrix[r] /= t;
        return true;
    }       // r /= t

    bool multRow(const int r, const T& t)
    {
        if (r < 1 || r > rows())
            return false;
        m_matrix[r] *= t;
        return true;
    }      // r *= t

    bool swapRows(const int r1, const int r2)
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
        
        // Access the row vector 'r' and set 'c' to value.
        m_matrix[r - 1]->m_vector[c - 1] = value;
        
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
        int i = 1;
        for (int k = 1; k <= rows(); k++)
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
            m_matrix[k]->print();
        cerr << endl;
    }

private:
    Vector<T>** m_matrix;    // Source matrix. Pointers to row vectors.
	int m_rows;
    int m_cols;
    int m_rank;
};

#endif  // MATRIX_INCLUDED