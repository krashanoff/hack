#ifndef RAY_H_
#define RAY_H_

#include "vector.h"
#include "macros.h"

/* ray.h
 * This is a high-level implementation of
 * a ray by the specifications of
 * raytracing.github.io.
 * It considers rays as a function of time
 * p(t) = A + tB, where A supplies the
 * origin and B supplies the direction of
 * the ray.
 */

template<typename T>
class ray
{
public:
    ray(const vector<T>, const vector<T>);

    vector<T> origin() const { return _a; }
    vector<T> direction() const { return _b; }
    vector<T> operator[](const LLONG& t) { return _a + t*_b; }

private:
    vector<T> _a;
    vector<T> _b;
};

template<typename T>
ray<T>::ray(const vector<T> a, const vector<T> b)
    : _a(a), _b(b) {}

#endif // RAY_H_