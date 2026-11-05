#include "font_awesome_5.h"
#include "CMenu.h"
#include "../Vars.h"
#include "ImGui/Vars/g_vars.h"
#include "ImGui/XorStr.h"
#include "ComponersImGui/Managers/animations.hpp"
#include "ComponersImGui/Managers/ChildManager.hpp"
#include "ComponersImGui/Managers/WidgetsManager.hpp"
#include "ComponersImGui/Managers/StyleManager.hpp"
#include "ComponersImGui/Managers/TabsManager.hpp"
#include "ComponersImGui/Managers/PopupManager.hpp"
#include "ComponersImGui/Managers/LangManager.hpp"
#include "ImGui/ImGui_Edited/imgui_edited.hpp"
#include "../../SDK/DirectX/d3dx9tex.h"
#include "ImGui/Fonts/images.h"
#include "ImGui/Fonts/font.h"
#include "ImGui/Fonts/fa.h"
#include "ImGui/anim/anim.h"
#pragma comment(lib, "d3dx9.lib")


//  Damn, other TF2 stuff here, god, what do i do, delete them?
#define TF_TEAM_AUTOASSIGN (TF_TEAM_COUNT + 1 )
#define TF_TEAM_HALLOWEEN TF_TEAM_AUTOASSIGN
#define TF_TEAM_PVE_INVADERS TF_TEAM_BLUE
#define TF_TEAM_PVE_DEFENDERS TF_TEAM_RED	
#define TF_TEAM_PVE_INVADERS_GIANTS 4


#define COLOR_TF_SPECTATOR Color( 245, 229, 196, 255 )
#define COLOR_TF_RED Color( 175, 73, 73, 255 )
#define COLOR_TF_BLUE Color( 79, 117, 143, 255 )

enum
{
    TF_ARENA_NOTIFICATION_CAREFUL = 0,
    TF_ARENA_NOTIFICATION_SITOUT,
    TF_ARENA_NOTIFICATION_NOPLAYERS
};

enum
{
    TEAM_ROLE_NONE = 0,
    TEAM_ROLE_DEFENDERS,
    TEAM_ROLE_ATTACKERS,
    NUM_TEAM_ROLES
};
vars g_var;
DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

ChildManager& cm = ChildManager::get();
auto& widgets = WidgetsManager::get();

#pragma region Features
// features
// AIMBOTS
#pragma region AIMBOT
void AimbotColumOne() {
    widgets.Checkbox(XorStr("Aimbot"), &g_var.aimbot, &g_var.keyaim);
    widgets.Checkbox(XorStr("Fov preview"), &g_var.circleFov, 0, g_var.ColorCircleFov);
    widgets.Combo(XorStr("Method"), &g_var.selectAimbot, { XorStr("Normal"), XorStr("Silent"), XorStr("Perfect Silent"),XorStr("Smooth") });
    widgets.SliderFloat(XorStr("Aimbot FOV"), &g_var.fovAimbot, 1, 180);

    if (g_var.selectAimbot == 3) {
        widgets.SliderFloat(XorStr("Aimbot Smooth"), &g_var.smoothAimbot, 1, 100);
    }
    widgets.Combo(XorStr("Sort"), &g_var.selectSortAimbot, { XorStr("FOV"), XorStr("Distance") });
    if (g_var.selectSortAimbot == 1) {
        widgets.SliderFloat(XorStr("Aimbot distance"), &g_var.distanceAimbot, 1, 5000);
    }
    if (g_var.selectAimbot == 0 || g_var.selectAimbot == 1 || g_var.selectAimbot == 2 || g_var.selectAimbot == 3) {
        widgets.Combo(XorStr("HitBox aimbot"), &g_var.selectAimbotBone, { XorStr("Head"), XorStr("Body"),XorStr("Auto") });
    }
    widgets.Checkbox(XorStr("Auto shoot"), &g_var.autoshoot);

}
void AimbotColumTwo() {
    widgets.MultiCombo(XorStr("Aimbot targets"), g_var.selectItemsAimbot, { XorStr("Special Infected"), XorStr("My Team") });
    widgets.Combo(XorStr("Common & witch hitbox"), &g_var.selectAimbotBoneCommon, { XorStr("Head"), XorStr("Body") });
    widgets.Checkbox(XorStr("Ignore aimbot on commons"), &g_var.IgnoreAimbotCommon);
    widgets.Checkbox(XorStr("Ignore aimbot on witch"), &g_var.IgnoreAimbotWitch);
    widgets.Checkbox(XorStr("Ignore aimbot on calm witch"), &g_var.ignoreShotWitchCalm);
    //  widgets.Checkbox(XorStr("autowall"), &g_var.autowall);

}
void AimbotColumTwoGroup() {
    widgets.Checkbox(XorStr("Enable hitscan"), &g_var.Aimbot_Hitscan_Active);
    if (g_var.Aimbot_Hitscan_Active) {
        widgets.Checkbox(XorStr("Scan head"), &g_var.Aimbot_Hitscan_Scan_Head);
        widgets.Checkbox(XorStr("Scan body"), &g_var.Aimbot_Hitscan_Scan_Body);
    }

}
#pragma endregion
#pragma region Triggerbot
void TriggerbotColumOne() {
    widgets.Checkbox(XorStr("Triggerbot"), &g_var.triggerbot);
    widgets.MultiCombo(XorStr("Triggerbot targets"), g_var.objtrigger, { XorStr("Enemies"), XorStr("Team"), XorStr("Commons"), XorStr("Witch") });
    widgets.Checkbox(XorStr("Crosshair display"), &g_var.triggerMira, 0, g_var.triggerMiraColor);
    widgets.SliderFloat(XorStr("Triggerbot distance"), &g_var.distanceTrigger, 100, 5000);

}
void TriggerbotColumTwo()
{
    widgets.Checkbox(XorStr("Head tracking"), &g_var.trigger_head_follow);

    if (g_var.trigger_head_follow) {
        widgets.Combo(XorStr("Bone trigger"), &g_var.selectTriggerBone, { XorStr("Head"), XorStr("Body"), XorStr("All") });
        widgets.Checkbox(XorStr("Silent triggerbot"), &g_var.trigger_silent);
    }

    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), XorStr(LangManager::get().translate("Witch")));
    widgets.Checkbox(XorStr("Ignore triggerbot on calm witch"), &g_var.ignoreWitchRage);

}
#pragma endregion
#pragma region OthersAims
void OtherAimsColumnOne() {
    widgets.Checkbox(XorStr("Auto pistol"), &g_var.rapidfire);
    ImGui::SetItemTooltip((LangManager::get().translate("Removes pistol and rifle delay.\nShoot continuously with one click.")));
    //  widgets.Checkbox(XorStr("Auto pistol v2"), &g_var.autopistol);
    //  ImGui::SetItemTooltip((LangManager::get().translate("Removes pistol and rifle delay.\nShoot continuously with one click.")));

    widgets.Checkbox(XorStr("Fast melee"), &g_var.meleeFast, &g_var.keyMeleeFast);
   // widgets.Checkbox(XorStr("Simple Auto Shove"), &g_var.Aimbot_AutoShove);
   // widgets.MultiCombo(XorStr("Auto shove targets"), g_var.selectAutoM2, { XorStr("HUNTER"), XorStr("SPITTER"), XorStr("JOCKEY"), XorStr("BOOMER") , XorStr("SMOKER") });
   // widgets.SliderFloat(XorStr("Shove range"), &g_var.range, 10, 300);

}
void OtherAimsColumnTwo() {
    widgets.Checkbox(XorStr("No recoil"), &g_var.noRecoil);
    widgets.Checkbox(XorStr("No spread"), &g_var.noSpreed);
    widgets.Checkbox(XorStr("Disable Screen Shake"), &g_var.bDisableScreenShake);

}

#pragma endregion

#pragma region Crosshair
void Aimbot_melee() {

}


#pragma endregion
// ESP
#pragma region ESP
void EspPlayersColumnOne() {
    widgets.Checkbox(XorStr("Enabled Esp"), &g_var.esp);
    widgets.Checkbox(XorStr("Esp preview"), &g_var.espPreview);
    widgets.Combo(XorStr("ESP config"), &g_var.selectEsp, { XorStr("Survivor"), XorStr("Infected") });
    widgets.Combo(XorStr("ESP targets"), &g_var.selectObjEsp, { XorStr("None"), XorStr("Survivor"), XorStr("Infected"), XorStr("All") });
}
void EspPlayersColumnOneConfigs() {

    widgets.SliderInt(XorStr("Bone thickness"), &g_var.ticknessBoneGlobal, 0, 5, "%d°");
    if (g_var.selectEsp == 0) {
        widgets.SliderFloat(XorStr("Survivor distance"), &g_var.distanceSurvivor, 1500, 5000);
        widgets.Checkbox(XorStr("2D Box"), &g_var.box2dSurvivor, 0, g_var.colorBoxSurvivor, [&]() {
            widgets.Combo(XorStr("Box type"), &g_var.selectTypeBoxSurvivor, { XorStr("Normal"), XorStr("Corners") });
            });
        widgets.SliderInt(XorStr("Box thickness"), &g_var.thicknessBox2DSurvivor, 0, 5, "%d°");
    }
    else if (g_var.selectEsp == 1) {
        widgets.SliderFloat(XorStr("Infected distance"), &g_var.distanceInfected, 1500, 5000);
        widgets.Checkbox(XorStr("2D Box"), &g_var.box2dInfected, 0, g_var.colorBoxInfected, [&]() {
            widgets.Combo(XorStr("Box type"), &g_var.selectTypeBoxInfected, { XorStr("Normal"), XorStr("Corners") });
            });
        widgets.SliderInt(XorStr("Box thickness"), &g_var.thicknessBox2DInfected, 0, 5, "%d°");
    }

}
void EspPlayersColumnTwoConfigs() {
    if (g_var.selectEsp == 0) {
        widgets.Combo(XorStr("Player name"), &g_var.selectTypeNameSurvivor, { XorStr("None"), XorStr("Right"), XorStr("Top") });
        widgets.Combo(XorStr("Player health"), &g_var.selectTypeHealthSurvivor, { XorStr("None"), XorStr("Right"), XorStr("Below") });
        widgets.Combo(XorStr("Health bar"), &g_var.selectTypeBarSurvivor, { XorStr("None"), XorStr("Left"), XorStr("Below") });
    }
    else if (g_var.selectEsp == 1) {
        widgets.Combo(XorStr("Player name"), &g_var.selectTypeNameInfected, { XorStr("None"), XorStr("Right"), XorStr("Top") });
        widgets.Combo(XorStr("Player health"), &g_var.selectTypeHealthInfected, { XorStr("None"), XorStr("Right"), XorStr("Below") });
        widgets.Combo(XorStr("Health bar"), &g_var.selectTypeBarInfected, { XorStr("None"), XorStr("Left"), XorStr("Below") });
    }

}
void EspPlayersColumnTwo() {

    if (g_var.selectEsp == 0) {
        widgets.Checkbox(XorStr("Esp Bone"), &g_var.boneSurvivor, 0, g_var.colorBoneSurvivor);
        widgets.Checkbox(XorStr("Esp line"), &g_var.lineSurvivor, 0, g_var.colorLineSurvivor);
        widgets.Checkbox(XorStr("Esp indicator"), &g_var.IndicatorSurvivor, 0, g_var.colorIndicatorSurvivor);
        widgets.Checkbox(XorStr("Esp head.."), &g_var.headEspSurvivor, 0, g_var.colorHeadEspSurvivor);
        widgets.Combo(XorStr("Head type esp"), &g_var.selectTypeHeadSurvivor, { XorStr("Square"), XorStr("Circle") });

        widgets.ColorEdit(XorStr("Name text color"), g_var.colornameTextSurvivor);
    }
    else if (g_var.selectEsp == 1) {
        widgets.Checkbox(XorStr("Esp Bone"), &g_var.boneInfected, 0, g_var.colorBoneInfected);
        widgets.Checkbox(XorStr("Esp line"), &g_var.lineInfected, 0, g_var.colorLineInfected);
        widgets.Checkbox(XorStr("Esp indicator"), &g_var.IndicatorInfected, 0, g_var.colorIndicatorInfected);
        widgets.Checkbox(XorStr("Esp head..."), &g_var.headEspInfected, 0, g_var.colorHeadEspInfected);
        widgets.Combo(XorStr("Head type esp.."), &g_var.selectTypeHeadInfected, { XorStr("Square."), XorStr("Circle.") });
        widgets.Checkbox(XorStr("Boomer radius"), &g_var.BoomerRadiusESP, 0, g_var.colorRadiusBoomer);

        widgets.ColorEdit(XorStr("Name text color"), g_var.colornameTextInfected);
        widgets.Checkbox(XorStr("Enabled class infected"), &g_var.classInfected);

        if (g_var.classInfected) {
            widgets.Combo(XorStr("Type class"), &g_var.selectTypeInfectedName, { XorStr("Icon"), XorStr("Text") });

            if (g_var.selectTypeInfectedName == 0) {
                widgets.SliderInt(XorStr("Icon size"), &g_var.iconSizeEsp, 18, 40, "%d°");
            }
            else {
                widgets.ColorEdit(XorStr("Text color"), g_var.colorClassInfected);
            }
        }
    }

}

