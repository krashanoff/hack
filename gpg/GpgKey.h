#ifndef GPGKEY_H
#define GPGKEY_H

/*
GpgKey

A basic but functional record of keys. Contains most fields
required for basic functionality.

PRESENTLY INCOMPLETE.
*/
class GpgKey
{
public:
    GpgKey();
    virtual ~GpgKey();

    char* getID();
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
    GpgKeyComplete();
    virtual ~GpgKeyComplete();

    char* getID();
    char* exportKeys();

private:
    char* m_recordType;
    char* m_validity;
    int m_keyLength;
    char* m_pubKeyAlgorithm;
    char* m_keyID;
    long m_creationDate;
    long m_expirationDate;
    long m_trustSignatures;
    char* m_userID;
    short m_signatureClass;
    char m_sigType;
    char* m_keyCapabilities;
    long m_issuerCertFingerprint;
    char m_flagField;
    short m_hashAlgorithm;
    long m_lastUpdate;
};

#endif