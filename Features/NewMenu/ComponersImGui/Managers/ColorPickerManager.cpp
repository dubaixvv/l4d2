#define _CRT_SECURE_NO_WARNINGS
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "..//..//ImGui/imgui.h"
#include "..//..//ImGui/imgui_internal.h"
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include "animations.hpp"
#include ".//../Combuilder/CompBuilder.hpp"
#include "ColorPickerManager.hpp"
#include "WidgetsManager.hpp"
//#include "FontManager.hpp"
#include "unicodes.hpp"
#include "../../ImGui/ImGui_Edited/imgui_edited.hpp"
using namespace ImGui;
bool ColorPickerManager::draw(const char* label, float col[4]) {
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
    flags |= ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoLabel;


    return edited::ColorEdit3(label, col, flags);
}

