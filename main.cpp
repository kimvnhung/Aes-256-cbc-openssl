#include "evp_implement.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <cstring>
#include <iomanip>
#include <sstream>

std::string ucharArrayToHexString(const unsigned char *data, size_t length)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0'); // Set the stream to output in hexadecimal format with leading zeros

    for (size_t i = 0; i < length; ++i)
    {
        ss << std::setw(2) << static_cast<int>(data[i]); // Convert each byte to a two-character hexadecimal representation
    }

    return ss.str();
}

int main()
{
    std::cout << "Starting encrypt/decrypt" << std::endl;

    std::string keyStr = "1231231231231231231231231231231";
    std::string ivStr = "1110001110001110001112223331112";

    std::vector<unsigned char> key(keyStr.begin(), keyStr.end());
    std::vector<unsigned char> iv(ivStr.begin(), ivStr.end());
    std::cout << "key : " << key.data() << " iv : " << iv.data() << std::endl;

    Cipher *cipher_encr = cipher_init(key.data(), iv.data(), ENCRYPT_MODE);

    unsigned char *plainText = (unsigned char *)"Hellworwwwwơldeđâsdasdsadasdasdasdasdasqweqwe";
    unsigned char *cipher_text = (unsigned char *)malloc(512 * sizeof(unsigned char));
    int input_len = strlen((char *)plainText);
    unsigned char *finalizeStr = (unsigned char *)malloc(16 * sizeof(unsigned char));

    std::cout << "check cipher pointer input_len : " << input_len << std::endl;

    int updateRs = update(cipher_encr, plainText, input_len, cipher_text);
    std::cout << updateRs << std::endl;
    int finalizeRs = finalize(cipher_encr, finalizeStr);
    std::cout << finalizeRs << std::endl;
    std::memcpy(cipher_text + updateRs, finalizeStr, finalizeRs);

    std::cout << "plaintext : " << plainText << std::endl;
    std::cout << "cipherText : " << ucharArrayToHexString(cipher_text, updateRs + finalizeRs) << std::endl;

    Cipher *cipher_decr = cipher_init(key.data(), iv.data(), DECRYPT_MODE);
    unsigned char *storageText = (unsigned char *)malloc(512 * sizeof(unsigned char));
    int updateDcrRs = update(cipher_decr, cipher_text, updateRs + finalizeRs, storageText);
    std::cout << "updateDcrRs : " << updateDcrRs << std::endl;
    unsigned char *finalizeStorageDcr = (unsigned char *)malloc(16 * sizeof(unsigned char));
    int finalizeDcrRs = finalize(cipher_decr, finalizeStorageDcr);
    std::cout << "finaliszeDcrRs : " << finalizeDcrRs << std::endl;

    std::memcpy(storageText + updateDcrRs, finalizeStorageDcr, finalizeDcrRs);

    unsigned char* result = (unsigned char*)malloc((updateDcrRs+finalizeDcrRs)*sizeof(unsigned char));
    std::memcpy(result,storageText,updateDcrRs+finalizeDcrRs);

    std::cout << "decrypted text : " << result << std::endl;

    return 0;
}