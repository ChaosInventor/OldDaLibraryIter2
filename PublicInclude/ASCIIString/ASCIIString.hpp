#ifndef ASCII_STRING__ASCII_STRING_ASCII_STRING_HPP
#define ASCII_STRING__ASCII_STRING_ASCII_STRING_HPP

#include "Array/Array.hpp"

namespace Library
{

    struct ASCIIString
    {
        
        //TODO:

        ASCIIString(ASCIIString&&);

        ASCIIString(const char*);

        operator Array<char>();

        bool operator==(const char*);

    };
    

    bool operator==(const char*, const ASCIIString&);

}

#endif //ASCII_STRING__ASCII_STRING_ASCII_STRING_HPP
