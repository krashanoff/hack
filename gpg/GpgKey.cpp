#include "GpgKey.h"

#include "../util/strTools.h"

#include <iostream>
#include <string.h>

// The default constructor for a GpgKey only sets up data
// members to their default values.
GpgKey::GpgKey()
    : m_validity(0), m_ownerTrust(0),
      m_recordType(0), m_keyLength(0),
      m_publicKeyAlgorithm(0), m_creationDate(0),
      m_expirationDate(0), m_keyID(nullptr),
      m_userID(nullptr), m_certEtc(nullptr)
{}

// The copy constructor simply copies all private fields appropriately
// and creates a copy of the character arrays for keyID, userID, certEtc.
GpgKey::GpgKey(const GpgKey& g)
    : m_validity(g.m_validity), m_ownerTrust(g.m_ownerTrust),
      m_recordType(g.m_recordType), m_keyLength(g.m_keyLength),
      m_publicKeyAlgorithm(g.m_publicKeyAlgorithm), m_creationDate(g.m_creationDate),
      m_expirationDate(g.m_expirationDate), m_keyID(nullptr),
      m_userID(nullptr), m_certEtc(nullptr)
{
    // Copy our string inputs.
    m_keyID = strTools::copyString(g.keyID());
    m_userID = strTools::copyString(g.userID());
    m_certEtc = strTools::copyString(g.certEtc());
}

// Construct a key from a sequence of preformatted inputs
// in the same manner that one would have received them from
// the output of gpg -k --with-colons.
// Same behavior as the copy constructor, just with explicit
// manual inputs.
GpgKey::GpgKey(const unsigned short recordType,
           const char validity,
           const unsigned short keyLength,
           const unsigned short publicKeyAlgorithm,
           const char* keyID,
           const unsigned long creationDate,
           const unsigned long expirationDate,
           const char* certificateEtc,
           const char ownerTrust,
           const char* userID)
    : m_recordType(recordType), m_validity(validity),
      m_keyLength(keyLength), m_publicKeyAlgorithm(publicKeyAlgorithm),
      m_keyID(nullptr), m_creationDate(creationDate),
      m_expirationDate(expirationDate), m_certEtc(nullptr),
      m_ownerTrust(ownerTrust), m_userID(nullptr)
{
    m_keyID = strTools::copyString(keyID);
    m_certEtc = strTools::copyString(certificateEtc);
    m_userID = strTools::copyString(userID);
}

// Takes a single line of output from `gpg -k --with-colons`
// and processes it into the data structure. O(n).
GpgKey::GpgKey(const char* input)
    : GpgKey()
{
    // Process input into a modifiable array.
    char* info = strTools::copyString(input);

    // Process our input to create our fields.
    int idx = 0;                // Processes our input string.
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

/*
 * ALL GETTER FUNCTIONS
 * Simply return the variable in question.
 */
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

unsigned long GpgKey::creationDate() const
{
    return m_creationDate;
}

unsigned long GpgKey::expirationDate() const
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
        m_keyLength = strTools::getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::PUBLIC_KEY_ALGORITHM:
        m_publicKeyAlgorithm = strTools::getNum<unsigned short>(inputString);
        break;

    case KEYFIELD::KEY_ID:
        // Copy the input string to the proper field.
        m_keyID = strTools::copyString(inputString);
        break;

    case KEYFIELD::CREATION_DATE:
        m_creationDate = strTools::getNum<unsigned long>(inputString);
        break;

    case KEYFIELD::EXPIRATION_DATE:
        m_expirationDate = strTools::getNum<unsigned long>(inputString);
        break;

    case KEYFIELD::CERTIFICATE_ETC:
        // Copy the input string to the proper field.
        m_certEtc = strTools::copyString(inputString);
        break;

    case KEYFIELD::OWNER_TRUST:
        // Copy the character.
        m_ownerTrust = inputString[0];
        break;

    case KEYFIELD::USER_ID:
        // Copy the input string to the proper field.
        m_userID = strTools::copyString(inputString);

        break;

    default:
        std::cerr << "Field not required. Skipping." << std::endl;
    }
}