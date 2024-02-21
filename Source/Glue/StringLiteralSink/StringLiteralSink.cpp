#include "Glue/StringLiteralSink/StringLiteralSink.hpp"
#include "DataSink/DataSinkDefinition.hpp"

namespace Library::Glue
{

    void
    WriteFromStringLiteralUsingDataSinkOfByteToSizeAsWrittenCallbackOnSinkFull(
        const StringLiteral& p_literal, DataSink<Byte>& p_sink, Size& p_written,
        Callback& p_sinkFull
    )
    {
        //TODO: This is kinda pushing the limits, it might be a problem and
        //be rather buggy.
        Array<Byte> l_literalAsArray(
            (Byte*)p_literal.m_Location, sizeof(char) * p_literal.m_Length
        );
        p_sink.WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
            l_literalAsArray, p_written, p_sinkFull
        );
    }
    void
    WriteFromStringLiteralUsingDataSinkOfCharToSizeAsWrittenCallbackOnSinkFull(
        const StringLiteral& p_literal, DataSink<char>& p_sink, Size& p_written,
        Callback& p_sinkFull
    )
    {
        Array<char> l_literalAsArray(
            (char*)p_literal.m_Location, p_literal.m_Length
        );
        p_sink.WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
            l_literalAsArray, p_written, p_sinkFull
        );
    }

    const StringLiteral& operator<<(
        DataSink<Byte>& p_sink, const StringLiteral& p_string
    )
    {
        Size l_tmp;
        WriteFromStringLiteralUsingDataSinkOfByteToSizeAsWrittenCallbackOnSinkFull(
            p_string, p_sink, l_tmp, g_NullCallback
        );
        return p_string;
    }
    const StringLiteral& operator<<(
        DataSink<char>& p_sink, const StringLiteral& p_string
    )
    {
        Size l_tmp;
        WriteFromStringLiteralUsingDataSinkOfCharToSizeAsWrittenCallbackOnSinkFull(
            p_string, p_sink, l_tmp, g_NullCallback
        );
        return p_string;
    }

}