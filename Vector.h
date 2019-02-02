#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <iostream>
using namespace std;

template <typename T>
struct Vector
{
    // Construct an empty vector of zeros.
	Vector(const int size = 2)
        : m_size(size)
    {
        m_vector = new T[m_size];
        for (int k = 0; k < m_size; k++)
            m_vector[k] = 0;
    }

    // Construct from a preexisting array.
    Vector(const T* items, const int size)
        : m_size(size)
    {
        m_vector = new T[m_size];
        for (int k = 0; k < m_size; k++)
            m_vector[k] = items[k];
    }

    // Copy constructor.
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
    double operator*(const Vector& v);			// Dot product returning a *SCALAR*.
	Vector<T>& crossprod(const Vector& v);		// Cross product. TBD OPERATOR.

    // Sum absolute value of components to get magnitude.
	double magnitude() const
    {
        double mag = 0;
        for (T entry : m_vector)
            mag += entry < 0 ? entry * -1 : entry;
        return mag;
    }

    void print() const
    {
        cerr << '[';
        for (int k = 0; k < m_size; k++)
            cerr << m_vector[k] << ',';
        cerr << ']' << endl;
    }

    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

#endif  // VECTOR_INCLUDED