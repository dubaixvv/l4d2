#include "Arrows.h"
#include "../NewMenu/ImGui/Vars/g_vars.h"

bool CFeatures_Arrows::GetBounds(C_BaseEntity* pBaseEntity, int& x, int& y, int& w, int& h)
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

void CFeatures_Arrows::Run()
{
	if (g_var.modeStream)
		return;
	if (!g_var.indicators || I::EngineVGui->IsGameUIVisible())
		return;
	const int nLocalIndex = I::EngineClient->GetLocalPlayer();
	C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TerrorPlayer*>();

	if (!pLocal)
		return;

	float flOriginalAlpha = I::MatSystemSurface->DrawGetAlphaMultiplier();
	if (g_var.indicators)
	{
		I::MatSystemSurface->DrawSetAlphaMultiplier(1.0f);

		for (int n = 1; n < (I::ClientEntityList->GetMaxEntities() + 1); n++)
		{
			if (n == nLocalIndex)
				continue;
			IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(n);

			if (!pEntity)
				continue;

			//auto pPlayer = pEntity->As<C_TerrorPlayer*>();
			C_TerrorPlayer* pPlayer = pEntity->As<C_TerrorPlayer*>();
			int isGhostTeam = pPlayer->IsGhost();

			Vector vPos = pEntity->GetAbsOrigin();
			int ClassInfected = pPlayer->m_zombieClass();
			if (pPlayer->deadflag())
				continue;
			bool bIsLocal = pPlayer == pLocal;

			int x, y, w, h;
			if (!GetBounds(pPlayer, x, y, w, h))
			{
				Color TEST(0, 0, 0, 255);
				/*
				if (g_var.indicators && pPlayer != pLocal && !pLocal->deadflag())
				{
					int nScreenCenterX = G::Draw.GetScreenW() / 2;
					int nScreenCenterY = G::Draw.GetScreenH() / 2;

					Vector vScreen = {}, vPlayerWSC = pPlayer->GetCenter();
					G::Draw.ScreenPosition(vPlayerWSC, vScreen);

					if (pLocal->GetCenter().DistTo(vPlayerWSC) > g_var.ESP_Players_Arrows_Max_Distance)
						continue;

					Vector vAngle = {};
					U::Math.VectorAngles({ nScreenCenterX - vScreen.x, nScreenCenterY - vScreen.y, 0.0f }, vAngle);

					float flYaw = DEG2RAD(vAngle.y);
					float flRadius = g_var.ESP_Players_Arrows_Radius;
					float flDrawX = nScreenCenterX - flRadius * cosf(flYaw);
					float flDrawY = nScreenCenterY - flRadius * sinf(flYaw);

					std::array<Vector2D, 3> vPoints = {
			Vector2D(flDrawX + g_var.trianguleSize, flDrawY + g_var.trianguleSize),
			Vector2D(flDrawX - 10.0f, flDrawY),
			Vector2D(flDrawX + g_var.trianguleSize, flDrawY - g_var.trianguleSize)
					};

					U::Math.RotateTriangle(vPoints, vAngle.y);
						Vector2D vTip = Vector2D(flDrawX - 22.0f, flDrawY);
						float rad = DEG2RAD(vAngle.y);
						float s = sinf(rad);
						float c = cosf(rad);

						float x = vTip.x - flDrawX;
						float y = vTip.y - flDrawY;

						float xnew = x * c - y * s;
						float ynew = x * s + y * c;

						Vector2D vTipRotated = Vector2D(xnew + flDrawX, ynew + flDrawY);

						Vector2D classPos = vTipRotated;
							G::Draw.FilledTriangle(vPoints, TEST);
						}
				*/
				continue;
			}
		}
	}
}

