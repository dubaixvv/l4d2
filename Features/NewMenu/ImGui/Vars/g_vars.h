#pragma once
struct vars {
public:


#pragma region AIMBOT CONFIG

    bool aimbot = true;
    int keyaim = 1, miscaim = 0;
    bool autoshoot = false;
    int selectAimbot = 1;
    const char* itemsAimbot[4]{ "Normal", "Silent", "Perfect Silent","Smooth" };
    int selectSortAimbot = 0;
    const char* itemsSortAimbot[2]{ "FOV", "Distance" };
    int selectAimbotBone = 0;
    const char* itemsAimbotBone[3]{ "Head", "Body","Auto" };
    bool selectItemsAimbot[2] = { true, true }; // multicombo
    const char* multi_itemsAimbot[2] = { "Special Infected", "My Team" };
    bool selectItemsAimbotEspeciales[2] = { false, false }; // multicombo
    const char* multi_itemsAimbotEspeciales[2] = { "None","Ghost" };
    bool circleFov = true;
    float ColorCircleFov[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f };

    float fovAimbot = 30.5;
    float distanceAimbot = 3000.0f;
    float smoothAimbot = 5.0f;

    bool Aimbot_Hitscan_Active = true;
    bool Aimbot_Hitscan_Target_LagRecords = false;
    bool Aimbot_Hitscan_Advanced_Smooth_AutoShoot = false;

    bool Aimbot_Hitscan_Scan_Head = true;
    bool Aimbot_Hitscan_Scan_Body = true;
    bool Aimbot_Hitscan_Scan_Arms = false;
    bool Aimbot_Hitscan_Scan_Legs = false;

    bool Aimbot_Target_Players = true;
    bool Misc_Accuracy_Improvements = false;
    bool noInterpolations = false;
    bool triggerbot = false;
    bool objtrigger[4] = { true, false,false,false };
    const char* itemstriggertObj[4]{ "Enemigos", "Team","Commons","Witch" };
    int selectTriggerBone = 0;
    const char* itemsTraceBoneTrigger[3]{ "Head","Body","All" };
    bool trigger_head_follow = true;
    bool triggerMira = true;
    float triggerMiraColor[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f };
    float distanceTrigger = 3000.0f;
    bool trigger_silent = true;
    bool ignoreWitchRage = true;
    bool rapidfire = true;
    bool autopistol = false;
    bool noRecoil = true;
    bool noSpreed = true;
    bool bDisableScreenShake = true;
    bool IgnoreAimbotCommon = false;
    bool IgnoreAimbotWitch = false;
    bool ignoreShotWitchCalm = true;
    int selectAimbotBoneCommon = 0;
    const char* itemsAimbotBoneCommon[2]{ "Head", "Body" };
    int selectAimbotBoneWitch = 0;
    const char* itemsAimbotBoneWitch[3]{ "Head", "Body" };

#pragma endregion

#pragma region ESP_CONFIG

    bool headEspSurvivor = false;
    bool headEspInfected = false;
    int selectTypeHeadSurvivor = 0;
    const char* itemsTypeHeadSurvivor[2] = { "Cuadrado", "Circulo" };
    int selectTypeHeadInfected = 0;
    const char* itemsTypeHeadInfected[2] = { "Cuadrado.", "Circulo." };

