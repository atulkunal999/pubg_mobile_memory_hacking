#pragma once
#include "pch.h"
#include "Utilities.h"
class Esp{
public:
	Esp();
	~Esp();

	DWORD viewWordBase;
	DWORD uWorld;
	DWORD gNames;
	BYTE ShellCode[96] = {
	0x89 ,0x15 ,0x70 ,0x00 ,0xDB ,0x3A ,0x8B ,0x55 ,0x34 ,0xA2 ,0x64 ,0x00 ,0xDB ,0x3A ,0x8A ,0x82 ,0xE0 ,0xFD ,0xFF ,0xFF,
	0xA2 ,0x68 ,0x00 ,0xDB ,0x3A ,0x8A ,0x82 ,0xE1 ,0xFD ,0xFF ,0xFF ,0xA2 ,0x6C ,0x00 ,0xDB ,0x3A ,0xA0 ,0x64 ,0x00 ,0xDB,
	0x3A ,0x81 ,0x3D ,0x68 ,0x00 ,0xDB ,0x3A ,0x54 ,0x00 ,0x00 ,0x00 ,0x74 ,0x0E ,0x8B ,0x15 ,0x70 ,0x00 ,0xDB ,0x3A ,0xC7,
	0x45 ,0x68 ,0x18 ,0xC0 ,0xF0 ,0x29 ,0xC3 ,0x81 ,0x3D ,0x6C ,0x00 ,0xDB ,0x3A ,0x05 ,0x00 ,0x00 ,0x00 ,0x74 ,0x02 ,0xEB,
	0xE4 ,0xC7 ,0x02 ,0x00 ,0x00 ,0x00 ,0x00 ,0xC7 ,0x42 ,0x04 ,0x00 ,0x00 ,0x00 ,0x00 ,0xEB ,0xD5
	};
	BYTE orginByte[7];
	DWORD MagicBulletHook;
	uintptr_t modBaseAddr = 0, modSize = 0;

	std::vector<playerData> playerdata,playerdatar;
	std::vector<Item> itemdata, itemdatar;
	std::vector<Vehicle> vehicledata, vehicledatar;
	std::vector<Lootbox> lootbox, lootboxr;
	std::vector<Item> boomalert, boomalertr;
	std::vector<Item> impitem, impitemr;
	std::vector<DWORD> MagicBulletList,NoRecoilList;
	D3DMatrix vt;
	Item tempb,itm;
	Vehicle vhi;
	Lootbox lbox;
	playerData pda;
	DWORD uWorlds, uLevel, gameInstance, playerController, playerCarry, uMyObject, MyWorld, entityEntry, entityCount, viewMatrixAddr;
	int status;
	DWORD entityAddv, entityStruct, playerWorld;
	std::string imptm, entityType, name, alert, vehicle,boxitem;
	Vector3 enpos,mypos;
	int iGet(DWORD base);
	float fGet(DWORD base);
	DWORD dGet(DWORD base);

	void initmymagic();
	void HookCall(DWORD HookAddr, DWORD CallAddr);
	bool areEqual(BYTE cmp1[], BYTE cmp2[]);
	bool HookMagic(float x, float y);
	void GetMagic();
	void Dump(DWORD adds,int size);
	void update(bool allitems = true, bool vichlesp = true,bool lboxshow = true,bool impitm = true);
	void init();
	Vector2 GetMagicCoord(Vector3 aim, Vector3 myPos);
	void GetModuleBaseAddress(DWORD procId, char * modName);
	void initMagic();
	void GetNorecoil();
	DWORD getViewWorld();

};


extern Esp* g_pEsp;