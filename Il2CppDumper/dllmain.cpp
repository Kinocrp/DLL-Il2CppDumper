#include "log.h"
#include "Il2Cpp/Il2Cpp.h"
#include <Windows.h>

void MainThread(HMODULE hModule) {
    LOGInit();

    LOG("[+] Il2CppDumper.dll by Kinocrp\n");
    LOG("[*] Waiting for GameAssembly...\n");
    while (!IL2CPP::Init()) Sleep(1000);
    while (!IL2CPP::Attach()) Sleep(1000);

    IL2CPP::Dump();

    Sleep(3000);

    LOGClose();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