// ESP ITEMS
void EspItemsColumOne() {
    widgets.Checkbox(XorStr("Items esp"), &g_var.enabledWeapons);
    widgets.Combo(XorStr("Type esp items"), &g_var.selectTypeItems, { XorStr("Icon"), XorStr("Text") });
    widgets.Checkbox(XorStr("Items esp box"), &g_var.enabledBoxWeapons);
    widgets.MultiCombo(XorStr("Item targets"), g_var.targetWeapons, { XorStr("Weapons"), XorStr("Medkits"), XorStr("Melee"), XorStr("Grenades"), XorStr("Others") });
    widgets.SliderFloat(XorStr("Item distance"), &g_var.distanceItems, 500, 3000);

}
void EspItemsColumTwo() {
    widgets.ColorEdit(XorStr("Weapons"), g_var.colorWeapons);
    widgets.ColorEdit(XorStr("Medications"), g_var.colorMedications);
    widgets.ColorEdit(XorStr("Grenades"), g_var.colorGrenades);
    widgets.ColorEdit(XorStr("Ammunition"), g_var.colorAmmunition);
    widgets.ColorEdit(XorStr("Melee"), g_var.colorMelee);

}

// ESP OTHERS

void EspOtherColumOne() {

    widgets.Checkbox(XorStr("Esp witch"), &g_var.espWitch, 0, g_var.witchColor);
    widgets.Combo(XorStr("Name type"), &g_var.selectTypeWitchName, { XorStr("Icon"), XorStr("Text") });

    if (g_var.selectTypeWitchName == 0) {
        widgets.SliderInt(XorStr("Icon size"), &g_var.iconSizeWitch, 18, 40, "%d°");
    }
    widgets.Checkbox(XorStr("ESP witch box 2d"), &g_var.witchBox);
    widgets.SliderFloat(XorStr("Witch distance"), &g_var.distanceWitch, 500, 3000);


}
void EspOtherColumTwo() {

    widgets.Checkbox(XorStr("ESP common infected"), &g_var.commonInfected, 0, g_var.colorcommonInfected);
    widgets.Checkbox(XorStr("ESP common box 2d"), &g_var.commonBox);
    widgets.SliderFloat(XorStr("Infected distance"), &g_var.distanceInfectedCommon, 300, 5000);

}
void EspOtherColumFour() {

    widgets.Checkbox(XorStr("ESP tank rock"), &g_var.rockTank, 0, g_var.colorrockTank);
    widgets.Checkbox(XorStr("ESP tank rock box 2d"), &g_var.rockTankBox);
    widgets.SliderFloat(XorStr("Tank rock distance"), &g_var.distancerockTank, 300, 5000);

}
void EspOtherColumTree() {
    widgets.Checkbox(XorStr("Ghost mode"), &g_var.modeGhost, 0, g_var.colorGhost);


}
#pragma endregion
//VISUALS
#pragma region VISUALS
// WORLD
void VisualsWorldColumOne() {
    widgets.Checkbox(XorStr("No fog"), &g_var.noFog);
    widgets.Checkbox(XorStr("No vomit"), &g_var.noVomit);
    widgets.Checkbox(XorStr("No fog sky"), &g_var.noFogSky);
    widgets.Checkbox(XorStr("Improve map textures"), &g_var.visualsImproveMapTextures);
    widgets.Checkbox(XorStr("Enhanced no vomit"), &g_var.visualsEnhancedNoVomit);
    widgets.Checkbox(XorStr("Remove ghost mode overlay"), &g_var.visualsDisableGhostMode);
    widgets.Checkbox(XorStr("Full bright"), &g_var.noVisionfullbrig);
    widgets.Checkbox(XorStr("Full flashlight"), &g_var.noVisionfullflash);
    widgets.Checkbox(XorStr("Use simple models"), &g_var.bUseSimpleModels);


}
void VisualsWorldColumOneOthers() {
    widgets.Checkbox(XorStr("Enable World Modulation"), &g_var.bWorldModulation);

    widgets.Combo(XorStr("World modulation mode"), &g_var.Visuals_World_Modulation_Mode, { XorStr("Nigth"), XorStr("Custom colors") });
    if (g_var.Visuals_World_Modulation_Mode == 1) {
        widgets.ColorEdit(XorStr("Sky color"), g_var.sKyColor);
    }
    else {
        widgets.SliderFloat(XorStr("Night mode"), &g_var.Visuals_Night_Mode, 0, 100);
    }
    widgets.Combo(XorStr("Particles mode"), &g_var.Visuals_Particles_Mode, { XorStr("Original"), XorStr("Custom colors"), XorStr("Raimbow") });
    if (g_var.Visuals_Particles_Mode == 1) {
        widgets.ColorEdit(XorStr("Particles color"), g_var.particulesColors);
    }
    else if (g_var.Visuals_Particles_Mode == 2) {
        widgets.SliderFloat(XorStr("Particles rainbow rate"), &g_var.Visuals_Particles_Rainbow_Rate, 1, 10);
    }

}
void VisualsWorldColumTwoThirPerson() {
    widgets.Checkbox(XorStr("Third Person"), &g_var.Visuals_Thirdperson_Active, &g_var.keyPerson);

    widgets.Combo(XorStr("Camera collision"), &g_var.selectCollision, { XorStr("Off"), XorStr("On") });
    widgets.SliderFloat(XorStr("Offset forward"), &g_var.Visuals_Thirdperson_Offset_Forward, 10, 500);
    PushItemWidth(CalcItemWidth() / 2 - 5);

    widgets.SliderFloat(XorStr("Offset right"), &g_var.Visuals_Thirdperson_Offset_Right, -50, 50);
    SameLine(0, 10);

    widgets.SliderFloat(XorStr("Offset up"), &g_var.Visuals_Thirdperson_Offset_Up, -50, 50);
    PopItemWidth();


}
void VisualsWorldColumTwoLocalView() {
    widgets.Checkbox(XorStr("Enabled view model"), &g_var.Visuals_ViewModel_Active);
    widgets.SliderFloat(XorStr("Fov override"), &g_var.Visuals_FOV_Override, 70, 170);
    widgets.SliderFloat(XorStr("Offset forward."), &g_var.Visuals_ViewModel_Offset_Forward, -50, 50);
    PushItemWidth(CalcItemWidth() / 2 - 5);

    widgets.SliderFloat(XorStr("Offset right."), &g_var.Visuals_ViewModel_Offset_Right, -50, 50);
    SameLine(0, 10);

    widgets.SliderFloat(XorStr("Offset up."), &g_var.Visuals_ViewModel_Offset_Up, -50, 50);
    PopItemWidth();


}
// ARROWS
void VisualsArrowsColumOne() {
    widgets.Checkbox(XorStr("Enabled Arrows"), &g_var.indicators);
    widgets.SliderFloat(XorStr("Arrow Radius"), &g_var.ESP_Players_Arrows_Radius, 50, 400);
    widgets.SliderFloat(XorStr("Arrow Max distance"), &g_var.ESP_Players_Arrows_Max_Distance, 100, 3000);
    widgets.MultiCombo(XorStr("Draw targets"), g_var.objetivosDraw, { XorStr("Infected"), XorStr("Survivor") });
    widgets.Combo(XorStr("Arrow type"), &g_var.typeIndicator, { XorStr("Triangule"), XorStr("Icon") });

    if (g_var.typeIndicator == 1) {
        widgets.SliderFloat(XorStr("Icon size"), &g_var.iconSize, 20, 50);
    }
    else if (g_var.typeIndicator == 0) {
        widgets.SliderFloat(XorStr("Triangle size"), &g_var.trianguleSize, 10, 30);
    }

}
void VisualsArrowsColumTwo() {
    widgets.ColorEdit(XorStr("Color survivors"), g_var.colorSurvivorsDraw);
    widgets.ColorEdit(XorStr("Color infected"), g_var.colorInfectedsDraw);
    widgets.ColorEdit(XorStr("Color infected ghosts"), g_var.colorInfectedsDrawGhost);
    widgets.ColorEdit(XorStr("Color witch"), g_var.witchColorWitchDraw);


}
void VisualsArrowsColumTree() {
    widgets.MultiCombo(XorStr("Esp arrows survivors"), g_var.objetivosEspArrowSurvivor, { XorStr("Name player."), XorStr("Survivor class") });
    widgets.ColorEdit(XorStr("Color name player"), g_var.colorSurvivorsNamePlayer);
    widgets.ColorEdit(XorStr("Color class"), g_var.colorSurvivorsClassPlayer);


}
void VisualsArrowsColumFour() {

    widgets.MultiCombo(XorStr("Esp arrows infecteds"), g_var.objetivosEspArrowInfected, { XorStr("Name player"), XorStr("Infected class") });
    widgets.ColorEdit(XorStr("Color  name player."), g_var.colorInfectedsNamePlayer);
    widgets.ColorEdit(XorStr("Color class."), g_var.colorInfectedsClassPlayer);

}
// ESPECTADORES Y RADAR
void VisualsEspectoresColumnOne() {
    widgets.Checkbox(XorStr("Enabled spectator list"), &g_var.Visuals_SpectatorList_Active);
    widgets.SliderFloat(XorStr("Outlines alpha"), &g_var.Visuals_SpectatorList_Outline_Alpha, 0, 1);
    widgets.SliderFloat(XorStr("Backgroud alpha"), &g_var.Visuals_SpectatorList_Background_Alpha, 0, 1);
    widgets.ColorEdit(XorStr("Color name"), g_var.colorNameEspectadores);
    widgets.ColorEdit(XorStr("Color 1P-3P"), g_var.colorNameType2dor3d);

}
void VisualsRadarColumTwo() {
    widgets.Checkbox(XorStr("Enabled radar"), &g_var.Radar_Active, 0, nullptr, [&]() {
        widgets.SliderFloat(XorStr("Max distance radar"), &g_var.radarDistanceEntity, 100, 3000);
        widgets.SliderInt(XorStr("Radar size"), &g_var.Radar_Size, 150, 700, "%d°");
        widgets.SliderFloat(XorStr("Radar radius"), &g_var.Radar_Radius, 200, 1000);
        });
    widgets.Combo(XorStr("Style radar"), &g_var.Radar_Style, { XorStr("Rectangle"), XorStr("Circle") });
    widgets.MultiCombo(XorStr("Radar targets"), g_var.radarTarget, { XorStr("Survivor"), XorStr("Infected") });
    widgets.Combo(XorStr("Type of radar"), &g_var.Radar_type, { XorStr("Normal"), XorStr("Icon") });
    widgets.Combo(XorStr("Shape style"), &g_var.typeNormal, { XorStr("Circles"), XorStr("Squares") });

    if (g_var.Radar_type == 0) {
        widgets.SliderInt(XorStr("Shape size"), &g_var.sizeNormalRadar, 10, 30, "%d°");
    }
    else {
        widgets.SliderInt(XorStr("Icon size"), &g_var.radarSizeIcon, 20, 50, "%d°");
    }


}
void VisualsRadarCommons() {

    widgets.Checkbox(XorStr("Enabled commons"), &g_var.infectedCommonRadar);
    widgets.SliderInt(XorStr("Size.."), &g_var.sizeNormalRadarCommons, 5, 20, "%d°");
    widgets.Combo(XorStr("Shape style..."), &g_var.typeNormalCommons, { XorStr("Circles.."), XorStr("Squares...") });
    widgets.ColorEdit(XorStr("Color infected commons"), g_var.colorRadarInfected);

}
void VisualsRadarColumTree() {

    widgets.Combo(XorStr("Health bar."), &g_var.HealthBarRadarSurvivor, { XorStr("None"), XorStr("Bottom"), XorStr("Left") });
    widgets.ColorEdit(XorStr("Color survivors"), g_var.colorSurvivorsRadar);




}
void VisualsRadarColumFour() {
    widgets.Combo(XorStr("Health bar"), &g_var.HealthBarRadarInfected, { XorStr("None"), XorStr("Bottom"), XorStr("Left") });
    widgets.ColorEdit(XorStr("Color infected"), g_var.colorInfectedRadar);
    widgets.ColorEdit(XorStr("Color infected ghosts"), g_var.colorInfectedsRadarGhost);
    widgets.ColorEdit(XorStr("Color Witch"), g_var.witchColorRadar);

}
// HUD INFO
void VisualsHudInfoColumOne() {
    widgets.Checkbox(XorStr("Enable HUD Info"), &g_var.Visuals_TeamWellBeing_Active);
    widgets.MultiCombo(XorStr("Select targets"), g_var.selectTargertWellBegin, { XorStr("Survivor"), XorStr("Infected") });
    widgets.SliderInt(XorStr("HUD width"), &g_var.Visuals_TeamWellBeing_Width, 10, 500, "%d°");
    widgets.SliderFloat(XorStr("Max distance HUD"), &g_var.dTeamWell, 100, 3000);

}
void VisualsHudInfoColumTwo() {
    widgets.ColorEdit(XorStr("Infected Name Color"), g_var.colorNameWellBegin);
    widgets.ColorEdit(XorStr("Survivor Name Color"), g_var.colorNameWellBeginSurvivors);
    widgets.ColorEdit(XorStr("Infected Class Color"), g_var.colorNameClassInfected);

}
#pragma endregion
//GLOW
#pragma region GLOW
void GlowHackColumnOne() {
    widgets.Checkbox(XorStr("Enabled glow"), &g_var.Outlines_Active);
    widgets.Combo(XorStr("Style glow"), &g_var.Outlines_Style, { XorStr("Bloom"), XorStr("Outline"), XorStr("Team fortress 2") });

    if (g_var.Outlines_Style == 0) {
        widgets.SliderInt(XorStr("Scale bloom"), &g_var.Outlines_Bloom_Amount, 1, 10, "%d°");
    }
    widgets.Combo(XorStr("Config select"), &g_var.selectGlowTargets, { XorStr("Survivors"), XorStr("Infecteds") });
    widgets.MultiCombo(XorStr("Glow targets"), g_var.selectTargertGlow, { XorStr("Survivor"), XorStr("Infected") });


}
void GlowHackColumnTwo() {
    widgets.Checkbox(XorStr("Enabled glow players"), &g_var.Outlines_Players_Active);
    widgets.SliderFloat(XorStr("Distance glow players"), &g_var.distanceGlowPlayers, 700, 3000);


}
void GlowHackColumnTwoSurvivors() {
    widgets.Combo(XorStr("Type glow"), &g_var.selectGlowTypeSurvivors, { XorStr("Custom"), XorStr("Health") });

    if (g_var.selectGlowTypeSurvivors == 0) {
        widgets.ColorEdit(XorStr("Color glow team"), g_var.colorGlowSurvivor);
    }
    else if (g_var.selectGlowTypeSurvivors == 1) {
        ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), XorStr("Glow colors by health status"));
        widgets.ColorEdit(XorStr("Critical health color"), g_var.colorGlowCriticoRojoSurvivor);
        widgets.ColorEdit(XorStr("Medium health color"), g_var.colorGlowMedioSurvivor);
        widgets.ColorEdit(XorStr("Good health color"), g_var.colorGlowBuenoSurvivor);
    }

}
void GlowHackColumnTwoInfecteds() {
    widgets.ColorEdit(XorStr("Color glow infected special"), g_var.colorGloeInfected);
    widgets.ColorEdit(XorStr("Color glow ghost"), g_var.colorGlowGhost);

}
// GLOW ITEMS
void GlowHackItemsColumnOne() {
    widgets.Checkbox(XorStr("Enabled glow items"), &g_var.enabledGlowItems);
    widgets.SliderFloat(XorStr("Distance glow items"), &g_var.distanceGlowItems, 600, 3000);
    widgets.MultiCombo(XorStr("Glow item targets"), g_var.targetWeaponsGlow, { XorStr("Weapons"), XorStr("Medkits"), XorStr("Melee"), XorStr("Grenades"), XorStr("Others") });

}
void GlowHackItemsColumnTwo() {
    widgets.ColorEdit(XorStr("Glow Weapons"), g_var.colorWeaponsGlow);
    widgets.ColorEdit(XorStr("Glow Medications"), g_var.colorMedicationsGlow);
    widgets.ColorEdit(XorStr("Glow Grenades"), g_var.colorGrenadesGlow);
    widgets.ColorEdit(XorStr("Glow Ammunition"), g_var.colorAmmunitionGlow);
    widgets.ColorEdit(XorStr("Glow Melee"), g_var.colorMeleeGlow);

}
// GLOW OTHERS
void GlowHackOthersColumnOne() {
    widgets.Checkbox(XorStr("Enabled glow witch"), &g_var.enabledGlowWitch);
    widgets.SliderFloat(XorStr("Distance glow witch"), &g_var.distanceGlowWitch, 600, 3000);
    widgets.ColorEdit(XorStr("Glow witch"), g_var.colorGlowWitch);


}
void GlowHackOthersColumnTwo() {
    widgets.Checkbox(XorStr("Enabled glow commons"), &g_var.enabledGlowCommons);
    widgets.SliderFloat(XorStr("Distance glow commons"), &g_var.distanceGlowCommons, 600, 3000);
    widgets.ColorEdit(XorStr("Glow commons"), g_var.colorGlowCommons);

}
void GlowHackTankRockColumnTwo() {
    widgets.Checkbox(XorStr("Enabled glow tank rock"), &g_var.enabledGlowTankRock);
    widgets.SliderFloat(XorStr("Distance glow tank rock"), &g_var.distanceGlowTankRock, 600, 5000);
    widgets.ColorEdit(XorStr("Glow tank rock"), g_var.colorGlowTankRock);

}
void GlowOtherSettigns() {
    widgets.Checkbox(XorStr("Glow boomer vomit states"), &g_var.enabledGlowStateBoomer);
    ImGui::SetItemTooltip((LangManager::get().translate("Changes the color state of the glow depending\non whether it was vomited by a boomer or a vomit jar.")));

}
#pragma endregion
//CHAMS
#pragma region CHAMS
// CHAMS PLAYERS
void ChamsColumOne() {
    widgets.Checkbox(XorStr("Enabled chams"), &g_var.enabledChamsGlobal);
    widgets.Combo(XorStr("Config select"), &g_var.selectChamsTargets, { XorStr("Survivors"), XorStr("Infecteds") });
    widgets.MultiCombo(XorStr("Target targets"), g_var.playersMaterialsIgnore, { XorStr("Survivors"), XorStr("Infecteds") });

}
void ChamsColumTwo() {
    widgets.Checkbox(XorStr("Enable players chams"), &g_var.playersChams);
    widgets.Combo(XorStr("Materials players"), &g_var.playerSelectMat, { XorStr("Original"), XorStr("Glow"), XorStr("Wireframe") });
    widgets.Checkbox(XorStr("Disable depth"), &g_var.playersNoDeph);

    // widgets.SliderFloat("Players alpha", &g_var.Materials_Players_Alpha, 0, 1);


}
void ChamsColumTwoSurvivors() {
    widgets.Combo(XorStr("Type chams players"), &g_var.selectChamsTypeSurvivors, { XorStr("Custom"), XorStr("Health") });

    if (g_var.selectChamsTypeSurvivors == 0) {
        widgets.ColorEdit(XorStr("Team chams color"), g_var.colorChamsSurvivor);
    }
    else if (g_var.selectChamsTypeSurvivors == 1) {
        ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), XorStr("Chams colors by health status"));
        widgets.ColorEdit(XorStr("Critical health color"), g_var.colorChamsCriticoRojoSurvivor);
        widgets.ColorEdit(XorStr("Medium health color"), g_var.colorChamsMedioSurvivor);
        widgets.ColorEdit(XorStr("Good health color"), g_var.colorChamsBuenoSurvivor);
    }

}
void ChamsColumTwoInfecteds() {
    widgets.ColorEdit(XorStr("Special infected chams color"), g_var.colorChamsInfected);
    widgets.ColorEdit(XorStr("Ghost chams color"), g_var.colorChamsGhost);

}
// CHAMS ITEMS
void ChamsItemsColumOne() {
    widgets.Checkbox(XorStr("Enable chams on items"), &g_var.Materials_World_Active);
    widgets.Combo(XorStr("Materials items"), &g_var.matItemsSelectMat, { XorStr("Original"), XorStr("Glow"), XorStr("Wireframe") });
    widgets.Checkbox(XorStr("Disable depth items"), &g_var.Materials_World_No_Depth);
    widgets.SliderFloat(XorStr("Items alpha"), &g_var.Materials_World_Alpha, 0, 1);
    widgets.SliderFloat(XorStr("Chams items distance"), &g_var.distanceChamsItems, 600, 3000);
    widgets.MultiCombo(XorStr("Chams items targets"), g_var.targetWeaponsChams, { XorStr("Weapons"), XorStr("Medications"), XorStr("Melee"), XorStr("Grenades"), XorStr("Others") });

}
void ChamsItemsColumTwo() {
    widgets.ColorEdit(XorStr("Chams weapons"), g_var.colorWeaponsChams);
    widgets.ColorEdit(XorStr("Chams medications"), g_var.colorMedicationsChams);
    widgets.ColorEdit(XorStr("Chams grenades"), g_var.colorGrenadesChams);
    widgets.ColorEdit(XorStr("Chams ammunition"), g_var.colorAmmunitionChams);
    widgets.ColorEdit(XorStr("Chams melee"), g_var.colorMeleeChams);


}
// CHAMS OTHERS
void ChamsOthersColumOne() {
    widgets.Checkbox(XorStr("Enable witch chams"), &g_var.bChamsWitch);
    widgets.Combo(XorStr("Materials witch"), &g_var.matWitchSelectMat, { XorStr("Original"), XorStr("Glow"), XorStr("Wireframe") });
    widgets.Checkbox(XorStr("Disable witch depth"), &g_var.Materials_Witch_No_Depth);
    widgets.SliderFloat(XorStr("Witch alpha"), &g_var.Materials_Witch_Alpha, 0, 1);
    widgets.SliderFloat(XorStr("Witch chams distance"), &g_var.distanceChamsWitch, 600, 3000);
    widgets.ColorEdit(XorStr("Witch chams color"), g_var.colorChamsWitch);

}
void ChamsOthersColumTwo() {

    widgets.Checkbox(XorStr("Enable commons chams"), &g_var.bChamsCommons);
    widgets.Combo(XorStr("Materials commons"), &g_var.matCommonSelectMat, { XorStr("Original"), XorStr("Glow"), XorStr("Wireframe") });
    widgets.Checkbox(XorStr("Disable commons depth"), &g_var.Materials_Common_No_Depth);
    widgets.SliderFloat(XorStr("Commons alpha"), &g_var.Materials_Common_Alpha, 0, 1);
    widgets.SliderFloat(XorStr("Commons chams distance"), &g_var.distanceChamsCommons, 600, 3000);
    widgets.ColorEdit(XorStr("Commons chams color"), g_var.colorChamsCommons);


}
void ChamsOthersColumTree() {

    widgets.Checkbox(XorStr("Enable tank rock chams"), &g_var.bChamsTankRock);
    widgets.Combo(XorStr("Materials tank rock"), &g_var.matTankRockSelectMat, { XorStr("Original"), XorStr("Glow"), XorStr("Wireframe") });
    widgets.Checkbox(XorStr("Disable tank rock depth"), &g_var.Materials_TankRock_No_Depth);
    widgets.SliderFloat(XorStr("Tank rock alpha"), &g_var.Materials_TankRock_Alpha, 0, 1);
    widgets.SliderFloat(XorStr("Tank rock chams distance"), &g_var.distanceChamsTankRock, 600, 3000);
    widgets.ColorEdit(XorStr("Tank rock chams color"), g_var.colorChamsTankRock);

}

