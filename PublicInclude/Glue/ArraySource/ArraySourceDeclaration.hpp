#ifndef DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DECLARATION_HPP
#define DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"
#include "Array/ArrayDeclaration.hpp"
#include "DataSource/DataSourceDeclaration.hpp"

namespace Library::Glue
{

    template<typename T>
    struct ArraySource;


    template<typename T>
    void CreateArraySourceAtFromArray(
        ArraySource<T>& p_location,
        const Array<T>& p_sourceArray
    );
    template<typename T>
    void CreateDataSourceAtFromArraySource(
        DataSource<T>& p_location,
        ArraySource<T>& p_arraySource
    );


    template<typename T>
    Size ReadArrayOfDataFromDataSourceCallbackOnFailure_ArraySource(
        Array<T>& p_data,
        DataSource<T>& p_source,
        Callback& p_callback
    );

}

#endif //DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DECLARATION_HPP