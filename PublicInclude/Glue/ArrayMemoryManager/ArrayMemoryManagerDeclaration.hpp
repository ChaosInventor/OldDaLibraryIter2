#ifndef ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DECLARATION_HPP
#define ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DECLARATION_HPP

#include "Array/ArrayDeclaration.hpp"
#include "MemoryManager/MemoryManagerDeclaration.hpp"

namespace Library::Glue
{

    template<typename T>
    void CreateArrayAtWithSizeUsingMemoryManagerCallbackOnAllocationErrorCallbackOnOverflow(
        Array<T>& p_array, const Size& p_withSize,
        MemoryManager& p_usingMemManager,
        Callback& p_allocationError, Callback& p_overflow
    );


    template<typename T>
    void
    ReSizeArrayToSizeUsingMemoryManagerUsingMemoryManagerReSizeFunctionCallbackOnAllocationErrorCallbackOnOverflow(
        Array<T>& p_array, const Size& p_toSize,
        MemoryManager& p_usingMemManager,
        MemoryManagerReSizeFunction& p_reSizeFunctionToUse,
        Callback& p_reSizeError, Callback& p_overflow
    );


    template<typename T>
    void DestroyArrayUsingMemoryManager(
        Array<T>& p_array, MemoryManager& p_usingMemManager
    );

}

#endif//ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DECLARATION_HPP