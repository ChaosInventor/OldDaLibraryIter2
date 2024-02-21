#ifndef SINK_SOURCE_GLUE__GLUE_SINK_SOURCE_SINK_SOURCE_HPP
#define SINK_SOURCE_GLUE__GLUE_SINK_SOURCE_SINK_SOURCE_HPP

#include "DataSink/DataSink.hpp"
#include "DataSource/DataSource.hpp"

#include "Buffer/Buffer.hpp"

namespace Library::Glue
{

    // template<typename T>
    // void Callback_WriteDataSourceToDataSinkUsingBuffer(void* p_data)
    // {

    //     void* l_dataUnpacked[2] = (void**)p_data;

    //     DataSink<T>& l_sink = l_dataUnpacked[0];
    //     Buffer<T>& l_buffer = l_dataUnpacked[1];

    //     l_buffer.WriteToDataSinkCallbackOnEmpty(l_sink, g_NullCallback);

    // }
    template<typename T>
    void WriteDataSourceToDataSinkUsingBuffer(
        DataSource<T>& p_source,
        DataSink<T>& p_sink,
        Buffer<T>& p_buffer
    );
}

#endif //SINK_SOURCE_GLUE__GLUE_SINK_SOURCE_SINK_SOURCE_HPP
