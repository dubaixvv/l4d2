#include "EndScene.h"
#include "../../Features/NewMenu/CMenu.h"
#include <intrin.h>

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/276438-stream-proof-visuals-method.html
HRESULT __stdcall EndSceneHook::Func(IDirect3DDevice9* pDevice)
{
	//prevent the Steam overlay from seeing or capturing what you're drawing when you activate streamer mode.
	/*
		static uintptr_t gameoverlay_return_address = 0;
	if (!gameoverlay_return_address) {
		MEMORY_BASIC_INFORMATION info;
		VirtualQuery(__builtin_return_address(0), &info, sizeof(info));

		char mod[MAX_PATH];
		GetModuleFileNameA((HMODULE)info.AllocationBase, mod, MAX_PATH);

		if (strstr(mod, XorStr("gameoverlay")))
			gameoverlay_return_address = (uintptr_t)(__builtin_return_address(0));
	}

	if (gameoverlay_return_address != (uintptr_t)(__builtin_return_address(0)) && g_var.modeStream)
		return CALL_ORIGINAL(device);
	
	*/
	static void* firstAddress = _ReturnAddress();
	if (firstAddress != _ReturnAddress())
		return Table.Original<fn>(42)(pDevice);

	g_Menu.Render(pDevice);
	/*
	if(g_var.modeStream){
	// here you call your functions made in imgui that are not shown in obs or some capture.
	// Render();
	}
	*/
	return Table.Original<fn>(42)(pDevice);
}

void EndSceneHook::Init()
{
	XASSERT(Table.Init(g_dwDirectXDevice) == false);
	XASSERT(Table.Hook(&Func, 42) == false);
}

// TO BE COMPATIBLE WITH FULL SCREEN, THE DIRECT3D 9 RESET INDEX IS 16 (HRESULT, __stdcall, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)

/* 
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT hr = CALL_ORIGINAL(device, pPresentationParameters);

	if (SUCCEEDED(hr))
	{
		G::D3DPresentParams = *pPresentationParameters;

		ImGui_ImplDX9_CreateDeviceObjects();
	}

	return hr;
	*/
