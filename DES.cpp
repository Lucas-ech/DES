#include "DES.h"

DES::DES(const std::string &data, const Key &key, unsigned long iv) : _key(key), _iv(iv), _data(data) {
    if(iv != 0) {
        _mode = Mode::CBC;
    } else {
        _mode = Mode::ECB;
    }
}

std::string DES::encrypt() {
    return crypt(Action::ENCRYPT);
}

std::string DES::decrypt() {
    return crypt(Action::DECRYPT);
}

void DES::setKey(const Key &key) {
    _key = key;
}

void DES::setData(const std::string &data) {
    _data = data;
}

void DES::setIv(const unsigned long iv) {
    _iv = iv;
}

void DES::setMode(Mode mode) {
    _mode = mode;
}

std::string DES::crypt(Action a) {
    unsigned long block, permuted, l, r, iv = _iv;
    Stream stream(_data), out;

    SubKeyGenerator subkeys(_key);

    while (!stream.iseof())
    {
        stream >> block;

        if(_mode == Mode::CBC) {
            block ^= iv;
        }

        permuted = Utils::permute(block, matrix::_ip);

        l = permuted >> 32;
        r = permuted & ((1ul << 32) - 1);

        block = rounds(l, r, subkeys, a);

        if(_mode == Mode::CBC) {
            iv = block;
        }

        out << block;
    }

    return static_cast<std::string>(out);
}


unsigned long DES::rounds(unsigned long l, unsigned long r, const SubKeyGenerator &subkeys, Action a) {
    unsigned long c;
    for (int it = 0; it < 16; ++it)
    {
        //Cipher function
        if(a == Action::DECRYPT) {
            c = cipher(r, subkeys.get(15 - it));
        } else {
            c = cipher(r, subkeys.get(it));
        }

        //XOR with Li-1
        c ^= l;

        l = r;
        r = c;
    }

    unsigned long out;
    out = (r << 32) + l;
    out = Utils::permute(out, matrix::_ipInv);

    return out;
}

unsigned long DES::cipher(unsigned long r, unsigned long subKey) {
    //Operate an expansion permutation
    r = Utils::permute(r, matrix::_e, 32);

    //XOR with the subkey
    r ^= subKey;

    //S-Boxes
    unsigned long final = sBoxes(r);

    //Permutation and XOR
    final = Utils::permute(final, matrix::_p, 32);

    return final;
}

unsigned long DES::sBoxes(unsigned long r) {
    unsigned int line, column;
    unsigned long out = 0;
    unsigned char block;
    for (int i = 7; i >= 0; --i)
    {
        block = (r >> i*6) & 0b111111;

        line = ((block >> 5) << 1) + (block & 0b1);
        column = (block & 0b011110) >> 1;

        out <<= 4;
        out += SBoxes::box[7 - i][16 * line + column];
    }

    return out;
}
