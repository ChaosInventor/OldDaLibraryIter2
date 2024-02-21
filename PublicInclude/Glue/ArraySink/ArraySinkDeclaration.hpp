#ifndef ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DECLARATION_HPP
#define ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DECLARATION_HPP

#include "Array/ArrayDeclaration.hpp"
#include "DataSink/DataSink.hpp"

#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"

namespace Library::Glue
{

    template<typename T>
    struct ArraySink;


    template<typename T>
    void CreateArraySinkAtFromArray(
        ArraySink<T>& p_location,
        const Array<T>& p_array
    );
    template<typename T>
    void CreateDataSinkAtFromArraySink(
        DataSink<T>& p_location,
        ArraySink<T>& p_arraySink
    );


    template<typename T>
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_ArraySink(
        const ReadOnlyArray<T>& p_arrayToWrite, DataSink<T>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    );

}

#endif //ARRAY_SINK__GLUE_ARRAY_SINK_ARRAY_SINK_DECLARATION_HPP