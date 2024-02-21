#ifndef ARRAY_INDEXABLE__GLUE_ARRAY_INDEXABLE_ARRAY_INDEXABLE_HPP
#define ARRAY_INDEXABLE__GLUE_ARRAY_INDEXABLE_ARRAY_INDEXABLE_HPP

#include "Debug/Debug.hpp"
#include "Array/Array.hpp"
#include "Indexable/Indexable.hpp"

#define ValidateIndexableIsArrayIndexable(p_indexable)\
    ValidateIndexable((p_indexable));                                                   \
    Check(                                                                              \
        (p_indexable).m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex  \
        ==                                                                              \
        ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex_ArrayIndexable,  \
        "Indexable does not appear to be using the array indexable function."           \
    );                                                                                  \
    Check(                                                                              \
        (p_indexable).m_GetSizeAsItemLengthUsingIndexable                               \
        ==                                                                              \
        GetSizeAsItemLengthUsingIndexable_ArrayIndexable,                               \
        "Indexable does not appear to be using the array indexable function."           \
    );                                                                                  \
    Check(                                                                              \
        (p_indexable).m_ReadToBatchAsNextUsingIndexableCallbackOnEnd                    \
        ==                                                                              \
        ReadToBatchUsingIndexableCallbackOnEnd_ArrayIndexable,                          \
        "Indexable does not appear to be using the array indexable function."           \
    );                                                                                  \
    Check(                                                                              \
        (p_indexable).m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd                \
        ==                                                                              \
        ReadToBatchUsingIndexableCallbackOnEnd_ArrayIndexable,                          \
        "Indexable does not appear to be using the array indexable function."           \
    );                                                                                  \
    Assert(                                                                             \
        (p_indexable).m_State != nullptr,                                               \
        "Array indexable must not have a null state."                                   \
    );


namespace Library::Glue
{

    template<typename T>
    struct ArrayIndexable
    {

        Array<T> m_Array;


        ArrayIndexable():
        m_Array()
        { }
        ArrayIndexable(const ArrayIndexable<T>& p_other) = delete;
        ArrayIndexable(ArrayIndexable<T>&& p_other):
        m_Array((Array<T>&&)p_other.m_Array)
        { }
        
        ArrayIndexable(const Array<T>& p_array):
        m_Array(p_array)
        { }


        ArrayIndexable& operator=(const ArrayIndexable<T>& p_other) = delete;
        ArrayIndexable& operator=(ArrayIndexable<T>&& p_other)
        {
            m_Array = (Array<T>&&)p_other.m_Array;
        }

        operator Indexable<T>()
        {
            Indexable<T> l_returnValue;
            CreateToIndexableFromArrayIndexable(l_returnValue, *this);
            return l_returnValue;
        }

    };


    template<typename T>
    void CreateToIndexableFromArrayIndexable(
        Indexable<T>& p_indexable, ArrayIndexable<T>& p_arrayIndexable
    )
    {

        ValidateArray(p_arrayIndexable.m_Array);


        p_indexable.m_State = &p_arrayIndexable;
        p_indexable.m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex
        = 
        ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex_ArrayIndexable<T>;
        p_indexable.m_GetSizeAsItemLengthUsingIndexable =
            GetSizeAsItemLengthUsingIndexable_ArrayIndexable<T>;
        p_indexable.m_ReadToBatchAsNextUsingIndexableCallbackOnEnd =
            ReadToBatchUsingIndexableCallbackOnEnd_ZeroIndexable<T>;
        p_indexable.m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd =
            ReadToBatchUsingIndexableCallbackOnEnd_ZeroIndexable<T>;
    
    }

    template<typename T>
    void
    ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex_ArrayIndexable(
        Batch<T>& p_batch, const Size& p_index, Indexable<T>& p_indexable,
        Callback& p_indexError
    )
    {

        ValidateIndexableIsArrayIndexable(p_indexable);
        ValidateCallback(p_indexError);


        ArrayIndexable<T>& l_self = *(ArrayIndexable<T>*)p_indexable.m_State;

        if(p_index >= l_self.m_Array.m_Size)
        {
            p_batch = Batch<T>();
            p_indexError();
            return;
        }

        p_batch.m_Location = l_self.m_Array.m_Location + p_index;
        p_batch.m_NumberOfItemsAfterLocation = l_self.m_Array.m_Size - p_index;
        p_batch.m_NumberOfItemsBeforeLocation = p_index;

    }

    template<typename T>
    Size GetSizeAsItemLengthUsingIndexable_ArrayIndexable(
        Indexable<T>& p_indexable
    )
    {
        ValidateIndexableIsArrayIndexable(p_indexable);
        return *((ArrayIndexable<T>*)p_indexable.m_State)->m_Array.m_Size;
    }

}

#endif //ARRAY_INDEXABLE__GLUE_ARRAY_INDEXABLE_ARRAY_INDEXABLE_HPP