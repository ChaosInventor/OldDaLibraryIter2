#ifndef INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DECLARATION_HPP
#define INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DECLARATION_HPP

#include "Indexable/IndexableDeclaration.hpp"
#include "DataSink/DataSinkDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    //TODO: Data sink that uses an indexable underneath.

    template<typename T>
    void WriteIndexableToDataSinkCallbackOnSinkFull(
        Indexable<T>& p_indexable, DataSink<T>& p_sink, Callback& p_sinkFull
    );

}

#endif //INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DECLARATION_HPP