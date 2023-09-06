#include <exception>
#include <iostream>

#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

enum CipherMode
{
    DECRYPT_MODE = 0,
    ENCRYPT_MODE = 1
};

class SecretError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Secret specific error";
    }
};

class NoDataError : public SecretError
{
public:
    const char *what() const noexcept override
    {
        return "No data to encrypt/decrypt";
    }
};

class DecryptionError : public SecretError
{
public:
    const char *what() const noexcept override
    {
        return "Decryption failed";
    }
};

class EncryptionError : public SecretError
{
public:
    const char *what() const noexcept override
    {
        return "Encryption failed";
    }
};

class PasswordError : public SecretError
{
public:
    const char *what() const noexcept override
    {
        return "Problem with password(s)";
    }
};

int encrypt(unsigned char *plaintext, unsigned char *ciphertext);

struct Cipher
{
    const EVP_CIPHER *cipher;
    EVP_CIPHER_CTX *ctx;
    CipherMode mode;
};

Cipher *cipher_init(const unsigned char *key, const unsigned char *iv, int mode);

int update(Cipher *cipher, unsigned char *inputText, int input_len, unsigned char *ouputText);

int finalize(Cipher *cipher, unsigned char *out);

int replace_string(unsigned char *target, int target_len);