void ChamsOtherSettigns() {
    widgets.Checkbox(XorStr("Chams boomer vomit states"), &g_var.enabledChamsStateBoomer);
    ImGui::SetItemTooltip((LangManager::get().translate("Changes the color state of the chams depending\non whether it was vomited by a boomer or a vomit jar.")));

}
#pragma endregion
//EXPLOITS
#pragma region MISC
// Exploits simples
void ExploitsColumnOne() {
    widgets.Checkbox(XorStr("Bunnyhop"), &g_var.Misc_Bunnyhop);

    widgets.Combo(XorStr("Bunnyhop mode"), &g_var.MethodBuny, { XorStr("Classic"), XorStr("Directional strafe"), XorStr("Mouse") });
    TextDisabled((LangManager::get().translate("Auto Movement for Beginners")));

    widgets.Checkbox(XorStr("Auto strafe"), &g_var.Misc_Auto_Strafe);
    widgets.SliderFloat(XorStr("Auto strafe turn scale"), &g_var.Misc_Auto_Strafe_Turn_Scale, 0, 1);


}
void ExploitsColumnTwo() {
    widgets.Checkbox(XorStr("Anti fall damage"), &g_var.falldamage, &g_var.keyfall);
    widgets.Checkbox(XorStr("Interpolation"), &g_var.Misc_Accuracy_Improvements);

    widgets.Checkbox(XorStr("Ping reducer"), &g_var.Misc_Ping_Reducer);
    ImGui::SetItemTooltip((LangManager::get().translate("Do not use exploits as they may conflict\nwith the ping reducer.\nUse it only if you plan to play legit :)")));

    widgets.Checkbox(XorStr("Anti AFK"), &g_var.bAntiAfk);
    widgets.Checkbox(XorStr("No push"), &g_var.Misc_No_Push);
    widgets.Checkbox(XorStr("SvPure Bypass"), &g_var.Misc_Pure_Bypass);
    widgets.Checkbox(XorStr("Streamer mode"), &g_var.modeStream);// xd

    widgets.Checkbox(XorStr("Fast animation"), &g_var.curacionRapid, 0, nullptr, [&]() {
        widgets.SliderInt(XorStr("Fast animation speed"), &g_var.crurapid, 1, 60, "%d°");
        });
    ImGui::SetItemTooltip((LangManager::get().translate("Reduces the time of healing, revive, and similar animations.\nIdeal for survivors in critical situations.")));
   // widgets.Checkbox(XorStr("Auto ceiling"), &g_var.bAutoCelling, &g_var.keyCell);
   // widgets.Checkbox(XorStr("Free camera"), &g_var.bFreeCamActive, 0, nullptr, [&]() {
    //    widgets.Binder(XorStr("Key camera"), &g_var.keyFreeCamera);
     //   widgets.SliderFloat(XorStr("Camera speed"), &g_var.camVelocity, 10, 50);
     //   });
    ImGui::SetItemTooltip((LangManager::get().translate("Enables a free camera mode, allowing you\nto move and look around freely.\nIdeal for spectating or exploring\nthe map without restrictions.")));


}
void ExploitsColumnTree() {

    widgets.Checkbox(XorStr("Speed hack"), &g_var.speedhack, &g_var.keyspeed);
    widgets.SliderInt(XorStr("Speed hack factor"), &g_var.speedfactor, 0, 100, "%d°");
    widgets.Checkbox(XorStr("Lag exploit"), &g_var.lagExploit, &g_var.keyLagExploit);
    ImGui::SetItemTooltip((LangManager::get().translate("Used when infected to respawn in\nfront of survivors while in ghost mode.")));

    widgets.SliderInt(XorStr("Factor Lag exploit"), &g_var.factorLagExploit, 0, 999, "%d°");
    widgets.Checkbox(XorStr("Lag exploit v2"), &g_var.lagExploitv2, &g_var.keyLagExploitv2);
    widgets.SliderInt(XorStr("Factor Lag exploit v2"), &g_var.factorLagExploitv2, 0, 999, "%d°");
    widgets.Checkbox(XorStr("Sprint"), &g_var.sprint, &g_var.keysprint);



}
void ExploitsColumnFour() {
    widgets.Checkbox(XorStr("Airstuck"), &g_var.airstuck, &g_var.keyairstuck);
    widgets.Checkbox(XorStr("Teleport key"), &g_var.teleport, &g_var.keyTeleport);
    widgets.Checkbox(XorStr("Anti Jockey"), &g_var.bAntiJockey);
    widgets.Checkbox(XorStr("Anti Smoker"), &g_var.bAntiSmoker);
    widgets.Checkbox(XorStr("Teleport Charger"), &g_var.bATeleportCharger);
    widgets.Checkbox(XorStr("Charger turn"), &g_var.bChargerTurn);
    widgets.Checkbox(XorStr("Tank combo"), &g_var.tankCombo, &g_var.Misc_Tank_Combo_Key);
    ImGui::SetItemTooltip((LangManager::get().translate("This is a combination of the\nTank's rock and punch attack.")));

}
// Exploits de daño
void ExploitsDamageColumnOne() {
    widgets.Checkbox(XorStr("Damage with a smoker"), &g_var.damageExcesive, &g_var.keydamageExcesive);
    ImGui::SetItemTooltip((LangManager::get().translate("Works only with Smoker and Charger.\nWith Smoker, deals damage with the tongue drag.\nWith Charger, deals damage while charging.")));

    ImGui::Separator();
    if (ImGui::TreeNode(XorStr("Attack Tick Settings"))) {
        ImGui::Unindent(2.0f);
        widgets.SliderInt(XorStr("Lag Exploit Factor"), &g_var.factorLagExploitDamage, 0, 500, "%d°");
        widgets.SliderInt(XorStr("Speed Factor"), &g_var.factorSpeedDamge, 1, 200, "%d°");
        ImGui::TreePop();
    }


}
void ExploitsDamageColumnTwo() {
    widgets.Checkbox(XorStr("One Shot"), &g_var.oneShot);
    widgets.Binder(XorStr("Lag One Shot Key"), &g_var.keyoneShotLag);
    widgets.Binder(XorStr("Speed One Shot Key"), &g_var.keyoneShotSpeed);

    ImGui::Separator();

    if (ImGui::TreeNode(XorStr("One Shot Tick Settings"))) {
        ImGui::Unindent(2.0f);
        widgets.SliderInt(XorStr("Lag Exploit One Shot"), &g_var.factorLagExploitOneShot, 1, 500, "%d°");
        widgets.SliderInt(XorStr("Speed Factor One Shot"), &g_var.factorSpeedHackOneShot, 1, 200, "%d°");
        ImGui::TreePop();
    }

}
void ExploitsDamageColumnTree() {
    widgets.Checkbox(XorStr("Excessive damage"), &g_var.speedOneShot, &g_var.keySpeedOneShot);
    ImGui::SetItemTooltip((LangManager::get().translate("Press the assigned key first, then M1 or M2 to deal all types of damage,\nespecially M2 or M1 as infected, and M1 as survivor.")));

    widgets.Combo(XorStr("Damage method"), &g_var.MethodDamage, { XorStr("Method 1"), XorStr("Rapid fire") });
    if (g_var.MethodDamage == 0) {
        widgets.SliderInt(XorStr("Extreme tick factor"), &g_var.FactorSpeedOneShot, 1, 200, "%d°");
    }
    else if (g_var.MethodDamage == 1) {
        widgets.SliderInt(XorStr("Extreme speed factor."), &g_var.FactorSpeedExtrme, 1, 500, "%d°");
        // widgets.SliderInt(XorStr("Extreme speed factor v2."), &g_var.forced_choke_value, 1, 200, "%d°");
    }


}
void ExploitsDamageColumnFour() {
    widgets.Checkbox(XorStr("Infinite spit and boomer"), &g_var.bSpitInfinito, &g_var.keySpitInfinito);
    ImGui::SetItemTooltip((LangManager::get().translate("Press the assigned key and spam M1.")));

    widgets.Checkbox(XorStr("Hunter damage"), &g_var.bHunterDamage, &g_var.keyHunterDamage);
    ImGui::SetItemTooltip((LangManager::get().translate("Just grab the target with the Hunter and\npress the damage key while holding it.")));

    widgets.Checkbox(XorStr("Jockey damage"), &g_var.bJockeyDamage, &g_var.keyJockeyDamage);
    ImGui::SetItemTooltip((LangManager::get().translate("You can deal damage with M1 or M2,\nbut always hold the key.\nBe careful when you die, as it can cause a\nbug preventing you from respawning.")));

}
void ExploitsDamageColumnFive() {
    widgets.Checkbox(XorStr("Storm's crosshairs"), &g_var.customCrosshairStorm);

}
// Consola
void ConsoleColumOne() {


}
void ConsoleColumTwo() {
    widgets.Checkbox(XorStr("Name stealer"), &g_var.enabledAntikick);
    widgets.Combo(XorStr("Mode"), &g_var.modeAntiKick, { XorStr("None"), XorStr("All"), XorStr("Enemies"), XorStr("Team") });

}
void ConsoleColumTree() {
    static std::vector<std::string> g_NameList;
    static int selectedName = 0;
    widgets.Combo(XorStr("Target team"), &g_var.modeRobName, { XorStr("None"), XorStr("All"), XorStr("Enemies"), XorStr("Team") });
    ImVec4 deleteColorsss = ImVec4(15.0f / 255.0f, 39.0f / 255.0f, 54.0f / 255.0f, 1.0f); // #0F2736
    ImGui::PushStyleColor(ImGuiCol_Button, deleteColorsss);       
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, deleteColorsss); 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, deleteColorsss);  
    if (widgets.Button(XorStr("Collect Names"), ImVec2(235, 30)))
    {
       // F::NameStelar->CollectNames(g_NameList);
        selectedName = 0;

        if (!g_NameList.empty())
        {
            strncpy(g_var.changeNameRapid, g_NameList[0].c_str(), sizeof(g_var.changeNameRapid) - 1);
            g_var.changeNameRapid[sizeof(g_var.changeNameRapid) - 1] = '\0';
        }
    }
    ImGui::PopStyleColor(3); 

    if (!g_NameList.empty())
    {
        ImGui::Text(XorStr("Available Names:"));
        if (ImGui::BeginListBox("##NameList", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int i = 0; i < g_NameList.size(); ++i)
            {
                const bool is_selected = (selectedName == i);
                if (ImGui::Selectable(g_NameList[i].c_str(), is_selected))
                {
                    selectedName = i;
                    strncpy(g_var.changeNameRapid, g_NameList[i].c_str(), sizeof(g_var.changeNameRapid) - 1);
                    g_var.changeNameRapid[sizeof(g_var.changeNameRapid) - 1] = '\0';
                }

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
    }

    widgets.TextField("##name", g_var.changeNameRapid, sizeof(g_var.changeNameRapid), { GetWindowWidth() + 20 - GetFrameHeight() - 10, GetFrameHeight() }, "New Name.......",NULL);
    ImVec4 deleteColorss = ImVec4(15.0f / 255.0f, 39.0f / 255.0f, 54.0f / 255.0f, 1.0f); // #0F2736
    ImGui::PushStyleColor(ImGuiCol_Button, deleteColorss);      
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, deleteColorss);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, deleteColorss);  
    if (widgets.Button(XorStr("Change Name"), ImVec2(235, 30)))
    {
       // F::NameStelar->StealName(g_var.changeNameRapid);
    }
    ImGui::PopStyleColor(3); 


}
void ConsoleColumFour() {
    widgets.TextField("##name", g_var.consoleFull, sizeof(g_var.consoleFull), { GetWindowWidth() + 20 - GetFrameHeight() - 10, GetFrameHeight() }, "Command Input....", NULL);
    ImVec4 deleteColors = ImVec4(15.0f / 255.0f, 39.0f / 255.0f, 54.0f / 255.0f, 1.0f); 
    ImGui::PushStyleColor(ImGuiCol_Button, deleteColors);        
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, deleteColors); 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, deleteColors);  
    if (widgets.Button(XorStr("Execute Command"), ImVec2(235, 30)))
    {
      //  F::NameStelar->ConsoleFull(g_var.consoleFull);
    }
    ImGui::PopStyleColor(3);

}

