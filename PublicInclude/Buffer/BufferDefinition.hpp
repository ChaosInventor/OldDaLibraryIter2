#ifndef BUFFER__BUFFER_BUFFER_DEFINITION_HPP
#define BUFFER__BUFFER_BUFFER_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "BufferDeclaration.hpp"

#define ValidateBuffer(p_buffer)\
Assert(                                                             \
    (p_buffer).m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty\
    !=                                                              \
    nullptr,                                                        \
    "Buffer cannot have any of it's funtions as null"               \
);                                                                  \
Assert(                                                             \
    (p_buffer).m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull    \
    !=                                                              \
    nullptr,                                                        \
    "Buffer cannot have any of it's funtions as null"               \
);


namespace Library
{

    template<typename T>
    struct Buffer
    {

        void* m_State;

        BufferReadFunction<T>
            m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty;
        BufferWriteFunction<T>
            m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull;

        Buffer():
        m_State(nullptr),
        m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty(
            nullptr
        ),
        m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull(
            nullptr
        )
        { }
        Buffer(const Buffer<T>& p_other) = delete;
        Buffer(Buffer<T>&& p_other):
        m_State(p_other.m_State),
        m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty(
            p_other.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty
        ),
        m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull(
            p_other.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull
        )
        {
            p_other.m_State = nullptr;
            p_other.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty = nullptr;
            p_other.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull = nullptr;
        }

        Buffer(
            void* p_state,
            BufferReadFunction<T>
                p_readUsingDataSourceUsingBufferCallbackOnSourceEmpty,
            BufferWriteFunction<T>
                p_writeUsingDataSinkUsingBufferCallbackOnSinkFull
        ):
        m_State(p_state),
        m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty(
            p_readUsingDataSourceUsingBufferCallbackOnSourceEmpty
        ),
        m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull(
            p_writeUsingDataSinkUsingBufferCallbackOnSinkFull
        )
        { }


        Buffer<T>& operator=(const Buffer<T>& p_other) = delete;
        Buffer<T>& operator=(Buffer<T>&& p_other)
        {

            m_State = p_other.m_State;
            m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty =
                p_other.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty;
            m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull =
                p_other.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull;

            p_other.m_State = nullptr;
            p_other.m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty = nullptr;
            p_other.m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull = nullptr;

            return *this;

        }


        inline void ReadUsingDataSourceCallbackOnDataSourceEmpty(
            DataSource<T>& p_fromSource,
            Callback& p_sourceEmpty
        )
        {
            ValidateBuffer(*this);
            m_ReadUsingDataSourceUsingBufferCallbackOnSourceEmpty(
                p_fromSource, *this, p_sourceEmpty
            );
        }
        inline void ReadUsingDataSource(DataSource<T>& p_fromSource)
        {
            ReadUsingDataSourceCallbackOnDataSourceEmpty(
                p_fromSource, g_NullCallback
            );
        }

        inline void WriteUsingDataSinkCallbackOnDataSinkFull(
            DataSink<T>& p_toSink,
            Callback& p_sinkFull
        )
        {
            ValidateBuffer(*this);
            m_WriteUsingDataSinkUsingBufferCallbackOnSinkFull(
                p_toSink, *this, p_sinkFull
            );
        }
        inline void WriteUsingDataSink(DataSink<T>& p_toSink)
        {
            WriteUsingDataSinkCallbackOnDataSinkFull(
                p_toSink, g_NullCallback
            );
        }

    };

}

#endif //BUFFER__BUFFER_BUFFER_HPP