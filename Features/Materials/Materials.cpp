/*
void CMaterials::Initialize()
{
	I::MaterialSystem->m_bAllocatingRenderTargets() = true;
	static ConVar* mat_hdr_level = I::CVar->FindVar("mat_hdr_level");
	if (!m_pFlat)
	{
		auto* kv = new KeyValues("UnlitGeneric");
		kv->SetString("$basetexture", "vgui/white");
		kv->SetString("$envmap", " ");
		kv->SetString("$selfillum", "1");
		kv->SetString("$nodecal", "1");
		kv->SetString("$wireframe", "0");
		kv->SetString("$flat", "1");
		kv->SetString("$znearer", "0");
		kv->SetString("$halflambert", "0");
		kv->SetString("$model", "1");
		kv->SetString("$nocull", "1");
		kv->SetString("$nofog", "0");
		m_pFlat = I::MaterialSystem->CreateMaterial("seo_material_flat", kv);
	}
	if (!m_pGlow)
	{
		auto* kv = new KeyValues("VertexLitGeneric");
		kv->SetString("$basetexture", "vgui/white");
		kv->SetString("$bumpmap", "vgui/white");
		kv->SetString("$selfillum", "1");
		kv->SetString("$selfIllumFresnel", "1");
		kv->SetString("$selfIllumFresnelMinMaxExp", "[0 0.18 0.1]");
		kv->SetString("$selfillumtint", "[0.3 0.001 0.1]");
		m_pGlow = I::MaterialSystem->CreateMaterial("seo_material_glow", kv);
		m_pGlowEnvmapTint = m_pGlow->FindVar("$selfillumtint", nullptr);
		m_pGlowSelfillumTint = m_pGlow->FindVar("$selfillumtint", nullptr);
	}
	if (!m_pPlastic)
	{
		auto* kv = new KeyValues("VertexLitGeneric");
		kv->SetString("$basetexture", "vgui/white");
		kv->SetString("$ignorez", "0");
		kv->SetString("$envmap", "env_cubemap");
		kv->SetString("$normalmapalphaenvmapmask", "1");
		kv->SetString("$envmapcontrast", "1");
		kv->SetString("$nofog", "1");
		kv->SetString("$model", "1");
		kv->SetString("$nocull", "0");
		kv->SetString("$selfillum", "1");
		kv->SetString("$halflambert", "1");
		kv->SetString("$znearer", "0");
		kv->SetString("$flat", "1");
		kv->SetString("$wireframe", "0");
		m_pPlastic = I::MaterialSystem->CreateMaterial("seo_material_plastic", kv);
	}
	if (!m_pWireframe)
	{
		auto* kv = new KeyValues("VertexLitGeneric");

		kv->SetString("$basetexture", "vgui/white");
		kv->SetString("$bumpmap", "vgui/white");
		kv->SetString("$wireframe", "1");
		kv->SetString("$flat", "1");
		kv->SetString("$selfillum", "1");
		kv->SetString("$selfIllumFresnel", "1");
		kv->SetString("$selfIllumFresnelMinMaxExp", "[0 0.3 1]");
		kv->SetString("$selfillumtint", "[0.0 1.0 1.0]");
		kv->SetString("$halflambert", "1");
		kv->SetString("$model", "1");
		kv->SetString("$nocull", "0");
		kv->SetString("$envmap", "env_cubemap");
		kv->SetString("$envmaptint", "[0.0 0.5 1.0]");
		kv->SetString("$envmapcontrast", "1");
		kv->SetString("$nofog", "1");

		m_pWireframe = I::MaterialSystem->CreateMaterial("seo_material_wireframe_glow", kv);
		m_pWireframeGlowTint = m_pWireframe->FindVar("$selfillumtint", nullptr);
		m_pWireframeSelfillumTint = m_pWireframe->FindVar("$selfillumtint", nullptr);

	}

}

*/