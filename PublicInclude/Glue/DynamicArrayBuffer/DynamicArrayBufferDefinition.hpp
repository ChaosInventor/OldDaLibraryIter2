#ifndef DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DEFINITION_HPP
#define DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DEFINITION_HPP

#include "DynamicArrayBufferDeclaration.hpp"
#include "Array/ArrayDefinition.hpp" //TODO: Could this just be array buffer?
#include "MemoryManager/MemoryManagerDefinition.hpp"
//TODO: Validate function

namespace Library::Glue
{

    template<typename T>
    struct DynamicArrayBuffer
    {

        Array<T> m_Array;
        Size m_MaximumPossibleSize;
        Array<T> m_UnbufferedNotGiven;
        Array<T> m_UnbufferedGiven;
        Array<T> m_BufferedNotGiven;
        Array<T> m_BufferedGiven;
        MemoryManager& m_MemManager;


        //TODO: All other constructors

        DynamicArrayBuffer(Array<T>& p_array, const Size& p_maxSize):
        m_Array(p_array),
        m_UnbufferedNotGiven(p_array),
        m_UnbufferedGiven(),
        m_BufferedNotGiven(),
        m_BufferedGiven(),
        m_MaximumPossibleSize(p_maxSize)
        {

            Assert(
                p_array.m_Size <= p_maxSize,
                "DynamicArrayBuffer cannot have it's maximum possible size be "
                "less than the size of the array that it's going to use."
            );

            m_MemManager = g_DefaultMemoryManager;

        }


        operator Buffer<T>()
        {
            Buffer<T> l_returnValue;
            CreateBufferAtFromDynamicArrayBuffer(l_returnValue, *this);
            return l_returnValue;
        }

    };
    

    template<typename T>
    void CreateBufferAtFromDynamicArrayBuffer(
        Buffer<T>& p_buffer, DynamicArrayBuffer<T>& p_dArrayBuffer
    );


    template<typename T>
    void GetUnbufferedArrayFromBufferCallbackOnFull_DynamicArrayBuffer(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    )
    {

        ValidateArray(p_bufferSpace);
        ValidateBuffer(p_buffer);
        ValidateCallback(p_failure);


        DynamicArrayBuffer<T>& l_self = *((DynamicArrayBuffer*)p_buffer.m_State);

        if(p_bufferSpace.m_Size > l_self.m_UnbufferedNotGiven.m_Size)
        {
            p_failure();
            return;
        }

        if(l_self.m_UnbufferedGiven.m_Location != nullptr)
        {
            p_bufferSpace.m_Location = l_self.m_UnbufferedGiven.m_Location + l_self.m_UnbufferedGiven.m_Size;
            l_self.m_UnbufferedGiven.m_Size += p_bufferSpace.m_Size;

            l_self.m_UnbufferedNotGiven.m_Location += p_bufferSpace.m_Size;
            l_self.m_UnbufferedNotGiven.m_Size -= p_bufferSpace.m_Size;    
        }
        else
        {
            p_bufferSpace.m_Location = l_self.m_UnbufferedNotGiven.m_Location;
            l_self.m_UnbufferedNotGiven.m_Location += p_bufferSpace.m_Size;
            l_self.m_UnbufferedNotGiven.m_Size -= p_bufferSpace.m_Size;
        }

    }
    template<typename T>
    void GetBufferedArrayFromBufferCallbackOnEmpty_DynamicBufferArray(
        Array<T>& p_bufferSpace,
        Buffer<T>& p_buffer,
        Callback& p_failure
    )
    {

        ValidateArray(p_bufferSpace);
        ValidateBuffer(p_buffer);
        ValidateCallback(p_failure);


        DynamicArrayBuffer<T>& l_self = *((DynamicArrayBuffer*)p_buffer.m_State);

        if(l_self.m_BufferedNotGiven.m_Size < p_bufferSpace.m_Size)
        {
            p_failure();
            return;
        }

    }
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

#endif //DYNAMIC_ARRAY_BUFFER__GLUE_DYNAMIC_ARRAY_BUFFER_DYNAMIC_ARRAY_BUFFER_DEFINITION_HPP