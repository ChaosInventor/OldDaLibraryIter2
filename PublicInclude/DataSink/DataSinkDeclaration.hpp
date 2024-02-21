#ifndef DATA_SINK__DATA_SINK_DATA_SINK_DECLARATION_HPP
#define DATA_SINK__DATA_SINK_DATA_SINK_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Array/ArrayDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library
{

    template<typename T>
    struct DataSink;


    template<typename T>
    using DataSinkWriteFunction = void (*) (
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    );


    //TODO: Is there a better place to place stdout and stderr than here? A proccess module perhaps?
    extern DataSink<Byte> g_StandardOutput;
    extern DataSink<Byte> g_StandardError;


    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_Null(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    );
    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_Full(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    );

}

#endif //DATA_SINK__DATA_SINK_DATA_SINK_DECLARATION_HPP