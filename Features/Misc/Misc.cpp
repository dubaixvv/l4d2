#include "Misc.h"
#include "../../SDK/L4D2/Interfaces/IConVar.h"
#include "../../SDK/EntityCache/entitycache.h"
#include <Windows.h>
#include <iostream>
#include "../NewMenu/ImGui/Vars/g_vars.h"
void CMisc::movement(C_TerrorPlayer* pLocal, CUserCmd* pCmd)
{
	if (!(pLocal->m_fFlags() & FL_ONGROUND) && pCmd->buttons & IN_JUMP)
	{
		//Bunnyhop
		if (g_var.Misc_Bunnyhop)
			pCmd->buttons &= ~IN_JUMP;
	}
}


void CMisc::run(C_TerrorPlayer* pLocal, CUserCmd* pCmd) {
	if (!I::EngineClient->IsInGame())
		return;
	movement(pLocal, pCmd);
}
/* 
void CMisc::AntiTracker(const char* name)
{
	if (g_var.bAntiTracker) {
		std::string command = "setinfo name \"" + std::string("\xE2\x80\x8B") + name + "\"";
		I::EngineClient->ClientCmd(command.c_str());
	}

}

void CMisc::antiAfkKick(CUserCmd* cmd)
{
	if (g_var.bAntiAfk && cmd->command_number % 2)
		cmd->buttons |= 1 << 26;
}

// anti smoker and jockey
if (Local_Players->m_jockeyAttacker().IsValid())
	{
		if (g_var.bAntiJockey)
		{
			if (auto nets = I::EngineClient->GetNetChannelInfo())
			{
				pCmd->tick_count = 0xFFFFFF;
			}
		}
	}

	if (auto smoker = Local_Players->m_tongueOwner(); smoker)
	{
		if (g_var.bAntiSmoker) {
			if (auto netf = I::EngineClient->GetNetChannelInfo())
			{
				I::ClientState->m_NetChannel->m_nOutSequenceNr += 500;
			}
		}
	}


	// name steal credits to the Osiris source
bool CMisc::changeName(bool reconnect, const char* newName, float delay)
{
	static auto exploitInitialized{ false };

	static ConVar* name = I::CVar->FindVar("name");

	if (reconnect) {
		exploitInitialized = false;
		return false;
	}
	auto localPlayer = H::Entities->GetLocal();

	player_info_t playerInfoS{};
	if (!exploitInitialized && I::EngineClient->IsInGame()) {
		if (player_info_t playerInfo; localPlayer && I::EngineClient->GetPlayerInfo(localPlayer->entindex(), &playerInfoS) && (!strcmp(playerInfo.name, "?empty") || !strcmp(playerInfo.name, "\n\xAD\xAD\xAD"))) {
			exploitInitialized = true;
		}
		else {
			name->m_fnChangeCallback = 0;
			name->SetValue("\n\xAD\xAD\xAD");
			return false;
		}
	}

	static auto nextChangeTime{ 0.0f };
	if (nextChangeTime <= I::GlobalVars->realtime) {
		name->SetValue(newName);
		nextChangeTime = I::GlobalVars->realtime + delay;
		return true;
	}
	return false;
}
void CMisc::stealNames()
{
	if (!g_var.nameStealer)
		return;
	auto localPlayer = H::Entities->GetLocal();

	if (!localPlayer)
		return;
	const int localIdx = I::EngineClient->GetLocalPlayer();
	if (localIdx == -1)
		return;
	static std::vector<int> stolenIds;

	for (int i = 1; i <= I::EngineClient->GetMaxClients(); ++i)
	{
		if (i == localIdx)
			continue;

		C_BasePlayer* entity = I::ClientEntityList->GetClientEntity(i)->As<C_BasePlayer>();
		if (!entity)
			continue;

		player_info_t playerInfo;
		if (!I::EngineClient->GetPlayerInfo(entity->entindex(), &playerInfo))
			continue;

		if (playerInfo.fakeplayer || std::find(stolenIds.cbegin(), stolenIds.cend(), playerInfo.userID) != stolenIds.cend())
			continue;

		if (changeName(false, (std::string{ playerInfo.name } + '\x1').c_str(), 1.0f))
			stolenIds.push_back(playerInfo.userID);

		return;
	}
	stolenIds.clear();
}
void CMisc::FreeCamera(CUserCmd* cmd, IClientEntity* pEntity)
{
	static bool bPrevState = false;

	if (GetAsyncKeyState(g_var.keyFreeCamera) & 0x8000)
	{
		if (!bPrevState)
		{
			g_var.bFreeCamActive = !g_var.bFreeCamActive;
		}
		bPrevState = true;
	}
	else
	{
		bPrevState = false;
	}

	if (!g_var.bFreeCamActive)
	{
		vCamOffset = {};
		return;
	}

	QAngle qCamAngles = I::EngineClient->GetViewAngles();

	if (vCamOffset.IsZero())
	{
		vCamOffset = pEntity->GetAbsOrigin();
		vCamOffset.z += 80.0f;
	}

	Vector vForward, vRight, vUp;
	Math::AngleVectors(qCamAngles, &vForward, &vRight, &vUp);

	Vector vMove(0.0f, 0.0f, 0.0f);
	if (cmd->buttons & IN_FORWARD)    vMove += vForward;
	if (cmd->buttons & IN_BACK)       vMove -= vForward;
	if (cmd->buttons & IN_MOVERIGHT)  vMove += vRight;
	if (cmd->buttons & IN_MOVELEFT)   vMove -= vRight;
	if (cmd->buttons & IN_JUMP)       vMove += vUp;
	if (cmd->buttons & IN_DUCK)       vMove -= vUp;

	vMove *= g_var.camVelocity;
	vCamOffset += vMove;

	cmd->viewangles = qCamAngles;
	I::EngineClient->SetViewAngles(qCamAngles);

	cmd->forwardmove = 0.0f;
	cmd->sidemove = 0.0f;
	cmd->upmove = 0.0f;
	cmd->buttons = 0;
}

*/


