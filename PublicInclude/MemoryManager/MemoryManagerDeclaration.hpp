#ifndef MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DECLARATION_HPP
#define MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DECLARATION_HPP

#include "Memory/MemoryDeclaration.hpp"
#include "Callback/Callback.hpp"
#include "Meta/Meta.hpp"

namespace Library
{

    struct MemoryManager;
    

    using MemoryManagerAllocateFunction = void (*) (
        Memory& p_mem,
        MemoryManager& p_manager,
        Callback& p_allocateError
    );
    
    using MemoryManagerReSizeFunction = void (*) (
        Memory& p_mem,
        MemoryManager& p_manager,
        const Size& p_size,
        Callback& p_reSizeError
    );
    using MemoryManagerRePermissionFunction = void (*) (
        Memory& p_mem,
        MemoryManager& p_manager,
        const Byte& p_permissions,
        Callback& p_rePermissionError
    );

    using MemoryManagerDeallocateFunction = void (*) (
        Memory& p_mem,
        MemoryManager& p_manager
    );


    extern MemoryManager g_DefaultMemoryManager;
    
    extern Callback g_DefaultAllocateError;
    extern Callback g_DefaultReSizeError;
    extern Callback g_DefaultRePermissionError;

}

#endif //MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DECLARATION_HPP