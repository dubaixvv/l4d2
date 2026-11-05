#include "SequenceFreezing.h"
#include "../Vars.h"
#include "../NewMenu/ImGui/Vars/g_vars.h"
void IDFDemo::RemoveConds(C_TerrorPlayer* local, CUserCmd* cmd, int value, bool disableattack)
{
	if (local == NULL) return;

	/*if(!cmd) return;
	if(!cmd->command_number) return;*/
	//if(!var.value) return;

	if (local->m_lifeState() != LIFE_ALIVE) return;

	if (disableattack)
		if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2) return;

	INetChannel* ch = (INetChannel*)I::EngineClient->GetNetChannelInfo();
	int& m_nOutSequenceNr = *(int*)((unsigned)ch + 8);
	m_nOutSequenceNr += value;
}


void IDFDemo::Run(CUserCmd* pCmd, C_TerrorPlayer* pLocal)
{
	if (g_var.lagExploit)
	{
		if (GetAsyncKeyState(g_var.keyLagExploit)) // VK_MENU is alt.
		{
			for (int n = 0; n < 2; n++)
				RemoveConds(pLocal, pCmd,g_var.factorLagExploit, false);
		}
	}
}