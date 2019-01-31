#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

template <typename T>
class Vector
{
public:
    // Constructors/destructors.
	Vector(const int size = 2);
    Vector(const Vector& v);
    ~Vector();

    // Operators.
    Vector<T>& operator=(const Vector& v);		// Assignment
    T& operator*(const Vector& v);				// Dot product returning a *SCALAR*.
	Vector<T>& operator?(const Vector& v);		// Cross product. TBD OPERATOR.

    // Helper functions.
    int size() const;	// Size
	double mag() const;	// Magnitude

private:
    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

#endif  // VECTOR_INCLUDED