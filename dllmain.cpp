#include <Windows.h>
#include <iostream>
#include "hooks/Hooks.h"

extern LPTHREAD_START_ROUTINE Hooking::_main();

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH: {

		AllocConsole();
		FILE* cons;
		freopen_s(&cons, "conin$", "r", stdin);
		freopen_s(&cons, "conout$", "w", stdout);
		SetConsoleTitle("Replicant Debug");
		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hooking::_main, NULL, NULL, NULL);

		if (auto handle = CreateThread(nullptr, NULL, Hooking::Intialize, hModule, NULL, nullptr))
			CloseHandle(handle);
		break;
	}

    case DLL_PROCESS_DETACH:
		Hooking::Uninitialize();
        break;
    }
    return TRUE;
}

