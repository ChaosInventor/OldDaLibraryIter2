#ifndef MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DEFINITION_HPP
#define MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "MemoryManagerDeclaration.hpp"

#define ValidateMemoryManager(p_memory_manager)\
    Assert(                                                                                     \
        (p_memory_manager).m_AllocateMemoryFromMemoryManagerCallbackOnFailure                   \
        !=                                                                                      \
        nullptr,                                                                                \
        "Cannot use memory manager with a null function"                                        \
    )                                                                                           \
    Assert(                                                                                     \
        (p_memory_manager).m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure        \
        !=                                                                                      \
        nullptr,                                                                                \
        "Cannot use memory manager with a null function"                                        \
    )                                                                                           \
    Assert(                                                                                     \
        (p_memory_manager).m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure       \
        !=                                                                                      \
        nullptr,                                                                                \
        "Cannot use memory manager with a null function"                                        \
    )                                                                                           \
    Assert(                                                                                     \
        (p_memory_manager).m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure  \
        !=                                                                                      \
        nullptr,                                                                                \
        "Cannot use memory manager with a null function"                                        \
    )                                                                                           \
    Assert(                                                                                     \
        (p_memory_manager).m_DeallocateMemoryFromMemoryManager                                  \
        !=                                                                                      \
        nullptr,                                                                                \
        "Cannot use memory manager with a null function"                                        \
    )


namespace Library
{

    struct MemoryManager
    {
        void* m_State;

        MemoryManagerAllocateFunction
            m_AllocateMemoryFromMemoryManagerCallbackOnFailure;

        MemoryManagerReSizeFunction
            m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure;
        MemoryManagerReSizeFunction
            m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure;
        MemoryManagerRePermissionFunction
            m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure;

        MemoryManagerDeallocateFunction m_DeallocateMemoryFromMemoryManager;


        MemoryManager():
        m_State(nullptr),
        m_AllocateMemoryFromMemoryManagerCallbackOnFailure(nullptr),
        m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure(nullptr),
        m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure(nullptr),
        m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure(nullptr),
        m_DeallocateMemoryFromMemoryManager(nullptr)
        { }
        MemoryManager(const MemoryManager& p_other) = delete;
        MemoryManager(MemoryManager&& p_other):
        m_State(
            p_other.m_State
        ),
        m_AllocateMemoryFromMemoryManagerCallbackOnFailure(
            p_other.m_AllocateMemoryFromMemoryManagerCallbackOnFailure
        ),
        m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure(
            p_other.m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure
        ),
        m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure(
            p_other.m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure
        ),
        m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure(
            p_other.m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure
        ),
        m_DeallocateMemoryFromMemoryManager(
            p_other.m_DeallocateMemoryFromMemoryManager
        )
        {

            p_other.m_State = nullptr;
            p_other.m_AllocateMemoryFromMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure = nullptr;
            p_other.m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure = nullptr;
            p_other.m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure = nullptr;
            p_other.m_DeallocateMemoryFromMemoryManager = nullptr;

        }

        MemoryManager(
            void* p_state,
            MemoryManagerAllocateFunction
                p_allocateMemoryFromMemoryManagerCallbackOnFailure,
            MemoryManagerReSizeFunction
                p_reSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure,
            MemoryManagerReSizeFunction
                p_reSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure,
            MemoryManagerRePermissionFunction
                p_rePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure,
            MemoryManagerDeallocateFunction p_deallocateMemoryFromMemoryManager
        ):
        m_State(p_state),
        m_AllocateMemoryFromMemoryManagerCallbackOnFailure(
            p_allocateMemoryFromMemoryManagerCallbackOnFailure
        ),
        m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure(
            p_reSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure
        ),
        m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure(
            p_reSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure
        ),
        m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure(
            p_rePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure
        ),
        m_DeallocateMemoryFromMemoryManager(
            p_deallocateMemoryFromMemoryManager
        )
        { }


        MemoryManager& operator=(const MemoryManager& p_other) = delete;
        MemoryManager& operator=(MemoryManager&& p_other)
        {

            m_State =
                p_other.m_State;
            m_AllocateMemoryFromMemoryManagerCallbackOnFailure =
                p_other.m_AllocateMemoryFromMemoryManagerCallbackOnFailure;
            m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure =
                p_other.m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure;
            m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure =
                p_other.m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure;
            m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure =
                p_other.m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure;
            m_DeallocateMemoryFromMemoryManager =
                p_other.m_DeallocateMemoryFromMemoryManager;

            p_other.m_State = nullptr;
            p_other.m_AllocateMemoryFromMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure = nullptr;
            p_other.m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure = nullptr;
            p_other.m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure = nullptr;
            p_other.m_DeallocateMemoryFromMemoryManager = nullptr;

            return *this;

        }


        inline void AllocateMemoryCallbackOnFailure(
            Memory& p_mem, Callback& p_allocateError
        )
        {
            ValidateMemoryManager(*this);
            m_AllocateMemoryFromMemoryManagerCallbackOnFailure(
                p_mem, *this, p_allocateError
            );
        }
        inline void AllocateMemory(Memory& p_mem)
        {
            AllocateMemoryCallbackOnFailure(p_mem, g_DefaultAllocateError);
        }

        inline void ReSizeMemoryForwardToSizeCallbackOnFailure(
            Memory& p_mem, const Size& p_newSize,
            Callback& p_reSizeError
        )
        {
            ValidateMemoryManager(*this);
            m_ReSizeMemoryFromMemoryManagerForwardToSizeCallbackOnFailure(
                p_mem, *this, p_newSize, p_reSizeError
            );
        }
        inline void ReSizeMemoryForwardToSize(
            Memory& p_mem, const Size& p_newSize
        )
        {
            ReSizeMemoryForwardToSizeCallbackOnFailure(
                p_mem, p_newSize, g_DefaultReSizeError
            );
        }
        inline void ReSizeMemoryBackwardToSizeCallbackOnFailure(
            Memory& p_mem, const Size& p_newSize,
            Callback& p_reSizeError
        )
        {
            ValidateMemoryManager(*this);
            m_ReSizeMemoryFromMemoryManagerBackwardToSizeCallbackOnFailure(
                p_mem, *this, p_newSize, p_reSizeError
            );
        }
        inline void ReSizeMemoryBackwardToSize(
            Memory& p_mem, const Size& p_newSize
        )
        {
            ReSizeMemoryBackwardToSizeCallbackOnFailure(
                p_mem, p_newSize, g_DefaultReSizeError
            );
        }
        inline void RePermissionMemoryToPermissionsCallbackOnFailure(
            Memory& p_mem, const Byte& p_newPermissions,
            Callback& p_rePermissionError
        )
        {
            ValidateMemoryManager(*this);
            m_RePermissionMemoryFromMemoryManagerToPermissionsCallbackOnFailure(
                p_mem, *this, p_newPermissions, p_rePermissionError
            );
        }
        inline void RePermissionMemoryToPermissions(
            Memory& p_mem, const Byte& p_newPermissions
        )
        {
            RePermissionMemoryToPermissionsCallbackOnFailure(
                p_mem, p_newPermissions, g_DefaultRePermissionError
            );
        }

        inline void DeallocateMemory(Memory& p_mem)
        {
            ValidateMemoryManager(*this);
            m_DeallocateMemoryFromMemoryManager(p_mem, *this);
        }

    };


}

#endif //MEMORY_MANAGER__MEMORY_MANAGER_MEMORY_MANAGER_DEFINITION_HPP