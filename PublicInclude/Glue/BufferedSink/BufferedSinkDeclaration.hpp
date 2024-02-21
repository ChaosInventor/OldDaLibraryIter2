#ifndef BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DECLARATION_HPP
#define BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DECLARATION_HPP

#include "DataSink/DataSinkDeclaration.hpp"
#include "Buffer/BufferDeclaration.hpp"

namespace Library::Glue
{

    template<typename T>
    struct BufferedSink;


    template<typename T>
    void CreateDataSinkAtFromBufferedSink(
        DataSink<T>& p_sink, BufferedSink<T>& p_bufferedSink
    );


    template<typename T>
    Size WriteArrayToDataSinkCallbackOnFull_BufferedSink(
        const Array<T>& p_data, DataSink<T>& p_sink,
        Callback& p_full
    );
    template<typename T>
    Size WriteArrayToDataSinkCallbackOnFull_BufferedSink(
        const Array<T>& p_data, DataSink<T>& p_sink,
        Callback& p_full
    );

    template<typename T>
    void WriteBufferToDataSinkCallbackOnFailure(
        Buffer<T>& p_buffer, DataSink<T>& p_sink,
        Callback& p_failure
    );

}

#endif //BUFFERED_SINK__BUFFERED_SINK_BUFFERED_SINK_DECLARATION_HPP