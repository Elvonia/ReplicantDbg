#include "Hooks.h"
#include <string>

int Hooking::Hooks::lua_dbg_hook(char* param_1, long long param_2, long long param_3, long long param_4)
{
	char cVar1;
	unsigned long* puVar2;
	char* pcVar3;
	unsigned long uVar4;
	long long lVar5;
	long long lVar6;

	if (param_4 == 0) {
		if (param_1 == (char*)0x0) {
			if (param_2 == 0) {
				return 0;
			}
		}
		else {
		LAB_14093906e:
			if (param_2 != 0) {
				if (param_4 == 0) {
					*param_1 = '\0';
					return 0;
				}
				if (param_3 != 0) {
					pcVar3 = param_1;
					lVar5 = param_2;
					lVar6 = param_4;
					if (param_4 == -1) {
						do {
							cVar1 = pcVar3[param_3 - (long long)param_1];
							*pcVar3 = cVar1;
							pcVar3 = pcVar3 + 1;
							if (cVar1 == '\0') break;
							lVar5 = lVar5 + -1;
						} while (lVar5 != 0);

					}
					else {
						do {
							cVar1 = pcVar3[param_3 - (long long)param_1];
							if (pcVar3 >= (char*)0x144890238 && pcVar3 <= (char*)0x1448902C4)
							{
								std::cout << cVar1;
								*pcVar3 = cVar1;
								pcVar3 = pcVar3 + 1;
								if ((cVar1 == '\0') || (lVar5 = lVar5 + -1, lVar5 == 0))
								{
									std::cout << std::endl;
									break;
								}
								lVar6 = lVar6 + -1;
							}
							else {
								*pcVar3 = cVar1;
								pcVar3 = pcVar3 + 1;
								if ((cVar1 == '\0') || (lVar5 = lVar5 + -1, lVar5 == 0)) break;
								lVar6 = lVar6 + -1;
							}
						} while (lVar6 != 0);
						if (lVar6 == 0) {
							*pcVar3 = '\0';
						}
					}
					if (lVar5 != 0) {
						return 0;
					}
					if (param_4 == -1) {
						param_1[param_2 + -1] = '\0';
						return 0x50;
					}
					*param_1 = '\0';
					puVar2 = __doserrno();
					uVar4 = 0x22;
					goto LAB_140939051;
				}
				*param_1 = '\0';
			}
		}
	}
	else {
		if (param_1 != (char*)0x0) goto LAB_14093906e;
	}
	puVar2 = __doserrno();
	uVar4 = 0x16;
LAB_140939051:
	*puVar2 = uVar4;
	Hooking::Functions::FUN_140939824;
	return uVar4;
}


LPTHREAD_START_ROUTINE Hooking::_main()
{
	//std::string input;
	//uintptr_t *L = Title_lua_State;

	while (true)
	{
		if ((GetAsyncKeyState(VK_END) & 1))
		{
			Hooking::RemoveHooks();
		}
	}
}

bool Hooking::InitializeHooks()
{
	if (MH_Initialize() != MH_OK) {
		std::cout << "Failed to initialize MH_Initialize" << std::endl;
		return false;
	}

	if (MH_CreateHook(Hooking::Functions::lua_dbg, &Hooking::Hooks::lua_dbg_hook, Hooking::Hooks::lua_dbg_orig) != MH_OK)
	{
		std::cout << "Failed to initialize lua_dbg hook";
		return false;
	}

	if (MH_EnableHook(Hooking::Functions::lua_dbg) != MH_OK) {
		std::cout << "Failed to enable dbg hook" << std::endl;
		return false;
	}

	std::cout << "[Initializer]: Hook(s) enabled" << std::endl;
	return true;
}

void Hooking::RemoveHooks()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

unsigned long WINAPI Hooking::Intialize(void* instance)
{
	Hooking::InitializeHooks();
	return true;
}

unsigned long WINAPI Hooking::Uninitialize()
{
	Hooking::RemoveHooks();
	return true;
}