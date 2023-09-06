#include "evp_implement.h"


Cipher *cipher_init(const unsigned char *key, const unsigned char *iv, int mode)
{

    const EVP_CIPHER *cipher = EVP_aes_256_cbc();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        throw EncryptionError();
    }

    if (mode == ENCRYPT_MODE)
    {
        if (EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            throw EncryptionError();
        }
    }
    else
    {
        if (EVP_DecryptInit_ex(ctx, cipher, nullptr, key, iv) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            throw EncryptionError();
        }
    }

    Cipher *result = (Cipher *)malloc(sizeof(Cipher));
    result->cipher = cipher;
    result->ctx = ctx;
    result->mode = static_cast<CipherMode>(mode);

    return result;
}

int update(Cipher *cipher, unsigned char *inputText, int input_len, unsigned char *ouputText)
{
    int output_len;
    if (cipher->mode == ENCRYPT_MODE)
    {
        if (EVP_EncryptUpdate(cipher->ctx, ouputText, &output_len, inputText, input_len) != 1)
        {
            EVP_CIPHER_CTX_free(cipher->ctx);
            throw EncryptionError();
        }
    }
    else
    {
        if (EVP_DecryptUpdate(cipher->ctx, ouputText, &output_len, inputText, input_len) != 1)
        {
            EVP_CIPHER_CTX_free(cipher->ctx);
            std::cout <<"error at 57"<<std::endl;
            throw DecryptionError();
        }
    }
    return output_len;
}

int finalize(Cipher *cipher, unsigned char *out)
{
    int finalLen;
    if (cipher->mode == ENCRYPT_MODE)
    {
        
        if (EVP_EncryptFinal_ex(cipher->ctx, out, &finalLen) != 1)
        {
            EVP_CIPHER_CTX_free(cipher->ctx);
            throw EncryptionError();
        }
    }
    else
    {
        if (EVP_DecryptFinal_ex(cipher->ctx, out, &finalLen) != 1)
        {
            // EVP_CIPHER_CTX_free(cipher->ctx);
            // LOGI("%s","decrypted failed at line 196");
            // throw DecryptionError();
        }
    }
    EVP_CIPHER_CTX_free(cipher->ctx);
    cipher->ctx = nullptr;
    delete cipher;
    return finalLen;
}

int replace_string(unsigned char *target, int target_len)
{
    for (int i = 0; i < target_len; i++)
    {
        target[i] = 'c';
    }
    return target_len;
}
