#ifndef DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DECLARATION_HPP
#define DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Array/ArrayDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library
{

    template<typename T>
    struct DataSource;


    template<typename T>
    using DataSourceReadFunction = void (*)(
        const Array<T>& p_fromArray, DataSource<T>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    );


    //TODO: Is there a better place to place this constants?
    extern DataSource<Byte> g_StandardInput;


    template<typename T>
    void ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty_Null(
        const Array<T>& p_fromArray, DataSource<T>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    );
    template<typename T>
    void ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty_Empty(
        const Array<T>& p_fromArray, DataSource<T>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    );

}

#endif //DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DECLARATION_HPP