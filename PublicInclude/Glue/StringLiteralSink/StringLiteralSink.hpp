#ifndef STRING_LITERAL_SINK__GLUE_STRING_LITERAL_SINK_STRING_LITERAL_SINK_HPP
#define STRING_LITERAL_SINK__GLUE_STRING_LITERAL_SINK_STRING_LITERAL_SINK_HPP

#include "StringLiteral/StringLiteral.hpp"
#include "DataSink/DataSinkDeclaration.hpp"

namespace Library::Glue
{

    void
    WriteFromStringLiteralUsingDataSinkOfByteToSizeAsWrittenCallbackOnSinkFull(
        const StringLiteral& p_literal, DataSink<Byte>& p_sink, Size& p_written,
        Callback& p_sinkFull
    );
    void
    WriteFromStringLiteralUsingDataSinkOfCharToSizeAsWrittenCallbackOnSinkFull(
        const StringLiteral& p_literal, DataSink<char>& p_sink, Size& p_written,
        Callback& p_sinkFull
    );


    const StringLiteral& operator<<(
        DataSink<Byte>& p_sink, const StringLiteral& p_string
    );
    const StringLiteral& operator<<(
        DataSink<char>& p_sink, const StringLiteral& p_string
    );

}

#endif //STRING_LITERAL_SINK__GLUE_STRING_LITERAL_SINK_STRING_LITERAL_SINK_HPP