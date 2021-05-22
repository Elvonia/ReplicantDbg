#ifndef HOOKS_H
#define HOOKS_H

#include <stdexcept>
#include <iostream>
#include "../minhook/minhook.h"

namespace Hooking
{
	bool InitializeHooks();
	void RemoveHooks();
	unsigned long WINAPI Intialize(void *instance);
	unsigned long WINAPI Uninitialize();
	LPTHREAD_START_ROUTINE _main();

	namespace Functions
	{
		static uintptr_t *FUN_140939824 = reinterpret_cast<uintptr_t *>(0x140939824);
		static uintptr_t *lua_dbg = reinterpret_cast<uintptr_t *>(0x140939028);
	}

	namespace Hooks
	{
		static auto lua_dbg_orig = nullptr;
		static int lua_dbg_hook(char* param_1, long long param_2, long long param_3, long long param_4);
	}
}

#endif 
