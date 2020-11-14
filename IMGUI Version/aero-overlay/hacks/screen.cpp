#include "screen.h"

Aimbot* g_pAimbot = new Aimbot();

Aimbot::Aimbot(){}
Aimbot::~Aimbot(){}
void Aimbot::updateaim()
{
	if (GetAsyncKeyState(aimkey))
	{
		AimAtPos();
		Vector2 lol = g_pEsp->GetMagicCoord(magicaim/*{100,100,100}*/, g_pEsp->mypos);
		g_pEsp->HookMagic(lol.x, lol.y);
	}
	Sleep(aimsleep);
}
void Aimbot::Boostplayer()
{
	if (GetAsyncKeyState(boostkey) && boostenabled)
	{
		for (int i = 0; i < 11; i++)
			g_pMemoryManager->Driver.WriteVirtualMemory<float>(g_pMemoryManager->processId, g_pEsp->boostAddv + (i * 4), boostval, sizeof(float));
		booststatus = true;
	}
	else if (boostenabled && booststatus)
	{
		for(int i=0;i<11;i++)
			g_pMemoryManager->Driver.WriteVirtualMemory<float>(g_pMemoryManager->processId, g_pEsp->boostAddv + (i*4), 1.0f, sizeof(float));
		booststatus = false;
	}
}

void Aimbot::IpadV()
{
	if (g_pEsp->ipad != 0)
	{
		g_pMemoryManager->Driver.WriteVirtualMemory<float>(g_pMemoryManager->processId, g_pEsp->ipad, ipadview, sizeof(float));
	}
}
void Aimbot::AimAtPos()
{
	float Width = g_Width;
	float Height = g_Height;
	float x = aimtarget.x;
	float y = aimtarget.y;
	int num = Width / 2;
	int num2 = Height / 2;
	float num3 = (float)smooth + 1.0f;
	float num4 = 0.0f;
	float num5 = 0.0f;
	if (x != 0.0f)
	{
		if (x > (float)num)
		{
			num4 = -((float)num - x);
			num4 /= num3;
			if ((num4 * num3) + (float)num > (float)(num * 2))
			{
				num4 = 0.0f;
			}
		}
		if (x < (float)num)
		{
			num4 = x - (float)num;
			num4 /= num3;
			if ((num4 * num3) + (float)num < 0.0f)
			{
				num4 = 0.0f;
			}
		}
	}
	if (y != 0.0f)
	{
		if (y > (float)num2)
		{
			num5 = -((float)num2 - y);
			num5 /= num3;
			if ((num5 * num3) + (float)num2 > (float)(num2 * 2))
			{
				num5 = 0.0f;
			}
		}
		if (y < (float)num2)
		{
			num5 = y - (float)num2;
			num5 /= num3;
			if ((num5 * num3) + (float)num2 < 0.0f)
			{
				num5 = 0.0f;
			}
		}
	}


	mouse_event(1U, (int)num4, (int)num5, NULL, NULL);
}