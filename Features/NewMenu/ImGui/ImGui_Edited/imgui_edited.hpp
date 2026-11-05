#define IMGUI_DEFINE_MATH_OPERATORS

#include "..//imgui_internal.h"
#include "..//main.h"
#include <cstdlib>
#include "..//imgui.h"
#include <map>
#include <string>
#include <wtypes.h>
namespace edited
{
	bool           ColorEdit3(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	bool           ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
	bool     ButtonExv2(const char* label, const ImVec2& size_arg = ImVec2(0, 0), ImGuiButtonFlags flags = 0, const char* typer = "normal");
	bool      Buttonv2(const char* label, const ImVec2& size = ImVec2(0, 0), const char* typer = "normal");

	bool ButtonExv3(const char* label, const ImVec2& size_arg = ImVec2(0, 0), ImGuiButtonFlags flags = 0, const char* typer = "normal", bool warning = false, const char* warning_msg = "none");
	bool Buttonv3(const char* label, const ImVec2& size = ImVec2(0, 0), const char* typer = "normal", bool warning = false, const char* warning_msg = "none");
	bool e_crosshair(int idx, bool active, int type);
	void draw_crosshair_preview(int type, float alpha);
	void lb_bg(ImVec2 pos, ImVec2 size, float active, float round);
}

