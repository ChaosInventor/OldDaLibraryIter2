#ifndef FILE__FILE_FILE_HPP
#define FILE__FILE_FILE_HPP

#include "Meta/Meta.hpp"
#include "DataSink/DataSink.hpp"
#include "DataSource/DataSource.hpp"
#include "MemoryManager/MemoryManager.hpp"

//TODO: Namespace for the file module should probably be under a platfrom abstraction namespace.
namespace Library
{

    struct File;

    struct FileCallbackBundle
    {

        Callback m_BadPath;
        Callback m_DoesNotExist;
        Callback m_NoPermission;
        Callback m_NotFile;
        Callback m_NotEnoughResources;
        Callback m_LowLevel;

    };


    //TODO: Platfrom independent
    using Offset = long long;


    extern Byte g_FileReadableBit;
    extern Byte g_FileWritableBit;

    extern FileCallbackBundle g_DefaultFileCallbackBundle;


    void AllocateUsingDataSinkOfFilePointerFromSizeAsAmountToSizeAsAllocatedUsingMemoryManagerCallbackOnNoMem(
        DataSink<File*>& p_sink, const Size& p_allocate, Size& p_allocated,
        MemoryManager& p_manager, Callback& p_noMemory
    );

    void CreateToFilePointerFromCStringAsPathFromByteAsPermissionsCallbackBundleOnFailure(
        File*& p_file, const char* p_filePath, const Byte& p_permissions,
        FileCallbackBundle& p_callbacks
    );


    void FindToFilePointerFromCStringAsPathFromByteAsPermissionsCallbackBundleOnFailure(
        File*& p_file, const char* p_filePath, const Byte& p_permissions,
        FileCallbackBundle& p_callbacks
    );


    void ReadFromArrayOfByteUsingFilePointerFromOffsetToSizeAsRedCallbackOnFailure(
        const Array<Byte>& p_array, File*& p_file, const Offset& p_offset,
        Size& p_red, Callback& p_file_error
    );

    void WriteFromArrayOfByteUsingFilePointerFromOffsetToSizeAsWrittenCallbackOnFailure(
        const Array<Byte>& p_array, File*& p_file, const Offset& p_offset,
        Size& p_written, Callback& p_file_error
    );


    void DeallocateUsingDataSourceOfFileUsingMemoryManager(
        DataSource<File*>& p_source, MemoryManager& p_manager
    );

}

#endif //FILE__FILE_FILE_HPP