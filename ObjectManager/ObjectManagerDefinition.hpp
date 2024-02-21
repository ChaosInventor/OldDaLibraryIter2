#ifndef OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DEFINITION_HPP
#define OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "ObjectManagerDeclaration.hpp"
#include "Glue/ArraySink/ArraySink.hpp"
#include "Glue/ArraySource/ArraySource.hpp"

#define ValidateObjectManager(p_objectManager)\
Assert((p_objectManager).m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure != nullptr, "Cannot use object manager with null function");           \
Assert((p_objectManager).m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure != nullptr, "Cannot use object manager with null function");   \
Assert((p_objectManager).m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager != nullptr, "Cannot use object manager with null function");


namespace Library
{

    template<typename T>
    struct ObjectManager
    {

        void* m_State;

        ObjectManagerAllocateFunction<T>
            m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure;

        //TODO: Should this have the ability to be null and to still have a valid
        //object manager? Some objects may not be copyable.
        ObjectManagerCopyFunction<T>
            m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure;

        ObjectManagerDeallocateFunction<T>
            m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager;

        //TODO: Object swap function?
        //TODO: Object move function?


        ObjectManager():
        m_State(nullptr),
        m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure(
            nullptr
        ),
        m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure(
            nullptr
        ),
        m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager(
            nullptr
        )
        { }
        ObjectManager(const ObjectManager& p_other) = delete;
        ObjectManager(ObjectManager&& p_other):
        m_State(p_other.m_State),
        m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure(
            p_other.m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure
        ),
        m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure(
            p_other.m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure
        ),
        m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager(
            p_other.m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager
        )
        {

            p_other.m_State = nullptr;
            p_other.m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager = nullptr;

        }


        ObjectManager& operator=(const ObjectManager& p_other) = delete;
        ObjectManager& operator=(ObjectManager&& p_other)
        {
            
            m_State = p_other.m_State;
            m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure = 
                p_other.m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure;
            m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure = 
                p_other.m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure;
            m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager = 
                p_other.m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager;
        
            p_other.m_State = nullptr;
            p_other.m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure = nullptr;
            p_other.m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager = nullptr;

        }

        inline Size AllocateNumberOfObjectsToDataSinkUsingMemoryManagerCallbackOnFailure(
            const Size& p_numberOfObjects,
            DataSink<T>& p_objectsSink, MemoryManager& p_memoryManager,
            Callback& p_failure
        )
        {
            ValidateObjectManager(*this);
            return m_AllocateNumberOfObjectsFromObjectManagerToDataSinkUsingMemoryManagerCallbackOnFailure(
                p_numberOfObjects, *this,
                p_objectsSink, p_memoryManager,
                p_failure
            );
        }
        inline Size AllocateNumberOfObjectsToDataSinkUsingCallbackOnFailure(
            const Size& p_numberOfObjects,
            DataSink<T>& p_objectsSink,
            Callback& p_failure
        )
        {
            return AllocateNumberOfObjectsToDataSinkUsingMemoryManagerCallbackOnFailure(
                p_numberOfObjects,
                p_objectsSink, g_DefaultMemoryManager,
                p_failure
            );
        }
        inline Size AllocateArrayCallbackOnFailure(
            const Array<T>& p_objectsArray,
            Callback& p_failure
        )
        {
            Glue::ArraySink<T> l_arraySink = p_objectsArray;
            DataSink<T> l_sink = l_arraySink;
            return AllocateNumberOfObjectsToDataSinkUsingMemoryManagerCallbackOnFailure(
                p_objectsArray.m_Size,
                l_sink, g_DefaultMemoryManager,
                p_failure
            );
        }
        inline void AllocateObjectAt(T& p_object)
        {
            AllocateArrayCallbackOnFailure(p_object, g_DefaultAllocateError);
        }

        inline Size CreateCopyOfObjectNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure(
            const T& p_object,
            const Size& p_numberOfTimesToCopy,
            DataSink<T>& p_objectSink, MemoryManager& p_memoryManager,
            Callback& p_failure
        )
        {
            ValidateObjectManager(*this);
            return m_CreateCopyOfObjectFromObjectManagerNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure(p_object, *this, p_numberOfTimesToCopy, p_objectSink, p_memoryManager, p_failure);
        }
        inline Size CreateCopyOfObjectNumberOfTimesToDataSinkCallbackOnFailure(
            const T& p_object,
            const Size& p_numberOfTimesToCopy,
            DataSink<T>& p_objectSink,
            Callback& p_failure
        )
        {
            return CreateCopyOfObjectNumberOfTimesToDataSinkUsingMemoryManagerCallbackOnFailure(p_object, p_numberOfTimesToCopy, p_objectSink, g_DefaultMemoryManager, p_failure);
        }
        inline Size CreateCopyOfObjectToArrayCallbackOnFailure(
            const T& p_object,
            const Array<T>& p_objectArray,
            Callback& p_failure
        )
        {
            Array<T> l_singleItemArray = p_object;
            Glue::ArraySink<T> l_arraySink = l_singleItemArray;
            DataSink<T> l_sink = l_arraySink;
            return CreateCopyOfObjectNumberOfTimesToDataSinkCallbackOnFailure(
                p_object, p_objectArray.m_Size,
                l_sink,
                p_failure
            );
        }
        inline Size CreateCopyOfObjectAtCallbackOnFailure(
            const T& p_object,
            T& p_object,
            Callback& p_failure
        )
        {
            //TODO: Make
            return CreateCopyOfObjectToArrayCallbackOnFailure(p_object, p_object, p_failure);
        }


        inline void DeallocateObjectsFromDataSourceUsingMemoryManager(
            DataSource<T>& p_objectsSource,
            MemoryManager& p_memoryManager
        )
        {
            ValidateObjectManager(*this);
            m_DeallocateObjectsFromObjectManagerFromDataSourceUsingMemoryManager(p_objectsSource, *this, p_memoryManager);
        }
        inline void DeallocateObjectsFromDataSource(
            DataSource<T>& p_objectsSource
        )
        {
            DeallocateObjectsFromDataSourceUsingMemoryManager(p_objectsSource, g_DefaultMemoryManager);
        }
        inline void DeallocateArray(
            Array<T>& p_objectsArray
        )
        {
            Glue::ArraySource<T> l_arraySource = p_objectsArray;
            DataSource<T> l_source = l_arraySource;
            DeallocateObjectsFromDataSource(l_source);
        }
        inline void DeallocateObject(const T& p_object)
        {
            DeallocateArray(p_object);
        }

    };

}

#endif //OBJECT_ALLOCATOR__OBJECT_ALLOCATOR_OBJECT_ALLOCATOR_DEFINITION_HPP