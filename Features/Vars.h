#pragma once
#include "../SDK/L4D2/Includes/color.h"
#include "../SDK/SDK.h"


template <class T>

class CVar
{
public:
	T m_Var;
	const wchar_t* m_szDisplayName;
};
