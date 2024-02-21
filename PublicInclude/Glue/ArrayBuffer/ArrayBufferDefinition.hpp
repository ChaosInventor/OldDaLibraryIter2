#ifndef ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DEFINITION_HPP
#define ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DEFINITION_HPP

#include "Array/ArrayDefinition.hpp"
#include "Buffer/BufferDefinition.hpp"
#include "DataSink/DataSinkDefinition.hpp"
#include "DataSource/DataSourceDefinition.hpp"
#include "Callback/Callback.hpp"

//TODO: Add
#define ValidateArrayBuffer(p_arrayBuffer)

namespace Library::Glue
{

    template<typename T>
    struct ArrayBuffer
    {

        //TODO: Would be better implemented as a circular array instead.
        Array<T> m_Array;
        Size m_Used;

        ArrayBuffer():
        m_Array(),
        m_Used(0)
        { }
        ArrayBuffer(const ArrayBuffer<T>& p_other) = delete;
        ArrayBuffer(ArrayBuffer<T>&& p_other):
        m_Array(p_other.m_Array),
        m_Used(p_other.m_Used)
        {
            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;
        }

        ArrayBuffer(Array<T>& p_array):
        m_Array(p_array),
        m_Used(0)
        {
            ValidateArray(p_array);
        }


        ArrayBuffer<T>& operator=(const ArrayBuffer<T>& p_other) = delete;
        ArrayBuffer<T>& operator=(ArrayBuffer<T>&& p_other)
        {

            m_Array = p_other.m_Array;
            m_Used = p_other.m_Used;

            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;

        }


        operator Buffer<T>()
        {
            Buffer<T> l_returnValue;
            CreateBufferAtFromArrayBuffer(l_returnValue, *this);
            return l_returnValue;
        } 

    };

    
    template<typename T>
    void CreateBufferAtFromArrayBuffer(
        Buffer<T>& p_buffer, ArrayBuffer<T>& p_fromArrayBuffer
    )
    {
        p_buffer.m_State = (void*)&p_fromArrayBuffer;
        p_buffer.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty =
            ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_ArrayBuffer;
        p_buffer.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull =
            WriteUsingDataSinkUsingBufferCallbackOnSinkFull_ArrayBuffer;
    }


    template<typename T>
    void ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_ArrayBuffer(
        DataSource<T>& p_fromSource, Buffer<T>& p_toBuffer,
        Callback& p_bufferFull, Callback& p_sourceEmpty
    )
    {

        //TODO: Checks and asserts for p_toBuffer
        ValidateDataSource(p_fromSource);
        ValidateCallback(p_bufferFull);
        ValidateCallback(p_sourceEmpty);


        ArrayBuffer<T>& l_self = *((ArrayBuffer<T>*)p_toBuffer.m_State);

        if(l_self.m_Array.m_Size == l_self.m_Used)
        {
            p_bufferFull();
            return;
        }

        Array<T> l_freePartOfArray(
            l_self.m_Array.m_Location + l_self.m_Used,
            l_self.m_Array.m_Size - l_self.m_Used
        );

        Size l_read = p_fromSource.ReadArrayOfDataCallbackOnEmpty(
            l_self.m_Array, p_sourceEmpty
        );

        l_self.m_Used += l_read;
        l_self.m_Array.m_Location += l_read;
        l_self.m_Array.m_Size -= l_read;

    }
    template<typename T>
    void WriteUsingDataSinkUsingBufferCallbackOnSinkFull_ArrayBuffer (
        DataSink<T>& p_toSink, Buffer<T>& p_fromBuffer,
        Callback& p_bufferEmpty, Callback& p_sinkFull
    )
    {

        //TODO: Validate p_fromBuffer.
        ValidateDataSource(p_fromSource);
        ValidateCallback(p_bufferFull);
        ValidateCallback(p_sourceEmpty);


        ArrayBuffer<T>& l_self = *((ArrayBuffer<T>*)p_toBuffer.m_State);

        if(l_self.m_Used == 0)
        {
            p_bufferEmpty();
            return;
        }

        Array<T> l_fullPartOfArray(l_self.m_Array.m_Location, l_self.m_Used);

        Size l_written = p_toSink.WriteFromArrayToSizeAsWrittenCallbackOnFull(
            l_fullPartOfArray, p_sinkFull
        );

        //TODO: As a flat array the items must be moved, as a circular only
        //2 indexes need to be moved.

    }

}


#endif//ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DEFINITION_HPP