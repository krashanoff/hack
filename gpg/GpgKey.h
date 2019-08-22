#ifndef GPGKEY_H
#define GPGKEY_H

// Defines all fields.
enum KEYFIELD
{
    RECORD_TYPE = 0,
    VALIDITY,
    KEY_LENGTH,
    PUBLIC_KEY_ALGORITHM,
    KEY_ID,
    CREATION_DATE,
    EXPIRATION_DATE,
    CERTIFICATE_ETC,  /* Certificate S/N, UID hash, trust signature info */
    OWNER_TRUST,
    USER_ID,
    SIGNATURE_CLASS,
    SIGNATURE_TYPE,
    KEY_CAPABILITIES,
    ISSUER_CERT_FINGERPRINT,
    FLAG_FIELD,
    TOKEN_SN,
    HASH_ALGORITHM,
    CURVE_NAME,
    COMPLIANCE_FLAGS,
    LAST_UPDATE,
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

    unsigned short recordType() const;
    char validity() const;
    unsigned short keyLength() const;
    unsigned short publicKeyAlgorithm() const;
    const char* keyID() const;
    unsigned short creationDate() const;
    unsigned short expirationDate() const;
    const char* certEtc() const;
    char ownerTrust() const;
    const char* userID() const;

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