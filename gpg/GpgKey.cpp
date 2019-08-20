#include "GpgKey.h"

#include <stdio.h>

// Takes a single line of output from `gpg -k --with-colons`
// and processes it into the data structure. O(n).

// TODO: Dynamically create field content values as one processes
// the string to reduce ultimate structure size.
GpgKeyComplete::GpgKeyComplete(const char* info)
{
    // Simply init our fields vector.
    for (int k = 0; k < KEYFIELD::FIELDCOUNT; k++)
        m_fields.push_back(new char[64]);

    /*
    Read in to create our field data.
    */
    int idx = 0;            // Processes our input string.
    int currentField = 0;   // Determines our current field based on the enum.
    int len = 0;            // Current length of the content of our field.
    while (info[idx] != 0)
    {
        // Terminate our current field on end.
        if (info[idx] == ':')
        {
            m_fields[currentField][len] = '\0';
            len = 0;
            currentField++;
        }
        else
        {
            m_fields[currentField][len] = info[idx];
            len++;
        }

        idx++;
    }

    // Terminate the final field.
    m_fields[currentField][len] = '\0';
}

GpgKeyComplete::~GpgKeyComplete()
{
    // Free memory.
    for (auto field : m_fields)
        delete[] field;
}

char* GpgKeyComplete::operator[](const KEYFIELD fieldID)
{
    return m_fields[fieldID];
}