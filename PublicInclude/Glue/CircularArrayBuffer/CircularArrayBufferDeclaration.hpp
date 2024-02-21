#ifndef CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DECLARATION_HPP
#define CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DECLARATION_HPP

#include "CircularArray/CircularArrayDeclaration.hpp"
#include "Buffer/BufferDeclaration.hpp"

namespace Library::Glue
{

    template<typename T>
    struct CircularArrayBuffer;


    template<typename T>
    void CreateToCircularArrayBufferUsingCircularArray(
        CircularArrayBuffer<T>& p_cArrayBuffer,
        CircularArray<T>& p_circularArray
    );
    template<typename T>
    void CreateToBufferUsingCircularArrayBuffer(
        Buffer<T>& p_buffer, CircularArrayBuffer<T>& p_cArrayBuffer
    );


    template<typename T>
    void ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_CircularArrayBuffer(
        DataSource<T>& p_fromSource, Buffer<T>& p_toBuffer,
        Callback& p_sourceEmpty
    );
    template<typename T>
    void WriteUsingDataSinkUsingBufferCallbackOnSinkFull_CircuarArrayBuffer(
        DataSink<T>& p_toSink, Buffer<T>& p_fromBuffer,
        Callback& p_sinkFull
    );

}

#endif //CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DECLARATION_HPP