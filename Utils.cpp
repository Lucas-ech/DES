#include "Utils.h"

unsigned long Utils::permute(unsigned long in, const std::vector<unsigned char> &matrix, unsigned int inBit) {
    if(matrix.size() > 64) {
        throw std::runtime_error("Utils::permute: Matrix permutation result is bigger than an unsigned long.");
    }
    unsigned long out = 0;
    for (unsigned int i = 0; i < matrix.size(); ++i)
    {
        out <<= 1;
        if((in & (1ul << (64 - (64 - inBit) - matrix[i]))) != 0) {
            out |= 1;
        }
    }

    return out;
}

unsigned long Utils::circularLeftShift(unsigned long in, unsigned int bitLen) {
    unsigned char lastBitVal = (in & (1ul << (bitLen - 1))) != 0 ? 1 : 0;

    in = (in << 1) & ((1ul << bitLen) - 1);
    in |= lastBitVal;

    return in;
}        

unsigned char Utils::hexChar(const unsigned char c) {
    if(c >= '0' && c <= '9') {
        return c - '0';
    }

    if(c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }

    if(c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }

    throw std::runtime_error("Invalid character");
}

unsigned long Utils::hexString(const std::string &in) {
    if(in.size() > 16) {
        throw std::runtime_error("Too long string to convert in unsigned long");
    }
    unsigned long out = 0;
    for (unsigned int i = 0; i < in.size(); ++i)
    {
        out <<= 4;
        out += hexChar(in[i]) & 0b1111;
    }

    return out;
}