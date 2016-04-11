#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdexcept>

class Utils
{
    public:
        /**
         * @brief Permutes an integer thanks to a matrix
         * 
         * @param in Input integer
         * @param matrix Permutation matrix
         * @param inBit Number of bits of the input integer (Default: 64)
         * @return Permuted value
         */
        static unsigned long permute(unsigned long in, const std::vector<unsigned char> &matrix, unsigned int inBit = 64);    

        /**
         * @brief Realizes a circular left shift
         * 
         * @param in input integer
         * @param bitLen Number of bits of the input integer
         * 
         * @return Shifted value
         */    
        static unsigned long circularLeftShift(unsigned long in, unsigned int bitLen);

        /**
         * @brief Converts an hexadecimal base char into an integer
         * 
         * @param c hexadecimal char
         * @return integer
         */
        static unsigned char hexChar(const unsigned char c);

        /**
         * @brief Converts an hexadecimal base string into an integer
         * 
         * @param in hexadecimal string
         * @return integer
         */
        static unsigned long hexString(const std::string &in);
    
};

#endif // UTILS_H