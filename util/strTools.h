#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <type_traits>

namespace util
{
    /* copyString
     * Return a pointer to a dynamically allocated copy of
     * the string pointed to by `input`.
     * RETURN TYPE IS DYNAMICALLY ALLOCATED AND MUST BE FREED
     * MANUALLY.
     */
    char* copyString(const char* input);

    /* getNum
     * Scans a string and returns its numerical representation.
     * The desired return type is determined by the template type.
     * The template type should be arithmetic in nature, and chosen
     * wisely. Overflow can occur: if one were to try putting a
     * 4-byte value into a `char`, then the return value would not
     * be accurate.
     */
    template<typename T>
    T getNum(const char* inputString);
}

char* util::copyString(const char* input)
{
    // Catch nullptr
    if (input == nullptr)
        return nullptr;

    // Get length for purpose of dynamically allocating
    // the character array.
    int idx = 0;
    while (input[idx] != '\0')
        idx++;
    char* result = new char[idx + 1];

    // Read in and copy the string.
    idx = 0;
    while (input[idx] != '\0')
    {
        result[idx] = input[idx];
        idx++;
    }
    result[idx] = '\0';

    return result;
}

template<typename T>
T util::getNum(const char* inputString)
{
    // Sanitize our template type.
    static_assert(std::is_arithmetic<T>::value, "getNum must be used with arithmetic types.");

    int idx = 0;
    T result = 0;

    while (inputString[idx] != '\0')
    {
        // Add our integer.
        result += (inputString[idx] - '0');

        // Multiply by ten if there are remaining digits.
        if (inputString[idx + 1] != '\0')
            result *= 10;
            
        idx++;
    }
    
    return result;
}

#endif