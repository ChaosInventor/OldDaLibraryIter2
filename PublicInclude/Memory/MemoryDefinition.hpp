#ifndef MEMORY__MEMORY_MEMORY_DEFINITION_HPP
#define MEMORY__MEMORY_MEMORY_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "MemoryDeclaration.hpp"
#include "Meta/Meta.hpp"

#define ValidateMemoryLocation(p_mem)       \
    Assert((p_mem).m_Location != nullptr,   \
    "Memory's location is null. Cannot use it")
#define ValidateMemorySize(p_mem, p_size)   \
    Assert((p_mem).m_Size < (p_size),       \
    "Memory's size is less than the expected " << (p_size))
#define ValidateMemoryPermissions(p_mem, p_permissions) \
    Assert(MemoryHasBits((p_mem), (p_permissions)),     \
    "Memory does not have the required permissions (" << (p_permissions) << ")")


namespace Library
{

    struct Memory
    {
    
        Byte* m_Location;
        Size m_Size;
        Byte m_Permissions: 3;


        Memory():
        m_Location(nullptr),
        m_Size(0),
        m_Permissions(0)
        { }
        Memory(const Memory& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size),
        m_Permissions(p_other.m_Permissions)
        { }
        Memory(Memory&& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size),
        m_Permissions(p_other.m_Permissions)
        {
            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
            p_other.m_Permissions = 0;
        }

        Memory(const Size& p_size, const Byte& p_permissions):
        m_Location(nullptr),
        m_Size(p_size),
        m_Permissions(p_permissions)
        { }
        Memory(Byte* const& p_location, const Size& p_size, const Byte& p_permissions):
        m_Location(p_location),
        m_Size(p_size),
        m_Permissions(p_permissions)
        { }


        Memory& operator=(const Memory& p_other)
        {
        
            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;
            m_Permissions = p_other.m_Permissions;

            return *this;
        
        }
        Memory& operator=(Memory&& p_other)
        {
        
            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;
            m_Permissions = p_other.m_Permissions;

            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
            p_other.m_Permissions = 0;

            return *this;
        
        }

        Byte& operator[](const Size& p_index)
        {
            return m_Location[p_index];
        }
        const Byte& operator[](const Size& p_index) const
        {
            return m_Location[p_index];
        }


        bool operator==(const Memory& p_other) const
        {
            return 
                m_Location == p_other.m_Location
                &&
                m_Size == p_other.m_Size
                &&
                m_Permissions == p_other.m_Permissions;
        }
        bool operator!=(const Memory& p_other) const
        {
            return !(*this == p_other);
        }

    };


    template<typename T>
    void CreateMemoryAtFromType(Memory& p_memory, T& p_thing)
    {
        p_memory.m_Location = (Byte*)&p_thing;
        p_memory.m_Size = sizeof(T);
        p_memory.m_Permissions = g_MemoryReadableBit | g_MemoryWriteableBit;
    }
    template<typename T>
    void CreateMemoryAtFromType(Memory& p_memory, const T& p_thing)
    {
        p_memory.m_Location = (Byte*)&p_thing;
        p_memory.m_Size = sizeof(T);
        p_memory.m_Permissions = g_MemoryReadableBit;
    }


    inline bool MemoryIsReadable(const Memory& p_memory)
    {
        return (p_memory.m_Permissions & g_MemoryReadableBit) == g_MemoryReadableBit;
    }
    inline bool MemoryIsWritable(const Memory& p_memory)
    {
        return (p_memory.m_Permissions & g_MemoryWriteableBit) == g_MemoryWriteableBit;
    }
    inline bool MemoryIsExecutable(const Memory& p_memory)
    {
        return (p_memory.m_Permissions & g_MemoryExecutableBit) == g_MemoryExecutableBit;
    }
    
    inline bool MemoryHasBits(const Memory& p_memory, const Byte& p_bits)
    {
        return (p_memory.m_Permissions & p_bits) == p_bits;
    }
    //TODO: There should be a way to better express the name, taking into
    //account what the == operator does.
    inline bool MemoryHasSameContentsAsMemory(
        const Memory& p_memory1, const Memory& p_memory2
    )
    {

        ValidateMemoryPermissions(p_memory1, g_MemoryReadableBit);
        ValidateMemoryPermissions(p_memory2, g_MemoryReadableBit);


        if(p_memory1.m_Size != p_memory2.m_Size)
        {
            return false;
        }

        //Note: in the case where there is a null m_Location in either memory,
        //if both have a null the first if will pass and the for loop will be
        //skiped, in the case where one has a null and the other does not, the
        //first if returns true.
        for(Size i = 0; i < p_memory1.m_Size; ++i)
        {
            if(p_memory1[i] != p_memory2[i])
            {
                return false;
            }
        }

        return true;

    }


    inline void WriteZerosToMemory(Memory& p_memory)
    {

        Assert(MemoryIsWritable(p_memory), "Cannot write to unwritable memory");


        for(Size i = 0; i < p_memory.m_Size; ++i)
        {
            p_memory.m_Location[i] = 0;
        }

    }

    inline Byte* ExtractNumberOfBytesFromStartOfMemory(
        const Size& p_number_of_bytes,
        Memory& p_mem
    )
    {

        ValidateMemoryLocation(p_mem);
        ValidateMemorySize(p_mem, p_number_of_bytes);


        Byte* l_returnValue = p_mem.m_Location;

        p_mem.m_Location += p_number_of_bytes;
        p_mem.m_Size -= p_number_of_bytes;

        return l_returnValue;

    }
    inline Byte* ExtractNumberOfBytesFromEndOfMemory(
        const Size& p_number_of_bytes,
        Memory& p_mem
    )
    {

        ValidateMemoryLocation(p_mem);
        ValidateMemorySize(p_mem, p_number_of_bytes);


        Byte* l_returnValue = (p_mem.m_Location + p_mem.m_Size) - p_number_of_bytes;

        p_mem.m_Size -= p_number_of_bytes;

        return l_returnValue;

    }


}

#endif //MEMORY__MEMORY_MEMORY_DEFINITION_HPP