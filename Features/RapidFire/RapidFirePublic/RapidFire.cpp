/*

if (g_var.iMethodRapidFire == 2)
{
	if (GetAsyncKeyState(g_var.iKeyRapidFire) & 0x8000)
	{
		DWORD ptr1 = *(DWORD*)(engineBase + 4352236);
		if (!ptr1)
			return;

		DWORD networkChannel = *(DWORD*)(ptr1 + 24);
		if (!networkChannel)
			return;

		// Validación básica de rango (opcional pero recomendable)
		if (IsBadWritePtr((void*)(networkChannel + 28), sizeof(int)))
			return;

		*(int*)(networkChannel + 16) = -1;
		*(int*)(networkChannel + 28) = 255;

		G::shouldForceSendPackets = true;
	}
}
*/