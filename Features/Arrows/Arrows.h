#pragma once

#include "../../SDK/SDK.h"

class CFeatures_Arrows
{
public:
	void Run();

private:
	bool GetBounds(C_BaseEntity* pBaseEntity, int& x, int& y, int& w, int& h);

	void Draw3DBox(C_BaseEntity* pEntity, const float flRotate, const Color clr);
	void OffScreenArrows(C_TerrorPlayer* pLocal);
};

namespace F { inline CFeatures_Arrows Arrows; }
