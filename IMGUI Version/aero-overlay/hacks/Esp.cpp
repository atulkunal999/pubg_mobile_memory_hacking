#include "Esp.h"

Esp* g_pEsp = new Esp();

Esp::Esp(){}


Esp::~Esp(){}


int Esp::iGet(DWORD base){
	return g_pMemoryManager->iRead(base);
}
float Esp::fGet(DWORD base){
	return g_pMemoryManager->fRead(base);
}
DWORD Esp::dGet(DWORD base){
	return g_pMemoryManager->dRead(base);
}

DWORD ProcessId = 0;
KeInterface Driver = KeInterface("\\\\.\\sametha");;
DWORD myTeamID = 9999;
DWORD myplayeradd = 0;
DWORD controllerOffset = 96;
DWORD posOffset = 336;
DWORD velOffset = 416;
DWORD healthOffset = 2088;
DWORD nameOffset = 1528;
DWORD teamIDOffset = 1568;
DWORD statusOffset = 868;
DWORD poseOffset = 288;
DWORD energyoffset = 0x16B0;
bool isteamwriiten = false;

void Esp::init(){
	//viewWordBase = getViewWorld();
	if (!viewWordBase)
	{
		MessageBox(0, L"Viewworld not found, so Restart Driver and Game.", L"", 0);
		std::cout << "\nPlease Start Hack From Loader.\n";
		exit(1);
	}
	ProcessId = g_pMemoryManager->processId;
	Driver = g_pMemoryManager->Driver;
	if(ProcessId){
		std::cout << "\nVWBASE : " << termcolor::green << "FOUND" << std::dec << termcolor::reset << "\n";
	} else{
		std::cout << termcolor::red << "View World Not Found ! \n" << termcolor::reset;
		return;
	}
	uWorld = viewWordBase - 4514932;
	gNames = viewWordBase - 4551792;
	if (ProcessId && uWorld > 0 && gNames > 0)
	{
		std::cout << "Started Mode : " << termcolor::green << "DEBUG" << termcolor::reset << "\n";
	}
	if (Driver.hDriver == NULL)
	{
		std::cout << termcolor::red << "\nDriver Not found.\n" << termcolor::reset;
		Sleep(10000);
		exit(1);
	}
	enpos.x = 0;
	enpos.y = 0;
	enpos.z = 0;
}

