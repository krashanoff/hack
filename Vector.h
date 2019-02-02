#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <iostream>
using namespace std;

/* TODOs:
 *  - How to enforce requirements for vector operations?
 */

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
    Vector<T>& operator=(const Vector& v)
    {
        if (v == *this)
            return *this;

        delete [] m_vector;
        m_size = v.m_size;
        m_vector = new T[m_size];
        for (int k = 0; k < v.m_size; k++)
            m_vector[k] = v.m_vector[k];

        return *this;
    }

    Vector<T>& operator+(const Vector& v)
    {
        for (int k = 0; k < m_size; k++)
            m_vector[k] += v.m_vector[k];
        return *this;
    }

    Vector<T>& operator-(const Vector& v)
    {
        for (int k = 0; k < m_size; k++)
            m_vector[k] -= v.m_vector[k];
        return *this;
    }

    Vector<T>& operator/(const T& t)
    {
        if (t == 0)
            return *this;

        for (int k = 0; k < m_size; k++)
            m_vector[k] /= t;
        return *this;
    }

    double& operator*(const Vector& v)
    {
        int tot = 0;
        for (int k = 0; k < m_size; k++)
            tot += m_vector[k] * v.m_vector[k];
        return tot;
    }

    Vector& operator*(const T& t)
    {
        for (int k = 0; k < m_size; k++)
            m_vector[k] *= t;
        return *this;
    }

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
        int k = 0;
        for (k = 0; k < m_size - 1; k++)
            cerr << m_vector[k] << ',';
        cerr << m_vector[k] << ']' << endl;
    }

    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

#endif  // VECTOR_INCLUDED