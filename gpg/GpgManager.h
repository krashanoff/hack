#ifndef GPGMANAGER_H
#define GPGMANAGER_H

#define SUPERGPGKEY(T) typename T, typename std::enable_if<std::is_base_of<GpgKey, T>::value>::type* = nullptr

#include <fstream>
#include <type_traits>

class GpgKeyComplete;

/*
GpgManager

Returns a unit through which GnuPG may be managed.
One can:
* Retrieve keys
* Sign
* Verify
* Encrypt files
* Decrypt files
* Read an encrypted file, then automatically delete
  the source
directly from a traditional C/C++ program, assuming
that the system has gpg installed.
*/

class GpgManager
{
public:
	GpgManager();
	virtual ~GpgManager();

	GpgKeyComplete* getKeys() const;
	GpgKeyComplete* getSecretKeys() const;

	bool sign(const char* filePath, bool clearSign = 0);
	bool verify(const char* key);

	FILE* decryptThenRead(const char* inPath) const;
	FILE* decrypt(const char* inPath, const char* outPath) const;
	FILE* encrypt(const char* inPath, const char* outPath, const char* recipientID, bool armored = 0) const;

private:
	GpgKeyComplete** m_db;
	short m_size;
};

#endif