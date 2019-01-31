#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

template <typename T>
class Vector;

template <typename T>
class Matrix
{
public:
    // Constructors/destructors.
	Matrix();
    Matrix(const Matrix& m);
    ~Matrix();

	// Operators.
	Matrix& operator=(const Matrix& m);		// Assignment
	Matrix& operator*(const Matrix& m);		// Multiplication
	Matrix& operator^(const int e);			// Exponentiation

    // Helper functions.
    int rows() const;             // Return the number of rows.
    int cols() const;             // Return the number of cols.
	int rank() const;			  // Return the number of leading ones in rref(this).
	bool invertible() const;      // Is this Matrix invertible?

    // Managing content.
    bool mod(const int row, const int col, const T& value);	// Replace a value. Returns if value changed or r,c is OOB.

    // Functions for modifying the matrix, etc.
    Matrix* inverse() const;     // Return inverse(this).
    Matrix* rref() const;        // Return the rref of this Matrix.
    Vector<T>* image() const;    // Return the image of this Matrix as a span of its column vectors.

private:
    Vector<T>* m_matrix;    // Source matrix. Composed of the column vectors.
	Matrix* m_rref;	        // Hold rref(this) in memory at all times as it is accessed often.
	int m_rows;
    int m_cols;
};

#endif  // MATRIX_INCLUDED