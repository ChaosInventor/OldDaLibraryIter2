#include "Process/Process.hpp"

#include <stdlib.h>

namespace Library
{

    void ExitWithInteger(const int& p_exitCode)
    {
        exit(p_exitCode);
    }
    void Abort()
    {
        abort();
    }

}