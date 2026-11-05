
#pragma once
#include "..//imgui.h"
namespace c
{
    // inline ImColor bg = ImColor(16, 16, 16, 255);
    inline ImColor bg0 = ImColor(16, 16, 16, 0);
    //  inline ImColor black = ImColor(0, 0, 0, 255);
    inline ImColor black48 = ImColor(0, 0, 0, 122);
    inline ImColor black24 = ImColor(0, 0, 0, 61);
    inline ImColor primary = ImColor(138, 223, 48, 255);
    inline ImColor primary48 = ImColor(138, 223, 48, 122);
    inline ImColor primary24 = ImColor(138, 223, 48, 61);
    inline ImColor primary12 = ImColor(138, 223, 48, 30);
    inline ImColor primary0 = ImColor(138, 223, 48, 0);
    inline ImColor secondary = ImColor(106, 175, 26, 255);
    inline ImColor secondary0 = ImColor(106, 175, 26, 0);
    inline ImColor error_primary = ImColor(223, 48, 48, 255);
    inline ImColor error_primary48 = ImColor(223, 48, 48, 122);
    inline ImColor error_secondary = ImColor(175, 26, 26, 255);
    inline ImColor error_secondary0 = ImColor(175, 26, 26, 0);
    inline ImColor info_primary = ImColor(48, 98, 223, 255);
    inline ImColor info_primary48 = ImColor(48, 98, 223, 122);
    inline ImColor info_secondary = ImColor(24, 68, 175, 255);
    inline ImColor info_secondary0 = ImColor(24, 68, 175, 0);
    inline ImColor white = ImColor(255, 255, 255, 255);
    inline ImColor white72 = ImColor(255, 255, 255, 182);
    inline ImColor white48 = ImColor(255, 255, 255, 122);
    inline ImColor white36 = ImColor(255, 255, 255, 91);
    inline ImColor white24 = ImColor(255, 255, 255, 61);
    inline ImColor white12 = ImColor(255, 255, 255, 30);
    inline ImColor white4 = ImColor(255, 255, 255, 10);
    inline ImColor white2 = ImColor(255, 255, 255, 5);
    inline ImColor white0 = ImColor(255, 255, 255, 0);

    inline struct highlight_t
    {
        ImColor f = ImColor(199, 255, 140, 255);
        ImColor s = secondary0;
    } highlight;

    inline struct error_highlight_t
    {
        ImColor f = ImColor(255, 140, 140, 255);
        ImColor s = error_secondary0;
    } error_highlight;

    inline struct info_highlight_t
    {
        ImColor f = ImColor(140, 173, 255, 255);
        ImColor s = info_secondary0;
    } info_highlight;
};
