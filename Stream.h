#ifndef STREAM_H
#define STREAM_H

#include <string>
#include <stdexcept>
#include "Utils.h"
#include "Key.h"

class Stream
{
    public:
        /**
         * @brief Creates an empty stream
         */
        Stream();

        /**
         * @brief Creates a stream from a string
         * 
         * @param in input string
         */
        explicit Stream(const std::string &in);

        /**
         * @brief Destructor
         */
        ~Stream();

        /**
         * @brief Gives a 64 bits block according to the seek
         * @return Block
         */
        unsigned long pickNextUL() const;

        /**
         * @brief Gives a 64 bits block according to the seek and increment it
         * @return Block
         */
        unsigned long getNextUL();

        /**
         * @brief Appends the stream with 64 bits
         * 
         * @param in input number
         */
        void setNextUL(unsigned long in);

        /**
         * @brief Checks if the end of the stream has been reached.
         * @return boolean
         */
        bool iseof() const;

        /**
         * @brief Clears the stream
         */
        void clear();

        /**
         * @brief Gives a 64 bits block according to the seek and increment it
         * 
         * @param b reference to store the extracted value
         */
        void operator >>(unsigned long &b);

        /**
         * @brief Appends the stream with 64 bits
         * 
         * @param b reference of the integer value
         */
        void operator <<(const unsigned long &b);

        /**
         * @brief Appends the stream with 64 bits
         * 
         * @param b reference of the string value
         */
        void operator <<(const std::string &b);

        /**
         * @brief Allows to cast to a std::string
         * @return The stream into a std::string
         */
        explicit operator std::string() const;

    private:
        std::string _stream;
        std::size_t _seek;
};

#endif // STREAM_H