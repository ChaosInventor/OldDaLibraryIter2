#include "MemoryManager/MemoryManager.hpp"

#include "Callback/Callback.hpp"
#include "Memory/Memory.hpp"

#include <stdlib.h>

namespace Library
{

    //HACK: Make proper default memory manager. this one just uses malloc.
    void AllocateMemoryFromMemoryManagerCallbackOnFailure_Default(
        Memory& p_mem,
        MemoryManager& p_memManager,
        Callback& p_failure
    )
    {

        ValidateMemoryManager(p_memManager);
        ValidateCallback(p_failure);

        if(MemoryHasBits(p_mem, g_MemoryExecutableBit))
        {
            Warn("Executable permission is not implemented yet");
        }


        if(p_mem.m_Size == 0)
        {
            p_mem.m_Location = nullptr;
            return;
        }

        p_mem.m_Location = (Byte*)malloc(p_mem.m_Size);
        if(p_mem.m_Location == nullptr)
        {
            p_failure();
        }

    }

    void ReSizeMemoryForwardFromMemoryManagerToSizeCallbackOnFailure(
        Memory& p_mem,
        MemoryManager& p_manager,
        const Size& p_size,
        Callback& p_reSizeError
    )
    {
        
        ValidateCallback(p_reSizeError);

        if(MemoryHasBits(p_mem, g_MemoryExecutableBit))
        {
            Warn("Executable permission is not implemented yet");
        }


        Byte* l_newLocation = (Byte*)realloc(p_mem.m_Location, p_size);
        if(l_newLocation == nullptr)
        {
            p_reSizeError();
            return;
        }

        p_mem.m_Location = l_newLocation;
        p_mem.m_Size = p_size;

    }
    void ReSizeMemoryBackwardFromMemoryManagerToSizeCallbackOnFailure(
        Memory& p_mem,
        MemoryManager& p_manager,
        const Size& p_size,
        Callback& p_reSizeError
    )
    {
        
        ValidateCallback(p_reSizeError);
        
        if(MemoryHasBits(p_mem, g_MemoryExecutableBit))
        {
            Warn("Executable permission is not implemented yet");
        }


        //HACK: This ENTIRE function is one gagantic hack and i hate it.
        if(p_size < p_mem.m_Size)
        {
            Size l_lostBytes = p_mem.m_Size - p_size;
            for(Size i = 0, j = l_lostBytes; j < p_mem.m_Size; ++i, j++)
            {
                p_mem.m_Location[i] = p_mem.m_Location[j];
            }
        }

        Byte* l_newLocation = (Byte*)realloc(p_mem.m_Location, p_size);
        if(l_newLocation == nullptr)
        {
            p_reSizeError();
            return;
        }

        if(p_size > p_mem.m_Size)
        {
            for(Size i = p_mem.m_Size - 1, j = p_size - 1; i-- > 0; --j)
            {
                p_mem.m_Location[j] = p_mem.m_Location[i];
            }
        }

        p_mem.m_Location = l_newLocation;
        p_mem.m_Size = p_size;

    }
    void RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure_Default(
        Memory& p_mem,
        MemoryManager& p_manager,
        const Byte& p_permissions,
        Callback& p_rePermissionError
    )
    {
        //FIXME: Can't implement with malloc functions
        Warn("Not implemented");
        return;
    }


    void DeallocateMemoryFromMemoryManager_Default(
        Memory& p_mem,
        MemoryManager& p_memManager
    )
    {
        free(p_mem.m_Location);
    }


    MemoryManager g_DefaultMemoryManager(
        nullptr,
        AllocateMemoryFromMemoryManagerCallbackOnFailure_Default,
        ReSizeMemoryForwardFromMemoryManagerToSizeCallbackOnFailure,
        ReSizeMemoryBackwardFromMemoryManagerToSizeCallbackOnFailure,
        RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure_Default,
        DeallocateMemoryFromMemoryManager_Default
    );


    #ifndef DO_NOT_DEFINE_DEFAULT_ALLOCATION_ERROR_CALLBACK
    Callback g_DefaultAllocationError(nullptr, NullCallback);
    #endif

    #ifndef DO_NOT_DEFINE_DEFAULT_RE_SIZE_ERROR_CALLBACK
    Callback g_DefaultReSizeError(nullptr, NullCallback);
    #endif

    #ifndef DO_NOT_DEFINE_DEFAULT_RE_PERMISSION_ERROR_CALLBACK
    Callback g_DefaultRePermissionError(nullptr, NullCallback);
    #endif

}
