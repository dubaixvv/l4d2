/*

bool CRadar::GetDrawPosition(int& x, int& y, const Vec3& vWorld)
{
	auto pLocal = H::Entities->GetLocal();
	if (!pLocal)
		return false;
	int nRadarX = g_var.Radar_Pos_X + (g_var.Radar_Size / 2);
	int nRadarY = g_var.Radar_Pos_Y + (g_var.Radar_Size / 2);
	float flYaw = I::EngineClient->GetViewAngles().y * (static_cast<float>(PI) / 180.0f);
	float flRadius = g_var.Radar_Radius;
	float flCos = cosf(flYaw);
	float flSin = sinf(flYaw);
	Vec3 vDelta = vWorld - pLocal->GetCenter();
	Vec2 vPos = { (vDelta.y * (-flCos) + vDelta.x * flSin), (vDelta.x * (-flCos) - vDelta.y * flSin) };
	switch (g_var.Radar_Style)
	{
	case 0:
	{
		if (fabsf(vPos.x) > flRadius || fabsf(vPos.y) > flRadius)
		{
			if (vPos.y > vPos.x)
			{
				if (vPos.y > -vPos.x)
				{
					vPos.x = flRadius * vPos.x / vPos.y;
					vPos.y = flRadius;
				}
				else
				{
					vPos.y = -flRadius * vPos.y / vPos.x;
					vPos.x = -flRadius;
				}
			}
			else
			{
				if (vPos.y > -vPos.x)
				{
					vPos.y = flRadius * vPos.y / vPos.x;
					vPos.x = flRadius;
				}
				else
				{
					vPos.x = -flRadius * vPos.x / vPos.y;
					vPos.y = -flRadius;
				}
			}
		}
		x = nRadarX + static_cast<int>(vPos.x / flRadius * static_cast<float>(g_var.Radar_Size / 2));
		y = nRadarY + static_cast<int>(vPos.y / flRadius * static_cast<float>(g_var.Radar_Size / 2));
		break;
	}
	case 1:
	{
		int nPosX = nRadarX + static_cast<int>(vPos.x / flRadius * static_cast<float>(g_var.Radar_Size / 2));
		int nPosY = nRadarY + static_cast<int>(vPos.y / flRadius * static_cast<float>(g_var.Radar_Size / 2));
		Vec2 vRadar = { static_cast<float>(nRadarX), static_cast<float>(nRadarY) };
		Vec2 vPoint = { static_cast<float>(nPosX), static_cast<float>(nPosY) };
		Vec2 vDelta = vPoint - vRadar;
		if (static_cast<int>(vDelta.Length()) > g_var.Radar_Size / 2)
		{
			vDelta *= static_cast<float>(g_var.Radar_Size / 2) / vDelta.Length();
			vPoint = vRadar + vDelta;
			x = static_cast<int>(vPoint.x);
			y = static_cast<int>(vPoint.y);
		}
		else
		{
			x = nPosX;
			y = nPosY;
		}
		break;
	}
	default: return false;
	}
	return true;
}

void CRadar::Run()
{
	if (g_var.modeStream)
		return;
	if (!g_var.Radar_Active || (I::EngineVGui->IsGameUIVisible() && !F::MenuImgui->IsOpen()))
		return;
	if (g_var.Misc_Clean_Screenshot && I::EngineClient->IsTakingScreenshot())
	{
		return;
	}
	int nRadarSize = g_var.Radar_Size;
	auto CrossColor = []() -> Color_t {
		Color_t Out = {
static_cast<unsigned char>(g_var.color[0] * 255),
static_cast<unsigned char>(g_var.color[1] * 255),
static_cast<unsigned char>(g_var.color[2] * 255),
255
		};
		Out.a = static_cast<byte>(g_var.Radar_Cross_Alpha * 255.0f);
		return Out;
		}();

	if (F::MenuImgui->IsOpen())
	switch (g_var.Radar_Style)
	{
	case 0:
	{
		int nRadarX = g_var.Radar_Pos_X;
		int nRadarY = g_var.Radar_Pos_Y;

		H::Draw->Rect(nRadarX, nRadarY, nRadarSize, nRadarSize, BackgroundColor);
		H::Draw->OutlinedRect(nRadarX, nRadarY, nRadarSize, nRadarSize, OutlineColor);
		H::Draw->Line(
			nRadarX + (nRadarSize / 8),
			nRadarY + (nRadarSize / 2),
			nRadarX + (nRadarSize - ((nRadarSize / 8))),
			nRadarY + (nRadarSize / 2),
			CrossColor
		);
		H::Draw->Line(
			nRadarX + (nRadarSize / 2),
			nRadarY + (nRadarSize / 8),
			nRadarX + (nRadarSize / 2),
			nRadarY + (nRadarSize - ((nRadarSize / 8))),
			CrossColor
		);
		break;
	}
	case 1:
	{
		int nRadarX = g_var.Radar_Pos_X + nRadarSize / 2;
		int nRadarY = g_var.Radar_Pos_Y + nRadarSize / 2;
		H::Draw->FilledCircle(nRadarX, nRadarY, nRadarSize / 2, 100, BackgroundColor);
		H::Draw->OutlinedCircle(nRadarX, nRadarY, nRadarSize / 2, 100, OutlineColor);
		nRadarX = g_var.Radar_Pos_X;
		nRadarY = g_var.Radar_Pos_Y;
		H::Draw->Line(
			nRadarX + (nRadarSize / 8),
			nRadarY + (nRadarSize / 2),
			nRadarX + (nRadarSize - ((nRadarSize / 8))),
			nRadarY + (nRadarSize / 2),
			CrossColor
		);
		H::Draw->Line(
			nRadarX + (nRadarSize / 2),
			nRadarY + (nRadarSize / 8),
			nRadarX + (nRadarSize / 2),
			nRadarY + (nRadarSize - ((nRadarSize / 8))),
			CrossColor
		);
		break;
	}
	default: return;
	}
	auto pLocal = H::Entities->GetLocal();
	if (!pLocal)
		return;
	float darkFactor = 0.2f;


	if (g_var.Radar_Players_Active)
	{
		for (auto pEntity : H::Entities->GetGroup(EEntGroup::PLAYERS_ALL))
		{
			if (!pEntity)
				continue;
			auto pPlayer = pEntity->As<C_TerrorPlayer>();
			if (pPlayer->deadflag())
				continue;
			int teamPlayer = pEntity->m_iTeamNum();
			int isGhostTeam = pPlayer->IsGhost();
			bool bIsLocal = pPlayer == pLocal;
			int ClassInfected = pPlayer->m_zombieClass();

			int x = 0, y = 0, h = 0;
			if (!GetDrawPosition(x, y, pPlayer->GetCenter()))
				continue;
			Vec3 vScreen = {}, vPlayerWSC = pPlayer->GetCenter();
			H::Draw->ScreenPosition(vPlayerWSC, vScreen);
			if (pLocal->GetCenter().DistTo(vPlayerWSC) > g_var.radarDistanceEntity)
				continue;
			Color_t Color = F::VisualUtils->GetEntityColor(pLocal, pPlayer);
			Color.a = 100;
			auto HealthColor = F::VisualUtils->GetHealthColor(pPlayer->GetActualHealth(), pPlayer->m_iMaxHealth());
			auto HealthColorSurvivors = F::VisualUtils->GetHealthColorV2(pPlayer->GetActualHealth(), pPlayer->m_iMaxHealth());
			float flHealth = static_cast<float>(pPlayer->GetActualHealth());
			float flMaxHealth = static_cast<float>(pPlayer->m_iMaxHealth());
			Color_t colorBlack = { 171, 171, 171, 255 };
			if (teamPlayer == 3 && g_var.radarTarget[1])
			{

				if (g_var.Radar_type == 0) {
					int size = g_var.sizeNormalRadar;
					const int half = size / 2;
						H::Draw->FilledCircle(x, y, (g_var.radarSizeIcon + 4) / 2, 20, curColorFilled);
						H::Draw->Texture(x, y, g_var.radarSizeIcon, g_var.radarSizeIcon, F::VisualUtils->GetClassIcon(ClassInfected), POS_CENTERXY);
						H::Draw->OutlinedCircle(x, y, (g_var.radarSizeIcon + 4) / 2, 20, curColorRadar);

				}
			}
		}
	}
}




*/