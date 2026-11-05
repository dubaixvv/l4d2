#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include <vector>
#include <string>
#include <d3d9.h>

namespace font
{
    inline IDirect3DTexture9* nick = nullptr;
    inline IDirect3DTexture9* smoker = nullptr;
    inline IDirect3DTexture9* hunterHit = nullptr;

    inline ImFont* icomoon = nullptr;
    inline ImFont* lexend_bold = nullptr;
    inline ImFont* lexend_regular = nullptr;
    inline ImFont* lexend_general_bold = nullptr;
    // ImFont* Nev = nullptr;
    inline ImFont* icomoon_widget = nullptr;
    inline ImFont* icomoon_widget2 = nullptr;
    inline ImFont* iconInfo = nullptr;
    inline ImFont* iconsBar = nullptr;
    inline   ImFont* Nev = nullptr;


}
namespace imagess
{
    inline IDirect3DTexture9* nicks = nullptr;

}
namespace c {
    inline ImVec4 txt = ImColor(255, 255, 255, 255);

    inline ImVec2 size = ImVec2(900, 515);
    inline ImVec4 green = ImColor(49, 255, 57);
    inline ImVec4 error = ImVec4(255, 0, 0, 255); 
    inline ImVec4 warning = ImVec4(255, 255, 0, 255); 
    namespace button {
        inline ImVec4 text_actives = ImColor(255, 255, 255, 200);


        inline ImVec4 button_bg = ImColor(27, 27, 29);
        inline ImVec4 text_active = ImColor(255, 255, 255);
        inline ImVec4 text_inactive = ImColor(76, 76, 77);
    }
    namespace bg
    {

        inline ImVec4 background = ImColor(14, 14, 15, 255);
        inline ImVec4 outline_background = ImColor(27, 29, 32, 255);
        inline ImVec2 size = ImVec2(100, 525);
        inline ImVec2 sizesbg = ImVec2(905, 640);
        inline float rounding = 12;
    }
    inline  float border;
    inline  float grosor;
    inline  float borders;
    inline  float grosors;
    inline ImColor text_activite(255, 0, 0, 255);

    inline ImVec4 accent = ImColor(255, 0, 0, 255);
    inline ImVec4 black = ImColor(0, 0, 0, 255);
    inline ImColor main_color(0, 247, 168);

    namespace info_bar
    {
        inline ImVec4 filling = ImColor(0, 0, 0, 255);
        inline ImVec4 stroke = ImColor(14, 15, 22, 255);
        inline float rounding = 8;
        inline ImVec4 box = ImColor(8, 9, 12, 255);
        inline ImVec4 box_outline = ImColor(22, 23, 26, 255);

    }

    namespace combo {


        inline ImVec4 text_active = ImColor(255, 255, 255);
        inline ImVec4 text_hovered = ImColor(150, 150, 150);
        inline ImVec4 text_inactive = ImColor(76, 76, 77);
        inline ImVec4 combo_bg = ImColor(12, 27, 29);

    }


    namespace picker
    {
        inline ImVec4 outline = ImColor(22, 24, 26, 255);
        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 2;
    }
    namespace text
    {
        inline ImVec4 text_hov = ImColor(245, 245, 255);
        inline ImVec4 text = ImColor(90, 93, 100);
        inline ImVec4 text2 = ImColor(90, 93, 100, 0);
        inline ImVec4 hide_text = ImColor(43, 48, 54, 255);

    }
    inline ImVec4 accent_text_color = ImColor(245, 245, 255);

    namespace checkbox
    {
        inline ImVec4 circle_inactive = ImColor(43, 48, 54, 255);

        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 30;
    }
    namespace background
    {
        inline ImVec4 background = ImColor(16, 16, 16, 200);
        inline ImVec4 filling = ImColor(12, 12, 12);
        inline ImVec4 fillings = ImColor(5, 5, 5, 255);
        inline ImVec4 stroke = ImColor(24, 26, 36);
        inline ImVec2 size = ImVec2(900, 515);

        inline float rounding = 6;
    }
    namespace tab
    {
        inline ImVec4 tab_active = ImColor(3, 3, 3, 255);


        inline ImVec4 border = ImColor(14, 14, 15);
    }
    namespace elements
    {
        inline ImVec4 mark = ImColor(255, 255, 255);
        inline ImVec4 textMessage = ImColor(255, 255, 255); 

        inline ImVec4 stroke = ImColor(28, 26, 37);

        inline  ImVec4 background = ImColor(3, 3, 3, 255);

        inline ImVec4 background_widget = ImColor(5, 5, 5, 255);

        inline ImVec4 text_active = ImColor(255, 255, 255);
        inline ImVec4 text_hov = ImColor(81, 92, 109);
        inline ImVec4 text = ImColor(43, 51, 63);
        inline ImVec4 outline = ImColor(22, 24, 26, 255);
        inline float rounding = 4;



    }
    namespace child
    {


        inline ImVec4 background = ImColor(0, 0, 0, 255);

        inline ImVec4 outline = ImColor(18, 20, 18, 255);
        inline float rounding = 8.f;
        inline ImVec2 size = ImVec2(900, 483);
        inline ImVec2 sizeSpy = ImVec2(750, 150);
        inline ImVec2 sizeTabla = ImVec2(750, 275);
        inline ImVec2 sizeTablay = ImVec2(750, 435);

        inline ImVec4 text = ImColor(255, 255, 255, 255);
        inline ImVec4 hint = ImColor(59, 62, 72, 255);

        inline ImVec2 spacing = ImVec2(15, 12);
        inline ImVec2 padding = ImVec2(15, 15);


    }
    namespace keybind
    {
        inline ImVec4 background_active = ImColor(26, 27, 29, 255);
        inline ImVec4 background_inactive = ImVec4(47.0f / 255.0f, 47.0f / 255.0f, 47.0f / 255.0f, 0.84f);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);

        inline float rounding = 2.f;
    }
}
using namespace ImGui;
inline float anim_speed;
inline void rect_glow(ImDrawList* draw, ImVec2 start, ImVec2 end, ImColor col, float rounding, float intensity) {
    while (true) {
        if (col.Value.w < 0.0019f)
            break;

        draw->AddRectFilled(start, end, col, rounding);

        col.Value.w -= col.Value.w / intensity;
        start = ImVec2(start.x - 1, start.y - 1);
        end = ImVec2(end.x + 1, end.y + 1);
    }
}
struct HitPoint {
    ImVec2 pos;
    int state = 0; 
};

inline extern std::vector<HitPoint> hitpoints;

std::vector<HitPoint> hitpoints = {
    { ImVec2(90, 32), 0 }, 
    { ImVec2(90, 87), 1 }, 
    { ImVec2(42, 87), 2 }, 
    { ImVec2(75, 160), 3 }
};

inline int g_HitpointsVersion = 0;
