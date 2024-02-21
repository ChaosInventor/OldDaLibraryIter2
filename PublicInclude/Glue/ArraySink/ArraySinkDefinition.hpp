#ifndef ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DEFINITION_HPP
#define ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DEFINITION_HPP

#include "Array/ArrayDefinition.hpp"
#include "DataSink/DataSinkDefinition.hpp"

#include "ArraySinkDeclaration.hpp"
#include "Debug/Debug.hpp"
#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"

#define ValidateArraySink(p_arraySink)\
    Check(                                                                      \
        p_arraySink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull  \
        ==                                                                      \
        &WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_ArraySink<T>, \
        "DataSink dose not appear to be an ArraySink."                          \
    );                                                                          \
    Assert(                                                                     \
        p_arraySink.m_State != nullptr, "ArraySink cannot have a null state"    \
    );                                                                          \
    ValidateArray(((ArraySink<T>*)p_arraySink.m_State)->m_Array);               \
    Assert(                                                                     \
        ((ArraySink<T>*)p_arraySink.m_State)->m_Used                            \
        <                                                                       \
        ((ArraySink<T>*)p_arraySink.m_State)->m_Array.m_Size,                   \
        "ArraySink cannot have used more items that there are in the array."    \
    );


namespace Library::Glue
{

    template<typename T>
    struct ArraySink
    {

        Array<T> m_Array;
        Size m_Used;


        ArraySink():
        m_Array(),
        m_Used(0)
        { }
        ArraySink(const ArraySink<T>& p_other):
        m_Array(p_other.m_Array),
        m_Used(p_other.m_Used)
        { }
        ArraySink(ArraySink<T>&& p_other):
        m_Array(p_other.m_Array),
        m_Used(p_other.m_Used)
        {
            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;
        }

        ArraySink(const Array<T>& p_array)
        {
            CreateArraySinkAtFromArray<T>(*this, p_array);
        }


        ArraySink& operator=(const ArraySink<T>& p_other)
        {
            m_Array = Array<T>(p_other.m_Array);
            m_Used = p_other.m_Used;
            return *this;
        }
        ArraySink& operator=(ArraySink<T>&& p_other)
        {
            
            m_Array = Array<T>(p_other.m_Array),
            m_Used = p_other.m_Used;
            
            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;
        
            return *this;

        }

        operator Array<T>()
        {
            return m_Array;
        }
        operator DataSink<T>()
        {
            DataSink<T> l_returnValue;
            CreateDataSinkAtFromArraySink(l_returnValue, *this);
            return l_returnValue;
        }

    };


    template<typename T>
    void CreateArraySinkAtFromArray(
        ArraySink<T>& p_location,
        const Array<T>& p_array
    )
    {
        p_location.m_Array = p_array;
        p_location.m_Used = 0;
    }
    template<typename T>
    void CreateDataSinkAtFromArraySink(
        DataSink<T>& p_location,
        ArraySink<T>& p_arraySink
    )
    {
        p_location.m_State = (void*)&p_arraySink;
        p_location.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull = 
            WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_ArraySink;
    }


    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_ArraySink(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_arraySink,
        Size& p_numberOfWrittenItems, Callback& p_full
    )
    {

        ValidateArraySink(p_arraySink);
        ValidateArray(p_arrayToWrite);
        ValidateCallback(p_full);


        ArraySink<T>& l_arraySinkReal = *(ArraySink<T>*)p_arraySink.m_State;

        for(
            p_numberOfWrittenItems = 0;
            p_numberOfWrittenItems < p_arrayToWrite.m_Size; 
            ++p_numberOfWrittenItems
        )
        {
            if(l_arraySinkReal.m_Used == l_arraySinkReal.m_Array.m_Size)
            {
                p_full();
                return;
            }

            l_arraySinkReal.m_Array[l_arraySinkReal.m_Used] =
                p_arrayToWrite[p_numberOfWrittenItems];

            ++l_arraySinkReal.m_Used;
        }

    }


}

#endif //ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DEFINITION_HPP