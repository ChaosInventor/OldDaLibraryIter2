#ifndef DIRECTORY__DIRECTORY_DIRECTORY_HPP
#define DIRECTORY__DIRECTORY_DIRECTORY_HPP

#include "ObjectManager/ObjectManager.hpp"

namespace Library
{

    struct Directory;
    

    extern ObjectManager<Directory*> g_DefaultDirectoryObjectManager;


    void FindDirectoryAt(
        Directory& p_directory,
        const char* p_path,
        Callback p_no_exist,
        Callback p_no_permission,
        Callback p_bad_path
    );

}

#endif //DIRECTORY__DIRECTORY_DIRECTORY_HPP