


// https://developer.valvesoftware.com/wiki/Left_4_Dead_2/Scripting/Game_Events

/*
// player_say
    if (!_stricmp(eventName, "player_say"))
    {
        int userid = event->GetInt("userid");
        int client = I::EngineClient->GetPlayerForUserID(userid);
        if (client <= 0 || client > 64)
            return;

        auto ent = I::ClientEntityList->GetClientEntity(client);
        if (!ent)
            return;

        C_TerrorPlayer* player = ent->As<C_TerrorPlayer>();
        auto localPlayer = H::Entities->GetLocal();
        int localTeam = localPlayer->m_iTeamNum();
        if (!player)
            return;

        int teamPlayer = player->m_iTeamNum();
        if (teamPlayer == localTeam)
          return;

        std::string playerName = GetNameS(client);
        if (playerName.empty())
            playerName = "Unknown";

        const wchar_t* wtext = event->GetWString("text");
        if (!wtext || !*wtext)
            return;
     I::ClientModeShared->PrintToChat(wtext.c_str());



     // VOTE
     void EventListener::OnVoteCast(int client, bool votedYes)
{
    if (!I::ClientEntityList)
        return;

    std::string name = GetNameS(client);
    if (name.empty())
        name = g_var.iSelectedLanguage == 0 ? "Unknown" : "Desconocido";

    auto ent = I::ClientEntityList->GetClientEntity(client);
    int team = 0;
    if (ent)
    {
        if (auto player = ent->As<C_TerrorPlayer>())
            team = player->m_iTeamNum();
    }

    if (g_var.bShowVotesIn[1] && g_var.bPlayerVotes)
    {

        I::ClientModeShared->PrintToChat(msg.c_str());
    }
}
       else if (!_stricmp(eventName, "vote_cast_yes") || !_stricmp(eventName, "vote_cast_no"))
        {
            int client = event->GetInt("entityid");
            if (client <= 0)
                return;

            bool votedYes = !_stricmp(eventName, "vote_cast_yes");
            OnVoteCast(client, votedYes);
        }

*/