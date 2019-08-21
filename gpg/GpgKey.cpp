#include "GpgKey.h"

#include <iostream>

GpgKey::GpgKey()
    : m_validity(0), m_ownerTrust(0),
      m_recordType(0), m_keyLength(0),
      m_publicKeyAlgorithm(0), m_creationDate(0),
      m_expirationDate(0), m_keyID(nullptr),
      m_userID(nullptr)
{
}

// Takes a single line of output from `gpg -k --with-colons`
// and processes it into the data structure. O(n).
GpgKey::GpgKey(const char* input)
    : GpgKey()
{
    // Process input into a modifiable array.
    int idx = 0;
    while (input[idx] != '\0')
        idx++;
    char* info = new char[idx + 1];
    idx = 0;
    while (input[idx] != '\0')
    {
        info[idx] = input[idx];
        idx++;
    }
    info[idx] = '\0';

    // Process our input to create our fields.
    idx = 0;                    // Processes our input string.
    int currentField = 0;       // Determines our current field based on the enum.
    int currentFieldStart = 0;  // Index of the start of the current field.

    while (info[idx] != 0)
    {
        // Terminate when we have expended our use for the
        // input string's fields.
        if (currentField > KEYFIELD::USERID)
            break;

        // Add a field when we have parsed the current one.
        if (info[idx] == ':')
        {
            info[idx] = '\0';
            
            createInfo(info + currentFieldStart, currentField);

            currentField++;
            currentFieldStart = idx + 1;
        }

        idx++;
    }

    // Free the memory we used in this function.
    delete[] info;
}

// Frees all memory allocated.
GpgKey::~GpgKey()
{
    delete[] m_keyID;
    delete[] m_userID;
    delete[] m_certEtc;
}

// Returns the content of the specified field.
const char* GpgKey::operator[](const KEYFIELD fieldID) const
{
    // If outside of the scope of our fields, return nullptr.
    if (fieldID > KEYFIELD::USERID)
        return nullptr;

    switch (fieldID)
    {
        case KEYFIELD::VALIDITY:
            break;
        case KEYFIELD::KEYLENGTH:
            break;
        case KEYFIELD::PUBLICKEYALGORITHM:
            break;
        case KEYFIELD::KEYID:
            break;
        case KEYFIELD::CREATIONDATE:
            break;
        case KEYFIELD::EXPIRATIONDATE:
            break;
        case KEYFIELD::OWNERTRUST:
            break;
        case KEYFIELD::USERID:
            break;
    }
}

void GpgKey::print() const
{
    std::cout << "Dump of our key information:" << std::endl;
    std::cout << m_recordType << ':';
    std::cout << m_validity << ':';
    std::cout << m_keyLength << ':';
    std::cout << m_publicKeyAlgorithm << ':';
    std::cout << m_keyID << ':';    
    std::cout << m_creationDate << ':';
    std::cout << m_expirationDate << ':';
    std::cout << m_certEtc << ':';
    std::cout << m_ownerTrust << ':';
    std::cout << m_userID << std::endl;
}

void GpgKey::createInfo(const char* inputString, const int fieldID)
{
    std::cerr << "Processing inputString: " << inputString << " using fieldID: " << fieldID << std::endl;
    int idx = 0;

    switch (fieldID)
    {
    case KEYFIELD::RECORDTYPE:
        // Conditionally set our record type.
        if (inputString == "tru")
            m_recordType = RECORDTYPE::TRU;
        else if (inputString == "pub")
            m_recordType = RECORDTYPE::PUB;
        else if (inputString == "fpr")
            m_recordType = RECORDTYPE::FPR;
        else if (inputString == "uid")
            m_recordType = RECORDTYPE::UID;
        else if (inputString == "sub")
            m_recordType = RECORDTYPE::SUB;
        break;

    case KEYFIELD::VALIDITY:
        // Simply set our validity to the character.
        m_validity = inputString[0];
        break;

    case KEYFIELD::KEYLENGTH:
        // Read in and set our key length.
        m_keyLength = getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::PUBLICKEYALGORITHM:
        m_publicKeyAlgorithm = getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::KEYID:
        // Get length and create array.
        while (inputString[idx] != '\0')
            idx++;
        m_keyID = new char[idx + 1];

        // Read into the array.
        for (idx = 0; inputString[idx] != '\0'; idx++)
            m_keyID[idx] = inputString[idx];
        m_keyID[idx] = '\0';

        break;

    case KEYFIELD::CREATIONDATE:
        m_creationDate = getNum<unsigned int>(inputString);
        break;

    case KEYFIELD::EXPIRATIONDATE:
        m_expirationDate = getNum<unsigned int>(inputString);
        break;

    case KEYFIELD::CERTIFICATE_ETC:
        // Get length and create array.
        while (inputString[idx] != '\0')
            idx++;
        
        // If empty, do nothing.
        if (idx == 0)
            break;
        
        // Otherwise, create and copy our contents.
        m_certEtc = new char[idx + 1];

        // Read into the array.
        for (idx = 0; inputString[idx] != '\0'; idx++)
            m_certEtc[idx] = inputString[idx];
        m_certEtc[idx] = '\0';

        break;

    case KEYFIELD::OWNERTRUST:
        m_ownerTrust = inputString[0];
        break;

    case KEYFIELD::USERID:
        // Get length and create array.
        while (inputString[idx] != '\0')
            idx++;
        m_userID = new char[idx + 1];

        // Read into the array.
        for (idx = 0; inputString[idx] != '\0'; idx++)
            m_userID[idx] = inputString[idx];
        m_userID[idx] = '\0';

        break;

    default:
        std::cerr << "Field not required. Skipping." << std::endl;
    }
}

// Scans a string and returns its short representation.
template<typename T>
T GpgKey::getNum(const char* inputString)
{
    int idx = 0;
    T result = 0;

    while (inputString[idx] != '\0')
    {
        result += (inputString[idx] - '0'); // Add our integer.
        result *= 10;   // Multiply by 10.
        idx++;
    }

    return result;
}