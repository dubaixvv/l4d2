#include "ESP.h"
#include "../../SDK/L4D2/Interfaces/IInput.h"
#include "../Vars.h"
#include "../NewMenu/ImGui/Vars/g_vars.h"


// T_T T_T T_T T_T T_T T_T LMAO - WHAT THE HELL ARE THEY DOING HERE? TF2 STUFF?? LOL
enum ProjectileType_t
{
	TF_PROJECTILE_NONE,
	TF_PROJECTILE_BULLET,
	TF_PROJECTILE_ROCKET,
	TF_PROJECTILE_PIPEBOMB,
	TF_PROJECTILE_PIPEBOMB_REMOTE,
	TF_PROJECTILE_SYRINGE,
	TF_PROJECTILE_FLARE,
	TF_PROJECTILE_JAR,
	TF_PROJECTILE_ARROW,
	TF_PROJECTILE_FLAME_ROCKET,
	TF_PROJECTILE_JAR_MILK,
	TF_PROJECTILE_HEALING_BOLT,
	TF_PROJECTILE_ENERGY_BALL,
	TF_PROJECTILE_ENERGY_RING,
	TF_PROJECTILE_PIPEBOMB_PRACTICE,
	TF_PROJECTILE_CLEAVER,
	TF_PROJECTILE_STICKY_BALL,
	TF_PROJECTILE_CANNONBALL,
	TF_PROJECTILE_BUILDING_REPAIR_BOLT,
	TF_PROJECTILE_FESTIVE_ARROW,
	TF_PROJECTILE_THROWABLE,
	TF_PROJECTILE_SPELL,
	TF_PROJECTILE_FESTIVE_JAR,
	TF_PROJECTILE_FESTIVE_HEALING_BOLT,
	TF_PROJECTILE_BREADMONSTER_JARATE,
	TF_PROJECTILE_BREADMONSTER_MADMILK,
	TF_PROJECTILE_GRAPPLINGHOOK,
	TF_PROJECTILE_SENTRY_ROCKET,
	TF_PROJECTILE_BREAD_MONSTER,
	TF_NUM_PROJECTILES
};


const char* GetZombieName(int index) {
	switch (index) {
		case Boomer: {
			return "Boomer";
			break;
		}
		case Smoker: {
			return "Smoker";
			break;
		}
		case Hunter: {
			return "Hunter";
			break;
		}
		case Jockey: {
			return "Jockey";
			break;
		}
		case Spitter: {
			return "Spitter";
			break;
		}
		case Charger: {
			return "Charger";
			break;
		}
		case Tank: {
			return "Tank";
			break;
		}
		case Witch: {
			return "Witch";
			break;
		}
		default:
			break;
	}
	return "Fuck niggers.";
}

