#include "Entry/Entry.h"
#include "Features/NewMenu/ComponersImGui/Managers/LangManager.hpp"
#include "Util/Byte_Manager/Byte_Manager.hpp"
void* Engine_Module;
void* Client_Module;
DWORD WINAPI dwMainThread(LPVOID lpArguments)
{
	G::ModuleEntry.Load();	
	LangManager::get().initialize();
	//DoMenuStuff(lpArguments);
	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(350));

	//InputSys::Get().Uninit(); 
	G::Hooks.Uninit();
	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(lpArguments), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		if (const HANDLE hMain = CreateThread(0, 0, dwMainThread, hInstance, 0, 0))
			CloseHandle(hMain);
	Client_Module = GetModuleHandleW(L"client.dll");
	Engine_Module = GetModuleHandleW(L"engine.dll");
	// Credits to the source of Storm
	// if you want to reverse this and be able to toggle it on and off, create a function that copies the bytes and restores 
	// them in the game. That way, you wouldn't have to call it here in DLLMAIN, but in another hook.
	// Workshop mods in vs 
	Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 350575), 1, 94); //  94 -> 0x5E
	// ChargerTurn
	 Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 417204), 1, 235);// 235 -> 0xEB
	// NoBlood
    Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2881566), 1, 246); //  246  -> 0xF6

	return true;
}