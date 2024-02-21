#ifndef BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DEFINITION_HPP
#define BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DEFINITION_HPP

#include "BufferedSinkDeclaration.hpp"
#include "DataSink/DataSinkDefinition.hpp"
#include "Buffer/BufferDefinition.hpp"

namespace Library::Glue
{

    template<typename T>
    struct BufferedSink
    {
        
        Buffer<T>& m_Buffer;
        DataSink<T>& m_Sink;
    

        BufferedSink(const BufferedSink<T>& p_other) = delete;
        BufferedSink(BufferedSink<T>&& p_other):
        m_Buffer((Buffer<T>&&)p_other.m_Buffer),
        m_Sink((DataSink<T>&&)p_other.m_Sink)
        { }

        BufferedSink(Buffer<T>& p_buffer, DataSink<T>& p_sink):
        m_Buffer(p_buffer),
        m_Sink(p_sink)
        { }


        operator DataSink<T>()
        {
            DataSink<T> l_returnValue;
            CreateDataSinkAtFromBufferedSink(l_returnValue, *this);
            return l_returnValue;
        }

    };


    template<typename T>
    void CreateDataSinkAtFromBufferedSink(
        DataSink<T>& p_sink, BufferedSink<T>& p_bufferedSink
    )
    {
        ValidateDataSink(p_bufferedSink.m_Sink);
        ValidateBuffer(p_bufferedSink.m_Buffer);
        p_sink = DataSink<T>(
            (void*)&p_bufferedSink,
            WriteArrayToDataSinkCallbackOnFull_BufferedSink
        );
    }


    //TODO: More sane callback naming.
    template<typename T>
    void CallbackCallbackWriteArrayFromDataSinkCallbackOnFull_BufferedSink(
        void* p_data
    )
    {

        void** l_dataPack = p_data;

        DataSink<T>& l_bufferedSink = *((DataSink*)l_dataPack[0]);
        Size& l_returnValue = *((Size*)l_dataPack[1]);
        Array<T>& l_bufferSpace = *((Array<T>*)l_dataPack[2]);

        BufferedSink<T>& l_self = *((BufferedSink<T>*)l_bufferedSink.m_State);

        //The underlying sink became full, so the original write function should
        //not get any more data into the buffer.
        //
        //This stops the original write function from putting more stuff into
        //the buffered sink's buffer.
        l_returnValue = 0;
        l_bufferSpace.m_Size = 0; //BUG: The 1st callback will allocate this,
        //which will not stop the original function's loop.
        //2 solutions:
        //1. Break the loop by setting i to a value and somehow use a value that
        //does not allocate anything in the 1st callback(impossible).
        //2. Change the buffer interface so that a value of 1 does not make it
        //so that any sized array is given(this functionality is moved to a
        //seprate function and 0 does not give back an array.)

        //If the underlying sink becomes full just once, the buffered sink
        //becomes full permanently.
        l_bufferedSink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull =
            g_FullSink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull;

    }
    template<typename T>
    void CallbackWriteArrayFromDataSinkCallbackOnFull_BufferedSink(void* p_data)
    {

        void** l_dataPack = p_data;

        DataSink<T>& l_bufferedSink = *((DataSink*)l_dataPack[0]);
        Size& l_returnValue = *((Size*)l_dataPack[1]);
        Array<T>& l_bufferSpace = *((Array<T>*)l_dataPack[2]);

        BufferedSink<T>& l_self = *((BufferedSink<T>*)l_bufferedSink.m_State);

        Callback l_sinkFull(p_data, CallbackCallbackWriteArrayFromDataSinkCallbackOnFull_BufferedSink);

        WriteBufferToDataSinkCallbackOnFailure(
            l_self.m_Buffer, l_self.m_Sink,
            l_sinkFull
        );

        l_self.m_Buffer.GetUnbufferedArrayCallbackOnFull(
            l_bufferSpace, l_sinkFull
        );

    }
    template<typename T>
    Size WriteArrayToDataSinkCallbackOnFull_BufferedSink(
        const Array<T>& p_data, DataSink<T>& p_sink,
        Callback& p_full
    )
    {

        ValidateArray(p_data);
        ValidateCallback(p_full);
        Check(
            p_sink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
            ==
            WriteArrayToDataSinkCallbackOnFull_BufferedSink,
            "The given data sink does not appear to be a buffered sink"
        );
        Assert(
            p_sink.m_State != nullptr, "Buffered sink cannot have a null state."
        );
    

        if(p_data.m_Location == nullptr)
        {
            return 0;
        }

        BufferedSink<T>& l_self = *((BufferedSink<T>*)p_sink.m_State);
        
        Size l_returnValue = p_data.m_Size;

        Array<T> l_bufferSpace(p_data.m_Size);

        //This callback is used in the case where m_Buffer becomes full. When
        //called it flushes m_Buffer to m_Sink.
        //
        //If m_Sink becomes full while flushing:
        //- The BufferedSink becomes full permanently by setting its function to
        //g_FullSink's function
        //- l_returnValue is adjusted
        //- l_bufferSpace.m_Size is set to 0 so that the for loop doesn't run
        //and the SetArrayAsBuffered function does nothing.
        void* l_bufferFullData[3];
        l_bufferFullData[0] = &p_sink;
        l_bufferFullData[1] = &l_returnValue;
        l_bufferFullData[2] = &l_bufferSpace;
        
        Callback l_bufferFull(
            (void*)l_bufferFullData,
            CallbackWriteArrayFromDataSinkCallbackOnFull_BufferedSink<T>
        );

        l_self.m_Buffer.GetUnbufferedArrayCallbackOnFull(
            l_bufferSpace,
            l_bufferFull
        );

        for(Size i = 0; i < l_bufferSpace.m_Size; ++i)
        {
            l_bufferSpace[i] = p_data[i];
        }

        l_self.m_Buffer.SetArrayAsBuffered(
            l_bufferSpace.m_Size, l_bufferSpace
        );

        return l_returnValue;

    }

    template<typename T>
    void WriteBufferToDataSinkCallbackOnFailure(Buffer<T>& p_buffer, DataSink<T>& p_sink);

}

#endif //BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DEFINITION_HPP