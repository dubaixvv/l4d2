#include "imgui_edited.hpp"
#include <vector>
#include <string>
#include "../Fonts/font_awesome_5.h"
#include "../Vars/g_vars.h"
#include "colors.h"
#include "../anim/anim.h"

using namespace ImGui;

namespace edited
{
    void CrosshairListCreations() {

    }

    ImColor lerp(ImColor col1, ImColor col2, float t, bool a = false, float extra_alpha = 1.f)
    {
        col1.Value.w *= extra_alpha;
        col2.Value.w *= extra_alpha;
        if (a)
        {
            col1.Value.w *= t;
            col2.Value.w *= t;
        }
        return ImLerp(col1.Value, col2.Value, t);
    }
    ImColor a(ImColor col, float t)
    {
        col.Value.w *= t;
        return col;
    }
    inline void ShadeVertsLinearGradY(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImColor col0, ImColor col1)
    {
        ImDrawVert* vert_start = draw_list->VtxBuffer.Data + vert_start_idx;
        ImDrawVert* vert_end = draw_list->VtxBuffer.Data + vert_end_idx;
        float ystal = gradient_p1.y - gradient_p0.y;

        for (ImDrawVert* vert = vert_start; vert < vert_end; vert++)
        {
            if (vert->col != IM_COL32_WHITE)
            {
                continue;
            }
            float d = (vert->pos.y - gradient_p0.y) / ystal;
            float t = ImClamp(d, 0.0f, 1.0f);
            vert->col = ImColor(ImLerp(col0.Value, col1.Value, t));
        }
    }
    void edited::lb_bg(ImVec2 pos, ImVec2 size, float active, float round = 4.f)
    {
        auto draw = ::GetWindowDrawList();

        draw->AddRectFilled(pos, pos + size, c::white2, round);
        if (active > 0.f)
        {
            int vert_start_idx = draw->VtxBuffer.Size;
            draw->AddRectFilled(pos, pos + size, IM_COL32_WHITE, round);
            int vert_end_idx = draw->VtxBuffer.Size;

            ShadeVertsLinearGradY(draw, vert_start_idx, vert_end_idx,
                pos, pos + size,
                lerp(c::secondary0.Value, ImColor(g_var.color[0], g_var.color[1], g_var.color[2]), active, true, .12f),
                c::secondary0);
        }

        draw->AddRect(pos, pos + size, c::white4, round);
        if (active > 0.f)
        {
            int vert_start_idx = draw->VtxBuffer.Size;
            draw->AddRect(pos, pos + size, IM_COL32_WHITE, round);
            int vert_end_idx = draw->VtxBuffer.Size;

            ShadeVertsLinearGradY(draw, vert_start_idx, vert_end_idx,
                pos, pos + size,
                lerp(c::secondary0.Value, ImColor(g_var.color[0], g_var.color[1], g_var.color[2]), active, true, .24f),
                c::secondary0);
        }
    }

