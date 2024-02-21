#ifndef MEMORY__MEMORY_MEMORY_DECLARATION_HPP
#define MEMORY__MEMORY_MEMORY_DECLARATION_HPP

#include "Meta/Meta.hpp"

namespace Library
{

    struct Memory;


    extern Byte g_MemoryReadableBit;
    extern Byte g_MemoryWriteableBit;
    extern Byte g_MemoryExecutableBit;


    template<typename T>
    inline void CreateMemoryAtFromType(T& p_thing);
    template<typename T>
    inline void CreateMemoryAtFromType(const T& p_thing);


    inline bool MemoryIsReadable(const Memory& p_memory);
    inline bool MemoryIsWritable(const Memory& p_memory);
    inline bool MemoryIsExecutable(const Memory& p_memory);
    
    inline bool MemoryHasBits(const Memory& p_memory, const Byte& p_bits);
    //TODO: There should be a way to better express the name, taking into
    //account what the == operator does.
    inline bool MemoryHasSameContentsAsMemory(
        const Memory& p_memory1, const Memory& p_memory2
    );


    inline Byte* ExtractNumberOfBytesFromStartOfMemory(
        const Size& p_number_of_bytes,
        Memory& p_mem
    );
    inline Byte* ExtractNumberOfBytesFromEndOfMemory(
        const Size& p_number_of_bytes,
        Memory& p_mem
    );

}

#endif //MEMORY__MEMORY_MEMORY_DECLARATION_HPP