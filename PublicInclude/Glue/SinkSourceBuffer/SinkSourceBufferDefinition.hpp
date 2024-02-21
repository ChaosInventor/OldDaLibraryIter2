#ifndef SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DEFINITION_HPP
#define SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DEFINITION_HPP

#include "DataSource/DataSourceDefinition.hpp"
#include "DataSink/DataSinkDefinition.hpp"
#include "Buffer/BufferDefinition.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    void CallbackWriteUsingDataSourceUsingDataSinkUsingBufferCallbackOnSinkFull(
        Callback& p_self
    )
    {

        ValidateCallback(p_self);
        Assume(p_self.m_State != nullptr);


        void** l_dataPack = (void**)p_self.m_State;
        bool& l_sourceNotEmpty = *(bool*)l_dataPack[0];
        Callback& l_sinkFull = *(Callback*)l_dataPack[1];

        l_sourceNotEmpty = false;
        l_sinkFull();

    }
    template<typename T>
    void WriteUsingDataSourceUsingDataSinkUsingBufferCallbackOnSinkFull(
        DataSource<T>& p_source, DataSink<T>& p_sink, Buffer<T>& p_buffer,
        Callback& p_sinkFull
    )
    {

        ValidateDataSource(p_source);
        ValidateDataSink(p_sink);
        ValidateBuffer(p_buffer);
        ValidateCallback(p_sinkFull);


        bool l_sourceNotEmpty = true;

        Callback l_handleSourceEmpty(
            &l_sourceNotEmpty, SetToFalse_AssumeStateIsLocationOfBool
        );

        void* l_handleSinkFullState[2];
        l_handleSinkFullState[0] = &l_sourceNotEmpty;
        l_handleSinkFullState[1] = &p_sinkFull;
        Callback l_handleSinkFull(
            l_handleSinkFullState,
            CallbackWriteUsingDataSourceUsingDataSinkUsingBufferCallbackOnSinkFull
        );

        do
        {
            
            p_buffer.ReadUsingDataSourceCallbackOnDataSourceEmpty(p_source, l_handleSourceEmpty);
            p_buffer.WriteUsingDataSinkCallbackOnDataSinkFull(p_sink, l_handleSinkFull);

        } while (l_sourceNotEmpty);

    }

}

#endif //SINK_SOURCE_BUFFER__GLUE_SINK_SOURCE_BUFFER_SINK_SOURCE_BUFFER_DEFINITION_HPP