template <class T> T get(DWORD address) {
	return Driver.ReadVirtualMemory<T>(ProcessId, address, sizeof(int));
}
void Esp::initmymagic()
{
	Vector2 Magic = GetMagicCoord(enpos, Driver.ReadVirtualMemory<Vector3>(ProcessId, uMyObject + posOffset, sizeof(int)));
	if (!HookMagic(Magic.x, Magic.y))
	{
		GetMagic();
		initMagic();
	}
}
std::string ReadString(DWORD adds, int size)
{
	char* temp = new char[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = Driver.ReadVirtualMemory<char>(ProcessId, adds + i, sizeof(char));
	}
	std::string ret = temp;
	delete temp;
	return ret;
}
std::string GetPlayerName(DWORD adds)
{
	char* temp = new char[34];
	for (int i = 0; i < 34; i++)
	{
		temp[i] = (unsigned char)Driver.ReadVirtualMemory<char>(ProcessId, adds + i * 2, sizeof(char));
	}
	std::string ret = temp;
	delete temp;
	return ret;
}
std::string GetEntityType(long gNames, long id)
{
	std::string result = "";
	DWORD gname = Driver.ReadVirtualMemory<DWORD>(ProcessId, gNames, sizeof(int));//Mem.ReadMemory<int>(gNames);
	if (id > 0 && id < 2000000)
	{
		DWORD page = id / 16384;
		DWORD index = id % 16384;
		DWORD secPartAddv = get<DWORD>(gname + page * 4);//Mem.ReadMemory<int>(gname + page * 4);
		if (secPartAddv > 0)
		{
			long nameAddv = get<DWORD>(secPartAddv + index * 4);//Mem.ReadMemory<int>(secPartAddv + index * 4);
			if (nameAddv > 0)
			{
				result = ReadString(nameAddv + 8, 32);
			}
		}
	}
	return result;
}
void Esp::Dump(DWORD adds,int size)
{
	for (int i = 0; i < size; i = i+4)
	{
		std::cout << i<<" : "<<Driver.ReadVirtualMemory<float>(ProcessId, adds + i, 4)<<std::endl;
	}
	system("cls");
}
void Esp::update(bool allitems,bool vichlesp,bool lboxshow,bool impitm)
{
	try {
		if (ProcessId)
		{
			vehicledata.clear();
			playerdata.clear();
			itemdata.clear();
			lootbox.clear();
			boomalert.clear();
			impitem.clear();

			uWorlds = Driver.ReadVirtualMemory<DWORD>(ProcessId, uWorld, sizeof(int));
			uLevel = Driver.ReadVirtualMemory<DWORD>(ProcessId, uWorlds + 32, sizeof(int));
			gameInstance = Driver.ReadVirtualMemory<DWORD>(ProcessId, uWorlds + 36, sizeof(int));
			playerController = Driver.ReadVirtualMemory<DWORD>(ProcessId, gameInstance + controllerOffset, sizeof(int));
			playerCarry = Driver.ReadVirtualMemory<DWORD>(ProcessId, playerController + 0x20, sizeof(int));
			uMyObject = Driver.ReadVirtualMemory<DWORD>(ProcessId, playerCarry + 792, sizeof(int));
			MyWorld = Driver.ReadVirtualMemory<DWORD>(ProcessId, uMyObject + 312, sizeof(int));
			entityEntry = Driver.ReadVirtualMemory<DWORD>(ProcessId, uLevel + 112, sizeof(int));
			entityCount = Driver.ReadVirtualMemory<DWORD>(ProcessId, uLevel + 116, sizeof(int));
			viewMatrixAddr = get<DWORD>(get<DWORD>(viewWordBase) + 32) + 512;
			vt = Driver.ReadVirtualMemory<D3DMatrix>(ProcessId, viewMatrixAddr, sizeof(D3DMatrix));
			if (gameInstance == 0)
			{
				vehicledatar = vehicledata;
				playerdatar = playerdata;
				itemdatar = itemdata;
				lootboxr = lootbox;
				boomalertr = boomalert;
				impitemr = impitem;
				return;
			}
			if (entityCount < 0) {
				entityCount = 0;
			}
			else if (entityCount > 1024) {
				entityCount = 1024;
			}
			for (int i = 0; i < entityCount; i++)
			{
				entityAddv = Driver.ReadVirtualMemory<DWORD>(ProcessId, entityEntry + i * 4, sizeof(int));//Mem.ReadMemory<int>(entityEntry + i * 4);
				entityStruct = Driver.ReadVirtualMemory<DWORD>(ProcessId, entityAddv + 16, sizeof(int));//Mem.ReadMemory<int>(entityAddv + 16);
				entityType = GetEntityType(gNames, entityStruct);

				if (Utilities::IsPlayer(entityType))
				{
					//std::cout << "found :"<<entityAddv<<"\n";
					playerWorld = get<DWORD>(entityAddv + 312);
					// read player info
					// dead player continue
					status = get<DWORD>(playerWorld + statusOffset);

					if (status == 6)
						continue;

					name = GetPlayerName(get<DWORD>(entityAddv + nameOffset));

					playerData pda;
					pda.Type = entityType;
					pda.Position = Utilities::Readvector3(Driver, playerWorld + posOffset, ProcessId);
					pda.Status = status;
					pda.Pose = get<int>(playerWorld + poseOffset);
					pda.IsRobot = Driver.ReadVirtualMemory<int>(ProcessId, entityAddv + 692, sizeof(int)) == 0 ? true : false;
					pda.Health = Driver.ReadVirtualMemory<float>(ProcessId, entityAddv + healthOffset, sizeof(float));
					pda.Name = name;
					pda.TeamID = get<int>(entityAddv + teamIDOffset);
					pda.energy = Driver.ReadVirtualMemory<float>(ProcessId, entityAddv + energyoffset, sizeof(float));
					pda.Address = entityAddv;
					pda.playerW1.itmid = get<int>(get<DWORD>(get<DWORD>(get<DWORD>(entityAddv + 0x12C) + 0x0) + 0x4E4) + 0xCC);
					pda.playerW2.itmid = get<int>(get<DWORD>(get<DWORD>(get<DWORD>(entityAddv + 0x12C) + 0x4) + 0x4E4) + 0xCC);
					pda.playerW1.displayName = Utilities::GetBoxItemByboth(pda.playerW1.itmid, "");
					pda.playerW2.displayName = Utilities::GetBoxItemByboth(pda.playerW2.itmid, "");
					pda.playerW1.ammoCur = get<int>(get<DWORD>(get<DWORD>(entityAddv + 0x12C) + 0x0) + 0x8C8);
					pda.playerW2.ammoCur = get<int>(get<DWORD>(get<DWORD>(entityAddv + 0x12C) + 0x4) + 0x8C8);
					pda.velocity = Utilities::Readvector3(Driver, playerWorld + velOffset, ProcessId);
					//std::cout << pda.velocity.x<<"\n"<<pda.velocity.y<<"\n"<<pda.velocity.z<<"\n";
					if (pda.Address == uMyObject)
					{
						myTeamID = pda.TeamID;
						myplayeradd = entityAddv;
						mypos = pda.Position;
						MyVelocity = pda.velocity;
						//(playerWorld + posOffset, 100);
						continue;
					}
					if (pda.TeamID == myTeamID)
					{
						myplayeradd = entityAddv;
						continue;
					}
					if (pda.TeamID == -1)
						continue;
					playerdata.push_back(pda);
					continue;
				}
				alert = Utilities::GetGrenadeType(entityType);
				if (alert.find("tatti") == std::string::npos)
				{
					/*FOR DRAWING BOOMBS*/
					tempb.displayName = alert;
					tempb.Position = Utilities::Readvector3(Driver, get<DWORD>(entityAddv + 312) + posOffset, ProcessId);
					boomalert.push_back(tempb);
				}
				if (Utilities::IsBox(entityType) && lboxshow)
				{
					lbox.Position = Utilities::Readvector3(Driver, get<DWORD>(entityAddv + 312) + posOffset, ProcessId);
					lootbox.push_back(lbox);
					int count = Driver.ReadVirtualMemory<int>(ProcessId, entityAddv + 0x440, sizeof(int));
					if (count > 32)
						count = 32;
					lbox.boxitem.clear();
					for (int t = 0; t < count; t++)
					{
						DWORD tem1 = Driver.ReadVirtualMemory<int>(ProcessId, entityAddv + 0x43C, sizeof(int));
						std::string bitm = Utilities::GetBoxItemByboth(Driver.ReadVirtualMemory<int>(ProcessId, tem1 + ((t * 48) + 0x4), sizeof(int)), "");
						if (bitm.find("tatti") == std::string::npos)
						{
							Itemb temo;
							bitm.append(" :- ").append(std::to_string(Driver.ReadVirtualMemory<int>(ProcessId, tem1 + ((t * 48) + 0x18), sizeof(int))));
							temo.Displayname = bitm;
							lbox.boxitem.push_back(temo);
						}
					}
					continue;
				}
				else
				{
					vehicle = Utilities::GetVehicleType(entityType);
					if (vehicle.find("tatti") == std::string::npos && vichlesp)
					{
						vhi.displayName = vehicle;
						vhi.Position = Utilities::Readvector3(Driver, get<DWORD>(entityAddv + 312) + posOffset, ProcessId);
						vhi.picid = Utilities::GetNameByIDSprite(entityStruct, entityType);
						vehicledata.push_back(vhi);
					}
					else
					{
						imptm = Utilities::GetImpItem(entityStruct, entityType);
						if (imptm.find("tatti") == std::string::npos && impitm)
						{
							itm.displayName = imptm;
							itm.Position = Utilities::Readvector3(Driver, get<DWORD>(entityAddv + 312) + posOffset, ProcessId);
							itm.picid = Utilities::GetNameByIDSprite(entityStruct, entityType);
							impitem.push_back(itm);
							continue;
						}
						boxitem = Utilities::GetBoxItemByboth(entityStruct, entityType);
						if (boxitem.find("tatti") == std::string::npos && allitems)
						{
							itm.displayName = boxitem;
							itm.Position = Utilities::Readvector3(Driver, get<DWORD>(entityAddv + 312) + posOffset, ProcessId);
							itm.picid = Utilities::GetNameByIDSprite(entityStruct, entityType);
							itemdata.push_back(itm);
						}
					}

				}


			}
			vehicledatar = vehicledata;
			playerdatar = playerdata;
			itemdatar = itemdata;
			lootboxr = lootbox;
			boomalertr = boomalert;
			impitemr = impitem;

			//initmymagic();
			//g_pDataPIL->update(playerdata, itemdata, vehicledata, lootbox, boomalert, impitem);
		}
	}
	catch(...){
		//lol
	}
}
DWORD Esp::getViewWorld(){
	ProcessId = g_pMemoryManager->processId;
	BYTE pattern[] = { 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01 };

	std::vector<DWORD_PTR> foundedBases;

	g_pMemoryManager->search(pattern, sizeof(pattern), 0x20000000, 0x30000000, false, 0, foundedBases);

	for (int i = 0; i < foundedBases.size(); i++) {
		DWORD cand = foundedBases[i] - 0x20;
		DWORD eng = dGet(cand) + 0x20;
		DWORD tmp = dGet(eng) + 0x200;
		float v1, v2, v3, v4;
		v1 = fGet(tmp + 0x8);
		v2 = fGet(tmp + 0x18);
		v3 = fGet(tmp + 0x28);
		v4 = fGet(tmp + 0x38);
		if (v1 == 0 && v2 == 0 && v3 == 0 && v4 >= 3) {
			foundedBases.clear();
			return cand;
		}
	}

	foundedBases.clear();
	g_pMemoryManager->search(pattern, sizeof(pattern), 0x30000000, 0x40000000, false, 0, foundedBases);

	for (int i = 0; i < foundedBases.size(); i++) {
		DWORD cand = foundedBases[i] - 0x20;
		DWORD eng = dGet(cand) + 0x20;
		DWORD tmp = dGet(eng) + 0x200;
		float v1, v2, v3, v4;
		v1 = fGet(tmp + 0x8);
		v2 = fGet(tmp + 0x18);
		v3 = fGet(tmp + 0x28);
		v4 = fGet(tmp + 0x38);
		if (v1 == 0 && v2 == 0 && v3 == 0 && v4 >= 3) {
			foundedBases.clear();
			return cand;
		}
	}
	foundedBases.clear();
	return 0;

}