void AntiTracker()
{
    bool bLoading = I::EngineClient->IsDrawingLoadingImage();
    bool bConnected = I::EngineClient->IsConnected();

    widgets.Checkbox(XorStr("Anti-tracking (tracker)"), &g_var.bAntiTracker);
    widgets.TextField(XorStr("##NewNameSettings"), g_var.sNewNameTracker, sizeof(g_var.sNewNameTracker),
        { GetWindowWidth() + 16 - GetFrameHeight() - 10, GetFrameHeight() },
        XorStr("rz"), NULL);
    widgets.Combo(XorStr("Operation type"), &g_var.modeAntiTracker, { XorStr("Button"), XorStr("Keybind"), XorStr("Automatic") });

    if (g_var.modeAntiTracker == 0 || g_var.modeAntiTracker == 1) {
        widgets.Checkbox(XorStr("Show debug info"), &g_var.showDebugClient);
    }

    if (g_var.modeAntiTracker == 0) {
        ImVec4 buttonColor = ImVec4(15.0f / 255.0f, 39.0f / 255.0f, 54.0f / 255.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);

        if (widgets.Button(XorStr("Execute Command"), ImVec2(235, 30)))
        {
            if (bConnected && bLoading)
            {
             //   F::NameStelar->AntiTracker(g_var.sNewNameTracker);
             //   F::notifs->success("Anti-tracker", "Executed successfully!");
            }
        }
        ImGui::PopStyleColor(3);
    }
    else if (g_var.modeAntiTracker == 1) {
        widgets.Binder(XorStr("Key Bind"), &g_var.keyNameChange);
    }
}

