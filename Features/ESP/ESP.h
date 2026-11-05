#pragma once

#include "../../SDK/SDK.h"
struct ImGuiESPData {
	float x, y, w, h; 
	std::string name;
	int health;
	Color colorStatusHealthSurvivor;
	Color colorStatusHealthInfected;
	std::string classInfect;
	float healthBar;
	float maxhealthBar;
	C_TerrorPlayer* pPlayer;
	Color colorBoxInfected;
	Color colorNameInfected;
	Color colorClassInfected;
	Color colorLineInfected;
	Color colorBoneInfected;
	Color colorIndicatorInfected;
};
class CFeatures_ESP
{
public:
	void Render();

	void RenderImGui();
	std::vector<ImGuiESPData> m_espSurvivors;
	std::vector<ImGuiESPData> m_espInfected;
private:
	bool GetBounds(C_BaseEntity* pBaseEntity, int& x, int& y, int& w, int& h);

	void Draw3DBox(C_BaseEntity* pEntity, const float flRotate, const Color clr);
	void OffScreenArrows(C_TerrorPlayer* pLocal);
};

namespace F { inline CFeatures_ESP ESP; }