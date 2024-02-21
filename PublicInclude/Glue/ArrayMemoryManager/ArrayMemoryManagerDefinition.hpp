#ifndef ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DEFINITION_HPP
#define ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DEFINITION_HPP

#include "ArrayMemoryManagerDeclaration.hpp"

#include "Array/ArrayDefinition.hpp"
#include "MemoryManager/MemoryManagerDefinition.hpp"
#include "Callback/Callback.hpp"
#include "Memory/Memory.hpp"

namespace Library::Glue
{

    template<typename T>
    void CallbackCreateArrayAtWithSizeUsingMemoryManagerCallbackOnAllocationErrorCallbackOnOverflow(Callback& p_callback)
    {

        void** l_dataPack = (void**)p_callback.m_State;

        Array<T>& l_outputArray = *((Array<T>*)l_dataPack[0]);
        Callback& l_neededCallback = *((Callback*)l_dataPack[1]);

        l_outputArray = Array<T>();

        l_neededCallback();

    }
    template<typename T>
    void CreateArrayAtWithSizeUsingMemoryManagerCallbackOnAllocationErrorCallbackOnOverflow(
        Array<T>& p_array, const Size& p_withSize,
        MemoryManager& p_usingMemManager,
        Callback& p_allocationError, Callback& p_overflow
    )
    {

        ValidateMemoryManager(p_usingMemManager);
        ValidateCallback(p_allocationError);
        ValidateCallback(p_overflow);


        //If this is true then p_withSize * sizeof(T) will overflow.
        if(SIZE_MAXIMUM / sizeof(T) < p_withSize)
        {
            p_array = Array<T>();
            p_overflow();
            return;
        }

        //This callback is needed so that the state of all of this function's
        //paramaters are valid for when p_allocationError is called.
        void* l_dataPack[2];
        l_dataPack[0] = &p_array;
        l_dataPack[1] = &p_allocationError;
        Callback l_allocError(
            (void*)l_dataPack,
            CallbackCreateArrayAtWithSizeUsingMemoryManagerCallbackOnAllocationErrorCallbackOnOverflow<T>
        );

        Memory l_memForArray(
            nullptr, p_withSize * sizeof(T),
            g_MemoryReadableBit | g_MemoryWriteableBit
        );
        p_usingMemManager.AllocateMemoryCallbackOnFailure(
            l_memForArray, l_allocError
        );

        //If allocation failed then nullptr and 0 would be copied, which is
        //what needs to happen.
        p_array.m_Location = l_memForArray.m_Location;
        p_array.m_Size = l_memForArray.m_Size;

    }


    template<typename T>
    void
    ReSizeArrayToSizeUsingMemoryManagerUsingMemoryManagerReSizeFunctionCallbackOnAllocationErrorCallbackOnOverflow(
        Array<T>& p_array, const Size& p_toSize,
        MemoryManager& p_usingMemManager,
        MemoryManagerReSizeFunction& p_reSizeFunctionToUse,
        Callback& p_reSizeError, Callback& p_overflow
    )
    {

        ValidateMemoryManager(p_usingMemManager);
        ValidateCallback(p_reSizeError);
        ValidateCallback(p_overflow);
        Assert(
                p_reSizeFunctionToUse
                ==
                p_usingMemManager.m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure
            ||
                p_reSizeFunctionToUse
                ==
                p_usingMemManager.m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure,
            "The resize function to use must be in the given memory manager."
        );

        //If this is true then p_toSize * sizeof(T) will overflow.
        if(SIZE_MAXIMUM / sizeof(T) < p_toSize)
        {
            p_overflow();
            return;
        }

        Memory l_reconstructedMemory(
            p_array.m_Location,
            p_array.m_Size,
            g_MemoryReadableBit | g_MemoryWriteableBit
        );
        p_reSizeFunctionToUse(
            l_reconstructedMemory, p_usingMemManager, p_toSize * sizeof(T),
            p_reSizeError
        );

        p_array.m_Location = l_reconstructedMemory.m_Location;
        p_array.m_Size = l_reconstructedMemory.m_Size;

    }


    template<typename T>
    void DestroyArrayUsingMemoryManager(
        Array<T>& p_array, MemoryManager& p_usingMemManager
    )
    {
        Memory l_reconstructedMemory(
            p_array.m_Location,
            p_array.m_Size,
            g_MemoryReadableBit | g_MemoryWriteableBit
        );
        p_usingMemManager.DeallocateMemory(l_reconstructedMemory);
        p_array = Array<T>();
    }

}

#endif //ARRAY_MEMORY_MANAGER__GLUE_ARRAY_MEMORY_MANAGER_ARRAY_MEMORY_MANAGER_DEFINITION_HPP