#pragma endregion

//SPY HACK
#pragma region SPYHACK
void SpyHackColumOne() {

    widgets.Checkbox(XorStr("Enabled Spyhack"), &g_var.Visuals_Chat_Player_List_Info);
    widgets.MultiCombo(XorStr("Spy targets"), g_var.playersSpyObj, { XorStr("Survivors"), XorStr("Infecteds") });


}
void SpyHackColumTwo() {
    widgets.Checkbox(XorStr("Enabled alert"), &g_var.visualSpyNotify);
    widgets.MultiCombo(XorStr("View type"), g_var.playersNotifySpy, { XorStr("Esp"), XorStr("Glow y chams"), XorStr("Panel emergente") });

}
void SpyHackColumTree() {

}

void SpyHackHistoryColumOne() {

}
void SpyHackHistoryColumTwo() {


}


// SETTIGNS 
void FilterColumOne() {
    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), XorStr("Filters"));
    widgets.TextField("##nameFilter", g_var.searchPlayerMarked, sizeof(g_var.searchPlayerMarked), { GetWindowWidth() + 20 - GetFrameHeight() - 10, GetFrameHeight() }, "Search player marked....", NULL);

}
void MarkedManualOne() {

    ImGui::TextColored(ImVec4(26.0f / 255.0f, 138.0f / 255.0f, 241.0f / 255.0f, 1.0f), LangManager::get().translate("ID STEAM:"));

    widgets.TextField("##name", g_var.addPlayerMarked, sizeof(g_var.addPlayerMarked), { GetWindowWidth() + 20 - GetFrameHeight() - 10, GetFrameHeight() }, "7777788888999991000", NULL);
    ImGui::TextColored(ImVec4(26.0f / 255.0f, 138.0f / 255.0f, 241.0f / 255.0f, 1.0f), LangManager::get().translate("Player name:"));

    widgets.TextField("##nameMarkedManual", g_var.addPlayerName, sizeof(g_var.addPlayerName), { GetWindowWidth() + 20 - GetFrameHeight() - 10, GetFrameHeight() }, "RazeHack", NULL);
    ImGui::TextColored(ImVec4(26.0f / 255.0f, 138.0f / 255.0f, 241.0f / 255.0f, 1.0f), LangManager::get().translate("Player type:"));

 //   widgets.Checkbox(XorStr("Problematic"), &g_var.ingored);
   // widgets.Checkbox(XorStr("Cheater"), &g_var.cheater);
  //  widgets.Checkbox(XorStr("Retard legit"), &g_var.retard_legit);


    ImGui::TextColored(ImVec4(26.0f / 255.0f, 138.0f / 255.0f, 241.0f / 255.0f, 1.0f), LangManager::get().translate("Description:"));


   // ImGui::InputTextMultiline("##Description", g_var.popup_buffer, sizeof(g_var.popup_buffer), ImVec2(230, 100));
   // if (g_var.popup_buffer[0] == '\0' && !ImGui::IsItemActive())
   // {
   //     ImVec2 pos = ImGui::GetItemRectMin();
   //     ImVec2 padding = ImVec2(4, 4);
   //     ImU32 col = ImColor(150, 150, 150, 255); 
  // //     ImGui::GetWindowDrawList()->AddText(pos + padding, col, LangManager::get().translate("Is cheater..."));
   // }

    static std::string lastErrorMsg;
    static float lastSuccessTime = 0.0f;
    static bool showSuccess = false;
    ImVec4 blueDark = ImVec4(15 / 255.f, 39 / 255.f, 54 / 255.f, 1.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, blueDark);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ blueDark.x / 1.15f, blueDark.y / 1.15f, blueDark.z / 1.15f, GImGui->Style.Alpha });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ blueDark.x / 1.35f, blueDark.y / 1.35f, blueDark.z / 1.35f, GImGui->Style.Alpha });
    ImGui::PopStyleColor(3);


    if (!lastErrorMsg.empty())
    {
        ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), LangManager::get().translate("%s"), lastErrorMsg.c_str());
    }
    if (showSuccess)
    {
        if (ImGui::GetTime() - lastSuccessTime < 3.0f) {
            ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1), LangManager::get().translate(XorStr("Added to list...")));
        }
        else {
            showSuccess = false;

        }
    }
}
void ColorMarked() {
    widgets.ColorEdit(XorStr("Problematic color"), g_var.colorFriend);
    widgets.ColorEdit(XorStr("Cheater color"), g_var.colorCheater);
    widgets.ColorEdit(XorStr("Retard Legit color"), g_var.colorRetardLegit);

}

