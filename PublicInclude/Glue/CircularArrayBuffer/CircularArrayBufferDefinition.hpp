#ifndef CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DEFINITION_HPP
#define CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DEFINITION_HPP

#include "CircularArrayBufferDeclaration.hpp"
#include "CircularArray/CircularArrayDefinition.hpp"
#include "Buffer/BufferDefinition.hpp"
#include "Glue/CircularArrayIndexRange/CircularArrayIndexRange.hpp"
#include "Glue/ArrayIndexRange/ArrayIndexRange.hpp"

namespace Library::Glue
{

    template<typename T>
    struct CircularArrayBuffer
    {

        CircularArray<T> m_CArrayBackend;

        //TODO: Functions such as this that cannot be easily described using
        //actions, or which can, but it will defeat their purpose of being quick
        //aliases.
        inline void Discard()
        {
            m_CArrayBackend.m_Front = 0;
            m_CArrayBackend.m_Back = 0;
        }

    };


    template<typename T>
    void CreateToCircularArrayBufferUsingCircularArray(
        CircularArrayBuffer<T>& p_cArrayBuffer,
        CircularArray<T>& p_circularArray
    )
    {
        ValidateCircularArray(p_circularArray);
        p_cArrayBuffer.m_CArrayBackend = p_circularArray;
    }
    template<typename T>
    void CreateToBufferUsingCircularArrayBuffer(
        Buffer<T>& p_buffer, CircularArrayBuffer<T>& p_cArrayBuffer
    )
    {
        p_buffer.m_State = &p_cArrayBuffer;
        p_buffer.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty =
            ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_CircularArrayBuffer;
        p_buffer.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull = 
            WriteUsingDataSinkUsingBufferCallbackOnSinkFull_CircuarArrayBuffer;
    }


    template<typename T>
    void ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_CircularArrayBuffer(
        DataSource<T>& p_fromSource, Buffer<T>& p_toBuffer,
        Callback& p_sourceEmpty
    )
    {

        ValidateDataSource(p_fromSource);
        ValidateCallback(p_sourceEmpty);

        Assume(p_toBuffer.m_State != nullptr);
        Check(
            p_toBuffer.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty
            ==
            ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_CircularArrayBuffer<T>,
            "This buffer interface dose not appear to be a circular array buffer"
        );
        Check(
            p_toBuffer.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull
            ==
            WriteUsingDataSinkUsingBufferCallbackOnSinkFull_CircuarArrayBuffer<T>,
            "This buffer interface dose not appear to be a circular array buffer"
        );


        CircularArrayBuffer<T>& l_self =
            *(CircularArrayBuffer<T>*)p_toBuffer.m_State;

        IndexRange l_rangeOfFreeSpace;
        CreateToIndexRangeAsFreeSpaceAfterFrontFromCircularArray(
            l_rangeOfFreeSpace, l_self.m_CArrayBackend
        );
        Array<T> l_freeSpace;
        CreateToArrayAsSubArrayFromArrayFromIndexRange(
            l_freeSpace, l_self.m_CArrayBackend.m_UnderlyingArray,
            l_rangeOfFreeSpace
        );

        Size l_red;

        bool l_sourceEmpty = false;

        Callback l_handleSourceEmpty(
            &l_sourceEmpty, SetToTrue_AssumeStateIsLocationOfBool
        );

        while(l_freeSpace.m_Size > 0)
        {
            p_fromSource.ReadFromArrayToSizeAsRedCallbackOnEmpty_Entirely(
                l_freeSpace, l_red, l_handleSourceEmpty
            );

            AdvanceUsingCircularArrayAsFrontFromSizeAsAmount(
                l_self.m_CArrayBackend, l_red
            );

            if(l_sourceEmpty)
            {
                p_sourceEmpty();
                return;
            }

            CreateToIndexRangeAsFreeSpaceAfterFrontFromCircularArray(
                l_rangeOfFreeSpace, l_self.m_CArrayBackend

            );
            //TODO: More elegant solution.
            if(l_rangeOfFreeSpace == IndexRange())
            {
                return;
            }
            CreateToArrayAsSubArrayFromArrayFromIndexRange(
                l_freeSpace, l_self.m_CArrayBackend.m_UnderlyingArray,
                l_rangeOfFreeSpace
            );

        }

    }
    template<typename T>
    void WriteUsingDataSinkUsingBufferCallbackOnSinkFull_CircuarArrayBuffer(
        DataSink<T>& p_toSink, Buffer<T>& p_fromBuffer,
        Callback& p_sinkFull
    )
    {

        ValidateDataSink(p_toSink);
        ValidateCallback(p_sinkFull);

        Assume(p_fromBuffer.m_State != nullptr);
        Check(
            p_fromBuffer.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty
            ==
            ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty_CircularArrayBuffer<T>,
            "This buffer interface dose not appear to be a circular array buffer"
        );
        Check(
            p_fromBuffer.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull
            ==
            WriteUsingDataSinkUsingBufferCallbackOnSinkFull_CircuarArrayBuffer<T>,
            "This buffer interface dose not appear to be a circular array buffer"
        );


        CircularArrayBuffer<T>& l_self =
            *(CircularArrayBuffer<T>*)p_fromBuffer.m_State;

        IndexRange l_rangeOfFullSpace;
        CreateToIndexRangeAsFullSpaceAfterBackFromCircularArray(
            l_rangeOfFullSpace, l_self.m_CArrayBackend
        );
        Array<T> l_fullSpace;
        CreateToArrayAsSubArrayFromArrayFromIndexRange(
            l_fullSpace, l_self.m_CArrayBackend.m_UnderlyingArray,
            l_rangeOfFullSpace
        );

        Size l_written;

        bool l_sinkFull = false;

        Callback l_handleSinkFull(
            &l_sinkFull, SetToTrue_AssumeStateIsLocationOfBool
        );

        while(l_fullSpace.m_Size > 0)
        {
            p_toSink.WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
                l_fullSpace, l_written, l_handleSinkFull
            );

            AdvanceUsingCircularArrayAsBackFromSizeAsAmount(
                l_self.m_CArrayBackend, l_written
            );

            if(l_sinkFull)
            {
                p_sinkFull();
                return;
            }

            CreateToIndexRangeAsFullSpaceAfterBackFromCircularArray(
                l_rangeOfFullSpace, l_self.m_CArrayBackend
            );
            //TODO: More elegant solution.
            if(l_rangeOfFullSpace == IndexRange())
            {
                return;
            }
            CreateToArrayAsSubArrayFromArrayFromIndexRange(
                l_fullSpace, l_self.m_CArrayBackend.m_UnderlyingArray,
                l_rangeOfFullSpace
            );

        }

    }

}

#endif //CIRCULAR_ARRAY_BUFFER__GLUE_CIRCULAR_ARRAY_BUFFER_CIRCULAR_ARRAY_BUFFER_DEFINITION_HPP