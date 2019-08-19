#include "GpgKey.h"

#include <stdio.h>

GpgKeyComplete::GpgKeyComplete()
{
    // Simply init our fields.
    for (int k = 0; k < KEYFIELD::FIELDCOUNT; k++)
        m_fields.push_back(new char[48]);
}

// Takes a single line of output from `gpg -k --with-colons`
// and processes it into the data structure. Realtively fast,
// O(n).

// TODO: Dynamically create field content values as one processes
// the string to reduce ultimate structure size.
GpgKeyComplete::GpgKeyComplete(const char* info)
    : GpgKeyComplete()
{
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
            m_fields[currentField][len] = 0;
            len = 0;
            currentField++;
            idx++;

            continue;
        }

        m_fields[currentField][len] = info[idx];
        len++;
        idx++;
    }

    // Terminate the final field.
    m_fields[currentField][len] = '\0';
}

GpgKeyComplete::~GpgKeyComplete()
{
    // Free memory.
    for (char* field : m_fields)
        delete[] field;
}

char* GpgKeyComplete::operator[](const KEYFIELD fieldID)
{
    return m_fields[fieldID];
}

void GpgKeyComplete::print() const
{
    for (auto s : m_fields)
        printf("%s\n", s);
}