#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        TCHAR szName[MAX_PATH] = { 0 };
        //std::string str = system("$(TargetName)");
        ::GetModuleFileName(hModule, szName, MAX_PATH);
        std::cout << "DLL_PROCESS_ATTACH" << std::endl;
        break;
    }
    case DLL_THREAD_ATTACH:
        std::cout << "DLL_THREAD_ATTACH" << std::endl;
        break;

    case DLL_THREAD_DETACH:
        std::cout << "DLL_THREAD_DETACH" << std::endl;
        break;

    case DLL_PROCESS_DETACH:
        std::cout << "DLL_PROCESS_DETACH" << std::endl;
        break;
    }

    return TRUE;
}