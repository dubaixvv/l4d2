#pragma once
#include <vector>
#include <windows.h>
#include <cstring>
#include "memoryapi.h"
#include "..//..//SDK/SDK.h"

namespace Byte_Manager
{
	inline void Set_Bytes(__int8 Writeable, void* Address, unsigned __int32 Size, unsigned __int8 Byte)
	{
		if (Writeable == 0)
		{
			DWORD Previous_Access_Rights;

			VirtualProtect(Address, Size, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			memset(Address, Byte, Size);

			VirtualProtect(Address, Size, Previous_Access_Rights, &Previous_Access_Rights);
		}
		else
		{
			memset(Address, Byte, Size);
		}
	}

	inline void Copy_Bytes(__int8 Writeable, void* Address, unsigned __int32 Size, void* Bytes)
	{
		if (Writeable == 0)
		{
			DWORD Previous_Access_Rights;

			VirtualProtect(Address, Size, PAGE_EXECUTE_READWRITE, &Previous_Access_Rights);

			memcpy(Address, Bytes, Size);

			VirtualProtect(Address, Size, Previous_Access_Rights, &Previous_Access_Rights);
		}
		else
		{
			memcpy(Address, Bytes, Size);
		}
	}
};