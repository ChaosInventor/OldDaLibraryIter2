#ifndef ASCII_SINK__GLUE_ASCII_SINK_ASCII_SINK_HPP
#define ASCII_SINK__GLUE_ASCII_SINK_ASCII_SINK_HPP

#include "ASCIIString/ASCIIString.hpp"
#include "DataSink/DataSink.hpp"

namespace Library::Glue
{

    void WriteASCIIStringToDataSinkOfByte(
        ASCIIString&& p_string, DataSink<Byte>& p_sink
    );

}

#endif //ASCII_SINK__GLUE_ASCII_SINK_ASCII_SINK_HPP