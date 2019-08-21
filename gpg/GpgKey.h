#ifndef GPGKEY_H
#define GPGKEY_H

#include <vector>

// Defines all fields.
enum KEYFIELD
{
    RECORDTYPE = 0,
    VALIDITY,
    KEYLENGTH,
    PUBLICKEYALGORITHM,
    KEYID,
    CREATIONDATE,
    EXPIRATIONDATE,
    CERTIFICATE_ETC,  /* Certificate S/N, UID hash, trust signature info */
    OWNERTRUST,
    USERID,
    SIGNATURECLASS,
    SIGNATURETYPE,
    KEYCAPABILITIES,
    ISSUERCERTFINGERPRINT,
    FLAGFIELD,
    TOKENSN,
    HASHALGORITHM,
    CURVENAME,
    COMPLIANCEFLAGS,
    LASTUPDATE,
    ORIGIN,
    COMMENT,
    EXTRA,
    FIELDCOUNT = 21
};

// Defines all record types.
enum RECORDTYPE
{
    TRU = 0,
    PUB,
    FPR,
    UID,
    SUB
    // TODO: remainder of types.
};

/* GpgKey
 * The most basic type. Allows for most basic operations
 * and retrieval of basic fields. Allows for retrieval of
 * its GpgKeyComplete type counterpart through the getComplete
 * function.
 */
class GpgKey
{
public:
    GpgKey();

    // Manual construction. Arguments are in the same
    // order that they would appear in the output of
    // gpg -k --with-colons.
    GpgKey(const unsigned short,
           const char,
           const unsigned short,
           const unsigned short,
           const char*,
           const unsigned int,
           const unsigned int,
           const char*,
           const char,
           const char*);

    GpgKey(const char*);
    virtual ~GpgKey();

    const char* operator[](const KEYFIELD) const;

    void print() const;

private:
    // Variables are laid out for memory optimization.
    char m_validity;
    char m_ownerTrust;
    unsigned short m_recordType;
    unsigned short m_keyLength;
    unsigned short m_publicKeyAlgorithm;
    unsigned int m_creationDate;
    unsigned int m_expirationDate;
    char* m_keyID;
    char* m_userID;
    char* m_certEtc;

    // Utility functions.
    void createInfo(const char*, const int);

    template<typename T>
    T getNum(const char*);
};

/*
GpgKeyComplete

A **COMPLETE** record of the key. Contains information
for all **21** potential key fields, as well as extended
trust information, etc. For information on these fields
and how they are used, please reference this thread:
https://git.gnupg.org/cgi-bin/gitweb.cgi?p=gnupg.git;a=blob_plain;f=doc/DETAILS
*/
class GpgKeyComplete : public GpgKey
{
public:
    GpgKeyComplete(const char*);
    ~GpgKeyComplete();

    const char* operator[](const KEYFIELD) const;

    const char* getID() const;

    void print() const;

private:
    // TBD: All of these field types are yet to be decided on.
    char* m_signatureClass;
    char* m_signatureType;
    char* m_keyCapabilities;
    char* m_issuerCertFingerprint;
    char* m_flagField;
    char* m_tokenSN;
    char* m_hashAlgorithm;
    char* m_curveName;
    char* m_complianceFlags;
    unsigned long m_lastUpdated;
    char* m_origin;
    char* m_comment;
};

#endif