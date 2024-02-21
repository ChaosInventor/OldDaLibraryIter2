#ifndef DATA_SINK__DATA_SINK_DATA_SINK_DEFINITION_HPP
#define DATA_SINK__DATA_SINK_DATA_SINK_DEFINITION_HPP

#include "DataSinkDeclaration.hpp"
#include "Debug/Debug.hpp"
#include "Callback/Callback.hpp"
#include "Array/ArrayDefinition.hpp"

#define ValidateDataSink(p_sink)\
    Assert(                                                                         \
    (p_sink).m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull != nullptr, \
    "Cannot use data sink at " << &(p_sink)                                         \
    << " because its write function is null."                                       \
    )


namespace Library
{

    template<typename T>
    void CallbackWriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
        Callback& p_callback
    )
    {

        void** l_dataPack = (void**)p_callback.m_State;

        ReadOnlyArray<T>& l_arrayToWrite = *(ReadOnlyArray<T>*)l_dataPack[0];
        Callback& l_full = *(Callback*)l_dataPack[1];

        l_arrayToWrite.m_Size = 0;
        l_full();

    }


    template <typename T>
    struct DataSink
    {

        void* m_State;
        DataSinkWriteFunction<T>
            m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull;


        DataSink():
        m_State(nullptr),
        m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull(nullptr)
        { }
        DataSink(const DataSink<T>& p_other) = delete;
        DataSink(DataSink<T>&& p_other):
        m_State(p_other.m_State),
        m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull(
            p_other.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
        )
        {
            p_other.m_State = nullptr;
            p_other.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull = nullptr;
        }

        DataSink(
            DataSinkWriteFunction<T>
                p_writeFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
        ):
        m_State(nullptr),
        m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull(
            p_writeFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
        )
        { }
        DataSink(
            void* const& p_state,
            DataSinkWriteFunction<T>
                p_writeFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
        ):
        m_State(p_state),
        m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull(
            p_writeFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
        )
        { }
        

        DataSink<T>& operator= (const DataSink<T>& p_other) = delete;
        DataSink<T>& operator= (DataSink<T>&& p_other)
        {
        
            m_State = p_other.m_State;
            m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull =
                p_other.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull;

            p_other.m_State = nullptr;
            p_other.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull = nullptr;

            return *this;
        
        }

        inline void WriteFromArrayToSizeAsWrittenCallbackOnFull(
            const ReadOnlyArray<T>& p_arrayToWrite, Size& p_numberOfWrittenItems,
            Callback& p_full
        )
        {
            ValidateDataSink(*this);
            m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull(
                p_arrayToWrite, *this, p_numberOfWrittenItems, p_full
            );
        }
        inline void WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
            ReadOnlyArray<T> p_arrayToWrite, Size& p_numberOfWrittenItems,
            Callback& p_full
        )
        {
            
            Size l_written = 0;
            p_numberOfWrittenItems = 0;

            void* l_dataForCallback[2];
            l_dataForCallback[0] = &p_arrayToWrite;
            l_dataForCallback[1] = &p_full;

            Callback l_whenFull(
                l_dataForCallback,
                CallbackWriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely<T>
            );

            while(p_arrayToWrite.m_Size != 0)
            {

                WriteFromArrayToSizeAsWrittenCallbackOnFull(
                    p_arrayToWrite, l_written,
                    l_whenFull
                );

                p_numberOfWrittenItems += l_written;

                CreateUsingArrayAsSubArrayWithoutBackByFromSizeAsCount(p_arrayToWrite, l_written);
            }

        }

    };


    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_Null(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    )
    {
        (void)p_toSink;
        (void)p_full;
        p_numberOfWrittenItems = p_arrayToWrite.m_Size;
    }
    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_Full(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    )
    {
        (void)p_toSink;
        (void)p_full;
        (void)p_arrayToWrite;
        ValidateCallback(p_full)
        p_numberOfWrittenItems = 0;
        p_full();
    }

}

#endif //DATA_SINK__DATA_SINK_DATA_SINK_DEFINITION_HPP