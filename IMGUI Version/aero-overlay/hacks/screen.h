#pragma once
#include "pch.h"

class Aimbot
{
public:
	bool aimbot = true, aimtype = true, boostenabled=false, booststatus = false;
	int boostkey = 86;
	float boostval = 1.0f, ipadview = 360.0f;
	int aimplayer = 0,aimkey = 88;
	float g_Height = 0, g_Width = 0,smooth = 15, aimsleep = 20;
	Vector2 aimtarget;
	Vector3 magicaim = { 0,0,0 };

	Aimbot();
	~Aimbot();
	void AimAtPos();
	void Boostplayer();
	void IpadV();
	void updateaim();
};

extern Aimbot* g_pAimbot;