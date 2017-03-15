#ifndef RESOURCE_PATH_HPP
#define RESOURCE_PATH_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <Shlwapi.h>

//TODO(robert): Make multiplatform
//TODO(robert): Create relative folder paths file containing references to Characters/fonts folders etc so that any changes to resources file paths does not require code change.
inline std::string resourcePath()
{
    HMODULE hModule = GetModuleHandle(nullptr);

    if(hModule)
    {
        char path[256];
        GetModuleFileName(hModule,path,sizeof(path));
        PathRemoveFileSpec(path);
        strcat_s(path,"\\"); // new
        return std::string(path); // new
    }

    return "";
}

#endif
