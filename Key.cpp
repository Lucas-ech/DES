#include "Key.h"

Key::Key(const std::string &key) {
    if(key.size() != 16) {
        throw std::runtime_error("Invalid key length");
    }

    _key = Utils::hexString(key);
}

Key::Key(unsigned long key) {
    _key = key;
}

Key::~Key() {

}

unsigned long Key::get() const {
    return _key;
}
