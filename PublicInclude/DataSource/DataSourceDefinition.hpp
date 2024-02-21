#ifndef DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DEFINITION_HPP
#define DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DEFINITION_HPP

#include "DataSourceDeclaration.hpp"
#include "Array/ArrayDefinition.hpp"
#include "Callback/Callback.hpp"

#define ValidateDataSource(p_source)\
    Assert(                                                                     \
        (p_source).m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty !=  \
            nullptr,                                                            \
        "Cannot use data source at " << &(p_source)                             \
        << " because it's read function is null"                                \
    );

namespace Library
{

    template<typename T>
    void CallbackReadFromArrayToSizeAsRedCallbackOnEmpty_Entirely(
        Callback& p_callback
    )
    {

        void** l_dataPack = (void**)p_callback.m_State;

        Array<T>& l_array = *(Array<T>*)l_dataPack[0];
        Callback& l_empty = *(Callback*)l_dataPack[1];

        l_array.m_Size = 0;
        l_empty();

    }

    template<typename T>
    struct DataSource
    {

        void* m_State;
        DataSourceReadFunction<T>
            m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty;
    
        DataSource():
        m_State(nullptr),
        m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty(nullptr)
        { }
        DataSource(const DataSource& p_other) = delete;
        DataSource(DataSource&& p_other):
        m_State(p_other.m_State),
        m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty(
            p_other.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
        )
        {
            p_other.m_State = nullptr;
            p_other.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty = nullptr;
        }

        DataSource(
            DataSourceReadFunction<T>
                p_readFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
        ):
        m_State(nullptr),
        m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty(
            p_readFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
        )
        { }
        DataSource(
            void* const& p_state,
            DataSourceReadFunction<T>
                p_readFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
        ):
        m_State(p_state),
        m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty(
            p_readFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
        )
        { }


        DataSource& operator=(const DataSource& p_other) = delete;
        DataSource& operator=(DataSource&& p_other)
        {
        
            m_State = p_other.m_State;
            m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty =
                p_other.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty;

            p_other.m_State = nullptr;
            p_other.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty = nullptr;

            return *this;
        
        }

        inline void ReadFromArrayToSizeAsRedCallbackOnEmpty(
            Array<T>& p_array, Size& p_numberOfRedItems, Callback& p_empty
        )
        {
            ValidateDataSource(*this);
            m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty(
                p_array, *this, p_numberOfRedItems, p_empty
            );
        }
        inline void ReadFromArrayToSizeAsRedCallbackOnEmpty_Entirely(
            Array<T>& p_array, Size& p_numberOfRedItems, Callback& p_empty
        )
        {
            
            Size l_red = 0;
            p_numberOfRedItems = 0;

            void* l_onEmptyData[2];
            l_onEmptyData[0] = &p_array;
            l_onEmptyData[1] = &p_empty;

            Callback l_onEmpty(
                l_onEmptyData,
                CallbackReadFromArrayToSizeAsRedCallbackOnEmpty_Entirely<T>
            );

            while(p_array.m_Size != 0)
            {
                ReadFromArrayToSizeAsRedCallbackOnEmpty(
                    p_array, l_red,
                    l_onEmpty
                );

                p_numberOfRedItems += l_red;

                CreateUsingArrayAsSubArrayWithoutBackByFromSizeAsCount(p_array, l_red);
            }

        }

    };


    template<typename T>
    void ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty_Null(
        const Array<T>& p_fromArray, DataSource<T>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    )
    {
        (void)p_usingSource;
        (void)p_empty;
        p_numberOfRedItems = p_fromArray.m_Size;
    }
    template<typename T>
    void ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty_Empty(
        const Array<T>& p_fromArray, DataSource<T>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    )
    {
    
        (void)p_fromArray;
        (void)p_usingSource;
        ValidateCallback(p_empty);


        p_numberOfRedItems = 0;
        p_empty();
    
    }

}

#endif //DATA_SOURCE__DATA_SOURCE_DATA_SOURCE_DEFINITION_HPP