void Esp::GetModuleBaseAddress(DWORD procId, char * modName)
{
	return;
}
void Esp::GetNorecoil() {
	//01 0a 30 ee 06 00 a0
	BYTE pattern[] = { 0x01 ,0x0A ,0x30 ,0xEE ,0x06 ,0x00 ,0xA0};
	std::vector<DWORD_PTR> tmp;
	std::vector<DWORD> RecoilList;
	g_pMemoryManager->search(pattern, sizeof(pattern), modBaseAddr, modBaseAddr + modSize, FALSE, 0, tmp);
	for (int i = 0; i < tmp.size(); i++) {
			RecoilList.push_back(tmp[i]);
	}
	NoRecoilList = RecoilList;
}
void Esp::ipadview()
{
	BYTE pattern[] = { 0x7F, 0x45, 0x4C, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x28, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x24, 0xF6, 0x88, 0x06, 0x00, 0x02, 0x00, 0x05, 0x34, 0x00, 0x20, 0x00, 0x0A, 0x00, 0x28, 0x00, 0x1A, 0x00, 0x19, 0x00, 0x06, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x74, 0x01, 0x00, 0x00, 0x74, 0x01, 0x00, 0x00 };
	std::vector<DWORD_PTR> tmp;
	std::vector<DWORD> MagicList;
	g_pMemoryManager->search(pattern, sizeof(pattern), 0x80000000, 0x90000000, FALSE, 0, tmp);
	
	if (tmp.size() > 0)
	{
		//360
		ipad = tmp[0] + 55410224;
	}
}
void Esp::GetMagic() {
	//66 0F 6E ?? A8 00 00 00 66 0F 7E ?? 28
	BYTE pattern[] = { 0x66,0x0F,0x7E,'?',0x28,0x02,0x00,0x00,0xC7,0x45 };
	std::vector<DWORD_PTR> tmp;
	std::vector<DWORD> MagicList;
	g_pMemoryManager->search(pattern, sizeof(pattern), 0x15000000, 0x25000000, FALSE, 0, tmp);
	MagicBulletList.clear();

	for (int i = 0; i < tmp.size(); i++) {
		if (Driver.ReadVirtualMemory<BYTE>(ProcessId,tmp[i] + 0xC,1) == 0x37)
		{
			MagicList.push_back(tmp[i]);
		}
	}
	MagicBulletList = MagicList;
}
LPVOID AllocateMemory(int size)
{
	return VirtualAllocEx(g_pMemoryManager->processHandle, NULL, size, 0x1000, 0x04);
}
void Esp::HookCall(DWORD HookAddr, DWORD CallAddr)
{
	unsigned char Shell[7] = { 0xE8,0x00,0x00,0x00,0x00,0x90,0x90 };
	*(uintptr_t*)(Shell + 1) = (uintptr_t)CallAddr - HookAddr - 5;
	for (int i = 0; i < 7; i++)
		Driver.WriteVirtualMemory<BYTE>(ProcessId, CallAddr+i, Shell[i], 1);
	//Driver.WriteVirtualMemory<void*>(ProcessId,HookAddr, (void*)Call, sizeof(Call));
}
void Esp::initMagic()
{
	if (MagicBulletList.size() == 0)
		return;
	DWORD addv = MagicBulletList[0];
	if (MagicBulletHook == NULL || MagicBulletHook == 0) 
	{
		MagicBulletHook = (uintptr_t)VirtualAllocEx(g_pMemoryManager->processHandle, 0, 500, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		//MagicBulletHook = (uintptr_t)Driver.virtual_alloc(g_pMemoryManager->processId, 500, MEM_COMMIT, PAGE_EXECUTE_READWRITE,0);
	}
	std::cout << MagicBulletHook;
	ShellCode[0x2F] = 0x14; //this need updated for every game version
	ShellCode[0x49] = 0xC0; //this need updated for every game version
	*(uintptr_t*)(ShellCode + 0x2) = (uintptr_t)MagicBulletHook + 0x70;
	*(uintptr_t*)(ShellCode + 0xA) = (uintptr_t)MagicBulletHook + 0x64;
	*(uintptr_t*)(ShellCode + 0x15) = (uintptr_t)MagicBulletHook + 0x68;
	*(uintptr_t*)(ShellCode + 0x20) = (uintptr_t)MagicBulletHook + 0x6C;
	*(uintptr_t*)(ShellCode + 0x25) = (uintptr_t)MagicBulletHook + 0x64;
	*(uintptr_t*)(ShellCode + 0x2B) = (uintptr_t)MagicBulletHook + 0x68;
	*(uintptr_t*)(ShellCode + 0x37) = (uintptr_t)MagicBulletHook + 0x70;
	*(uintptr_t*)(ShellCode + 0x45) = (uintptr_t)MagicBulletHook + 0x6C;
	for (int i = 0; i < 96; i++)
		Driver.WriteVirtualMemory<BYTE>(ProcessId, MagicBulletHook + i, ShellCode[i], 1);
	Driver.RVM(ProcessId,addv + 0x8, *realCode, 7);
	for (int i = 0; i < 7; i++)
		Driver.WriteVirtualMemory<BYTE>(ProcessId, MagicBulletHook + 0x3B + i, realCode[i], 1);
	
}
void Esp::initBoost()
{
	BYTE pattern[] = { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80 ,0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00 };

	std::vector<DWORD_PTR> foundedBases;

	g_pMemoryManager->search(pattern, sizeof(pattern), 0x40000000, 0x70000000, false, 0, foundedBases);

	if(foundedBases.size() != 0)
	{
		int temp = foundedBases[0] + 0x10;
		boostAddv = temp;
		boostactivated = false;
	}
}
bool Esp::areEqual(BYTE cmp1[], BYTE cmp2[],int size)
{
	try {
		for (int i = 0; i < size; i++)
		{
			if (cmp1[i] != cmp2[i])
			{
				return false;
			}
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}
bool Hooked(uintptr_t addr)//check if hooked
{
	unsigned char tmp[7];
	Driver.RVM(ProcessId,addr + 0x8, *tmp, 7);
	if (tmp[0] == 0xE8 && tmp[5] == 0x90 && tmp[6] == 0x90)
		return true;
	return false;
}
bool Esp::HookMagic(float x, float y) {
	if (MagicBulletList.size() == 0)
		return false;
	BYTE tmp[7];
	for (int i=0;i<MagicBulletList.size();i++)
	{
		DWORD addv = MagicBulletList[i];
		if (Driver.ReadVirtualMemory<BYTE>(ProcessId,addv + 0xC,1) != 0x37 && !Hooked(addv))
			return false;
		BYTE tmp[7];
		Driver.RVM(ProcessId,addv + 0x8, *tmp, 7);
		if (areEqual(tmp, realCode, 7))
		{
			HookCall(addv + 0x8, MagicBulletHook);
		}
	}
	Driver.WriteVirtualMemory<float>(ProcessId, MagicBulletHook + 83, y, sizeof(float));
	Driver.WriteVirtualMemory<float>(ProcessId, MagicBulletHook + 90, x, sizeof(float));
	return true;
}
Vector2 Esp::GetMagicCoord(Vector3 aim, Vector3 myPos)
{
	float xDif = aim.x - myPos.x;
	float yDif = aim.y - myPos.y;
	float zDif = aim.z - myPos.z;
	Vector2 coord;
	coord.x = std::atan2(yDif, xDif) * 180.0f / 3.1415926535897;
	coord.y = std::atan2(zDif, std::sqrt(xDif * xDif + yDif * yDif)) * 180.0f / 3.1415926535897;
	return coord;
}