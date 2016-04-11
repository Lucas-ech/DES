#ifndef KEY_H
#define KEY_H

#include <string>
#include <stdexcept>
#include "Utils.h"

class Key
{
    public:
        /**
         * @brief Generates a key from string
         * 
         * @param key key string
         */
        explicit Key(const std::string &key);

        /**
         * @brief Creates a key from the integer
         * 
         * @param key key
         */
        explicit Key(unsigned long key);

        /**
         * @brief Key destructor
         */
        ~Key();

        /**
         * @brief Give the internal key
         * @return key
         */
        unsigned long get() const;
    
    private:
        unsigned long _key;

};

#endif // KEY_H