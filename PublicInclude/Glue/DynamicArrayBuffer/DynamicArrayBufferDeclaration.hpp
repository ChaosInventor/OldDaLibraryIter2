#ifndef DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DECLARATION_HPP
#define DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DECLARATION_HPP

#include "Buffer/BufferDeclaration.hpp"
#include "Array/ArrayDeclaration.hpp"

#include "Callback/Callback.hpp"

namespace Library::Glue
{

    template<typename T>
    struct DynamicArrayBuffer;
    

    template<typename T>
    void CreateBufferAtFromDynamicArrayBuffer(
        Buffer<T>& p_buffer, DynamicArrayBuffer<T>& p_dArrayBuffer
    );


    template<typename T>
    void GetUnbufferedArrayFromBufferCallbackOnFull_DynamicArrayBuffer(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    );
    template<typename T>
    void GetBufferedArrayFromBufferCallbackOnEmpty_DynamicBufferArray(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    );
    template<typename T>
    void GetUnbufferedArrayFromBufferCallbackOnFull_AnySize_DynamicBufferArray(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    );
    template<typename T>
    void GetBufferedArrayFromBufferCallbackOnEmpty_AnySize_DynamicBufferArray(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    );


    template<typename T>
    void SetArrayFromBufferAsBuffered_DynamicBufferArray(
        const Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer
    );
    template<typename T>
    void SetArrayFromBufferAsUnbuffered_DynamicBufferArray(
        const Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer
    );

}

#endif //DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DECLARATION_HPP