    void edited::draw_crosshair_preview(int type, float alpha)
    {
        ImGuiWindow* window = GetCurrentWindow();
        auto dl = window->DrawList;

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImVec2(230, 150);
        ImVec2 center = pos + size * 0.5f;

        ImVec4 colVec4(g_var.colorCrosshair[0], g_var.colorCrosshair[1], g_var.colorCrosshair[2], g_var.colorCrosshair[3]);
        ImColor col(colVec4);

        float s = (float)g_var.crossSize;
        float thick = g_var.crosshairTicknes;
        float t = g_var.crosshairTicknes;

        switch (type)
        {
        case 0:
            dl->AddCircleFilled(center, -3 + s, col, 16);
            break;

        case 1:
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(s, 0), col, 2.f);
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, s), col, 2.f);
            break;

        case 2:
            dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(s, s), col, 2.f);
            dl->AddLine(center + ImVec2(-s, s), center + ImVec2(s, -s), col, 2.f);
            break;

        case 3:
            dl->AddCircle(center, s, col, 32, 2.f);
            break;

        case 4:
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-6, 0), col, 2.f);
            dl->AddLine(center + ImVec2(6, 0), center + ImVec2(s, 0), col, 2.f);
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -6), col, 2.f);
            dl->AddLine(center + ImVec2(0, 6), center + ImVec2(0, s), col, 2.f);
            break;

        case 5:
            dl->AddRect(center - ImVec2(s, s), center + ImVec2(s, s), col, 0, 0, t);
            break;

        case 6:
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(s, 0), col, t);
            dl->AddLine(center + ImVec2(s, 0), center + ImVec2(0, s), col, t);
            dl->AddLine(center + ImVec2(0, s), center + ImVec2(-s, 0), col, t);
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(0, -s), col, t);
            break;

        case 7:
            dl->AddRect(center - ImVec2(s, s), center + ImVec2(s, s), col, 0, 0, t);
            dl->AddCircleFilled(center, 2.f, col, 16);
            break;
        case 8:
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-s / 2, 0), col, t);
            dl->AddLine(center + ImVec2(s / 2, 0), center + ImVec2(s, 0), col, t);
            break;

        case 9:
            dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(-s + 6, -s + 6), col, t);
            dl->AddLine(center + ImVec2(s, -s), center + ImVec2(s - 6, -s + 6), col, t);
            dl->AddLine(center + ImVec2(-s, s), center + ImVec2(-s + 6, s - 6), col, t);
            dl->AddLine(center + ImVec2(s, s), center + ImVec2(s - 6, s - 6), col, t);
            break;

        case 10:
            dl->PathArcTo(center, s, IM_PI * 0.00f, IM_PI * 0.40f, 32);
            dl->PathStroke(col, false, t);
            dl->PathArcTo(center, s, IM_PI * 0.60f, IM_PI * 1.00f, 32);
            dl->PathStroke(col, false, t);
            dl->PathArcTo(center, s, IM_PI * 1.20f, IM_PI * 1.60f, 32);
            dl->PathStroke(col, false, t);
            dl->PathArcTo(center, s, IM_PI * 1.80f, IM_PI * 2.00f, 32);
            dl->PathStroke(col, false, t);
            break;

        case 11:
            dl->AddCircle(center, s, col, 32, t);
            dl->AddCircle(center, s * 0.5f, col, 32, t);
            break;

        case 12:
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-s / 3, 0), col, t);
            dl->AddLine(center + ImVec2(s / 3, 0), center + ImVec2(s, 0), col, t);
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -s / 3), col, t);
            dl->AddLine(center + ImVec2(0, s / 3), center + ImVec2(0, s), col, t);
            break;

        case 13:
            dl->AddCircle(center, s, col, 32, t);
            dl->AddCircleFilled(center, 2.f, col, 16);
            break;

        case 14:
            dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(s, 0), col, t);
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, s), col, t);
            dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(s, s), col, t);
            dl->AddLine(center + ImVec2(-s, s), center + ImVec2(s, -s), col, t);
            break;
        case 15:
        {
            dl->AddCircleFilled(center, 2.f, col, 16);

            float dist = s * 2.0f;
            float wing = s * 0.35f;

            dl->AddLine(center + ImVec2(-dist, -wing), center + ImVec2(-t * 2, 0), col, t);
            dl->AddLine(center + ImVec2(-dist, wing), center + ImVec2(-t * 2, 0), col, t);
            dl->AddLine(center + ImVec2(dist, -wing), center + ImVec2(t * 2, 0), col, t);
            dl->AddLine(center + ImVec2(dist, wing), center + ImVec2(t * 2, 0), col, t);

            break;
        }

        case 16:
            dl->AddCircleFilled(center, 2.f, col, 16);
            dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -t * 2), col, t);
            dl->AddLine(center + ImVec2(-s * 0.8f, s * 0.6f),
                center + ImVec2(-t * 1.5f, t * 1.5f),
                col, t);
            dl->AddLine(center + ImVec2(s * 0.8f, s * 0.6f),
                center + ImVec2(t * 1.5f, t * 1.5f),
                col, t);

            break;
        case 17:
        {
            float h = s;
            float w = s * 0.6f;

            ImVec2 top = center + ImVec2(0, -h);
            ImVec2 left = center + ImVec2(-w, -h * 0.3f);
            ImVec2 right = center + ImVec2(w, -h * 0.3f);

            dl->AddLine(left, top, col, t);
            dl->AddLine(top, right, col, t);
            break;
        }

        case 18:
        {
            float dist = s * 0.9f;
            float tri_len = s * 0.42f;
            float t_small = t;
            float dot_r = 1.8f;
            dl->AddCircleFilled(center, dot_r, col, 16);
            ImVec2 topApex = center + ImVec2(0.0f, -dist);
            ImVec2 topL = topApex + ImVec2(-tri_len * 0.6f, tri_len * 0.9f);
            ImVec2 topR = topApex + ImVec2(tri_len * 0.6f, tri_len * 0.9f);
            dl->AddLine(topL, topApex, col, t_small);
            dl->AddLine(topApex, topR, col, t_small);
            ImVec2 blApex = center + ImVec2(-dist * 0.78f, dist * 0.56f);
            ImVec2 blL = blApex + ImVec2(-tri_len * 0.9f, -tri_len * 0.25f);
            ImVec2 blR = blApex + ImVec2(tri_len * 0.55f, tri_len * 0.7f);
            dl->AddLine(blL, blApex, col, t_small);
            dl->AddLine(blApex, blR, col, t_small);
            ImVec2 brApex = center + ImVec2(dist * 0.78f, dist * 0.56f);
            ImVec2 brL = brApex + ImVec2(-tri_len * 0.55f, tri_len * 0.7f);
            ImVec2 brR = brApex + ImVec2(tri_len * 0.9f, -tri_len * 0.25f);
            dl->AddLine(brL, brApex, col, t_small);
            dl->AddLine(brApex, brR, col, t_small);

            break;
        }
        case 19:
        {
            float len = 6.f;
            float off = 10.f;
            dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off + len, -off + len), col, t);
            dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off - len, -off + len), col, t);
            dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off + len, off - len), col, t);
            dl->AddLine(center + ImVec2(off, off), center + ImVec2(off - len, off - len), col, t);
            dl->AddCircleFilled(center, 2.f, col, 16);
        }
        break;
        case 20:
        {
            float len = 14.f;
            float sep = 8.f;
            dl->AddLine(center + ImVec2(-sep, 0),
                center + ImVec2(-sep - len * 0.7f, -len * 0.7f),
                col, t);
            dl->AddLine(center + ImVec2(sep, 0),
                center + ImVec2(sep + len * 0.7f, -len * 0.7f),
                col, t);
            dl->AddCircleFilled(center, 2.f, col, 16);
        }
        break;
        case 21:
        {
            float dist = s * 0.9f;
            float wing = s * 0.35f;

            dl->AddCircleFilled(center, 1.5f, col, 16);
            dl->AddCircle(center, s * 0.3f, col, 32, t);
            dl->AddLine(center + ImVec2(-dist, 0), center + ImVec2(-dist + wing * 0.7f, wing), col, t);
            dl->AddLine(center + ImVec2(-dist, 0), center + ImVec2(-dist + wing * 0.7f, -wing), col, t);
            dl->AddLine(center + ImVec2(dist, 0), center + ImVec2(dist - wing * 0.7f, wing), col, t);
            dl->AddLine(center + ImVec2(dist, 0), center + ImVec2(dist - wing * 0.7f, -wing), col, t);

            break;
        }
        case 22:
        {
            float len = s * 0.3f;
            float off = s * 0.8f;
            float t_small = t;
            dl->AddCircleFilled(center, 1.8f, col, 16);
            dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off, -off + len), col, t_small);
            dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off + len, -off), col, t_small);
            dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off, -off + len), col, t_small);
            dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off - len, -off), col, t_small);
            dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off, off - len), col, t_small);
            dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off + len, off), col, t_small);
            dl->AddLine(center + ImVec2(off, off), center + ImVec2(off, off - len), col, t_small);
            dl->AddLine(center + ImVec2(off, off), center + ImVec2(off - len, off), col, t_small);

            break;
        }
        case 23:
        {
            float radius = s * 0.7f;
            float dot_r = 1.8f;
            dl->AddCircleFilled(center, dot_r, col, 16);
            float startAngleLeft = IM_PI * 0.7f;
            float endAngleLeft = IM_PI * 1.3f;
            dl->PathArcTo(center, radius, startAngleLeft, endAngleLeft, 32);
            dl->PathStroke(col, false, t);
            float startAngleRight = IM_PI * 1.7f;
            float endAngleRight = IM_PI * 0.3f;
            dl->PathArcTo(center, radius, startAngleRight, IM_PI * 2.0f, 32);
            dl->PathStroke(col, false, t);

            dl->PathArcTo(center, radius, IM_PI * 0.0f, endAngleRight, 32);
            dl->PathStroke(col, false, t);

            break;
        }


        }
    }



    bool edited::e_crosshair(int idx, bool active, int type)
    {
        ImGuiWindow* window = GetCurrentWindow();
        std::string label = std::to_string(idx);

        ImVec2 size = ImVec2(60.f, 60.f);
        ImVec2 pos = window->DC.CursorPos;

        auto curr = anims::animation((label + "##lcrosshair").c_str(), anim_t(clamp_out, 0.1f));
        auto curr_h = anims::animation((label + "##lhcrosshair").c_str(), anim_t(clamp_out, 0.2f));
        curr->active = active;
        float extra_a = std::clamp(curr->val + (curr_h->val / 2.f), 0.f, 1.f);

        lb_bg(pos, size, extra_a, 8.f);

        {
            auto dl = window->DrawList;
            ImVec2 center = pos + ImVec2(size.x * 0.5f, size.y * 0.5f);
            ImColor col = a(c::white, std::clamp(extra_a + 0.5f, 0.f, 1.f));
            float s = 13.f;
            float t = 2.f;

            switch (type)
            {
            case 0:
                dl->AddCircleFilled(center, 2.f, col, 16);
                break;

            case 1:
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(s, 0), col, 2.f);
                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, s), col, 2.f);
                break;

            case 2:
                dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(s, s), col, 2.f);
                dl->AddLine(center + ImVec2(-s, s), center + ImVec2(s, -s), col, 2.f);
                break;

            case 3:
                dl->AddCircle(center, s, col, 32, 2.f);
                break;

            case 4:
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-6, 0), col, 2.f);
                dl->AddLine(center + ImVec2(6, 0), center + ImVec2(s, 0), col, 2.f);
                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -6), col, 2.f);
                dl->AddLine(center + ImVec2(0, 6), center + ImVec2(0, s), col, 2.f);
                break;
            case 5:
                dl->AddRect(center - ImVec2(s, s), center + ImVec2(s, s), col, 0, 0, t);
                break;

            case 6:
                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(s, 0), col, t);
                dl->AddLine(center + ImVec2(s, 0), center + ImVec2(0, s), col, t);
                dl->AddLine(center + ImVec2(0, s), center + ImVec2(-s, 0), col, t);
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(0, -s), col, t);
                break;

            case 7:
                dl->AddRect(center - ImVec2(s, s), center + ImVec2(s, s), col, 0, 0, t);
                dl->AddCircleFilled(center, 2.f, col, 16);
                break;
            case 8:
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-s / 2, 0), col, t);
                dl->AddLine(center + ImVec2(s / 2, 0), center + ImVec2(s, 0), col, t);
                break;

            case 9:
                dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(-s + 6, -s + 6), col, t);
                dl->AddLine(center + ImVec2(s, -s), center + ImVec2(s - 6, -s + 6), col, t);
                dl->AddLine(center + ImVec2(-s, s), center + ImVec2(-s + 6, s - 6), col, t);
                dl->AddLine(center + ImVec2(s, s), center + ImVec2(s - 6, s - 6), col, t);
                break;

            case 10:
                dl->PathArcTo(center, s, IM_PI * 0.00f, IM_PI * 0.40f, 32);
                dl->PathStroke(col, false, t);
                dl->PathArcTo(center, s, IM_PI * 0.60f, IM_PI * 1.00f, 32);
                dl->PathStroke(col, false, t);
                dl->PathArcTo(center, s, IM_PI * 1.20f, IM_PI * 1.60f, 32);
                dl->PathStroke(col, false, t);
                dl->PathArcTo(center, s, IM_PI * 1.80f, IM_PI * 2.00f, 32);
                dl->PathStroke(col, false, t);
                break;

            case 11:
                dl->AddCircle(center, s, col, 32, t);
                dl->AddCircle(center, s * 0.5f, col, 32, t);
                break;

            case 12:
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(-s / 3, 0), col, t);
                dl->AddLine(center + ImVec2(s / 3, 0), center + ImVec2(s, 0), col, t);
                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -s / 3), col, t);
                dl->AddLine(center + ImVec2(0, s / 3), center + ImVec2(0, s), col, t);
                break;

            case 13:
                dl->AddCircle(center, s, col, 32, t);
                dl->AddCircleFilled(center, 2.f, col, 16);
                break;

            case 14:
                dl->AddLine(center + ImVec2(-s, 0), center + ImVec2(s, 0), col, t);
                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, s), col, t);
                dl->AddLine(center + ImVec2(-s, -s), center + ImVec2(s, s), col, t);
                dl->AddLine(center + ImVec2(-s, s), center + ImVec2(s, -s), col, t);
                break;
            case 15:
            {
                dl->AddCircleFilled(center, 2.f, col, 16);
                float dist = s * 1.0f;
                float wing = s * 0.35f;
                dl->AddLine(center + ImVec2(-dist, -wing), center + ImVec2(-t * 2, 0), col, t);
                dl->AddLine(center + ImVec2(-dist, wing), center + ImVec2(-t * 2, 0), col, t);
                dl->AddLine(center + ImVec2(dist, -wing), center + ImVec2(t * 2, 0), col, t);
                dl->AddLine(center + ImVec2(dist, wing), center + ImVec2(t * 2, 0), col, t);

                break;
            }

            case 16:
                dl->AddCircleFilled(center, 2.f, col, 16);

                dl->AddLine(center + ImVec2(0, -s), center + ImVec2(0, -t * 2), col, t);
                dl->AddLine(center + ImVec2(-s * 0.8f, s * 0.6f),
                    center + ImVec2(-t * 1.5f, t * 1.5f),
                    col, t);
                dl->AddLine(center + ImVec2(s * 0.8f, s * 0.6f),
                    center + ImVec2(t * 1.5f, t * 1.5f),
                    col, t);

                break;
            case 17:
            {
                float h = s;
                float w = s * 0.6f;
                ImVec2 top = center + ImVec2(0, -h);
                ImVec2 left = center + ImVec2(-w, -h * 0.3f);
                ImVec2 right = center + ImVec2(w, -h * 0.3f);
                dl->AddLine(left, top, col, t);
                dl->AddLine(top, right, col, t);
                break;
            }

            case 18:
            {
                float dist = s * 0.9f;
                float tri_len = s * 0.42f;
                float t_small = t;
                float dot_r = 1.8f;

                dl->AddCircleFilled(center, dot_r, col, 16);
                ImVec2 topApex = center + ImVec2(0.0f, -dist);
                ImVec2 topL = topApex + ImVec2(-tri_len * 0.6f, tri_len * 0.9f);
                ImVec2 topR = topApex + ImVec2(tri_len * 0.6f, tri_len * 0.9f);
                dl->AddLine(topL, topApex, col, t_small);
                dl->AddLine(topApex, topR, col, t_small);
                ImVec2 blApex = center + ImVec2(-dist * 0.78f, dist * 0.56f);
                ImVec2 blL = blApex + ImVec2(-tri_len * 0.9f, -tri_len * 0.25f);
                ImVec2 blR = blApex + ImVec2(tri_len * 0.55f, tri_len * 0.7f);
                dl->AddLine(blL, blApex, col, t_small);
                dl->AddLine(blApex, blR, col, t_small);
                ImVec2 brApex = center + ImVec2(dist * 0.78f, dist * 0.56f);
                ImVec2 brL = brApex + ImVec2(-tri_len * 0.55f, tri_len * 0.7f);
                ImVec2 brR = brApex + ImVec2(tri_len * 0.9f, -tri_len * 0.25f);

                dl->AddLine(brL, brApex, col, t_small);
                dl->AddLine(brApex, brR, col, t_small);

                break;
            }
            case 19:
            {
                float len = 6.f;
                float off = 10.f;
                dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off + len, -off + len), col, t);
                dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off - len, -off + len), col, t);
                dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off + len, off - len), col, t);
                dl->AddLine(center + ImVec2(off, off), center + ImVec2(off - len, off - len), col, t);
                dl->AddCircleFilled(center, 2.f, col, 16);
            }
            break;
            case 20:
            {
                float len = 14.f;
                float sep = 8.f;
                dl->AddLine(center + ImVec2(-sep, 0),
                    center + ImVec2(-sep - len * 0.7f, -len * 0.7f),
                    col, t);
                dl->AddLine(center + ImVec2(sep, 0),
                    center + ImVec2(sep + len * 0.7f, -len * 0.7f),
                    col, t);
                dl->AddCircleFilled(center, 2.f, col, 16);
            }
            break;

            case 21:
            {
                float dist = s * 0.9f;
                float wing = s * 0.35f;

                dl->AddCircleFilled(center, 1.5f, col, 16);
                dl->AddCircle(center, s * 0.3f, col, 32, t);
                dl->AddLine(center + ImVec2(-dist, 0), center + ImVec2(-dist + wing * 0.7f, wing), col, t);
                dl->AddLine(center + ImVec2(-dist, 0), center + ImVec2(-dist + wing * 0.7f, -wing), col, t);
                dl->AddLine(center + ImVec2(dist, 0), center + ImVec2(dist - wing * 0.7f, wing), col, t);
                dl->AddLine(center + ImVec2(dist, 0), center + ImVec2(dist - wing * 0.7f, -wing), col, t);

                break;
            }
            case 22:
            {
                float len = s * 0.3f;
                float off = s * 0.8f;
                float t_small = t;

                dl->AddCircleFilled(center, 1.8f, col, 16);
                dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off, -off + len), col, t_small);
                dl->AddLine(center + ImVec2(-off, -off), center + ImVec2(-off + len, -off), col, t_small);
                dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off, -off + len), col, t_small);
                dl->AddLine(center + ImVec2(off, -off), center + ImVec2(off - len, -off), col, t_small);
                dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off, off - len), col, t_small);
                dl->AddLine(center + ImVec2(-off, off), center + ImVec2(-off + len, off), col, t_small);
                dl->AddLine(center + ImVec2(off, off), center + ImVec2(off, off - len), col, t_small);
                dl->AddLine(center + ImVec2(off, off), center + ImVec2(off - len, off), col, t_small);

                break;
            }
            case 23:
            {
                float radius = s * 0.7f;
                float dot_r = 1.8f;

                dl->AddCircleFilled(center, dot_r, col, 16);
                float startAngleLeft = IM_PI * 0.7f;
                float endAngleLeft = IM_PI * 1.3f;
                dl->PathArcTo(center, radius, startAngleLeft, endAngleLeft, 32);
                dl->PathStroke(col, false, t);
                float startAngleRight = IM_PI * 1.7f;
                float endAngleRight = IM_PI * 0.3f;
                dl->PathArcTo(center, radius, startAngleRight, IM_PI * 2.0f, 32);
                dl->PathStroke(col, false, t);

                dl->PathArcTo(center, radius, IM_PI * 0.0f, endAngleRight, 32);
                dl->PathStroke(col, false, t);
                break;
            }
            }

        }

        ::GetCurrentWindow()->DC.CursorPos = pos;
        bool ret = ::InvisibleButton((label + "##lcrosshair").c_str(), size);
        curr_h->active = ::IsItemHovered() || curr->active;
        return ret;
    }





    static void ColorEditRestoreHS(const float* col, float* H, float* S, float* V)
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.ColorEditCurrentID != 0);
        if (g.ColorEditSavedID != g.ColorEditCurrentID || g.ColorEditSavedColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0))) return;

        if (*S == 0.0f || (*H == 0.0f && g.ColorEditSavedHue == 1))
            *H = g.ColorEditSavedHue;

        if (*V == 0.0f) *S = g.ColorEditSavedSat;
    }
    static void ColorEditRestoreH(const float* col, float* H)
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.ColorEditCurrentID != 0);
        if (g.ColorEditSavedID != g.ColorEditCurrentID || g.ColorEditSavedColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0)))
            return;
        *H = g.ColorEditSavedHue;
    }
    struct edit_state
    {
        ImVec4 text;
        float alpha = 0.f, alpha_search;
        bool hovered, active;
    };
    struct picker_state
    {
        float hue_bar;
        float alpha_bar;
        float circle;
        ImVec2 circle_move;
    };
    bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags, const float* ref_col)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImDrawList* draw_list = window->DrawList;
        ImGuiStyle& style = g.Style;
        ImGuiIO& io = g.IO;

        const float width = CalcItemWidth();
        g.NextItemData.ClearFlags();

        PushID(label);
        const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
        if (set_current_color_edit_id)
            g.ColorEditCurrentID = window->IDStack.back();
        BeginGroup();

        if (!(flags & ImGuiColorEditFlags_NoSidePreview)) flags |= ImGuiColorEditFlags_NoSmallPreview;

        if (!(flags & ImGuiColorEditFlags_NoOptions)) ColorPickerOptionsPopup(col, flags);

        if (!(flags & ImGuiColorEditFlags_PickerMask_)) flags |= ((g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_) ? g.ColorEditOptions : ImGuiColorEditFlags_DefaultOptions_) & ImGuiColorEditFlags_PickerMask_;
        if (!(flags & ImGuiColorEditFlags_InputMask_)) flags |= ((g.ColorEditOptions & ImGuiColorEditFlags_InputMask_) ? g.ColorEditOptions : ImGuiColorEditFlags_DefaultOptions_) & ImGuiColorEditFlags_InputMask_;
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_PickerMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));
        if (!(flags & ImGuiColorEditFlags_NoOptions)) flags |= (g.ColorEditOptions & ImGuiColorEditFlags_AlphaBar);

        int components = (flags & ImGuiColorEditFlags_NoAlpha) ? 3 : 4;
        bool alpha_bar = (flags & ImGuiColorEditFlags_AlphaBar) && !(flags & ImGuiColorEditFlags_NoAlpha);
        ImVec2 picker_pos = window->DC.CursorPos;
        float square_sz = GetFrameHeight();
        float bars_width = 15.f;
        float sv_picker_size = ImMax(bars_width * 1, width - (alpha_bar ? 2 : 1) * (bars_width));
        float bar0_pos_x = picker_pos.x + sv_picker_size + 10;
        float bar1_pos_x = bar0_pos_x + bars_width + 10;
        float bars_triangles_half_sz = IM_TRUNC(bars_width * 0.20f);

        float backup_initial_col[4];
        memcpy(backup_initial_col, col, components * sizeof(float));

        float H = col[0], S = col[1], V = col[2];
        float R = col[0], G = col[1], B = col[2];
        if (flags & ImGuiColorEditFlags_InputRGB)
        {
            ColorConvertRGBtoHSV(R, G, B, H, S, V);
            ColorEditRestoreHS(col, &H, &S, &V);
        }
        else if (flags & ImGuiColorEditFlags_InputHSV)
        {
            ColorConvertHSVtoRGB(H, S, V, R, G, B);
        }

        bool value_changed = false, value_changed_h = false, value_changed_sv = false;

        InvisibleButton("sv", ImVec2(sv_picker_size, sv_picker_size));
        if (IsItemActive())
        {
            S = ImSaturate((io.MousePos.x - picker_pos.x) / (sv_picker_size - 1));
            V = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
            ColorEditRestoreH(col, &H);
            value_changed = value_changed_sv = true;
        }
        if (!(flags & ImGuiColorEditFlags_NoOptions)) OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

        SetCursorScreenPos(ImVec2(bar0_pos_x, picker_pos.y));
        InvisibleButton("hue", ImVec2(bars_width, sv_picker_size));
        if (IsItemActive())
        {
            H = ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
            value_changed = value_changed_h = true;
        }

        if (alpha_bar)
        {
            SetCursorScreenPos(ImVec2(bar1_pos_x, picker_pos.y));
            InvisibleButton("alpha", ImVec2(bars_width, sv_picker_size));
            if (IsItemActive())
            {
                col[3] = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
                value_changed = true;
            }
        }

        if (!(flags & ImGuiColorEditFlags_NoLabel))
        {
            const char* label_display_end = FindRenderedTextEnd(label);
            if (label != label_display_end)
            {
                if ((flags & ImGuiColorEditFlags_NoSidePreview))
                    SameLine(0, style.ItemInnerSpacing.x);
                TextEx(label, label_display_end);
            }
        }

        if (value_changed_h || value_changed_sv)
        {
            if (flags & ImGuiColorEditFlags_InputRGB)
            {
                ColorConvertHSVtoRGB(H, S, V, col[0], col[1], col[2]);
                g.ColorEditSavedHue = H;
                g.ColorEditSavedSat = S;
                g.ColorEditSavedID = g.ColorEditCurrentID;
                g.ColorEditSavedColor = ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0));
            }
            else if (flags & ImGuiColorEditFlags_InputHSV)
            {
                col[0] = H;
                col[1] = S;
                col[2] = V;
            }
        }

        if (value_changed)
        {
            if (flags & ImGuiColorEditFlags_InputRGB)
            {
                R = col[0];
                G = col[1];
                B = col[2];
                ColorConvertRGBtoHSV(R, G, B, H, S, V);
                ColorEditRestoreHS(col, &H, &S, &V);
            }
            else if (flags & ImGuiColorEditFlags_InputHSV)
            {
                H = col[0];
                S = col[1];
                V = col[2];
                ColorConvertHSVtoRGB(H, S, V, R, G, B);
            }
        }

        const int style_alpha8 = IM_F32_TO_INT8_SAT(style.Alpha);
        const ImU32 col_black = IM_COL32(0, 0, 0, style_alpha8);
        const ImU32 col_white = IM_COL32(255, 255, 255, style_alpha8);
        const ImU32 col_midgrey = IM_COL32(128, 128, 128, style_alpha8);
        const ImU32 col_hues[6 + 1] = { IM_COL32(255,0,0,style_alpha8), IM_COL32(255,255,0,style_alpha8), IM_COL32(0,255,0,style_alpha8), IM_COL32(0,255,255,style_alpha8), IM_COL32(0,0,255,style_alpha8), IM_COL32(255,0,255,style_alpha8), IM_COL32(255,0,0,style_alpha8) };

        ImVec4 hue_color_f(1, 1, 1, style.Alpha); ColorConvertHSVtoRGB(H, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z);
        ImU32 hue_color32 = ColorConvertFloat4ToU32(hue_color_f);
        ImU32 user_col32_striped_of_alpha = ColorConvertFloat4ToU32(ImVec4(R, G, B, style.Alpha));

        static std::map<ImGuiID, picker_state> anim;
        picker_state& state = anim[ImGui::GetID(label)];

        ImVec2 sv_cursor_pos;

        draw_list->AddRectFilledMultiColors(picker_pos, picker_pos + ImVec2(sv_picker_size, sv_picker_size), col_white, hue_color32, hue_color32, col_white, 5.f, ImDrawFlags_RoundCornersAll);
        draw_list->AddRectFilledMultiColors(picker_pos - ImVec2(1, 1), picker_pos + ImVec2(sv_picker_size + 1, sv_picker_size + 1), 0, 0, col_black, col_black, 5.f, ImDrawFlags_RoundCornersAll);

        sv_cursor_pos.x = ImClamp(IM_ROUND(picker_pos.x + ImSaturate(S) * sv_picker_size), picker_pos.x + 2, picker_pos.x + sv_picker_size - 2);
        sv_cursor_pos.y = ImClamp(IM_ROUND(picker_pos.y + ImSaturate(1 - V) * sv_picker_size), picker_pos.y + 2, picker_pos.y + sv_picker_size - 2);

        for (int i = 0; i < 6; ++i) draw_list->AddRectFilledMultiColors(ImVec2(bar0_pos_x, picker_pos.y + i * (sv_picker_size / 6) - (i == 5 ? 1 : 0)), ImVec2(bar0_pos_x + bars_width, picker_pos.y + (i + 1) * (sv_picker_size / 6) + (i == 0 ? 1 : 0)), col_hues[i], col_hues[i], col_hues[i + 1], col_hues[i + 1], 10.f, i == 0 ? ImDrawFlags_RoundCornersTop : i == 5 ? ImDrawFlags_RoundCornersBottom : ImDrawFlags_RoundCornersNone);

        float bar0_line_y = IM_ROUND(picker_pos.y + H * sv_picker_size);
        bar0_line_y = ImClamp(bar0_line_y, picker_pos.y + 3.f, picker_pos.y + (sv_picker_size - 13));

        state.hue_bar = ImLerp(state.hue_bar, bar0_line_y + 5, g.IO.DeltaTime * 24.f);
        draw_list->AddCircleFilled(ImVec2(bar0_pos_x + 7.5f, state.hue_bar), 4.5f, col_black, 100.f);

        float sv_cursor_rad = value_changed_sv ? 10.0f : 6.0f;
        int sv_cursor_segments = draw_list->_CalcCircleAutoSegmentCount(sv_cursor_rad);

        state.circle_move = ImLerp(state.circle_move, sv_cursor_pos, g.IO.DeltaTime * 10.f);
        state.circle = ImLerp(state.circle, value_changed_sv ? 6.0f : 4.0f, g.IO.DeltaTime * 24.f);

        draw_list->AddCircle(state.circle_move, state.circle, col_white, sv_cursor_segments, 2.f);

        if (alpha_bar)
        {
            float alpha = ImSaturate(col[3]);
            ImRect bar1_bb(bar1_pos_x, picker_pos.y, bar1_pos_x + bars_width, picker_pos.y + sv_picker_size);

            draw_list->AddRectFilledMultiColors(bar1_bb.Min, bar1_bb.Max, user_col32_striped_of_alpha, user_col32_striped_of_alpha, user_col32_striped_of_alpha & ~IM_COL32_A_MASK, user_col32_striped_of_alpha & ~IM_COL32_A_MASK, 100.f, ImDrawFlags_RoundCornersTop);

            float bar1_line_y = IM_ROUND(picker_pos.y + (1.0f - alpha) * sv_picker_size);
            bar1_line_y = ImClamp(bar1_line_y, picker_pos.y + 3.f, picker_pos.y + (sv_picker_size - 13));

            state.alpha_bar = ImLerp(state.alpha_bar, bar1_line_y + 5, g.IO.DeltaTime * 24.f);
            draw_list->AddCircleFilled(ImVec2(bar1_pos_x + 7.5f, state.alpha_bar), 4.5f, col_black, 100.f);
        }

        EndGroup();

        if (value_changed && memcmp(backup_initial_col, col, components * sizeof(float)) == 0) value_changed = false;
        if (value_changed) MarkItemEdited(g.LastItemData.ID);

        PopID();

        return value_changed;
    }
    struct button_states
    {
        ImVec4 background, outline, text;
        ImVec2 pos = { 0.f, 0.f };
        float size = 0.f;
        bool active;
        float alpha;
    };

    bool ColorEdit3(const char* label, float col[4], ImGuiColorEditFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const float square_sz = 18.f;
        const float w_full = CalcItemWidth();
        const float w_button = (flags & ImGuiColorEditFlags_NoSmallPreview) ? 0.0f : square_sz;
        const float w_inputs = w_full - w_button;
        const char* label_display_end = FindRenderedTextEnd(label);
        g.NextItemData.ClearFlags();
        char buf[64];
        static bool search_col = false;

        BeginGroup();
        PushID(label);
        const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
        if (set_current_color_edit_id) g.ColorEditCurrentID = window->IDStack.back();

        const ImGuiColorEditFlags flags_untouched = flags;

        if (flags & ImGuiColorEditFlags_NoInputs) flags = (flags & (~ImGuiColorEditFlags_DisplayMask_)) | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoOptions;

        if (!(flags & ImGuiColorEditFlags_NoOptions)) ColorEditOptionsPopup(col, flags);

        if (!(flags & ImGuiColorEditFlags_DisplayMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DisplayMask_);
        if (!(flags & ImGuiColorEditFlags_DataTypeMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DataTypeMask_);
        if (!(flags & ImGuiColorEditFlags_PickerMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_);
        if (!(flags & ImGuiColorEditFlags_InputMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_InputMask_);
        flags |= (g.ColorEditOptions & ~(ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_DisplayMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));

        const bool alpha = (flags & ImGuiColorEditFlags_NoAlpha) == 0;
        const bool hdr = (flags & ImGuiColorEditFlags_HDR) != 0;
        const int components = alpha ? 4 : 3;

        float f[4] = { col[0], col[1], col[2], alpha ? col[3] : 1.0f };
        if ((flags & ImGuiColorEditFlags_InputHSV) && (flags & ImGuiColorEditFlags_DisplayRGB))
            ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
        else if ((flags & ImGuiColorEditFlags_InputRGB) && (flags & ImGuiColorEditFlags_DisplayHSV))
        {
            ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);
            ColorEditRestoreHS(col, &f[0], &f[1], &f[2]);
        }
        int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

        bool value_changed = false;
        bool value_changed_as_float = false;

        const ImVec2 pos = window->DC.CursorPos;
        const float inputs_offset_x = (style.ColorButtonPosition == ImGuiDir_Left) ? w_button : 0.0f;
        window->DC.CursorPos.x = pos.x + inputs_offset_x;

        if ((flags & (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV)) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
        {
            const float w_item_one = ImMax(1.0f, IM_FLOOR((w_inputs - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
            const float w_item_last = ImMax(1.0f, IM_FLOOR(w_inputs - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));

            const bool hide_prefix = (w_item_one <= CalcTextSize((flags & ImGuiColorEditFlags_Float) ? "M:0.000" : "M:000").x);
            static const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
            static const char* fmt_table_int[3][4] =
            {
                {   "%3d",   "%3d",   "%3d",   "%3d" },
                { "R:%3d", "G:%3d", "B:%3d", "A:%3d" },
                { "H:%3d", "S:%3d", "V:%3d", "A:%3d" }
            };

            static const char* fmt_table_float[3][4] =
            {
                {   "%0.3f",   "%0.3f",   "%0.3f",   "%0.3f" },
                { "R:%0.3f", "G:%0.3f", "B:%0.3f", "A:%0.3f" },
                { "H:%0.3f", "S:%0.3f", "V:%0.3f", "A:%0.3f" }
            };

            const int fmt_idx = hide_prefix ? 0 : (flags & ImGuiColorEditFlags_DisplayHSV) ? 2 : 1;

            for (int n = 0; n < components; n++)
            {
                if (n > 0) SameLine(0, style.ItemInnerSpacing.x);
                SetNextItemWidth((n + 1 < components) ? w_item_one : w_item_last);

                if (flags & ImGuiColorEditFlags_Float)
                {
                    value_changed |= DragFloat(ids[n], &f[n], 1.0f / 255.0f, 0.0f, hdr ? 0.0f : 1.0f, fmt_table_float[fmt_idx][n]);
                    value_changed_as_float |= value_changed;
                }
                else
                {
                    value_changed |= DragInt(ids[n], &i[n], 1.0f, 0, hdr ? 0 : 255, fmt_table_int[fmt_idx][n]);
                }
                if (!(flags & ImGuiColorEditFlags_NoOptions)) OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
            }
        }

        static std::map<ImGuiID, edit_state> anim;
        edit_state& state = anim[ImGui::GetID(label)];


        ImGuiWindow* picker_active_window = NULL;
        if (!(flags & ImGuiColorEditFlags_NoSmallPreview))
        {
            const float button_offset_x = ((flags & ImGuiColorEditFlags_NoInputs) || (style.ColorButtonPosition == ImGuiDir_Left)) ? 0.0f : w_inputs + style.ItemInnerSpacing.x;
            window->DC.CursorPos = ImVec2(pos.x + button_offset_x, pos.y);

            const ImVec4 col_v4(col[0], col[1], col[2], alpha ? col[3] : 1.0f);


            if (!(flags & ImGuiColorEditFlags_NoOptions)) OpenPopupOnItemClick("contextss", ImGuiPopupFlags_MouseButtonRight);
            ImRect itemRect = g.LastItemData.Rect;
            bool mouse_in_item_area = itemRect.Contains(g.IO.MousePos) && g.IO.MouseClicked[0];
            bool should_toggle_active = state.active && !search_col && g.IO.MouseClicked[0] && !state.hovered;
            if (mouse_in_item_area || should_toggle_active) {
                state.active = !state.active;
            }
            state.alpha_search = ImLerp(state.alpha_search, search_col ? 1.f : 0.f, g.IO.DeltaTime * 6.f);
            ImGuiColorEditFlags picker_flags_to_forward = ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar;
            ImGuiColorEditFlags picker_flags = (flags_untouched & picker_flags_to_forward) | ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf;
            {
                const char* display_label = (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel)) ? label : "Color picker";
                ImVec2 text_size = CalcTextSize(display_label);
                ImVec2 text_pos = ImGui::GetCursorScreenPos();  
                ImGui::GetWindowDrawList()->AddText(text_pos, GetColorU32(c::elements::text_active), display_label);
                ImGui::SetCursorScreenPos(text_pos + ImVec2(0.0f, text_size.y + 5.0f)); 
            }


            ImGui::PushItemWidth(180.0f);
            value_changed |= ColorPicker4("##picker", col, picker_flags, &g.ColorPickerRef.x);
            ImGui::PopItemWidth();

        }

        state.text = ImLerp(state.text, state.active ? c::elements::text_active : c::elements::text, g.IO.DeltaTime * 6.f);

        if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel))
        {
            SameLine(0.0f, style.ItemInnerSpacing.x);
            window->DC.CursorPos.x = pos.x - w_button + ((flags & ImGuiColorEditFlags_NoInputs) ? w_button : w_full);
        }
        PopID();
        EndGroup();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15.0f);
        return value_changed;
    }


    bool edited::ButtonExv2(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags, const char* typer)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = size_arg;

        if (size.x <= 0.0f) {
            size.x = label_size.x + style.FramePadding.x * 2.0f;
        }
        if (size.y <= 0.0f) {
            size.y = label_size.y + style.FramePadding.y * 2.0f;
        }

        const ImRect bb(pos, pos + size);

        ItemSize(ImRect(bb.Min, bb.Max));
        if (!ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        static std::map<ImGuiID, button_states> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end()) {
            anim.insert({ id, button_states() });
            it_anim = anim.find(id);
        }

        if (pressed && !it_anim->second.active && it_anim->second.alpha <= 0.1f) {
            it_anim->second.pos = GetMousePos();
            it_anim->second.active = true;
        }

        it_anim->second.alpha = ImClamp(it_anim->second.alpha + (4.f * g.IO.DeltaTime * (it_anim->second.active ? 1.f : -1.f)), 0.f, 1.f);

        if (it_anim->second.active)
            it_anim->second.size += (size.x / 2.f) * g.IO.DeltaTime * 5.f;

        if (it_anim->second.alpha <= 0.1f)
            it_anim->second.size = 0.f;

        if (it_anim->second.size >= size.x / 2.f)
            it_anim->second.active = false;

        it_anim->second.outline = ImLerp(it_anim->second.outline, it_anim->second.active ? c::accent : c::button::button_bg, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, it_anim->second.active ? c::accent : c::text::text_hov, g.IO.DeltaTime * 6.f);

        ImVec4 bg_color = c::button::button_bg;

        if (strcmp(typer, "delete") == 0)
            bg_color = ImColor(145, 10, 10, 255);
        else if (strcmp(typer, "save") == 0)
            bg_color = ImColor(15, 54, 21, 255);
        else if (strcmp(typer, "load") == 0)
            bg_color = ImColor(15, 39, 54, 255);

        ImGui::GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(bg_color), 4.f);
        ImGui::GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU322(c::accent, 0.1f * it_anim->second.alpha), 4.f);
        ImGui::GetWindowDrawList()->AddRect(bb.Min, bb.Max, GetColorU32(it_anim->second.outline), 4.f);

        ImVec2 text_pos = ImVec2(bb.Min.x + (size.x - label_size.x) * 0.5f, bb.Min.y + (size.y - label_size.y) * 0.5f);
        ImGui::GetWindowDrawList()->AddText(text_pos, GetColorU32(it_anim->second.text), label);

        return pressed;
    }

    bool edited::Buttonv2(const char* label, const ImVec2& size_arg, const char* typer)
    {
        return ButtonExv2(label, size_arg, ImGuiButtonFlags_None, typer);
    }
    bool edited::ButtonExv3(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags, const char* typer, bool warning, const char* warning_msg)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = size_arg;
        if (size.x <= 0.0f) size.x = label_size.x + style.FramePadding.x * 2.0f;
        if (size.y <= 0.0f) size.y = label_size.y + style.FramePadding.y * 2.0f;

        const ImRect bb(pos, pos + size);
        ItemSize(bb);
        if (!ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        ImVec4 bg_color = c::button::button_bg;
        if (strcmp(typer, "delete") == 0) bg_color = ImVec4(145.0f / 255.0f, 10.0f / 255.0f, 10.0f / 255.0f, 1.0f);
        else if (strcmp(typer, "save") == 0) bg_color = ImColor(15, 54, 21, 255);
        else if (strcmp(typer, "load") == 0) bg_color = ImColor(15, 39, 54, 255);

        ImGui::GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(bg_color), 4.f);

        ImVec2 text_pos = ImVec2(bb.Min.x + (size.x - label_size.x) * 0.5f, bb.Min.y + (size.y - label_size.y) * 0.5f);
        ImGui::GetWindowDrawList()->AddText(text_pos, GetColorU32(c::text::text_hov), label);

        if (pressed && warning) {
            ImGui::OpenPopup(label); 
            pressed = false; 
        }

        if (ImGui::BeginPopup(label)) {
            ImGui::TextColored(ImVec4(1.f, 0.4f, 0.f, 1.f), "%s %s", ICON_FA_TRIANGLE_EXCLAMATION, warning_msg);
            ImGui::Separator();

            if (Buttonv2("Yes", ImVec2(100, 0), "save")) {
                pressed = true;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (Buttonv2("No", ImVec2(100, 0), "delete")) {
                pressed = false; 
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        return pressed;
    }

    bool edited::Buttonv3(const char* label, const ImVec2& size, const char* typer, bool warning, const char* warning_msg)
    {
        return ButtonExv3(label, size, ImGuiButtonFlags_None, typer, warning, warning_msg);
    }



}