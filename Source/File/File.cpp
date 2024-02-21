#include "File/File.hpp"
#include "Memory/MemoryDefinition.hpp"

#include <unistd.h>
#include <fcntl.h>

namespace Library
{

    struct File
    {

        int m_FileDesc;
        Offset m_Size;

    };


    Byte g_FileReadableBit = 0b01;
    Byte g_FileWritableBit = 0b10;

    //TODO:
    FileCallbackBundle g_DefaultFileCallbackBundle;


    void AllocateUsingDataSinkOfFilePointerFromSizeAsAmountToSizeAsAllocatedUsingMemoryManagerCallbackOnNoMem(
        DataSink<File*>&& p_sink, const Size& p_allocate, Size& p_allocated,
        MemoryManager& p_manager, Callback& p_noMemory
    )
    {

        Size l_toAllocate = p_allocate * sizeof(File);
        if(SIZE_MAXIMUM / sizeof(File) < p_allocate)
        {
            l_toAllocate = (SIZE_MAXIMUM / sizeof(File)) * sizeof(File);
        }

        Memory l_memForFiles(
            nullptr, l_toAllocate,
            g_MemoryReadableBit | g_MemoryWriteableBit
        );

        p_manager.AllocateMemoryCallbackOnFailure(l_memForFiles, p_noMemory);

        //TODO: Does memory get 0ed out on a failed allocation?
        p_sink.WriteFromArrayToSizeAsWrittenCallbackOnFull_Entirely(
            Array<File*>(
                (File**)&l_memForFiles.m_Location,
                l_memForFiles.m_Size / sizeof(File)
            ),
            p_allocated, g_NullCallback
        );

    }

    void CreateToFilePointerFromCStringAsPathFromByteAsPermissionsCallbackBundleOnFailure(
        File*& p_file, const char* p_filePath, const Byte& p_permissions,
        FileCallbackBundle& p_callbacks
    )
    {
        Warn("Not implemented");
        //TODO:
    }


    void FindToFilePointerFromCStringAsPathFromByteAsPermissionsCallbackBundleOnFailure(
        File*& p_file, const char* p_filePath, const Byte& p_permissions,
        FileCallbackBundle& p_callbacks
    )
    {
        
        int l_flags = O_CLOEXEC;
        if((p_permissions & g_FileReadableBit) == g_FileReadableBit)
        {
            l_flags |= O_RDONLY;
        }
        if((p_permissions & g_FileWritableBit) == g_FileWritableBit)
        {
            l_flags |= O_WRONLY;
        }

        p_file->m_FileDesc = open(p_filePath, l_flags);
        Assert(p_file->m_FileDesc > -1, "Error handling for opening files in not implemented yet");

    }


    void ReadFromArrayOfByteUsingFilePointerFromOffsetToSizeAsRedCallbackOnFailure(
        const Array<Byte>& p_array, File*& p_file, const Offset& p_offset,
        Size& p_red, Callback& p_file_error
    )
    {

        ValidateArray(p_array);
        ValidateCallback(p_file_error);

        p_red = pread(p_file->m_FileDesc, p_array.m_Location, p_array.m_Size, p_offset);
        if(p_red <= 0)
        {
            p_red = 0;
            p_file_error();
            return;
        }

    }

    void WriteFromArrayOfByteUsingFilePointerFromOffsetToSizeAsWrittenCallbackOnFailure(
        const Array<Byte>& p_array, File*& p_file, const Offset& p_offset,
        Size& p_written, Callback& p_file_error
    )
    {

        ValidateArray(p_array);
        ValidateCallback(p_file_error);

        p_written = pwrite(p_file->m_FileDesc, p_array.m_Location, p_array.m_Size, p_offset);
        if(p_written <= 0)
        {
            p_written = 0;
            p_file_error();
            return;
        }

    }


    void DeallocateUsingDataSourceOfFileUsingMemoryManager(
        DataSource<File*>& p_source, MemoryManager& p_manager
    )
    {
        
    }


}