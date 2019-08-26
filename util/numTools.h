#ifndef NUMTOOLS_H
#define NUMTOOLS_H

#include <type_traits>

namespace util
{
    /* encodeInto
     * Encode an array of `U`s into a single `T`
     * if possible. Returns nullptr if impossible.
     * T and U must be integral types.
     * 
     * For example, one may encode eight `char`s
     * into a single `long`.
     */
    template<typename T, typename U>
    T* encodeInto(const U* src, const int size);

    /* decodeInto
     * The opposite of encodeInto. Notice the lack of
     * a `size` argument. It is not needed, as the resulting
     * array is dynamically allocated based on the size of
     * the data type we wish to convert to.
     * If `src` is nullptr, the function returns nullptr.
     * T and U must be integral types.
     * 
     * For example, one may decode eight `char`s from a 
     * single `long`.
     * 
     * It is named decodeInto because semantically,
     * we are decoding into the template type from the
     * argument:
     * decodeInto<int>(argument)
     */
    template<typename T, typename U>
    T* decodeInto(const U src);
}

template<typename T, typename U>
T* util::encodeInto(const U* src, const int size)
{
    // Sanitize template types.
    static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value);

    int tsize = sizeof(T);
    int usize = sizeof(U);

    // Test that encoding is possible.
    if (tsize < (usize * size))
        return nullptr;

    T* dst = new T(0);  // Our result.
    U current = *src;   // Our "current" value.

    for (int k = 0; k < size; k++)
    {
        current = src[k];   // Get the current value.
        *dst += current;    // Add it to the zeroed out result.

        // Stop before we lose data.
        if (k + 1 == size)
            break;

        *dst <<= usize * 8;  // Shift left the proper number of bits.
    }

    return dst;
}

template<typename T, typename U>
T* util::decodeInto(const U src)
{
    // Sanitize template types.
    static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value);

    // Catch impossible decoding.
    if (sizeof(T) > sizeof(U))
        return nullptr;

    // Determine the size of our array.
    int arraySize = sizeof(U) / sizeof(T);
    T* result = new T[arraySize];

    // Decode src using a mask based on the size of our variable.
    for (int k = 0; k < arraySize; k++)
        result[arraySize - k - 1] = (src >> (sizeof(T) * k * 8));

    return result;
}

#endif