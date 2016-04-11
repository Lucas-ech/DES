#include "Stream.h"

Stream::Stream() : _seek(0) {

}

Stream::Stream(const std::string &in) : _stream(in), _seek(0) {

}

Stream::~Stream() {

}

unsigned long Stream::pickNextUL() const {
    unsigned long out = 0;
    for (unsigned int i = _seek; i < _seek + 8; ++i)
    {
        out <<= 8;
        if(i < _stream.size()) {
            out += static_cast<unsigned char>(_stream[i]);
        }
    }

    return out;
}

unsigned long Stream::getNextUL() {
    unsigned long out = pickNextUL();
    _seek += 8;

    return out;
}

void Stream::setNextUL(unsigned long in) {
    for (int i = 7; i >= 0; --i)
    {
        _stream += ((in >> 8*i) & ((1 << 8) -1));
    }
}

bool Stream::iseof() const {
    return (_seek >= _stream.size());
}

void Stream::clear() {
    _stream.clear();
}


void Stream::operator >>(unsigned long &b) {
    b = getNextUL();
}

void Stream::operator <<(const unsigned long &b) {
    setNextUL(b);
}

void Stream::operator <<(const std::string &b) {
    _stream += b;
}

Stream::operator std::string() const {
    return _stream;
}
