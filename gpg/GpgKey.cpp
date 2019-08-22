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
        if (currentField > KEYFIELD::USER_ID)
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

unsigned short GpgKey::recordType() const
{
    return m_recordType;
}

char GpgKey::validity() const
{
    return m_validity;
}

unsigned short GpgKey::keyLength() const
{
    return m_keyLength;
}

unsigned short GpgKey::publicKeyAlgorithm() const
{
    return m_publicKeyAlgorithm;
}

const char* GpgKey::keyID() const
{
    return m_keyID;
}

unsigned short GpgKey::creationDate() const
{
    return m_creationDate;
}

unsigned short GpgKey::expirationDate() const
{
    return m_expirationDate;
}

const char* GpgKey::certEtc() const
{
    return m_certEtc;
}

char GpgKey::ownerTrust() const
{
    return m_ownerTrust;
}

const char* GpgKey::userID() const
{
    return m_userID;
}

// Print out all information about our key.
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

/* createInfo()
 * Utility function. Passed an input string and a fieldID, it
 * creates the proper entry in our GpgKey for the specified data
 * type.
 */
void GpgKey::createInfo(const char* inputString, const int fieldID)
{
    std::cerr << "Processing inputString: " << inputString << " using fieldID: " << fieldID << std::endl;
    int idx = 0;

    switch (fieldID)
    {
    case KEYFIELD::RECORD_TYPE:
        // Conditionally set our record type.
        if (strcmp(inputString, "tru") == 0)
            m_recordType = RECORDTYPE::TRU;
        else if (strcmp(inputString, "pub") == 0)
            m_recordType = RECORDTYPE::PUB;
        else if (strcmp(inputString, "fpr") == 0)
            m_recordType = RECORDTYPE::FPR;
        else if (strcmp(inputString, "uid") == 0)
            m_recordType = RECORDTYPE::UID;
        else if (strcmp(inputString, "sub") == 0)
            m_recordType = RECORDTYPE::SUB;
        break;

    case KEYFIELD::VALIDITY:
        // Simply set our validity to the character.
        m_validity = inputString[0];
        break;

    case KEYFIELD::KEY_LENGTH:
        // Read in and set our key length.
        m_keyLength = getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::PUBLIC_KEY_ALGORITHM:
        m_publicKeyAlgorithm = getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::KEY_ID:
        // Get length and create array.
        while (inputString[idx] != '\0')
            idx++;
        m_keyID = new char[idx + 1];

        // Read into the array.
        for (idx = 0; inputString[idx] != '\0'; idx++)
            m_keyID[idx] = inputString[idx];
        m_keyID[idx] = '\0';

        break;

    case KEYFIELD::CREATION_DATE:
        m_creationDate = getNum<unsigned int>(inputString);
        break;

    case KEYFIELD::EXPIRATION_DATE:
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

    case KEYFIELD::OWNER_TRUST:
        m_ownerTrust = inputString[0];
        break;

    case KEYFIELD::USER_ID:
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

// Scans a string and returns its numerical representation.
// The desired return type is determined by the template type.
// The template type should be arithmetic in nature.
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