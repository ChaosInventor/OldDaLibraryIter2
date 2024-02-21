#include "DataSource/DataSource.hpp"

#include <unistd.h>

namespace Library
{

    //TODO: Platfrom independent
    void ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_STD(
        const Array<Byte>& p_fromArray, DataSource<Byte>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    )
    {

        ValidateCallback(p_empty);


        if(ArrayIsNull(p_fromArray))
        {
            p_numberOfRedItems = 0;
            return;
        }

        ssize_t l_read = read(
            *(int*)p_usingSource.m_State, p_fromArray.m_Location,
            p_fromArray.m_Size
        );
        //If an error occurred or nothing was red, don't bother to fix
        //it just make the sink full permanently.
        if(l_read <= 0)
        {
            p_usingSource.m_State = nullptr;
            p_usingSource.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty = 
                ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty_Empty;

            p_numberOfRedItems = 0;
            p_empty();

            return;
        }

        p_numberOfRedItems = l_read;

    }
  
    const int g_STD_IN_FILE_DESC = STDIN_FILENO;

    DataSource<Byte> g_StandardInput(
        (void*)&g_STD_IN_FILE_DESC,
        ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_STD
    );

}
