#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

// TODO: Something to consider - should vectors be structs?
template <typename T>
class Vector
{
public:
    // Constructors/destructors.
	Vector(const int size = 2)
        : m_size(size)
    {
        m_vector = new T[size];
        for (int k = 0; k < size; k++)
            m_vector[k] = 0;
    }

    Vector(const Vector& v)
    {
        delete [] m_vector;
        
        m_size = v.m_size;

        m_vector = new T[size()];
        for (int k = 0; k < size(); k++)
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

    void mod(const int n, const T& val)
    {
        m_vector[n - 1] = val;
    }

    T& get(const int n)
    {
        return m_vector[n - 1];
    }

    // Getter functions.
    int size() const { return m_size; }

    // Sum absolute value of components to get magnitude.
	double mag() const
    {
        double mag = 0;
        for (T entry : m_vector)
            mag += entry < 0 ? entry * -1 : entry;
        return mag;
    }

private:
    T* m_vector;    // Representation of this vector as a dynamically allocated array.
    int m_size;		// Dimension of this vector.
};

#endif  // VECTOR_INCLUDED