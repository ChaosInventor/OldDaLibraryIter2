#ifndef FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DECLARATION_HPP
#define FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DECLARATION_HPP

#include "DataSource/DataSourceDeclaration.hpp"
#include "File/File.hpp"

namespace Library::Glue
{
 
    struct FileSource;

    void CreateToFileSourceUsingFilePointer(
        FileSource& p_fileSource, File*& p_file
    );
    void CreateToDataSourceOfByteUsingFileSource(
        DataSource<Byte>& p_source, FileSource& p_fileSource
    );


    void
    ReadFromArrayOfByteUsingDataSourceToSizeAsRedCallbackOnEmpty_FileSource(
        const Array<Byte>& p_fromArray, DataSource<Byte>& p_usingSource,
        Size& p_numberOfRedItems, Callback& p_empty
    );

}

#endif //FILE_SOURCE__GLUE_FILE_SOURCE_FILE_SOURCE_DECLARATION_HPP