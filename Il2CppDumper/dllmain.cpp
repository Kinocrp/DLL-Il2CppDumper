#include "log.h"
#include "Il2Cpp/Il2Cpp.h"
#include <Windows.h>

static size_t m_cachedAttacker = 0;
static size_t isMainChar = 0;

bool (*o__ProcessDamage)(void*, void*, void*, void*, bool, void*) = nullptr;
bool h__ProcessDamage(void* _this, void* effectSource, void* inputTarget, void* targetWrapper, bool isExtraTarget, void* transferredSource) {
    auto Attacker = IL2CPP::GetFieldPointer<void>(_this, m_cachedAttacker);
    auto mainChar = IL2CPP::GetFieldValue<bool>(Attacker, isMainChar, true);
    if (mainChar) return o__ProcessDamage(_this, effectSource, inputTarget, targetWrapper, isExtraTarget, transferredSource);
    return false;
}

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
