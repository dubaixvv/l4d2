

/* 


void CMiscVisuals::UpdateConVar()
{
	static bool bright = false, flashlight = false;

	if (g_var.noVisionfullbrig != bright)
	{
		bright = g_var.noVisionfullbrig;
		static ConVar* mat_fullbright = I::CVar->FindVar(XorStr("mat_fullbright"));
		mat_fullbright->SetValue(bright);
	}
	if (g_var.noVisionfullflash != flashlight)
	{
		flashlight = g_var.noVisionfullflash;
		static ConVar* r_flashlightfov = I::CVar->FindVar(XorStr("r_flashlightfov"));
		static ConVar* r_flashlightconstant = I::CVar->FindVar(XorStr("r_flashlightconstant"));
		static ConVar* cl_max_shadow_renderable_dist = I::CVar->FindVar(XorStr("cl_max_shadow_renderable_dist"));

		if (flashlight)
		{
			r_flashlightfov->SetValue(120);
			r_flashlightconstant->SetValue(1);
			cl_max_shadow_renderable_dist->SetValue(0);
		}
		else
		{
			r_flashlightfov->SetValue(53);
			r_flashlightconstant->SetValue(0);
			cl_max_shadow_renderable_dist->SetValue(3000);
		}
	}

}
*/


// Use the ParticleEffect signature and add this code to the hook
/*
if (g_var.bNoSmoke)
	{
		static HMODULE Client_Module = GetModuleHandleW(L"client.dll");

		using Get_Effect_Name_Type = char* (__thiscall*)(void* a1);
		char* Effect_Name = Get_Effect_Name_Type((unsigned __int32)Client_Module + 1423120)((void*)((unsigned __int32)ecx - 8));

		if (__builtin_strstr(Effect_Name, "ecloud_") == nullptr)
		{
			return CALL_ORIGINAL(ecx, Unknown_Parameter_1, Unknown_Parameter_2);
		}

		return 0;
	}

*/