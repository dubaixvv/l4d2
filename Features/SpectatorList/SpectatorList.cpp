/* 



bool CSpectatorList::GetSpectators()
{
	m_vecSpectators.clear();

	auto pLocal = H::Entities->GetLocal();

	if (!pLocal || pLocal->deadflag())
		return false;

	for (int n = 1; n < I::EngineClient->GetMaxClients() + 1; n++)
	{
		auto pEntity = I::ClientEntityList->GetClientEntity(n);

		if (!pEntity || pEntity->GetClassId() != ClassIds::CTerrorPlayer)
			continue;

		auto pPlayer = pEntity->As<C_TerrorPlayer>();

		if (!pPlayer->deadflag() || pPlayer->m_hObserverTarget().Get() != pLocal)
			continue;

		int nMode = pPlayer->m_iObserverMode();

		if (nMode != OBS_MODE_IN_EYE && nMode != OBS_MODE_CHASE)
			continue;

		player_info_t PlayerInfo = {};

		if (!I::EngineClient->GetPlayerInfo(n, &PlayerInfo))
			continue;

		m_vecSpectators.emplace_back(Spectator_t{ Utils::ConvertUtf8ToWide(PlayerInfo.name), nMode });
	}

	return !m_vecSpectators.empty();
}


void CSpectatorList::Run()
{
	if (g_var.modeStream)
		return;
	if (!g_var.Visuals_SpectatorList_Active)
		return;

	if (!F::MenuImgui->IsOpen() && I::EngineVGui->IsGameUIVisible())
		return;

	auto OutlineColor = []() -> Color_t {
		Color Out = {
static_cast<unsigned char>(g_var.color[0] * 255),
static_cast<unsigned char>(g_var.color[1] * 255),
static_cast<unsigned char>(g_var.color[2] * 255),
255
		};
		Out.a = static_cast<byte>(g_var.Visuals_SpectatorList_Outline_Alpha * 255.0f);
		return Out;
		}();
	auto BackgroundColor = []() -> Color_t {
		Color Out = CFG::Menu_Background;
		Out.a = static_cast<byte>(g_var.Visuals_SpectatorList_Background_Alpha * 255.0f);
		return Out;
		}();

	H::Draw->Rect(
		g_var.Visuals_SpectatorList_Pos_X,
		g_var.Visuals_SpectatorList_Pos_Y,
		LIST_WIDTH,
		g_var.Menu_Drag_Bar_Height,
		BackgroundColor
	);
	H::Draw->String(
		H::Fonts->Get(EFonts::Menu),
		g_var.Visuals_SpectatorList_Pos_X + (LIST_WIDTH / 2),
		g_var.Visuals_SpectatorList_Pos_Y + (g_var.Menu_Drag_Bar_Height / 2),
		CFG::Menu_Text,
		POS_CENTERXY,
		"Spectators"
	);
	H::Draw->OutlinedRect(
		g_var.Visuals_SpectatorList_Pos_X,
		g_var.Visuals_SpectatorList_Pos_Y,
		LIST_WIDTH,
		g_var.Menu_Drag_Bar_Height,
		OutlineColor
	);
	if (!GetSpectators())
		return;
	for (size_t n = 0; n < m_vecSpectators.size(); n++)
	{
		const auto& Spectator = m_vecSpectators[n];
		H::Draw->Rect(
			g_var.Visuals_SpectatorList_Pos_X,
			g_var.Visuals_SpectatorList_Pos_Y + (g_var.Menu_Drag_Bar_Height * (n + 1)) - 1,
			LIST_WIDTH,
			g_var.Menu_Drag_Bar_Height + 1,
			BackgroundColor
		);
		int nModeX = g_var.Visuals_SpectatorList_Pos_X;
		int nModeOffsetX = LIST_WIDTH / 8;
		int nTextY = g_var.Visuals_SpectatorList_Pos_Y + (g_var.Menu_Drag_Bar_Height * (n + 1)) - 1;
		int nTextX = nModeX + nModeOffsetX + g_var.Menu_Spacing_X;
		int nY = g_var.Visuals_SpectatorList_Pos_Y + (g_var.Menu_Drag_Bar_Height * (n + 1)) - 1;
		H::Draw->Line(nModeX + nModeOffsetX, nY, nModeX + nModeOffsetX, nY + g_var.Menu_Drag_Bar_Height, OutlineColor);
		H::Draw->String(
			H::Fonts->Get(EFonts::Menu),
			nModeX + (nModeOffsetX / 2),
			nTextY + (g_var.Menu_Drag_Bar_Height / 2) + 1,
			ColorTypeEspectadores,
			POS_CENTERXY,
			Spectator.m_nMode == OBS_MODE_IN_EYE ? "1P" : "3P"
		);
		I::MatSystemSurface->DisableClipping(false);
		I::MatSystemSurface->SetScissorRect(nModeX, nTextY, (nModeX + LIST_WIDTH) - (g_var.Menu_Spacing_X + 1), nTextY + g_var.Menu_Drag_Bar_Height);
		H::Draw->String(
			H::Fonts->Get(EFonts::Menu),
			nTextX,
			nTextY + (g_var.Menu_Drag_Bar_Height / 2) + 1,
			ColorNameSpectadors,
			POS_CENTERY,
			Spectator.m_wsName.c_str()
		);
		I::MatSystemSurface->DisableClipping(true);

		H::Draw->OutlinedRect(
			g_var.Visuals_SpectatorList_Pos_X,
			g_var.Visuals_SpectatorList_Pos_Y + (g_var.Menu_Drag_Bar_Height * (n + 1)) - 1,
			LIST_WIDTH,
			g_var.Menu_Drag_Bar_Height + 1,
			OutlineColor
		);
	}
}







*/