    float colorHeadEspInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };  
    float colorHeadEspSurvivor[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 

    bool BoomerRadiusESP = true;
    int BoomerRadiusSize = 210;
    float colorRadiusBoomer[4] = { 1.0f, 0.0f, 0.0f, 1.0f };  
    int boneTypeColor = 0;
    int ignoreEsp = 0;
    int EspNameInfectedColor = 0;
    int espLineTrace_from = 2;
    int espLineTrace_to = 2;
    bool esp = true;
    bool espPreview = true;


    int selectEsp = 0;
    const char* itemsEsp[2]{ "Survivor", "Infected" };
    int selectObjEsp = 3;
    const char* itemsObjEsp[4]{ "None", "Survivor", "Infected", "All" };

    int ticknessBoneGlobal = 1;
    float distanceSurvivor = 3500.0f;
    bool box2dSurvivor = true;
    float colorBoxSurvivor[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    int selectTypeBoxSurvivor = 0;
    const char* itemsTypeBoxSurvivor[2]{ "Normal", "Corners" };
    int thicknessBox2DSurvivor = 1;
    int selectTypeNameSurvivor = 1;
    const char* itemsTypeNameSurvivor[3]{ "None", "Right", "Top" };

    int selectTypeHealthSurvivor = 1;
    const char* itemsTypeHealthSurvivor[3]{ "None", "Right", "Below" };

    int selectTypeBarSurvivor = 0;
    const char* itemsTypeBarSurvivor[3]{ "None", "Left", "Below" };
    bool lineSurvivor;
    float colorLineSurvivor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

    bool IndicatorSurvivor = true;
    float colorIndicatorSurvivor[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    float colornameTextSurvivor[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    bool boneSurvivor = false;
    float colorBoneSurvivor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
    float distanceInfected = 3500.0f;
    bool box2dInfected = true;
    float colorBoxInfected[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f };
    int selectTypeBoxInfected = 0;
    const char* itemsTypeBoxInfected[2]{ "Normal", "Corners" };
    int thicknessBox2DInfected = 1;
    int selectTypeNameInfected = 2;
    const char* itemsTypeNameInfected[3]{ "None", "Right", "Top" };
    int selectTypeHealthInfected = 1;
    const char* itemsTypeHealthInfected[3]{ "None", "Right", "Below" };

    int selectTypeBarInfected = 1;
    const char* itemsTypeBarInfected[3]{ "None", "Left", "Below" };
    bool lineInfected;
    float colorLineInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    bool HeadEspSurvivor = false;
    bool IndicatorInfected;
    float colorIndicatorInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    float colornameTextInfected[4] = { 1.0f, 200 / 255.0f, 0.0f, 1.0f };
    bool classInfected = true;
    int selectTypeInfectedName = 0;
    const char* itemsTypeInfectedName[2]{ "Icon", "Text" };

    int iconSizeEsp = 30;
    float colorClassInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    bool boneInfected = false;
    float colorBoneInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    bool commonInfected = true;
    bool commonBox = false;
    float colorcommonInfected[4] = { 0.0f, 0.478f, 1.0f, 1.0f }; 
    float distanceInfectedCommon = 700.0f;
    bool rockTank = true;
    bool rockTankBox = false;
    float colorrockTank[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; 
    float distancerockTank = 2600.0f;
    bool enabledWeapons = false;
    int selectTypeItems = 1; 
    int sizeIconItems = 20;
    const char* itemsTypeClass[2] = { "Icon", "Text" };
    bool enabledBoxWeapons = false;
    bool targetWeapons[5] = { true, false, false,false,false, };
    const char* itemsWeapons[5] = { "Weapons", "Medkits", "Melee", "Grenades", "Others" };
    float distanceItems = 1300.0f;
    float colorWeapons[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    float colorMedications[4] = { 255.0f / 255.0f, 105.0f / 255.0f, 180.0f / 255.0f, 1.0f };
    float colorGrenades[4] = { 0.0f, 128.0f / 255.0f, 0.0f, 1.0f };
    float colorAmmunition[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 0.0f, 1.0f };
    float colorMelee[4] = { 255.0f / 255.0f, 165.0f / 255.0f, 0.0f, 1.0f };
    bool modeGhost = true;
    float colorGhost[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float colorBoxIncapacited[4] = { 148.0f / 255.0f, 0.0f, 211.0f / 255.0f, 1.0f }; 
    float colorApuntoDemorir[4] = { 169.0f / 255.0f, 169.0f / 255.0f, 169.0f / 255.0f, 1.0f }; 
    bool muerteDonde = true;
    float colorDondeMurio[4] = { 186.0f / 255.0f, 85.0f / 255.0f, 211.0f / 255.0f, 1.0f };
    bool espWitch = true;
    float witchColor[4] = { 0.9098f, 0.0f, 1.0f, 1.0f };
    bool witchBox = true;
    float distanceWitch = 1500.0f;
    int selectTypeWitchName = 0;
    const char* itemsTypeWitchName[2]{ "Icon", "Text" };

    int iconSizeWitch = 20;
#pragma endregion

#pragma region VISUALS_CONFIG

    bool noFog = false;
    bool noVomit = false;
    bool noFogSky = true;
    bool Visuals_Disable_Detail_Props = false;
    bool Visuals_Simple_Models = false;
    bool noVisionfullbrig = false;
    bool noVisionfullflash = false;

    bool visualsImproveMapTextures = false;
    bool visualsEnhancedNoVomit = true;
    bool visualsDisableGhostMode = true;
    bool bUseSimpleModels = false;
    bool Visuals_Thirdperson_Active = false;
    int selectCollision = 0;
    int keyPerson, miscPerson = 0;
    float Visuals_FOV_Override = 90.0f;
    float Visuals_Thirdperson_Offset_Forward = 150.0f;
    float Visuals_Thirdperson_Offset_Right = 0.0f;
    float Visuals_Thirdperson_Offset_Up = 0.0f;
    bool Visuals_ViewModel_Active = false;
    bool Visuals_ViewModel_Sway = false;
    float Visuals_ViewModel_Sway_Scale = 0.1f;
    float Visuals_ViewModel_Offset_Forward = 0.0f;
    float Visuals_ViewModel_Offset_Right = 0.0f;
    float Visuals_ViewModel_Offset_Up = 0.0f;
    bool myespects = true;
    float colorEspectador[4] = { 255.0f / 255.0f, 215.0f / 255.0f, 0.0f / 255.0f, 1.0f }; 
    bool  Visuals_Distance_Prop_Alpha = false;
    bool   Visuals_World_Modulation_No_Sky_Change = false;

    bool bWorldModulation = false;
    int Visuals_World_Modulation_Mode = 0;
    const char* itemsWordlModulation[2]{ "Nigth", "Custom colors" };
    float Visuals_Night_Mode = 50.0f;
    float sKyColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 


    int Visuals_Particles_Mode = 0;
    const char* itemsParticulesMode[3]{ "Original", "Custom colors","Raimbow" };
    float Visuals_Particles_Rainbow_Rate = 3.0f;
    float particulesColors[4] = { 0.0f, 1.0f, 1.0f, 1.0f };


    bool selectItemsrRemovals[6] = { false, false,false,false,false,false }; 
    const char* multi_itemsRemovals[6] = { "Scope", "Zoom","Punch","Screen_Overlay","Screen_Shake" ,"Screen_Fade" };
    int Visuals_Removals_Mode = 0;
    const char* itemsrRemovalsMode[2]{ "Everyone", "Local" };
    bool antiOBBS = false;

    bool indicators = true;

    bool objetivosDraw[2] = { true, true };
    const char* itemsObjetivosDraw[2]{ "Infected", "Survivor" };

    int typeIndicator = 1;
    const char* itemstypeIndicator[2]{ "Triangule", "Icon" };
    float iconSize = 36.0f;
    float trianguleSize = 10.0f;
    float colorSurvivorsDraw[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
    float colorInfectedsDraw[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float colorInfectedsDrawGhost[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    float witchColorWitchDraw[4] = { 0.9098f, 0.0f, 1.0f, 1.0f };


    float ESP_Players_Arrows_Radius = 100.0f;
    float ESP_Players_Arrows_Max_Distance = 1500.0f;
    bool objetivosEspArrowSurvivor[2] = { true, true };
    bool objetivosEspArrowInfected[2] = { true, true };

    float colorSurvivorsNamePlayer[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 
    float colorSurvivorsClassPlayer[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 

    float colorInfectedsNamePlayer[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    float colorInfectedsClassPlayer[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    bool Visuals_SpectatorList_Active = true;
    bool Misc_Clean_Screenshot = true;
    float Visuals_SpectatorList_Outline_Alpha = 1.0f;
    float Visuals_SpectatorList_Background_Alpha = 1.0f;
    int Visuals_SpectatorList_Pos_X = 615;
    int Visuals_SpectatorList_Pos_Y = 1;
    int Menu_Drag_Bar_Height = 15;
    int Visuals_SpectatorList_Width = 200;
    int Menu_Spacing_X = 3;
    float colorNameEspectadores[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float colorNameType2dor3d[4] = { 0.0f, 0.5f, 1.0f, 1.0f }; 
    bool Radar_Active = true;
    int Radar_Style = 1;
    const char* styleRadar[2] = { "Rectangle", "Circle" };
    bool radarTarget[2] = { true, true };
    const char* itemsradarTarget[2] = { "Survivor", "Infected" };
    int Radar_type = 1;
    const char* itemsRadar_type[2] = { "Normal", "Icon" };

    int typeNormal = 1;
    const char* itemstypeNormal[2] = { "Circles", "Squares" };
    int sizeNormalRadar = 10;
    int radarSizeIcon = 36;
    float radarDistanceEntity = 1500.0f;
    float colorSurvivorsRadar[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 
    float colorInfectedRadar[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    float colorInfectedsRadarGhost[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 

    float witchColorRadar[4] = { 0.9098f, 0.0f, 1.0f, 1.0f }; 


    int Radar_Pos_X = 20;
    int Radar_Pos_Y = 20;
    int Radar_Size = 250;
    float Radar_Radius = 1200.0f;
    float Radar_Cross_Alpha = 0.5f;
    float Radar_Outline_Alpha = 1.0f;

    int HealthBarRadarInfected = 1;
    const char* itemsHealthBarRadarInfected[3] = { "None","Bottom", "Left" };

    int HealthBarRadarSurvivor = 1;
    const char* itemsHealthBarRadarSurvivor[3] = { "None","Bottom", "Left" };
    bool infectedCommonRadar = true;
    int sizeNormalRadarCommons = 5;

    int typeNormalCommons = 1;
    const char* itemstypeNormalCommons[2] = { "Circles", "Squares" };
    float colorRadarInfected[4] = { 0.0f, 123.0f / 255.0f, 255.0f / 255.0f, 1.0f }; 

    bool Visuals_TeamWellBeing_Active = true;
    float Visuals_TeamWellBeing_Background_Alpha = 1.0f;
    int Visuals_TeamWellBeing_Pos_X = 700;
    int Visuals_TeamWellBeing_Pos_Y = 20;
    int Visuals_TeamWellBeing_Width = 217;

    bool selectTargertWellBegin[2] = { true, true };
    const char* multi_itemsWellBeginTargert[2] = { "Survivor", "Infected" };

    float colorNameWellBegin[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float colorNameWellBeginSurvivors[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; 
    float colorNameClassInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    float dTeamWell = 800.0f;

    int Menu_Spacing_Y = 15;
#pragma endregion

#pragma region MISC_CONFIG
    bool Misc_Bunnyhop = true;
    bool Misc_Choke_On_Bhop = false;
    int MethodBuny = 2;
    const char* itemsMethodBuny[3]{ "Classic", "Intermediate", "Advanced" };
    bool Misc_No_Push = true;
    bool Misc_Pure_Bypass = false;
    bool Visuals_Reveal_Scoreboard = false;
    bool Misc_Fast_Stop = false;
    bool Misc_ComputeLightingOrigin_Fix = false;
    bool Misc_SetupBones_Optimization = false;
    bool Misc_Auto_Strafe = true;
    float Misc_Auto_Strafe_Turn_Scale = 0.5f;
    int Misc_Auto_Rocket_Jump_Key, Misc_Auto_Air_Pogo_Key, Misc_Edge_Jump_Key = 0;
    int miscRocket, miscAirpogo, miscEdgejump = 0;
    bool falldamage;
    int keyfall, miscfall = 0;
    bool Misc_Ping_Reducer;
    bool bAntiAfk = false;
    bool sprint = true;
    int keysprint = 0, miscsprint = 0;
    float sprintSpeed = 30.0f;

    bool speedhack = true;
    int keyspeed = 6, miscspeed = 0;
    int speedfactor = 1;
    bool lagExploit = false;
    int keyLagExploit = 5, miscLagExploit = 0;
    int factorLagExploit = 550;

    bool lagExploitv2 = false;
    int keyLagExploitv2, miscLagExploitv2 = 0;
    int factorLagExploitv2 = 350;

    bool airstuck;
    int keyairstuck = 86, miscairstuck = 0;
    bool teleport = false;
    int keyTeleport, miscTeleport = 0;
    int factorLagExploitDamage = 8;
    int factorSpeedDamge = 32;
    bool damageExcesive = false;
    int keydamageExcesive = 81, miscdamageExcesive = 0;
    bool oneShot = false;
    int keyoneShotLag = 81, misconeShotLag = 0;
    int keyoneShotSpeed = 6, misconeShotSpeed = 0;
    int factorLagExploitOneShot = 8;
    int factorSpeedHackOneShot = 32;
    bool speedOneShot = false;
    int keySpeedOneShot = 20, MiscSpeedOneShot = 0;
    int FactorSpeedOneShot = 50;
    int MethodDamage = 1;
    const char* itemsMethodDamage[2]{ "Method 1", "Method 2" };
    int FactorSpeedExtrme = 150;
    int forced_choke_value = 155;

    bool secuence = false;
    bool chockedPacked = false;
    int forced_sequence_value = -1;


    bool chatSpamer = false;
    char sNewlineAdvertise[65] = { "RazeHack | unknowncheats.me " };
    float fSpeed = 20.0f;

    bool enabledAntikick = false;
    int modeAntiKick = 0;
    const char* modeItemsKick[4]{ "None", "All", "Enemies", "Team" };

    float fSpeedName = 1.0f;
    bool enabledSingle = false;
    bool refress = false;

    char changeNameRapid[200] = { "" };
    int modeRobName = 2;
    const char* modeItemsRobName[4]{ "None", "All", "Enemies", "Team" };

    char consoleFull[200] = { "" };
    bool bSendOnce = true;
    bool bUseNewlines = true;

    int Misc_Tank_Combo_Key = 71;
    int misTankCombo = 0;
    bool tankCombo = true;

    bool curacionRapid = true;
    int crurapid = 10;


    bool bAntiJockey = false;
    bool bAntiSmoker = false;
    bool bATeleportCharger = false;
    bool bSpitInfinito = false;
    int keySpitInfinito, miscSpitInfinito = 0;

    bool bHunterDamage = false;
    int keyHunterDamage, miscHunterDamage = 0;

    bool bJockeyDamage = false;
    int keyJockeyDamage, miscJockeyDamage = 0;


    bool customCrosshairStorm = false;
    bool meleeFast = false;
    int keyMeleeFast, miscMeleeFast = 0;

    bool bChargerTurn = false;
    bool modeStream = false;
#pragma endregion

#pragma region GLOW_CONFIG

    bool Outlines_Active = true;
    int Outlines_Style = 0;
    const char* itemsGlow[3]{ "Blur", "Outline", "Team fortress 2" };
    int Outlines_Bloom_Amount = 3;
    int selectGlowTargets = 0;
    const char* itemsGlowTargets[2]{ "Survivors", "Infecteds" };
    bool Outlines_Players_Active = true;
    float Outlines_Players_Alpha = 1.0f;
    int localPlayer = 1;
    float distanceGlowPlayers = 2000.0f;
    bool selectTargertGlow[2] = { true, true };
    const char* multi_itemsGlowTargert[2] = { "Survivor", "Infected" };
    float colorGlowSurvivor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
    float colorGloeInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float colorGlowGhost[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float colorGlowCriticoRojoSurvivor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    float colorGlowMedioSurvivor[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; 
    float colorGlowBuenoSurvivor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; 
    int selectGlowTypeSurvivors = 0;
    const char* itemsGlowTypeSurvivors[2]{ "Custom", "Health" };
    bool enabledGlowWitch = true;
    float Outlines_World_AlphaWitch = 1.0f;
    float colorGlowWitch[4] = { 1.0f, 0.0f, 0.8627f, 1.0f };
    float distanceGlowWitch = 1900.0f;

    bool enabledGlowCommons = true;
    float Outlines_World_AlphaCommons = 1.0f;
    float colorGlowCommons[4] = { 0.0118f, 0.0f, 1.0f, 1.0f };
    float distanceGlowCommons = 1900.0f;
    bool enabledGlowTankRock = true;
    float Outlines_World_AlphaTankRock = 1.0f;
    float colorGlowTankRock[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float distanceGlowTankRock = 1900.0f;
    bool enabledGlowItems = true;
    float distanceGlowItems = 1900.0f;
    float Outlines_World_Alpha = 1.0f;
    bool targetWeaponsGlow[5] = { true, true, true,true,true, };
    const char* itemsWeaponsGlow[5] = { "Weapons", "Medkits", "Melee", "Grenades", "Others" };

    float colorWeaponsGlow[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    float colorMedicationsGlow[4] = { 255.0f / 255.0f, 105.0f / 255.0f, 180.0f / 255.0f, 1.0f };
    float colorGrenadesGlow[4] = { 0.0f, 128.0f / 255.0f, 0.0f, 1.0f };
    float colorAmmunitionGlow[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 0.0f, 1.0f };
    float colorMeleeGlow[4] = { 255.0f / 255.0f, 165.0f / 255.0f, 0.0f, 1.0f };

    bool enabledGlowStateBoomer = true;

#pragma endregion

#pragma region CHAMS_CONFIG

    bool enabledChamsGlobal = true;
    bool playersChams = true;
    bool playersNoDeph = false;
    float playersAlpha = 1.0f;
    float Materials_Players_Alpha = 1.0f;
    int playerSelectMat = 1;
    const char* itemsMaterialPlayers[3] = { "Original","Glow","Plastic" };

    bool playersMaterialsIgnore[2] = { true, true };
    const char* itemsMaterialPlayersIgnore[2] = { "Survivors", "Infecteds" };
    int selectChamsTypeSurvivors = 0;
    const char* itemsChamsTypeSurvivors[2]{ "Custom", "Health" };
    int selectChamsTargets = 0;
    const char* itemsChamsTargets[2]{ "Survivors", "Infecteds" };

    float colorChamsSurvivor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
    float colorChamsInfected[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float colorChamsGhost[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float colorChamsCriticoRojoSurvivor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    float colorChamsMedioSurvivor[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; 
    float colorChamsBuenoSurvivor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };


    bool Materials_World_Active = true;
    int matItemsSelectMat = 1;
    const char* itemsMaterialItems[3] = { "Original","Glow","Plastic" };

    float Materials_World_Alpha = 0.5f;
    bool Materials_World_No_Depth = true;
    float distanceChamsItems = 1900.0f;
    bool targetWeaponsChams[5] = { true, true, true,true,true, };
    const char* itemsWeaponsChams[5] = { "Armas ", "Medicinas","Melee","Granadas","Otros" };

    float colorWeaponsChams[4] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f };
    float colorMedicationsChams[4] = { 1.0f, 0.047f, 0.521f, 1.0f };
    float colorGrenadesChams[4] = { 0.0f, 128.0f / 255.0f, 0.0f, 1.0f };
    float colorAmmunitionChams[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 0.0f, 1.0f };
    float colorMeleeChams[4] = { 255.0f / 255.0f, 165.0f / 255.0f, 0.0f, 1.0f };
    bool bChamsWitch = true;
    int matWitchSelectMat = 1;
    const char* itemsMaterialWitch[3] = { "Original","Glow","Plastic" };
    float Materials_Witch_Alpha = 0.5f;
    bool Materials_Witch_No_Depth = true;
    float colorChamsWitch[4] = { 1.0f, 0.0f, 0.8627f, 1.0f };
    float distanceChamsWitch = 1900.0f;
    bool bChamsCommons = true;
    int matCommonSelectMat = 1;
    const char* itemsMaterialCommon[3] = { "Original","Glow","Plastic" };
    float Materials_Common_Alpha = 0.4f;
    bool Materials_Common_No_Depth = true;
    float colorChamsCommons[4] = { 0.0118f, 0.0f, 1.0f, 1.0f };
    float distanceChamsCommons = 1900.0f;
    bool bChamsTankRock = true;
    int matTankRockSelectMat = 1;
    const char* itemsMaterialTankRock[3] = { "Original","Glow","Plastic" };
    float Materials_TankRock_Alpha = 1.0f;
    bool Materials_TankRock_No_Depth = true;
    float colorChamsTankRock[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float distanceChamsTankRock = 1900.0f;
    bool enabledChamsStateBoomer = true;




#pragma endregion

#pragma region SPYHACK
    bool Visuals_Chat_Player_List_Info = true;
    bool playersSpyObj[2] = { true, true };
    const char* itemsSpyPlayers[2] = { "Survivors", "Infecteds" };
    bool visualSpyNotify = true;
    bool playersNotifySpy[3] = { true, true,true };
    const char* itemsPlayersNotifySpy[3] = { "Esp", "Glow y chams","Panel emergente" };
    float colorFriend[4] = { 0.0f, 0.047f, 1.0f, 1.0f };
    float colorCheater[4] = { 1.0f, 0.922f, 0.0f, 1.0f };
    float colorRetardLegit[4] = { 0.875f, 0.0f, 1.0f, 1.0f };
    int Visuals_SpyCamera_Pos_X = 1003;
    int Visuals_SpyCamera_Pos_Y = 6;
    int Visuals_SpyCamera_Pos_W = 280;
    int Visuals_SpyCamera_Pos_H = 250;

    char searchPlayerMarked[65] = { "" };
    char addPlayerMarked[100] = { "" };
    char addPlayerName[100] = { "" };


#pragma endregion

#pragma region SETTINGS_CONFIG
    bool enabledAimbot;
    int keyAimbotenabled, miscAimbotenabled = 0;

    bool enabledTriggerbot;
    int keyTriggerbotenabled, miscTriggerbotenabled = 0;

    bool enabledEsp;
    int keyEspenabled, miscEspenabled = 0;



    bool enabledGlow;
    int keyGlowenabled, miscGlowenabled = 0;

    bool enabledBuny;
    int keyBunyenabled, miscBunyenabled = 0;

    bool enabledSpeed;
    int keySpeedenabled, miscSpeedenabled = 0;


    bool disabledAll;
    int keydisabledAll, miscdisabledAll = 0;
    bool panelkeybind = false;

    int panelPosX = 10;
    int panelPosY = 1;
    int Menu_HeightBinds = 15;
    int Visuals__WidthBinds = 200;
    char SaveLoadName[200] = { "" };
    char SelectedConfig[200] = { "" };  

    float color[4] = { 0.0f, 1.0f, 0.902f, 1.0f }; 
    float dpi_scale = 1.0f;
    int notify_select = 0;
    const char* notify_items[2]{ "Circle", "Line" };

    int notify_positions = 1;
    const char* notify_items_positions[2]{ "Top", "Bottom" };

    int keyShowMenu = 45, misShowMenu = 0;
    bool showNotify = false;
    bool showtoolbar = false;
    int FontSizeGlobal = 15;
    bool bAntiTracker = false;
    bool showDebugClient = false;
    char sNewNameTracker[65] = { "Rz ---- Rz" };
    int keyNameChange = 81, miscNameChange = 0;
    int modeAntiTracker = 2;

#pragma endregion

#pragma region OTHERS

    // LOADER TEXT TITLE
    float text_animation = 0.00f;
    float loader_animation = 0.f;
    bool text_animation_hide = true;

    int page = 0;
    int currentSubtabMenu;
    float tab_alpha = 0.f; /* */  float tab_add; /* */  int active_tab = 0;
    float subtab_alpha = 0.0f;
    float subtab_add;
    int subtabMenu;

    // Submenu aims
    int subtabMenuAims;
    int currentSubtabMenuAims;
    float subtab_alphaAims = 0.0f;
    float subtab_addAims;
    // submenu exploit
    int subtabMenuEx;
    int currentSubtabMenuEx;
    float subtab_alphaEx = 0.0f;
    float subtab_addEx;
    // submenu settings
    int subtabMenuSt;
    int currentSubtabMenuSt;
    float subtab_alphaSt = 0.0f;
    float subtab_addSt;
    // submenu visuals
    int subtabMenuV;
    int currentSubtabMenuV;
    float subtab_alphaV = 0.0f;
    float subtab_addV;
    // submenu Glowhack
    int subtabMenuGH;
    int currentSubtabMenuGH;
    float subtab_alphaGH = 0.0f;
    float subtab_addGH;
    // submenu CHAMShack
    int subtabMenuChams;
    int currentSubtabMenuChams;
    float subtab_alphaChams = 0.0f;
    float subtab_addChams;

    // submenu spyhack
    int subtabMenuSpy;
    int currentSubtabMenuSpy;
    float subtab_alphaSpy = 0.0f;
    float subtab_addSpy;


    //SUBTABS
    int activeSubTabAimbot = 0;
    int activeSubTabVisuals = 0;
    int activeSubTabVisualsV2 = 0;
    int activeSubTabExploits = 0;
    int activeSubTabConfigs = 0;

#pragma endregion

#pragma region Crosshair
    bool customCrosshair = false;
    float colorCrosshair[4] = { 1.0f, 0.1f, 0.1f, 1.0f };
    float crosshairTicknes = 1.5f;
    int crossSize = 5;
    int selected_crosshair{};
    int selected_language = 0;


#pragma endregion

    
};
extern vars g_var;


