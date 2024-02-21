#ifndef BUFFER__BUFFER_BUFFER_DECLARATION_HPP
#define BUFFER__BUFFER_BUFFER_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "DataSource/DataSourceDeclaration.hpp"
#include "DataSink/DataSinkDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library
{

    template<typename T>
    struct Buffer;


    template<typename T>
    using BufferReadFunction = void (*) (
        DataSource<T>& p_fromSource, Buffer<T>& p_toBuffer,
        Callback& p_sourceEmpty
    );
    template<typename T>
    using BufferWriteFunction = void (*) (
        DataSink<T>& p_toSink, Buffer<T>& p_fromBuffer,
        Callback& p_sinkFull
    );

}

#endif //BUFFER__BUFFER_BUFFER_HPP