#pragma endregion
#pragma region SETTIGNS

// SETTIGNS

void SettingsKeyBids() {
    widgets.Checkbox(XorStr("Enabled aimbot"), &g_var.enabledAimbot, &g_var.keyAimbotenabled);
    widgets.Checkbox(XorStr("Enabled triggerbot"), &g_var.enabledTriggerbot, &g_var.keyTriggerbotenabled);
    widgets.Checkbox(XorStr("Enabled esp all"), &g_var.enabledEsp, &g_var.keyEspenabled);
    widgets.Checkbox(XorStr("Enabled glow all"), &g_var.enabledGlow, &g_var.keyGlowenabled);
    widgets.Checkbox(XorStr("Enabled bunnyhop"), &g_var.enabledBuny, &g_var.keyBunyenabled);
    widgets.Checkbox(XorStr("Enabled speedhack"), &g_var.enabledSpeed, &g_var.keySpeedenabled);
    widgets.Checkbox(XorStr("Disable everything"), &g_var.disabledAll, &g_var.keydisabledAll);
    widgets.Separator();
    widgets.Checkbox(XorStr("Show binds"), &g_var.panelkeybind);
}
void SettingsPanel() {
    widgets.ColorEdit(XorStr("Color menu"), g_var.color);
    widgets.SliderFloat(XorStr("DPI Scale"), &g_var.dpi_scale, 1.0f, 2.0f);
    widgets.Checkbox(XorStr("Hide notifications"), &g_var.showNotify);
    widgets.Checkbox(XorStr("Hide watermark"), &g_var.showtoolbar);
    widgets.Binder(XorStr("Show menu key"), &g_var.keyShowMenu);
    widgets.Separator();
    /*  
    widgets.TextField(XorStr("##Name panel"), g_var.NameMenu, sizeof(g_var.NameMenu),
        { GetWindowWidth() + 16 - GetFrameHeight() - 10, GetFrameHeight() },
        XorStr("RAZE"), NULL);

    widgets.TextField(XorStr("##Name panelSecun"), g_var.NameMenuTwo, sizeof(g_var.NameMenuTwo),
        { GetWindowWidth() + 16 - GetFrameHeight() - 10, GetFrameHeight() },
        XorStr("HACK"), NULL);
        */

}
void FontSize() {
    if (widgets.SliderInt("Font size all", &g_var.FontSizeGlobal, 15, 30, "%d°")) {

    }

}

#pragma endregion

static int cfg = 0;
#pragma region CONFIG  / ABAUT

