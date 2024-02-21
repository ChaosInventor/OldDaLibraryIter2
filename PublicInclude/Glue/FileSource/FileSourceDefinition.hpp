#ifndef FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DEFINITION_HPP
#define FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DEFINITION_HPP

#include "DataSource/DataSourceDefinition.hpp"
#include "File/File.hpp"

namespace Library::Glue
{
 
    struct FileSource
    {
        File* m_MyFile;
        Offset m_CurrentOffset;
    };

    void CreateToFileSourceUsingFilePointer(
        FileSource& p_fileSource, File*& p_file
    )
    {
        p_fileSource.m_MyFile = p_file;
        p_fileSource.m_CurrentOffset = 0;
    }
    void CreateToDataSourceOfByteUsingFileSource(
        DataSource<Byte>& p_source, FileSource& p_fileSource
    )
    {
        p_source.m_State = &p_fileSource;
        p_source.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty =
            ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_FileSource;
    }


    void
    ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_FileSource(
        const Array<Byte>& p_fromArray, DataSource<Byte>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    )
    {

        ValidateArray(p_fromArray);
        ValidateDataSource(p_usingSource);
        ValidateCallback(p_empty);

        Assert(
            p_usingSource.m_State != nullptr,
            "State of file source may not be null"
        );
        Check(
            p_usingSource.m_ReadFromArrayUsingDataSourceToSizeAsRedCallbackOnEmpty
            ==
            ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_FileSource,
            "The given data source does not appear to be a file source"
        );


        if(ArrayIsNull(p_fromArray))
        {
            p_numberOfRedItems = 0;
            return;
        }

        FileSource& l_self = *(FileSource*)p_usingSource.m_State;

        ReadFromArrayOfByteUsingFilePointerFromOffsetToSizeAsRedCallbackOnFailure(
            p_fromArray, l_self.m_MyFile, l_self.m_CurrentOffset,
            p_numberOfRedItems, p_empty
        );

        l_self.m_CurrentOffset += p_numberOfRedItems;

    }

}

#endif //FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DEFINITION_HPP