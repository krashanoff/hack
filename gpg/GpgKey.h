#ifndef GPGKEY_H
#define GPGKEY_H

#include <vector>

enum KEYFIELD
{
    RECORDTYPE = 0,
    VALIDITY,
    KEYLENGTH,
    PUBLICKEYALGORITHM,
    KEYID,
    CREATIONDATE,
    EXPIRATIONDATE,
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
    FIELDCOUNT = 20
};

/*
GpgKeyComplete

A **COMPLETE** record of the key. Contains information
for all **21** potential key fields, as well as extended
trust information, etc. For information on these fields
and how they are used, please reference this thread:
https://git.gnupg.org/cgi-bin/gitweb.cgi?p=gnupg.git;a=blob_plain;f=doc/DETAILS
*/
class GpgKeyComplete
{
public:
    GpgKeyComplete();
    GpgKeyComplete(const char*);
    ~GpgKeyComplete();

    char* operator[](const KEYFIELD);

    char* getID();
    char* exportKeys();

    void print() const;

private:
    std::vector<char*> m_fields;
};

#endif