void ConfigColumnOne() {
   
}
void ConfigColumnTwo() {

    const char* configName = g_var.SelectedConfig;
    if (strlen(configName) == 0)
        configName = "None";

    TextDisabled(LangManager::get().translate(XorStr("Name:")));
    SameLine(GetWindowWidth() - CalcTextSize(configName).x - GImGui->Style.WindowPadding.x);
    Text(configName);

    TextDisabled(LangManager::get().translate(XorStr("Created:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("12.09.2025")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("12.09.2025"));

    TextDisabled(LangManager::get().translate(XorStr("Created by:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("RazeHack")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("RazeHack"));


    widgets.Separator();

    ImVec4 customColor = ImVec4(0.082f, 0.113f, 0.870f, 1.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, customColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, customColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, customColor);

    if (widgets.Button(XorStr("Load"))) {
      
    }

    ImGui::PopStyleColor(3);
    if (strlen(g_var.SelectedConfig) > 0) { 
        if (edited::ButtonExv3(LangManager::get().translate("Delete"), ImVec2(240, 0), ImGuiButtonFlags_None, "delete", true, LangManager::get().translate("Do you really want to\ndelete this config?")))
        {
           
        }
    }


}


void About() {
    TextDisabled(LangManager::get().translate(XorStr("Released:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("08.09.2025")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("06.09.2025"));
    TextDisabled(LangManager::get().translate(XorStr("Developers:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("noex,alan02,Elvis,\nCristian Q²")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("noex,alan02,Elvis,\nCristian Q²"));
    TextDisabled(LangManager::get().translate(XorStr("Game:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("Left 4 Dead 2")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("Left 4 Dead 2"));
    TextDisabled(LangManager::get().translate(XorStr("Version:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("1.0.4")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("1.0.4"));
    TextDisabled(LangManager::get().translate(XorStr("Testers:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("BlaxFly,Agente 308,BloodyBaby47")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("BlaxFly,Agente 308,BloodyBaby47"));
    widgets.Separator();
    TextDisabled(LangManager::get().translate(XorStr("Posted on:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("unknowncheats.me")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("unknowncheats.me"));
}
void AboutTwo() {
    TextDisabled(LangManager::get().translate(XorStr("Build type:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("Internal")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("Internal"));

    TextDisabled(LangManager::get().translate(XorStr("Status:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("Undetected")).x - GImGui->Style.WindowPadding.x);
    Text(LangManager::get().translate(XorStr("Undetected")));

    TextDisabled(LangManager::get().translate(XorStr("Base SDK:")));
    SameLine(GetWindowWidth() - CalcTextSize(XorStr("Polonium by Lak3")).x - GImGui->Style.WindowPadding.x);
    Text(XorStr("Polonium by Lak3"));

    widgets.Separator();

    TextDisabled(LangManager::get().translate(XorStr("Note:")));
    TextWrapped(LangManager::get().translate(XorStr("With this free cheat, you have full access to all its features. Have fun, explore, and discover everything it has to offer at no cost.")));

}
#pragma endregion

#pragma region Crosshair
void Cross() {
    ImGui::BeginChild("crosshair_left", ImVec2(296, 0), false, ImGuiWindowFlags_NoBackground);
    {
        for (int i = 0; i < 24; i++)
        {
            if (i % 4 != 0)
                ImGui::SameLine();

            if (edited::e_crosshair(i, i == g_var.selected_crosshair, i))
                g_var.selected_crosshair = i;
        }
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("crosshair_right", ImVec2(290, 0), false, ImGuiWindowFlags_NoBackground);
    {
        ImVec2 preview_size = ImVec2(230, 370);
        ImVec2 preview_pos = GetCurrentWindow()->DC.CursorPos;

        auto anim_prev = anims::animation("preview_anim", anim_t(clamp_out, 0.15f));
        anim_prev->active = true;

        edited::lb_bg(preview_pos, preview_size, anim_prev->val, 8.f);

        edited::draw_crosshair_preview(g_var.selected_crosshair, anim_prev->val);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);

        ImGui::Indent(20.f);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(50, 12));
        BeginGroup();
        {
            widgets.Checkbox("Enable custom aiming", &g_var.customCrosshair);
            widgets.ColorEdit("Color", g_var.colorCrosshair);
            widgets.SliderFloat("Thickness", &g_var.crosshairTicknes, 1, 5);
            widgets.SliderInt("Size", &g_var.crossSize, 5, 50, "%d°");
        }
        EndGroup();
        ImGui::PopStyleVar();

        ImGui::Unindent(20.f);

    }
    ImGui::EndChild();
}
#pragma endregion
#pragma endregion

void CMenu::Render(IDirect3DDevice9* pDevice) {
    static bool bInitImGui = false;
    static bool bColumnsWidthened = false;
    bool modified_custom_style = false;
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
    pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    static LPDIRECT3DTEXTURE9 lg = nullptr;
    if (!bInitImGui) {
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(FindWindowW(_(L"Valve001"), 0));
        ImGui_ImplDX9_Init(pDevice);

        auto& io = ImGui::GetIO();
        io.IniFilename = NULL;
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavEnableKeyboard;
        ImFontConfig font_config;
        font_config.OversampleH = 1;
        font_config.OversampleV = 1;
        font_config.PixelSnapH = 1;
        ImVector<ImWchar> ranges;
        ImFontGlyphRangesBuilder builder;
        builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
        builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());
        builder.AddRanges(io.Fonts->GetGlyphRangesChineseFull());
        builder.BuildRanges(&ranges);
        char systemPath[MAX_PATH];
        GetWindowsDirectoryA(systemPath, MAX_PATH);
        std::string fontPath = std::string(systemPath) + "\\Fonts\\msyhbd.ttc";

        ImFont* fontGlobal = io.Fonts->AddFontFromFileTTF(
            fontPath.c_str(),
            16.0f,
            &font_config,
            ranges.Data
        );

        if (!fontGlobal) {
            MessageBoxA(0, "Failed to load global font!", "Font Error", MB_OK | MB_ICONERROR);
        }
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;

        io.Fonts->AddFontFromMemoryCompressedTTF(
            FA_compressed_data,
            FA_compressed_size,
            16.0f,
            &icons_config,
            icons_ranges
        );
        font::Nev = io.Fonts->AddFontFromMemoryTTF(
            &nev,
            sizeof(nev),
            35.0f,
            nullptr,
            io.Fonts->GetGlyphRangesCyrillic()
        );
      
        io.Fonts->Build();

        bInitImGui = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        I::VGuiSurface->SetCursorAlwaysVisible(menuOpen = !menuOpen);
        g_Menu.flTimeOnChange = I::EngineClient->GetTimescale();
    }

    g_Menu.m_flFadeElapsed = I::EngineClient->GetTimescale() - g_Menu.flTimeOnChange;

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    ImGui::GetIO().MouseDrawCursor = menuOpen;
    if (menuOpen)
    {
        StyleManager::get().Styles();
        StyleManager::get().Colors();
        c::accent = { g_var.color[0], g_var.color[1], g_var.color[2], 1.f };

        ImGui::SetNextWindowSize(ImVec2(750, 540));
        ImGui::Begin(XorStr("Left 4 Dead 2"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);
        {
#pragma region a
            ImGuiStyle* style = &ImGui::GetStyle();
            const ImVec2& pos = ImGui::GetWindowPos();
            const auto& pp = ImGui::GetWindowPos();
            anim_speed = ImGui::GetIO().DeltaTime * 8.f;
            const ImVec2& region = ImGui::GetContentRegionMax();
            const ImVec2& spacing = style->ItemSpacing;
            auto ds = ImGui::GetWindowDrawList();
            auto p = ImGui::GetWindowPos();

            const int vtx_idx_1 = ds->VtxBuffer.Size;
            ds->AddRect(pos,
                ImVec2(pos.x + region.x, pos.y + region.y),
                ImGui::GetColorU32(c::background::background),
                c::background::rounding,
                ImDrawFlags_None,
                3.f
            );

            ImGui::ShadeVertsLinearColorGradientKeepAlpha(
                ds,
                vtx_idx_1,
                ds->VtxBuffer.Size,
                pos,
                ImVec2(pos.x + region.x / 2, pos.y + region.y / 2),
                ImGui::GetColorU32(c::accent),
                ImColor(24, 24, 24, 0));

            float alpha_line = 0.0f;
            float tab_width = 80.0f;
            float max_text_width = 45.0f;
            float max_text_widthTwo = 55.0f;
            float tab_widthTwo = 150.0f;


            const char* panel_name ="Raze";
            ImVec2 text_size = ImGui::CalcTextSize(panel_name);

            float base_font_size = 25.0f;
            float font_size = base_font_size;

            if (text_size.x > max_text_width) {
                font_size *= max_text_width / text_size.x;
            }

            text_size = ImGui::CalcTextSize(panel_name) * (font_size / base_font_size);
            ImVec2 pos_name = ImVec2(p.x + ((tab_width - text_size.x) * 0.5f), p.y + 18);

            ImGui::GetForegroundDrawList()->AddText(font::Nev, font_size, pos_name,
                ImColor(g_var.color[0], g_var.color[1], g_var.color[2]), panel_name);

            const char* panel_name_two = "HACK";
            ImVec2 text_size_two = ImGui::CalcTextSize(panel_name_two);

            float base_font_size_two = 15.0f;
            float font_size_two = base_font_size_two;

            if (text_size_two.x > max_text_widthTwo) {
                font_size_two *= max_text_widthTwo / text_size_two.x;
            }

            text_size_two = ImGui::CalcTextSize(panel_name_two) * (font_size_two / base_font_size_two);
            ImVec2 pos_name_two = ImVec2(p.x + ((tab_widthTwo - text_size_two.x) * 0.5f), p.y + 50);

            ImGui::GetForegroundDrawList()->AddText(font::Nev, font_size_two, pos_name_two,
                ImColor(g_var.color[0], g_var.color[1], g_var.color[2]), panel_name_two);

            ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x + 30, p.y + 80), ImVec2(p.x + 91, p.y + 79), ImGui::GetColorU322(c::accent, alpha_line), ImGui::GetColorU32(c::accent), ImGui::GetColorU32(c::accent), ImGui::GetColorU322(c::accent, alpha_line));
            ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x + 91, p.y + 80), ImVec2(p.x + 170, p.y + 79), ImGui::GetColorU32(c::accent), ImGui::GetColorU322(c::accent, alpha_line), ImGui::GetColorU322(c::accent, alpha_line), ImGui::GetColorU32(c::accent));

#pragma endregion 


            BeginChild("navbar", { 180, 0 }, 0, ImGuiWindowFlags_NoBackground);
            {
                WidgetsManager::get().Separator();
                SetCursorPosX(14);
                SetCursorPosY(100);

                TabsManager::get().render_tabs(8);

                GetWindowDrawList()->AddRectFilled(GetWindowPos() + ImVec2{ GetWindowWidth() - 1, 0 }, GetWindowPos() + GetWindowSize(), GetColorU32(ImGuiCol_Border));

                SetCursorPos({ 14, GetWindowHeight() - 38 });
                CompBuilder::get().OpenButton(
                    "lang selector",
                    { 32 + ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1, LangManager::get().get_lang_name()).x, 24 },
                    [&](CompBuilder::OpenButtonEnv env)


                    {
                        GetWindowDrawList()->AddRectFilled(env.bb.Min, env.bb.Max, GetColorU32(ImGuiCol_ChildBg), GImGui->Style.FrameRounding);
                        GetWindowDrawList()->AddText(
                            ImGui::GetFont(),
                            ImGui::GetFontSize(),
                            { env.bb.Min.x + 6, env.bb.GetCenter().y - 8 },
                            GetColorU32(ImGuiCol_Scheme),
                            ICON_FA_EARTH_AMERICAS
                        );

                        GetWindowDrawList()->AddText(
                            ImGui::GetFont(),
                            ImGui::GetFontSize(),
                            { env.bb.Min.x + 26, env.bb.GetCenter().y - 8 },
                            GetColorU32(ImGuiCol_Text),
                            LangManager::get().get_lang_name()
                        );

                        if (env.pressed) {
                            env.open = !env.open;
                        }

                        if (env.hovered) env.open = true;

                        if (env.anim.open > 0.05f) {
                            PushStyleVar(ImGuiStyleVar_Alpha, env.anim.open);
                            PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
                            PushStyleVar(ImGuiStyleVar_WindowRounding, GImGui->Style.FrameRounding);
                            PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 8 });
                            PushStyleVar(ImGuiStyleVar_FramePadding, { 10, 8 });
                            PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
                            PushStyleColor(ImGuiCol_WindowBg, GetColorU32(ImGuiCol_FrameBg));
                            Begin("lang selector", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
                            {
                                SetWindowPos({ env.bb.Min.x, env.bb.GetCenter().y - GetWindowHeight() / 2 });
                                SetWindowSize({ 100, (GetCurrentWindow()->ContentSize.y + GImGui->Style.WindowPadding.y * 2) * env.anim.open });

                                BringWindowToDisplayFront(GetCurrentWindow());
                                BringWindowToFocusFront(GetCurrentWindow());

                                if (!IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) && !env.hovered) {
                                    env.open = false;
                                }

                                PushStyleColor(ImGuiCol_FrameBg, GetColorU32(ImGuiCol_FrameBgHovered));

                                auto& langs = LangManager::get().get_langs();
                                for (int i = 0; i < langs.size(); ++i) {
                                    std::string label = std::string(langs[i].label) + "##lang" + std::to_string(i);
                                    bool selected = g_var.selected_language == i;

                                    if (WidgetsManager::get().Selectable(label.c_str(), selected)) {
                                        g_var.selected_language = i;
                                        LangManager::get().set_lang(i);
                                    }
                                }




                                PopStyleColor();
                            }
                            End();
                            PopStyleColor();
                            PopStyleVar(6);
                        }
                    });
            }
            EndChild();

            SameLine(0, 0);

            BeginChild("main", { 0, 0 }, 0,
                ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse);
            {
                ChildManager::get().smoothscroll();

                float paddingRight = 10.0f;
                const float searchWidth = 0.0f;

                float searchWidthAdjusted = searchWidth - paddingRight;

                if (BeginTable("main_header", 2,
                    ImGuiTableFlags_SizingStretchProp |
                    ImGuiTableFlags_NoPadInnerX |
                    ImGuiTableFlags_NoBordersInBody))
                {
                    TableSetupColumn("left", ImGuiTableColumnFlags_WidthStretch);
                    TableSetupColumn("right", ImGuiTableColumnFlags_WidthFixed, searchWidth);
                    TableNextRow();
                    TableSetColumnIndex(0);
                    TabsManager::get().render_subtabs(20);

                    TableSetColumnIndex(1);
                    {
                        ImVec2 cur = GetCursorPos();
                        SetCursorPosY(cur.y + (GetFrameHeight() - GetFontSize()) * 0.5f - 2.0f);

                        PushStyleColor(ImGuiCol_FrameBg, GetColorU32(ImGuiCol_FrameBg, 0.f));
                        PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
                        PushItemFlag(ImGuiItemFlags_NoNav, true);
                        PopItemFlag();
                        PopStyleVar();
                        PopStyleColor();
                    }

                    EndTable();
                }


                    auto window = GetCurrentWindow();
                    PushStyleVar(ImGuiStyleVar_Alpha,
                        GImGui->Style.Alpha * TabsManager::get().get_anim() * GImGui->Style.Alpha);

                    PushStyleVar(ImGuiStyleVar_WindowPadding, { 14, 5 });
                    BeginChild("content", { 0, 480 }, ImGuiChildFlags_AlwaysUseWindowPadding,
                        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse);
                    {
                        TabsManager::get().draw_page(window);
                    }
                    EndChild();
                    PopStyleVar(2);
                

            }
            EndChild();

            PopupManager::get().handle();

#pragma region SECCION_AIMS 

            TabsManager::get().add_page(0, [&]() {
                BeginGroup();
                {
                    cm.beginchild("General");
                    {
                        AimbotColumOne();
                    }
                    cm.endchild();

                }
                EndGroup();

                SameLine();

                BeginGroup();
                {
                    cm.beginchild("Aim settings");
                    {
                        AimbotColumTwo();
                    }
                    cm.endchild();

                    cm.beginchild("Scanning");
                    {
                        AimbotColumTwoGroup();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            TabsManager::get().add_page(0, [&]() {
                BeginGroup();
                {
                    cm.beginchild("General");
                    {
                        TriggerbotColumOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Tracking settings");
                    {
                        TriggerbotColumTwo();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            TabsManager::get().add_page(0, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Rapid fire options");
                    {
                        OtherAimsColumnOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Recoil control system");
                    {
                        OtherAimsColumnTwo();
                    }
                    cm.endchild();
                }
                EndGroup();

                });










#pragma endregion

#pragma region SECCION_ESP
            // esp players
            TabsManager::get().add_page(1, [&]() {
                BeginGroup();
                {
                    cm.beginchild("General");
                    {
                        EspPlayersColumnOne();
                    }
                    cm.endchild();
                    const char* child_titleConfig = nullptr;

                    if (g_var.selectEsp == 0) {
                        child_titleConfig = "Settings - Survivors";
                    }
                    else if (g_var.selectEsp == 1) {
                        child_titleConfig = "Settings - Infecteds";
                    }
                    else {
                        child_titleConfig = "ESP Config";
                    }
                    cm.beginchild(child_titleConfig);
                    {
                        EspPlayersColumnOneConfigs();
                    }
                    cm.endchild();

                }
                EndGroup();

                SameLine();

                BeginGroup();
                {
                    const char* child_title = nullptr;

                    if (g_var.selectEsp == 0) {
                        child_title = "ESP Text - Survivors";
                    }
                    else if (g_var.selectEsp == 1) {
                        child_title = "ESP Text - Infected";
                    }
                    else {
                        child_title = "ESP Config";
                    }
                    cm.beginchild(child_title);
                    {
                        EspPlayersColumnTwoConfigs();
                    }
                    cm.endchild();

                    cm.beginchild("Others esp");
                    {
                        EspPlayersColumnTwo();

                    }
                    cm.endchild();
                }
                EndGroup();

                });
            // esp items
            TabsManager::get().add_page(1, [&]() {
                BeginGroup();
                {
                    cm.beginchild("ESP Items");
                    {
                        EspItemsColumOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("ESP Item Colors");
                    {
                        EspItemsColumTwo();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            // esp others
            TabsManager::get().add_page(1, [&]() {
                BeginGroup();
                {
                    cm.beginchild("ESP - Witch");
                    {
                        EspOtherColumOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("ESP - Common Infected");
                    {
                        EspOtherColumTwo();
                    }
                    cm.endchild();
                    cm.beginchild("ESP - Tank rock");
                    {
                        EspOtherColumFour();
                    }
                    cm.endchild();

                    cm.beginchild("ESP - Entity States Color");
                    {
                        EspOtherColumTree();
                    }
                    cm.endchild();



                }
                EndGroup();

                });


#pragma endregion                  

#pragma  region SECCION_VISUALS
            // world
            TabsManager::get().add_page(2, [&]() {
                BeginGroup();
                {
                    cm.beginchild("World Visuals");
                    {
                        VisualsWorldColumOne();
                    }
                    cm.endchild();

                    cm.beginchild("Sky color and particles");
                    {
                        VisualsWorldColumOneOthers();
                    }
                    cm.endchild();

                }
                EndGroup();

                SameLine();

                BeginGroup();
                {

                    cm.beginchild("Third Person View");
                    {
                        VisualsWorldColumTwoThirPerson();
                    }
                    cm.endchild();

                    cm.beginchild("Local Model View");
                    {
                        VisualsWorldColumTwoLocalView();

                    }
                    cm.endchild();
                }
                EndGroup();

                });
            TabsManager::get().add_page(2, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Indicator Arrows");
                    {
                        VisualsArrowsColumOne();
                    }
                    cm.endchild();



                }
                EndGroup();

                SameLine();

                BeginGroup();
                {

                    cm.beginchild("Indicator Colors");
                    {
                        VisualsArrowsColumTwo();
                    }
                    cm.endchild();
                    cm.beginchild("Esp arrows survivor");
                    {
                        VisualsArrowsColumTree();
                    }
                    cm.endchild();
                    cm.beginchild("Esp arrows infected");
                    {
                        VisualsArrowsColumFour();
                    }
                    cm.endchild();

                }
                EndGroup();

                });
            TabsManager::get().add_page(2, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Radar Visuals");
                    {
                        VisualsRadarColumTwo();

                    }
                    cm.endchild();
                    cm.beginchild("Radar infecteds commons");
                    {
                        VisualsRadarCommons();

                    }
                    cm.endchild();


                }
                EndGroup();

                SameLine();

                BeginGroup();
                {
                    if (g_var.radarTarget[0]) {
                        cm.beginchild("Survivor radar color config");
                        {
                            VisualsRadarColumTree();

                        }
                        cm.endchild();
                    }
                    if (g_var.radarTarget[1]) {
                        cm.beginchild("Infected radar color config");
                        {
                            VisualsRadarColumFour();

                        }
                        cm.endchild();
                    }
                    cm.beginchild("Spectator Visuals");
                    {
                        VisualsEspectoresColumnOne();

                    }
                    cm.endchild();


                }
                EndGroup();

                });
            TabsManager::get().add_page(2, [&]() {
                BeginGroup();
                {
                    cm.beginchild("HUD Info Visuals");
                    {
                        VisualsHudInfoColumOne();
                    }
                    cm.endchild();



                }
                EndGroup();

                SameLine();

                BeginGroup();
                {

                    cm.beginchild("Name Color Settings");
                    {
                        VisualsHudInfoColumTwo();
                    }
                    cm.endchild();


                }
                EndGroup();

                });



#pragma endregion


#pragma region SECCION_GLOW
            // GLOW PLAYERS
            TabsManager::get().add_page(3, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Global Settings");
                    {
                        GlowHackColumnOne();
                    }
                    cm.endchild();



                }
                EndGroup();

                SameLine();

                BeginGroup();
                {

                    cm.beginchild("Player Glow Settings");
                    {
                        GlowHackColumnTwo();
                    }
                    cm.endchild();

                    if (g_var.selectGlowTargets == 0) {

                        cm.beginchild("Survivor Glow Configuration");
                        {
                            GlowHackColumnTwoSurvivors();
                        }
                        cm.endchild();


                    }
                    else if (g_var.selectGlowTargets == 1) {
                        cm.beginchild("Infected Glow Configuration");
                        {
                            GlowHackColumnTwoInfecteds();
                        }
                        cm.endchild();

                    }


                }
                EndGroup();

                });
            // GLOW ITEMS
            TabsManager::get().add_page(3, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Glow items");
                    {
                        GlowHackItemsColumnOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Item Glow Color Configuration");
                    {
                        GlowHackItemsColumnTwo();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            // GLOW OTHERS
            TabsManager::get().add_page(3, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Glow: Witch");
                    {
                        GlowHackOthersColumnOne();
                    }
                    cm.endchild();
                    cm.beginchild("Glow: Tank rock");
                    {
                        GlowHackTankRockColumnTwo();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Glow: Common Infected");
                    {
                        GlowHackOthersColumnTwo();
                    }
                    cm.endchild();

                    cm.beginchild("Glow: Boomer vomit state");
                    {
                        GlowOtherSettigns();
                    }
                    cm.endchild();

                }
                EndGroup();

                });


#pragma endregion


#pragma region SECCION_CHAMS
            //CHAMS PLAYERS
            TabsManager::get().add_page(4, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Global Settings");
                    {
                        ChamsColumOne();
                    }
                    cm.endchild();

                    cm.beginchild("Player Chams Settings");
                    {
                        ChamsColumTwo();
                    }
                    cm.endchild();

                }
                EndGroup();

                SameLine();

                BeginGroup();
                {

                    if (g_var.selectChamsTargets == 0) {
                        cm.beginchild("Survivor Chams Configuration");
                        {
                            ChamsColumTwoSurvivors();
                        }
                        cm.endchild();


                    }
                    else if (g_var.selectChamsTargets == 1) {
                        cm.beginchild("Infected Chams Configuration");
                        {
                            ChamsColumTwoInfecteds();
                        }
                        cm.endchild();

                    }


                }
                EndGroup();

                });
            //CHAMS ITEMS
            TabsManager::get().add_page(4, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Chams items");
                    {
                        ChamsItemsColumOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Item Chams Color Configuration");
                    {
                        ChamsItemsColumTwo();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            //CHAMS OTHERS
            TabsManager::get().add_page(4, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Chams: Witch");
                    {
                        ChamsOthersColumOne();
                    }
                    cm.endchild();
                    cm.beginchild("Chams: Tank rock");
                    {
                        ChamsOthersColumTree();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Chams: Common Infected");
                    {
                        ChamsOthersColumTwo();
                    }
                    cm.endchild();

                    cm.beginchild("Chams: Boomer vomit state");
                    {
                        ChamsOtherSettigns();
                    }
                    cm.endchild();

                }
                EndGroup();

                });



#pragma endregion

#pragma region SECCION_MISC
            //EXPLOITS SIMPLES
            TabsManager::get().add_page(5, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Movement");
                    {
                        ExploitsColumnOne();
                    }
                    cm.endchild();
                    cm.beginchild("Game");
                    {
                        ExploitsColumnTwo();
                    }
                    cm.endchild();

                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Other Exploits");
                    {
                        ExploitsColumnTree();
                    }
                    cm.endchild();
                    cm.beginchild("Others Movements Exploits");
                    {
                        ExploitsColumnFour();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            //EXPLOITS DE DAÑO
            TabsManager::get().add_page(5, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Infected Power Attack Exploits");
                    {
                        ExploitsDamageColumnOne();
                    }
                    cm.endchild();
                    cm.beginchild("Power Attack Exploits for Survivors");
                    {
                        ExploitsDamageColumnTwo();
                    }
                    cm.endchild();


                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("HvH: Extreme Damage");
                    {
                        ExploitsDamageColumnTree();
                    }
                    cm.endchild();
                    cm.beginchild("Game Breaking");
                    {
                        ExploitsDamageColumnFour();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            //CONSOLE
            TabsManager::get().add_page(5, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Chat spam | Your phrases");
                    {
                        ConsoleColumOne();
                    }
                    cm.endchild();
                    cm.beginchild("Name Stealer");
                    {
                        ConsoleColumTwo();
                    }
                    cm.endchild();



                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Rapid Name Change");
                    {
                        ConsoleColumTree();
                    }
                    cm.endchild();
                    cm.beginchild("Console");
                    {
                        ConsoleColumFour();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            TabsManager::get().add_page(5, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Anti tracker");
                    {
                        AntiTracker();
                    }
                    cm.endchild();

                }
                EndGroup();

                });


#pragma endregion


#pragma region SECCION_SPYHACK
            TabsManager::get().add_page(6, [&]() {
                BeginGroup();
                {
                    cm.beginchild("General");
                    {
                        SpyHackColumOne();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Spy-hack notify");
                    {
                        SpyHackColumTwo();
                    }
                    cm.endchild();
                }
                EndGroup();
                float totalWidth = ((c::child::sizeSpy.x - 200));
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.0f);

                cm.beginchild("Players in play", ImVec2(totalWidth,
                    c::child::sizeTabla.y));
                {

                    SpyHackColumTree();
                }
                cm.endchild();

                });
            TabsManager::get().add_page(6, [&]() {
                float totalWidth = ((c::child::sizeSpy.x - 200));

                ImGui::Text(LangManager::get().translate("History of marked players"));
                float textFieldWidth = 200.0f;
                ImGui::SameLine(totalWidth - textFieldWidth);
                widgets.TextField("##nameFilter", g_var.searchPlayerMarked, sizeof(g_var.searchPlayerMarked),
                    { textFieldWidth, GetFrameHeight() }, "Search player marked....", NULL);


                cm.beginchild("##History of marked players", ImVec2(totalWidth,
                    c::child::sizeTablay.y));
                {

                    SpyHackHistoryColumOne();
                }
                cm.endchild();



                });
            TabsManager::get().add_page(6, [&]() {
                BeginGroup();
                {
                    cm.beginchild("Colors config");
                    {
                        ColorMarked();
                    }
                    cm.endchild();

                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Mark a player manually by \nID STEAM64");
                    {
                        ImGui::Separator();

                        MarkedManualOne();
                    }
                    cm.endchild();
                }
                EndGroup();


                });


#pragma endregion

#pragma region Crosshair
            //secion crosshair 
            TabsManager::get().add_page(7, [&]() {

                Cross();

                });

#pragma endregion

#pragma region SECCION_SETTINGS
            TabsManager::get().add_page(8, [&]() {
                // Subtab "Triggerbot"
                BeginGroup();
                {
                    cm.beginchild("Keybinds");
                    {
                        SettingsKeyBids();
                    }
                    cm.endchild();
                }
                EndGroup();
                SameLine();
                BeginGroup();
                {
                    cm.beginchild("Settings Panel");
                    {
                        SettingsPanel();
                    }
                    cm.endchild();
                }
                EndGroup();

                });
            TabsManager::get().add_page(8, [&]() {
                // Subtab "Triggerbot"
                BeginGroup();
                {
                    cm.beginchild("Font size for ALL ESP");
                    {
                        FontSize();
                    }
                    cm.endchild();
                }
                EndGroup();


                });


#pragma endregion

#pragma region SECCION_About
            TabsManager::get().add_page(9, [&]() {

                BeginGroup();
                {
                    PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
                    BeginChild("configs", { GetWindowWidth() / 2 - 14 - GImGui->Style.ItemSpacing.x / 2, 0 }, ImGuiChildFlags_Border);
                    {
                        ConfigColumnOne();
                    }
                    EndChild();
                    PopStyleVar();
                }
                EndGroup();

                SameLine();

                BeginGroup();
                {
                    cm.beginchild("Your Settings");
                    {
                        ConfigColumnTwo();
                    }
                    cm.endchild();
                }
                EndGroup();
                });
            TabsManager::get().add_page(9, [&]() {

                BeginGroup();
                {
                    cm.beginchild("General");
                    {
                        About();
                    }
                    cm.endchild();

                }
                EndGroup();

                SameLine();

                BeginGroup();
                {
                    cm.beginchild("Others");
                    {
                        AboutTwo();
                    }
                    cm.endchild();
                }
                EndGroup();
                });
#pragma endregion
        }
        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
}