#ifndef DES_H
#define DES_H

#include <string>
#include "Utils.h"
#include "Stream.h"
#include "Key.h"
#include "SubKeyGenerator.h"
#include "SBoxes.h"

class DES
{
    public:
        enum class Action {ENCRYPT, DECRYPT};
        enum class Mode {ECB, CBC};
        
        /**
         * @brief DES constructor
         * 
         * @param plain plaintext to encrypt
         * @param key Key used to encrypt the plaintext
         * @param iv Initialization vector (Only for CBC Mode)
         */
        DES(const std::string &data, const Key &key, unsigned long iv = 0x0);

        ~DES() = default;

        /**
         * @brief Encrypts plaintext with DES algorithm
         * @return Cipher produced by DES encryption
         */
        std::string encrypt();

        /**
         * @brief Decrypts cipher width DES algorithm
         * @return Plaintext produced by DES decryption
         */
        std::string decrypt();

        /**
         * @brief Sets the DES key
         * 
         * @param key key
         */
        void setKey(const Key &key);

        /**
         * @brief Sets data that will be encrypted or decrypted
         * 
         * @param data Data
         */
        void setData(const std::string &data);

        /**
         * @brief Sets the initialization vector
         * 
         * @param iv Initialization vector
         */
        void setIv(const unsigned long iv);

        /**
         * @brief Sets the encryption mode (Only ECB and CBC are supported)
         * 
         * @param mode Mode
         */
        void setMode(Mode mode);

    private:
        /**
         * @brief Prepares data to be encrypted or decrypted according to Action and send it to rounds
         * 
         * @param a Used to know if we encrypt or decrypt
         * @return Encrypted or decrypted data
         */
        std::string crypt(Action a);

        /**
         * @brief Realizes the 16 DES's rounds
         * 
         * @param l Left part of the permuted data
         * @param r Right part of the permuted data
         * @param subkeys Pre-generated subkeys from the main key
         * @param a Used to know if we encrypt or decrypt
         * @return Block encrypted or decrypted
         */
        unsigned long rounds(unsigned long l, unsigned long r, const SubKeyGenerator &subkeys, Action a);

        /**
         * @brief main DES algorithm
         * 
         * @param r Right part data from rounds
         * @param subKey Subkey
         * 
         * @return Result of one round iteration
         */
        unsigned long cipher(unsigned long r, unsigned long subKey);
        
        /**
         * @brief Computes data to the eight DES's S-Boxes
         * 
         * @param r data
         * @return Computed data of 32 bits
         */
        unsigned long sBoxes(unsigned long r);

        Key _key;
        Mode _mode;
        unsigned long _iv;
        std::string _data;

};

/**
 * DES's matrix used for permutations
 */
namespace matrix {
    const std::vector<unsigned char> _ip = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    const std::vector<unsigned char> _ipInv = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
    const std::vector<unsigned char> _e = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
    const std::vector<unsigned char> _p = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
};

#endif // DES_H