#ifndef INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DEFINITION_HPP
#define INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DEFINITION_HPP

#include "Indexable/IndexableDefinition.hpp"
#include "DataSink/DataSinkDefinition.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    //TODO: Data sink that uses an indexable underneath.

    template<typename T>
    void WriteIndexableToDataSinkToSizeAsWrittenCallbackOnSinkFull(
        Indexable<T>& p_indexable, DataSink<T>& p_sink, Size& p_written,
        Callback& p_sinkFull
    )
    {

        ValidateIndexable(p_indexable);
        ValidateDataSink(p_sink);
        ValidateCallback(p_sinkFull);


        p_written = 0;

        Batch<T> l_curBatch;
        p_indexable.ReadToBatchFromSizeAsIndexCallbackOnInvalidIndex(
            l_curBatch, 0, g_NullCallback
        );

        bool l_notEnd = true;
        
        Size l_written = 0;
        
        Callback l_handleEndOfIndexable(
            &l_notEnd, SetToFalse_AssumeStateIsLocationOfBool
        );

        void* l_stateForHandleSinkFull[2];
        l_stateForHandleSinkFull[0] = &l_handleEndOfIndexable;
        l_stateForHandleSinkFull[1] = &p_sinkFull;
        Callback l_handleSinkFull(
            l_stateForHandleSinkFull, ForkCallback_AssumingStateHasCallbacks
        );

        do
        {
            
            p_sink.WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
                *(Array<T>*)&l_curBatch, l_written, l_handleSinkFull
            );

            p_written += l_written;

            AdvanceUsingBatchAsLocationFromSizeAsAmount(l_curBatch, l_written);
            if(l_curBatch.m_NumberOfItemsAfterLocation == 0)
            {
                p_indexable.ReadToBatchAsNextCallbackOnEnd(
                    l_curBatch, l_handleEndOfIndexable
                );
                l_curBatch.AllToStart();
            }

        } while (l_notEnd);

    }

}

#endif //INDEXABLE_SINK__GLUE_INDEXABLE_SINK_INDEXABLE_SINK_DEFINITION_HPP