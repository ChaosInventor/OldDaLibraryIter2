#ifndef ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DECLARATION_HPP
#define ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DECLARATION_HPP

#include "Buffer/BufferDeclaration.hpp"
#include "DataSource/DataSourceDeclaration.hpp"
#include "DataSink/DataSinkDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    template<typename T>
    struct ArrayBuffer;

    
    template<typename T>
    void CreateBufferAtFromArrayBuffer(
        Buffer<T>& p_buffer, ArrayBuffer<T>& p_fromArrayBuffer
    );


    template<typename T>
    void ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_ArrayBuffer(
        DataSource<T>& p_fromSource, Buffer<T>& p_toBuffer,
        Callback& p_bufferFull, Callback& p_sourceEmpty
    );
    template<typename T>
    void WriteUsingDataSinkUsingBufferCallbackOnSinkFull_ArrayBuffer (
        DataSink<T>& p_toSink, Buffer<T>& p_fromBuffer,
        Callback& p_bufferEmpty, Callback& p_sinkFull
    );

}

#endif//ARRAY_BUFFER__GLUE_ARRAY_BUFFER_ARRAY_BUFFER_DECLARATION_HPP