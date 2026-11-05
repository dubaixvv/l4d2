#pragma once
#include "../../SDK/SDK.h"
class CFeatures_Outlines
{
public:
	void Render();

private:
	IMaterial* m_pMatGlowColor = nullptr, * m_pMatHaloAddToScreen = nullptr;
	ITexture* m_pRtFullFrame = nullptr, * m_pRenderBuffer0 = nullptr, * m_pRenderBuffer1 = nullptr;
	IMaterial* m_pMatBlurX = nullptr, * m_pMatBlurY = nullptr;
	IMaterialVar* m_pBloomAmount = nullptr;

	void Initialize();
};

namespace F { inline CFeatures_Outlines Outlines; }