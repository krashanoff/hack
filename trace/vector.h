#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <math.h>
#include "macros.h"

/* vector.h
 * Interface for a friendly high-level implementation of
 * the R3 vector provided in vector.c.
 */

template<typename T>
class vector
{
public:
    vector(LLONG);                      // init all vals to zero, given dimension.
    vector(LLONG, const T*);            // init vals to those provided from an existing array.
    vector(std::initializer_list<T>);   // init vals from inline array.
    vector(const vector<T>&);
    ~vector();

    vector<T>& operator=(const vector<T>&);

    T& operator[](LLONG i) { return _v[i]; }
    T& operator[](LLONG i) const { return _v[i]; }
    vector<T> operator+(const vector<T>&) const;
    vector<T> operator-(const vector<T>&) const;
    vector<T> operator*(const vector<T>&) const;
    vector<T> operator/(const vector<T>&) const;

    vector<T> operator*(const T&) const;
    vector<T> operator/(const T&) const;

    vector<T> operator^(const vector<T>&) const;    // dot product.

    LLONG dim() const { return _d; }

    T length() const;
    vector<T> unit() const;

private:
    T* _v;         // internal array of values.
    LLONG _d;      // dimension of the vector.
};

// init a vector of dimension d with all values init to zero.
template<typename T>
vector<T>::vector(LLONG d)
    : _v(nullptr), _d(d)
{
    _v = new T[d];

    for (int k = 0; k < d; k++)
        _v[k] = 0;
}

// init a vector of dimension d, and copy values from src.
template<typename T>
vector<T>::vector(LLONG d, const T* src)
    : vector(d)
{
    for (int k = 0; k < d; k++)
        _v[k] = src[k];
}

// init a vector from an initializer list.
template<typename T>
vector<T>::vector(std::initializer_list<T> i)
    : vector(i.size())
{
    LLONG idx = 0;

    for (auto k = i.begin(); k != i.end(); k++)
    {
        _v[idx] = *k;
        idx++;
    }
}

// copy constructor.
template<typename T>
vector<T>::vector(const vector<T>& o)
    : vector(o._d, o._v) {}

// destructor.
template<typename T>
vector<T>::~vector()
{
    delete[] _v;
}

// assignment.
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& o)
{
    if (&o == this)
        return *this;

    delete[] _v;
    this = vector<T>(o);
}

// add two vectors.
template<typename T>
vector<T> vector<T>::operator+(const vector<T>& o) const
{
    LLONG resultSize = MIN(_d, o._d);
    vector<T> result(resultSize);

    for (int k = 0; k < resultSize; k++)
        result[k] = _v[k] + o[k];
    
    return result;
}

// subtract two vectors.
template<typename T>
vector<T> vector<T>::operator-(const vector<T>& o) const
{
    LLONG resultSize = MIN(_d, o._d);
    vector<T> result(resultSize);

    for (int k = 0; k < resultSize; k++)
        result[k] = _v[k] - o[k];
    
    return result;
}

// multiplication.
template<typename T>
vector<T> vector<T>::operator*(const vector<T>& o) const
{
    LLONG resultSize = MIN(_d, o._d);
    vector<T> result(resultSize);

    for (int k = 0; k < resultSize; k++)
        result[k] = _v[k] * o[k];
    
    return result;
}

// division.
template<typename T>
vector<T> vector<T>::operator/(const vector<T>& o) const
{
    LLONG resultSize = MIN(_d, o._d);
    vector<T> result(resultSize);

    for (int k = 0; k < resultSize; k++)
        result[k] = _v[k] / o[k];

    return result;
}

// multiply by a constant.
template<typename T>
vector<T> vector<T>::operator*(const T& t) const
{
    vector<T> result(_d);

    for (int k = 0; k < _d; k++)
        result[k] = _v[k] * t;
    
    return result;
}

// divide by a constant.
template<typename T>
vector<T> vector<T>::operator/(const T& t) const
{
    vector<T> result(_d);

    for (int k = 0; k < _d; k++)
        result[k] = _v[k] / t;

    return result;
}

// dot product.
template<typename T>
vector<T> vector<T>::operator^(const vector<T>& o) const
{
    LLONG smallerSize = MIN(_d, o._d);
    T result = 0;

    for (int k = 0; k < smallerSize; k++)
        result += _v[k] * o[k];
    
    return result;
}

// returns the length of the vector.
template<typename T>
T vector<T>::length() const
{
    T result = 0;
    for (int k = 0; k < _d; k++)
        result += _v[k]*_v[k];
    return sqrt(result);
}

// returns the unit vector of the current vector.
template<typename T>
vector<T> vector<T>::unit() const
{
    return *this / this->length();
}

#endif // VECTOR_H_