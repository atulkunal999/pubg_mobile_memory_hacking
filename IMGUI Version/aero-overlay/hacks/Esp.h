#pragma once
#include "pch.h"
class Esp{
public:
	Esp();
	~Esp();

	DWORD viewWordBase;
	DWORD uWorld;
	DWORD gNames;
	BYTE ShellCode[96] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, //mov DWORD PTR ds:0x0,edx
	0x8B, 0x55, 0x34, //mov edx,DWORD PTR [ebp+0x34]
	0xA2, 0x00, 0x00, 0x00, 0x00, //mov ds:0x0,al
	0x8A, 0x82, 0xE0, 0xFD, 0xFF, 0xFF, //mov al,BYTE PTR [edx-0x220]
	0xA2, 0x00, 0x00, 0x00, 0x00, //mov ds:0x0,al
	0x8A, 0x82, 0xE1, 0xFD, 0xFF, 0xFF, //mov al,BYTE PTR [edx-0x21f]
	0xA2, 0x00, 0x00, 0x00, 0x00, //mov ds:0x0,al
	0xA0, 0x00, 0x00, 0x00, 0x00, //mov al,ds:0x0
	0x81, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp DWORD PTR ds:0x0,0x0
	0x74, 0x0E, //je 0x43
	0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, //mov edx,DWORD PTR ds:0x0
	0xC7, 0x45, 0x68, 0x00, 0x00, 0x00, 0x00, //mov DWORD PTR [ebp+0x68],0x0
	0xC3, //ret
	0x81, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp DWORD PTR ds:0x0,0x0
	0x74, 0x02, //je 0x51
	0xEB, 0xE4, //jmp 0x35
	0xC7, 0x02, 0x00, 0x00, 0x00, 0x00, //mov DWORD PTR [edx],0x0
	0xC7, 0x42, 0x04, 0x00, 0x00, 0x00, 0x00, //mov DWORD PTR [edx+0x4],0x0
	0xEB, 0xD5 //jmp 0x35
	};
	BYTE realCode[7];
	DWORD MagicBulletHook = NULL;
	uintptr_t modBaseAddr = 0, modSize = 0;
	DWORD boostAddv;
	bool boostactivated = false;
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
	DWORD uWorlds, uLevel, gameInstance, playerController, playerCarry, uMyObject, MyWorld, entityEntry, entityCount, viewMatrixAddr;
	int status;
	DWORD entityAddv, entityStruct, playerWorld;
	std::string imptm, entityType, name, alert, vehicle,boxitem;
	Vector3 enpos,mypos, MyVelocity;
	int iGet(DWORD base);
	float fGet(DWORD base);
	DWORD dGet(DWORD base);
	DWORD ipad = 0;
	void ipadview();
	void initmymagic();
	void HookCall(DWORD HookAddr, DWORD CallAddr);
	bool areEqual(BYTE cmp1[], BYTE cmp2[],int size);
	bool HookMagic(float x, float y);
	void initBoost();
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