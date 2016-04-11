#include "SubKeyGenerator.h"

SubKeyGenerator::SubKeyGenerator(const Key &key) {
    unsigned long keyN = key.get();

    //First permutation with PC⁻¹
    //Removing parity bits results in 56 bits key
    keyN = Utils::permute(keyN, _pc1);

    //Cut keyN in two parts of 28 bits
    unsigned long l, r;
    l = keyN >> 28;
    r = keyN & ((1 << 28) - 1);

    //Generating subKeys with circular left shift
    for (int i = 0; i < 16; ++i)
    {

        for (int j = 0; j < _ls[i]; ++j)
        {
            l = Utils::circularLeftShift(l, 28);
            r = Utils::circularLeftShift(r, 28);
        }

        _subkeys[i] = Utils::permute(((l << 28) + r), _pc2, 56);
    }

}

SubKeyGenerator::~SubKeyGenerator() {

}

unsigned long SubKeyGenerator::get(std::size_t index) const {
    if(index >= _subkeys.size()) {
        throw std::runtime_error("SubKeyGenerator::get: index out of range.");
    }

    return _subkeys[index];
}