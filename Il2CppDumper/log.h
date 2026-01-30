#pragma once

#include <windows.h>
#include <cstdio>
#include <cstdarg>

static HANDLE hMyConsole = INVALID_HANDLE_VALUE;

inline void LOGInit() {
    if (!AllocConsole()) return;

    hMyConsole = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    HANDLE hNul = CreateFileA("NUL", GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);

    SetStdHandle(STD_OUTPUT_HANDLE, hNul);
    SetStdHandle(STD_ERROR_HANDLE, hNul);
    SetStdHandle(STD_INPUT_HANDLE, hNul);

    FILE* fDummy;
    freopen_s(&fDummy, "NUL", "w", stdout);
    freopen_s(&fDummy, "NUL", "w", stderr);
}

inline void LOG(const char* fmt, ...) {
    if (hMyConsole == INVALID_HANDLE_VALUE) return;

    char buffer[2048];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    DWORD written;
    WriteConsoleA(hMyConsole, buffer, (DWORD)strlen(buffer), &written, NULL);
}

inline void LOGClose() {
    if (hMyConsole != INVALID_HANDLE_VALUE) {
        CloseHandle(hMyConsole);
        hMyConsole = INVALID_HANDLE_VALUE;
    }
    FreeConsole();
}
