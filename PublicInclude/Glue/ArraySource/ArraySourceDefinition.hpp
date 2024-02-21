#ifndef DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DEFINITION_HPP
#define DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "ArraySourceDeclaration.hpp"
#include "DataSource/DataSourceDefinition.hpp"
#include "Array/ArrayDefinition.hpp"

#define ValidateArraySource(p_arraySource)\
    Check(                                                                      \
        p_arraySource.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty            \
        ==                                                                      \
        ReadArrayOfDataFromDataSourceCallbackOnFailure_ArraySource,             \
        "The given DataSource dose not appear to be an ArraySource."            \
    );                                                                          \
    Assert(                                                                     \
        p_arraySource.m_State != nullptr,                                       \
        "An ArraySource cannot have a null state."                              \
    );                                                                          \
    ValidateArray(((ArraySource<T>*)p_arraySource.m_State)->m_Array)            \
    Assert(                                                                     \
        ((ArraySource<T>*)p_arraySource.m_State)->m_Used                        \
        >                                                                       \
        ((ArraySource<T>*)p_arraySource.m_State)->m_Array.m_Size,               \
        "ArraySource cannot have used more items than there are in the array."  \
    )


namespace Library::Glue
{

    template<typename T>
    struct ArraySource
    {

        Array<T> m_Array;
        Size m_Used;

        ArraySource():
        m_Array(),
        m_Used(0)
        { }
        ArraySource(const ArraySource<T>& p_other):
        m_Array(p_other.m_Array),
        m_Used(p_other.m_Used)
        { }
        ArraySource(ArraySource<T>&& p_other):
        m_Array(p_other.m_Array),
        m_Used(p_other.m_Used)
        {
            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;
        }

        ArraySource(const Array<T>& p_array)
        {
            CreateArraySourceAtFromArray(*this, p_array);
        }


        ArraySource<T>& operator=(const ArraySource<T>& p_other)
        {
            m_Array = Array<T>(p_other.m_Array);
            m_Used = p_other.m_Used;
            return *this;
        }
        ArraySource<T>& operator=(ArraySource<T>&& p_other)
        {

            m_Array = Array<T>(p_other.m_Array);
            m_Used = p_other.m_Used;

            p_other.m_Array = Array<T>();
            p_other.m_Used = 0;
        
            return *this;

        }

        operator Array<T>()
        {
            return m_Array;
        }
        operator DataSource<T>()
        {
            DataSource<T> l_returnValue;
            CreateDataSourceAtFromArraySource(l_returnValue, *this);
            return l_returnValue;
        }

    };


    template<typename T>
    void CreateArraySourceAtFromArray(
        ArraySource<T>& p_location,
        const Array<T>& p_sourceArray
    )
    {
        p_location.m_Array = p_sourceArray;
        p_location.m_Used = 0;
    }
    template<typename T>
    void CreateDataSourceAtFromArraySource(
        DataSource<T>& p_location,
        ArraySource<T>& p_arraySource
    )
    {
        p_location.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty = 
            ReadArrayOfDataFromDataSourceCallbackOnFailure_ArraySource;
        p_location.m_State = (void*)&p_arraySource;
    }


    template<typename T>
    Size ReadArrayOfDataFromDataSourceCallbackOnFailure_ArraySource(
        Array<T>& p_data,
        DataSource<T>& p_source,
        Callback& p_callback
    )
    {

        ValidateArray(p_data);
        ValidateCallback(p_callback);
        ValidateArraySource(p_source);


        ArraySource<T>& l_arraySource = *((ArraySource<T>*)p_source.m_State);

        if(l_arraySource.m_Used == l_arraySource.m_Array.m_Size)
        {
            p_callback();
            return 0;
        }

        Size l_read;
        for(l_read = 0; l_read < p_data.m_Size; ++l_read)
        {
            p_data[l_read] = l_arraySource.m_Array[l_arraySource.m_Used];
            
            ++l_arraySource.m_Used;
            if(l_arraySource.m_Used == l_arraySource.m_Array.m_Size)
            {
                break;
            }
        }

        return l_read;

    }

}

#endif //DATA_SOURCE__DATA_SOURCE_ARRAY_SOURCE_DEFINITION_HPP