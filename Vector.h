#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

// TODO: Something to consider - should vectors be structs?
template <typename T>
struct Vector
{
    // Constructors/destructors.
	Vector(const int size = 2)
        : m_size(size)
    {
        m_vector = new T[m_size];
        for (int k = 0; k < m_size; k++)
            m_vector[k] = 0;
    }

    Vector(const Vector& v)
    {
        delete [] m_vector;
        
        m_size = v.m_size;

        m_vector = new T[m_size];
        for (int k = 0; k < m_size; k++)
            m_vector[k] = v.m_vector[k];
    }

    ~Vector()
    {
        delete [] m_vector;
    }

    // Operators.
    Vector<T>& operator=(const Vector& v);		// Assignment
    double operator*(const Vector& v);				// Dot product returning a *SCALAR*.
	Vector<T>& crossprod(const Vector& v);		// Cross product. TBD OPERATOR.

    // Sum absolute value of components to get magnitude.
	double mag() const
    {
        double mag = 0;
        for (T entry : m_vector)
            mag += entry < 0 ? entry * -1 : entry;
        return mag;
    }

    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

#endif  // VECTOR_INCLUDED