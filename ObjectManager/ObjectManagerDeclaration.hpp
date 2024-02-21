#ifndef OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DECLARATION_HPP
#define OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"
#include "DataSink/DataSinkDeclaration.hpp"
#include "DataSource/DataSourceDeclaration.hpp"
#include "MemoryManager/MemoryManagerDeclaration.hpp"

namespace Library
{

    template<typename T>
    struct ObjectManager;

    template<typename T>
    using ObjectManagerAllocateFunction = Size (*) (
        const Size& p_numberOfObjects,
        ObjectManager<T>& p_objectManager,
        DataSink<T>& p_objectsSink, MemoryManager& p_memoryManager,
        Callback& p_failure
    );

    template<typename T>
    using ObjectManagerCopyFunction = Size (*) (
        const T& p_object,
        ObjectManager<T>& p_objectManager,
        const Size& p_numberOfTimesToCopy,
        DataSink<T>& p_objectSink, MemoryManager& p_memoryManager,
        Callback p_failure
    );

    template<typename T>
    using ObjectManagerDeallocateFunction = void (*) (
        ObjectManager<T>& p_objectManager,
        DataSource<T>& p_objectsSource, MemoryManager& p_memoryManager
    );


}

#endif //OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DECLARATION_HPP