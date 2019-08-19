#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <iostream>

/* TODOs:
 *  - How to enforce requirements for vector operations?
 *  - Create pointer versions of operators.
 */

template<typename T>
struct Vector
{
    // Constructors, destructors
	Vector(const int size = 2);  // Construct an empty vector of zeros.
    Vector(const T* items, const int size);  // Construct from a preexisting array.
    Vector(const Vector<T>& v);  // Copy constructor.
    ~Vector();   // Destructor.

    // Operators
    Vector<T>& operator=(const Vector<T>& v);   // Assignment operator.

    Vector<T>& operator+(const Vector<T>& v);   // Add two vectors of the same size.
    Vector<T>& operator+=(const Vector<T>& v) { return *this + v; }

    Vector<T>& operator-(const Vector<T>& v);   // Subtract two vectors of the same size.
    Vector<T>& operator-=(const Vector<T>& v) { return *this - v; }

    Vector<T>& operator/(const T& t);    // Divide by a scalar constant.
    Vector<T>& operator/=(const T& t) { return *this / t; }

    double& operator*(const Vector<T>& v);  // Multiply by a scalar constant.
    Vector<T>& operator*(const T& t);   // Dot product two vectors of the same size.
    Vector<T>& operator*=(const T& t) { return *this * t; }

	Vector<T>& crossprod(const Vector<T>& v);		// Cross product. TBD OPERATOR.

    // Utility functions
	double magnitude() const;   // Sum absolute value of components to get magnitude.
    void print() const;     // Print the contents of the vector to cout.

    // Data members
    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

template<typename T>
Vector<T>::Vector(const int size)
    : m_size(size)
{
    m_vector = new T[m_size];
    for (int k = 0; k < m_size; k++)
        m_vector[k] = 0;
}

template<typename T>
Vector<T>::Vector(const T* items, const int size)
    : m_size(size)
{
    m_vector = new T[m_size];
    for (int k = 0; k < m_size; k++)
        m_vector[k] = items[k];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v)
{      
    m_size = v.m_size;

    m_vector = new T[m_size];
    for (int k = 0; k < m_size; k++)
        m_vector[k] = v.m_vector[k];
}

template<typename T>
Vector<T>::~Vector()
{
    delete [] m_vector;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
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

template<typename T>
Vector<T>& Vector<T>::operator+(const Vector<T>& v)
{
    for (int k = 0; k < m_size; k++)
        m_vector[k] += v.m_vector[k];
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-(const Vector<T>& v)
{
    for (int k = 0; k < m_size; k++)
        m_vector[k] -= v.m_vector[k];
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator/(const T& t)
{
    if (t == 0)
        return *this;

    for (int k = 0; k < m_size; k++)
        m_vector[k] /= t;
    return *this;
}

template<typename T>
double& Vector<T>::operator*(const Vector<T>& v)
{
    int tot = 0;
    for (int k = 0; k < m_size; k++)
        tot += m_vector[k] * v.m_vector[k];
    return tot;
}

template<typename T>
Vector<T>& Vector<T>::operator*(const T& t)
{
    for (int k = 0; k < m_size; k++)
        m_vector[k] *= t;
    return *this;
}

template<typename T>
double Vector<T>::magnitude() const
{
    double mag = 0;
    for (T entry : m_vector)
        mag += entry < 0 ? entry * -1 : entry;
    return mag;
}

template<typename T>
void Vector<T>::print() const
{
    std::cout << '[';
    int k = 0;
    for (k = 0; k < m_size - 1; k++)
        std::cout << m_vector[k] << ',';
    std::cout << m_vector[k] << ']' << std::endl;
}

#endif  // VECTOR_INCLUDED