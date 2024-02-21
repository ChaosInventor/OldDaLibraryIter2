#ifndef META__META_META_HPP
#define META__META_META_HPP

#include <stddef.h> //For size_t

//TODO: Should this module really be called meta? is there a better name for it?

namespace Library
{

    using Byte = unsigned char;

    extern const Byte BYTE_MINIMUM;
    extern const Byte BYTE_MAXIMUM;

    extern const Byte BITS_PER_BYTE;


    using Size = size_t;

    extern const Size SIZE_MINIMUM;
    extern const Size SIZE_MAXIMUM;

}

#endif //META__META_META_HPP