void CFeatures_ESP::Render()
{
	if (!I::EngineClient->IsInGame() || I::EngineVGui->IsGameUIVisible())
		return;
	if (!g_var.esp)
		return;
	const int nLocalIndex = I::EngineClient->GetLocalPlayer();

	C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TerrorPlayer*>();

	if (!pLocal)
		return;

	player_info_t pi;

	int x, y, w, h;
	for (int n = 1; n < (I::ClientEntityList->GetMaxEntities() + 1); n++)
	{
		if (n == nLocalIndex)
			continue;
		

		IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(n);

		if (!pEntity || pEntity->IsDormant())
			continue;

		ClientClass* pCC = pEntity->GetClientClass();

		if (!pCC)
			continue;
		
		switch (pCC->m_ClassID)
		{
			case CTerrorPlayer:
			case SurvivorBot:
			{
				C_TerrorPlayer* pPlayer = pEntity->As<C_TerrorPlayer*>();

				if (pPlayer->deadflag() || !GetBounds(pPlayer, x, y, w, h))
					break;

				const int nDrawX = x + (w / 2);
				int nDrawY = y + (h / 2);

				const int nHealth = pPlayer->GetActualHealth(); 
				const int nMaxHealth = pPlayer->GetMaxHealth();
				const int newHealth = std::clamp(nHealth, 0, nMaxHealth);
				const bool bIsSurvivor = (pPlayer->GetTeamNumber() == TEAM_SURVIVOR);
				int distance = U::Math.GetDistanceMeters(pLocal->GetAbsOrigin(), pPlayer->GetAbsOrigin());

				const Color clrHealth = G::Util.GetHealthColor(nHealth, nMaxHealth);
				Color test(0, 0, 0, 255);
				// ESP BOX
				if (g_var.box2dInfected)
				{
					if (g_var.selectTypeBoxInfected == 0)
					{  // box normal
						int t = g_var.thicknessBox2DInfected;
						G::Draw.OutlinedRect(x, y, w, h, test);

						G::Draw.OutlinedRect(x - t, y - t, w + (t * 2), h + (t * 2), test);

						G::Draw.OutlinedRect(x + 1, y + 1, w - 2, h - 2, test);


					}
					else if (g_var.selectTypeBoxInfected == 1) {
						// box corners
						//G::Draw.DrawEspCorners(x, y, w, h, test);

					}
				}
				if (g_var.selectTypeNameInfected == 2)
				{
					if (I::EngineClient->GetPlayerInfo(n, &pi))
					{
						G::Draw.String(EFonts::ESP_NAME, x + (w / 2),
							y - G::Draw.GetFontHeight(EFonts::ESP_NAME) - 1,
							test,
							TXT_CENTERX,
							pi.name);
					}
				}
				// helth
				if (g_var.selectTypeBarInfected == 1) {
					float flHealth = static_cast<float>(newHealth);
					float flMaxHealth = static_cast<float>(nMaxHealth);
					int nHeight = (h + (flHealth < flMaxHealth ? 2 : 1));
					int nHeight2 = (h + 2);
					float ratio = (flHealth / flMaxHealth);
					G::Draw.Rect(x - 6, y - 1, 4, h + 2, Color(0, 0, 0, 255));
					G::Draw.Rect(x - 5, (y + nHeight - (nHeight * ratio)), 2, (nHeight * ratio) - 1, Color(0, 255, 0, 255));
				}
				break;
			}
			case CWeaponSpawn:
			{
				C_WeaponSpawn* pSpawn = pEntity->As<C_WeaponSpawn*>();

				if (!GetBounds(pSpawn, x, y, w, h))
					break;
				const int nID = U::Math.Clamp(pSpawn->GetWeaponID(), 0, 38);
				if (g_var.selectTypeItems == 1) {
					G::Draw.String(EFonts::ESP_NAME, x + (w / 2), y + (h / 2), g_aSpawnInfo[nID].m_Color, TXT_CENTERXY, g_aSpawnInfo[nID].m_szName);
				}
				break;
			}
			case Boomer:
			case Smoker:
			case Hunter:
			case Jockey:
			case Spitter:
			case Charger:
			case Tank:
			{
				C_BaseEntity* pZombies = pEntity->As<C_BaseEntity*>();
				if (!GetBounds(pZombies, x, y, w, h) || !pZombies)
					break;
				if (!G::Util.IsInfectedAlive(pZombies->m_usSolidFlags(), pZombies->As<C_BaseAnimating*>()->m_nSequence(), pCC->m_ClassID))
				{
					continue;
				}
				const int nDrawX = x + (w / 2);
				int nDrawY = y + (h / 2);
				int distance = U::Math.GetDistanceMeters(pLocal->GetAbsOrigin(), pZombies->GetAbsOrigin());
				break;
			}
			default:
				break;
		}
	}
}

bool CFeatures_ESP::GetBounds(C_BaseEntity* pBaseEntity, int& x, int& y, int& w, int& h)
{
	Vector vPoints[8];
	U::Math.BuildTransformedBox(vPoints, pBaseEntity->m_vecMins(), pBaseEntity->m_vecMaxs(), pBaseEntity->RenderableToWorldTransform());

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	if (G::Util.W2S(vPoints[3], flb) && G::Util.W2S(vPoints[5], brt)
		&& G::Util.W2S(vPoints[0], blb) && G::Util.W2S(vPoints[4], frt)
		&& G::Util.W2S(vPoints[2], frb) && G::Util.W2S(vPoints[1], brb)
		&& G::Util.W2S(vPoints[6], blt) && G::Util.W2S(vPoints[7], flt)
		&& G::Util.W2S(vPoints[6], blt) && G::Util.W2S(vPoints[7], flt))
	{
		const Vector vTransformed[8] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float righ = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++)
		{
			if (left > vTransformed[n].x)
				left = vTransformed[n].x;

			if (top < vTransformed[n].y)
				top = vTransformed[n].y;

			if (righ < vTransformed[n].x)
				righ = vTransformed[n].x;

			if (bottom > vTransformed[n].y)
				bottom = vTransformed[n].y;
		}

		x = static_cast<int>(left);
		y = static_cast<int>(bottom);
		w = static_cast<int>(righ - left);
		h = static_cast<int>(top - bottom);

		return !(x > G::Draw.m_nScreenW || (x + w) < 0 || y > G::Draw.m_nScreenH || (y + h) < 0);
	}

	return false;
}


// here's what i use in IMGUI; this is useful when i use the mode stream and render in EndScene.
void CFeatures_ESP::RenderImGui()
{
	/*  
	if (!g_var.esp) return;
	if (!g_var.esp || I::EngineVGui->IsGameUIVisible() )
		return;



	float nameHeight = 10.f;

	for (const auto& data : m_espSurvivors) {

		if (g_var.box2dSurvivor)
		{
			if (g_var.selectTypeBoxSurvivor == 0) {
				DrawBox(data.x, data.y, data.w, data.h, colorBoxSurvivor, g_var.thicknessBox2DSurvivor);
			}
			else if (g_var.selectTypeBoxSurvivor == 1) {
				DrawEspCorners(data.x, data.y, data.w, data.h, colorBoxSurvivor, g_var.thicknessBox2DSurvivor);
			}
		}
	}*/
}