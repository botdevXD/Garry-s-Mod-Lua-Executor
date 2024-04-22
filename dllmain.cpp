#include "pch.h"
#include <windows.h>
#include <iostream>
#include <psapi.h>
#include <functional>
#include <fstream>
#include <string>
#include <vector>

#include "../include/MinHook.h"
//#include "executorgui_dx11.h"
#include "executorgui_dx9.h"

void createConsole(const char* title) {
    AllocConsole();
    SetConsoleTitleA(title);

    freopen_s((FILE**)stdin, "conin$", "r", stdin);
    freopen_s((FILE**)stdout, "conout$", "w", stdout);
}

DWORD WINAPI main()
{
    if (lua_sharedBase) {
        if (MH_Initialize() != MH_STATUS::MH_OK)
        {
            return FALSE;
        }
        
        MH_CreateHook(MAYBE_GMOD_RUNTIME_SETUP, &MAYBE_GMOD_RUNTIME_SETUP_HOOK, (LPVOID*)&MAYBE_GMOD_RUNTIME_SETUP_PTR);
        MH_CreateHook(GMOD_LUA_STACK_CHECK, &GMOD_LUA_STACK_CHECK_HOOK, (LPVOID*)&GMOD_LUA_STACK_CHECK_PTR);
        MH_CreateHook(lua_close, &lua_close_HOOK, (LPVOID*)&lua_close_PTR);
        MH_CreateHook(lua_pcall, &lua_pcall_HOOK, (LPVOID*)&lua_pcall_PTR);

		MH_EnableHook(MH_ALL_HOOKS);

        execution_gui::Init();
	}
    else {
		exit(0);
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        MH_Uninitialize();

        FreeConsole();
        break;
    }
    return TRUE;
}

