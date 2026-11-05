#include "CL_Main.h"

#include "../../Features/Vars.h"
#include "../../Features/NewMenu/ImGui/Vars/g_vars.h"

using namespace Hooks;

void __cdecl CL_Main::CL_Move::Detour(float accumulated_extra_samples, bool bFinalTick)
{
	Func.Original<FN>()(accumulated_extra_samples, bFinalTick);

	if (GetAsyncKeyState(g_var.keyspeed) && g_var.speedhack)
	{
		for (int n = 0; n < g_var.speedfactor; n++)
		{
			Func.Original<FN>()(accumulated_extra_samples, bFinalTick);
		}

	}
}

void __fastcall CL_Main::CL_SendMove::Detour(void* ecx, void* edx) {

}

void CL_Main::Init()
{
	//CL_Move
	{
		using namespace CL_Move;

		const FN pfCLMove = reinterpret_cast<FN>(U::Offsets.m_dwCLMove);
		XASSERT(pfCLMove == nullptr);

		if (pfCLMove)
			XASSERT(Func.Init(pfCLMove, &Detour) == false);
	}
}