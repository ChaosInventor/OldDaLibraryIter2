#include <Meta/Meta.hpp>

#include <stdint.h> //For UINT8_MAX and SIZE_MAXIMUM
#include <limits.h> //For CHAR_BIT

namespace Library
{

    const Byte BYTE_MINIMUM = 0;
    const Byte BYTE_MAXIMUM = UINT8_MAX;

    const Byte BITS_PER_BYTE = CHAR_BIT;


    const Size SIZE_MINIMUM = 0;
    const Size SIZE_MAXIMUM = SIZE_MAX;

}