#ifndef SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DECLARATION_HPP
#define SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DECLARATION_HPP

#include "DataSource/DataSourceDeclaration.hpp"
#include "DataSink/DataSinkDeclaration.hpp"
#include "Buffer/BufferDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    template<typename T>
    void WriteUsingDataSourceUsingDataSinkUsingBufferCallbackOnSinkFull(
        DataSource<T>& p_source, DataSink<T>& p_sink, Buffer<T>& p_buffer,
        Callback& p_sinkFull
    );

}

#endif //SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DECLARATION_HPP