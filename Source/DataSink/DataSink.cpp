#include "DataSink/DataSink.hpp"

#include <unistd.h>

namespace Library
{

    //TODO: Make platfrom independent.
    void WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_STD(
        const ReadOnlyArray<Byte>& p_arrayToWrite, DataSink<Byte>& p_toSink,
        Size& p_numberOfWrittenItems, Callback& p_full
    )
    {

        ValidateArray(p_arrayToWrite);
        ValidateCallback(p_full);
        Check(
            p_toSink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull
            ==
            WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_STD,
            "Given data sink does not apper to be a standard sink."
        );
        Assert(
            p_toSink.m_State != nullptr,
            "State of standard data sink cannot be null."
        );


        if(ArrayIsNull(p_arrayToWrite))
        {
            p_numberOfWrittenItems = 0;
            return;
        }

        ssize_t l_written = write(
            *(int*)p_toSink.m_State,
            p_arrayToWrite.m_Location, p_arrayToWrite.m_Size
        );
        //If an error occurred or nothing was written, don't bother to fix
        //it just make the sink full permanently.
        if(l_written <= 0)
        {            
            //TODO: Proper error handling.

            p_toSink.m_WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull =
                WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_Full;
            p_toSink.m_State = nullptr;

            p_numberOfWrittenItems = 0;

            p_full();
            return;
        }

        p_numberOfWrittenItems = l_written;

    }


    const int g_STD_OUT_FILE_DESC = STDOUT_FILENO;
    const int g_STD_ERR_FILE_DESC = STDERR_FILENO;

    DataSink<Byte> g_StandardOutput(
        (void*)&g_STD_OUT_FILE_DESC,
        WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_STD
    );
    DataSink<Byte> g_StandardError(
        (void*)&g_STD_ERR_FILE_DESC,
        WriteFromArrayUsingDataSinkToSizeAsWrittenCallbackOnFull_STD
    );

}
