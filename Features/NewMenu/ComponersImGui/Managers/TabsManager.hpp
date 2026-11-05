#pragma once
#include <vector>
#include <functional>
#include "..//..//ImGui/Fonts/font_awesome_5.h"

class TabsManager {
    float anim = 1.f, subtabs_anim = 1.f;
    float anim_dest = 1.f, subtabs_anim_dest = 1.f;

    struct Tab {
        const char* icon;
        const char* label;

        std::vector< const char* > subtabs;

        std::vector< std::function< void() > > pages{ };

        int next = 0;
        int cur = 0;
    };

    std::vector< Tab > tabs{

        { ICON_FA_SKULL,"Aims", { "Aimbot", "Triggerbot","Other Aims"}}, // 0
        { ICON_FA_EYE,"Esp" ,{ "Esp players", "Esp items","Esp settings"}},// 1
        { ICON_FA_MOUNTAIN_CITY,"Visuals",{"World","Draw arrows","Radar|Spectator","HUD"}},// 2
        { ICON_FA_PAINTBRUSH,"Glow",{"Glow players","Glow items","Glow others"}},// 3
        { ICON_FA_PEOPLE_GROUP,"Chams",{"Chams players","Chams items","Chams others"}},// 4
        { ICON_FA_SHIELD_HALVED,"Exploits",{"Exploits_","Others","Console","Anti_tracker"}},// 5
        { ICON_FA_CROSSHAIRS,"Spy-Hack",{"Spy-Hack_","Marked history","Settings"}},// 6
        { ICON_FA_ANGLES_RIGHT,"Crosshair",{"Crosshair_"}},// 7
        { ICON_FA_GEARS,"Settings",{"Settings_","Font size"}},// 8 
        { ICON_FA_DATABASE,"Config / About",{"Config","About"}},// 9


    };
public:
    int current = 0, next = 0;

    bool tab(int i);
    bool subtab(int i);

    void render_tabs(float spacing, bool line = false);
    void render_subtabs(float spacing, bool line = true);
    void handle();

    void add_page(int tab, std::function< void() > code);
    void draw_page(ImGuiWindow* window);

    float& get_subtabs_anim() {
        return subtabs_anim;
    }

    float& get_tabs_anim() {
        return anim;
    }

    float get_anim() {
        return subtabs_anim * anim;
    }

    Tab& get_tab() {
        return tabs[current];
    }

    Tab& get_tab(int i) {
        return tabs[i];
    }

    static TabsManager& get() {
        static TabsManager s{ };
        return s;
    }
};
