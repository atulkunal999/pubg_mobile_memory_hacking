#include "Utilities.h"


bool Utilities::IsPlayer(std::string str)
{
   if (str.find("BP_PlayerPawn") != std::string::npos)
   {
     return true;
   }
    return false;
}
Vector3 Utilities::Readvector3(KeInterface drv, DWORD adds, DWORD ProcessId)
{
	Vector3 temp;
	temp.x = drv.ReadVirtualMemory<float>(ProcessId, adds, sizeof(float));
	temp.y = drv.ReadVirtualMemory<float>(ProcessId, adds + 4, sizeof(float));
	temp.z = drv.ReadVirtualMemory<float>(ProcessId, adds + 8, sizeof(float));
	return temp;
}
std::string Utilities::GetVehicleType(std::string classname)
{
    if (classname.find("BRDM") != std::string::npos)
        return "BRDM";
    if (classname.find("Scooter") != std::string::npos)
        return "Scooter";
    if (classname.find("Motorcycle") != std::string::npos)
        return "Motorcycle";
    if (classname.find("MotorcycleCart") != std::string::npos)
        return "MotorcycleCart";
    if (classname.find("Snowmobile") != std::string::npos)
        return "Snowmobile";
    if (classname.find("Tuk") != std::string::npos)
        return "Tuk";
    if (classname.find("Buggy") != std::string::npos)
        return "Buggy";
    if (classname.find("open") != std::string::npos)
        return "Sports";
    if (classname.find("close") != std::string::npos)
        return "Sports";
    if (classname.find("Dacia") != std::string::npos)
        return "Dacia";
    if (classname.find("Rony") != std::string::npos)
        return "Rony";
    if (classname.find("UAZ") != std::string::npos)
        return "UAZ";
    if (classname.find("MiniBus") != std::string::npos)
        return "MiniBus";
    if (classname.find("PG117") != std::string::npos)
        return "PG117";
    if (classname.find("AquaRail") != std::string::npos)
        return "AquaRail";
    if (classname.find("BP_AirDropPlane_C") != std::string::npos)
        return "BP_AirDropPlane";
    return "tatti";
}
bool Utilities::IsBox(std::string classname)
{
    if (classname.find("PlayerDeadInventoryBox") != std::string::npos || classname.find("PickUpListWrapperActor") != std::string::npos)
        return true;
    return false;
}
int Utilities::GetNameByIDSprite(DWORD id,std::string classname)
{
    if (id == 601003 || classname.find("Injection_Pickup") != std::string::npos)
        return 64;
    if (id == 103001)
        return 2;
    if (classname.find("LadaNiva_01") != std::string::npos)
        return 3;
    if (classname.find("BP_Rifle_M16A4_Wrapper") != std::string::npos)
        return 4;
    if (classname.find("BP_Sniper_M24_Wrapper") != std::string::npos)
        return 5;
    if (id == 105001 || classname.find("BP_Other_M249_Wrapper") != std::string::npos)
        return 6;
    if (id == 101004 || classname.find("BP_Rifle_M416_Wrapper") != std::string::npos)
        return 7;
    if (id == 101008 || classname.find("BP_Rifle_M762_Wrapper_C") != std::string::npos)
        return 8;
    if (id == 0 && classname.find("VH_MiniBus_01_C") != std::string::npos)
        return 9;
    if (id == 103006 || classname.find("BP_Sniper_Mini14_Wrapper_C") != std::string::npos)
        return 10;
    if (classname.find("open") != std::string::npos)
        return 11;
    if (classname.find("close") != std::string::npos)
        return 12;
    if (id == 103007 || classname.find("BP_WEP_Mk14_Pickup_C") != std::string::npos)
        return 13;
    if (id == 101009 || classname.find("BP_Rifle_Mk47_Wrapper_C") != std::string::npos)
        return 14;
    if (classname.find("BP_Grenade_Burn_C") != std::string::npos)
        return 15;
    if (classname.find("MotorcycleCart") != std::string::npos)
        return 17;
    if (classname.find("Motorcycle") != std::string::npos)
        return 16;
   /* if (id == 601003) // player image
        return 18;*/
    if (id == 601003 || classname.find("Pills_Pickup_C") != std::string::npos)
        return 19;
    if (id == 108004 || classname.find("BP_WEP_Pan_Pickup_C") != std::string::npos)
        return 20;
    if (id == 0 && classname.find("Rony_C") != std::string::npos)
        return 21;
    if (id == 0 && classname.find("BP_AirDropPlane") != std::string::npos)
        return 22;
    if (id == 103010 || classname.find("BP_Sniper_QBU_Wrapper_C") != std::string::npos)
        return 23;
    if (id == 101007 || classname.find("BP_Rifle_QBZ_Wrapper_C") != std::string::npos)
        return 24;
    if (id == 0 && classname.find("Rony") != std::string::npos)
        return 25;
    if (id == 104003 || classname.find("BP_ShotGun_S12K_Wrapper_C") != std::string::npos)
        return 26;
    if (id == 104002 || classname.find("BP_ShotGun_S1897_Wrapper_C") != std::string::npos)
        return 27;
    if (id == 101003 || classname.find("BP_Rifle_SCAR_Wrapper_C") != std::string::npos)
        return 28;
    if (classname.find("Scooter") != std::string::npos)
        return 29;
    if (id == 103004 || classname.find("BP_Sniper_SKS_Wrapper_C") != std::string::npos)
        return 30;
    if (id == 103009 || classname.find("BP_Sniper_SLR_Wrapper_C") != std::string::npos)
        return 31;
    if (classname.find("BP_Grenade_Smoke_C") != std::string::npos)
        return 32;
    if (classname.find("Snowmobile") != std::string::npos)
        return 33;
    if (id == 0 && classname.find("Snowbike") != std::string::npos)
        return 34;
    if (classname.find("BP_Grenade_tun_C") != std::string::npos)
        return 35;
    if (id == 102004 || classname.find("BP_MachineGun_TommyGun_Wrapper_C") != std::string::npos)
        return 36;
    if (classname.find("Tuk") != std::string::npos)
        return 37;
    if (classname.find("UAZ") != std::string::npos)
        return 38;
    if (id == 102003 || classname.find("BP_MachineGun_Vector_Wrapper_C") != std::string::npos)
        return 39;
    if (id == 503002 || classname.find("PickUp_BP_Armor_Lv2_C") != std::string::npos)
        return 40;
    if (id == 503003 || classname.find("PickUp_BP_Armor_Lv3_C") != std::string::npos)
        return 41;
    if (classname.find("BP_AirDropBox_C") != std::string::npos)
        return 42;
    if (id == 101001 || classname.find("BP_Rifle_AKM_Wrapper_C") != std::string::npos)
        return 43;
    if (classname.find("AquaRail") != std::string::npos)
        return 44;
    if (id == 101006 || classname.find("BP_Rifle_AUG_Wrapper_C") != std::string::npos)
        return 45;
    if (id == 103003 || classname.find("BP_Sniper_AWM_Wrapper_C") != std::string::npos)
        return 46;
    if (id == 501005 || classname.find("PickUp_BP_Bag_Lv2") != std::string::npos)
        return 47;
    if (id == 501006 || classname.find("PickUp_BP_Bag_Lv3") != std::string::npos)
        return 48;
    if (id == 601004 || classname.find("Bandage_Pickup_C") != std::string::npos)
        return 62;
    if (classname.find("PG117") != std::string::npos)
        return 50;
    if (classname.find("BRDM") != std::string::npos)
        return 51;
    if (classname.find("Buggy") != std::string::npos)
        return 52;
    if (classname.find("ARROW") != std::string::npos)
        return 53;
    if (classname.find("Dacia") != std::string::npos)
        return 54;
    if (id == 104004 || classname.find("BP_ShotGun_DP12_Wrapper_C") != std::string::npos)
        return 55;
    if (id == 105002 || classname.find("BP_Other_DP28_Wrapper_C") != std::string::npos)
        return 56;
    if (id == 601001 || classname.find("Drink_Pickup_C") != std::string::npos)
        return 63;
    if (id == 601005 || classname.find("Firstaid_Pickup_C") != std::string::npos)
        return 58;
    if (id == 308001 || classname.find("BP_Ammo_Flare_Pickup_C") != std::string::npos)
        return 59;
    if (classname.find("BP_Grenade_tun_C") != std::string::npos)
        return 60;
    if (id == 101010 || classname.find("BP_Rifle_G36_Wrapper_C") != std::string::npos)
        return 61;
    /*if (id == 601003) //bandages
        return 62;
    if (id == 601003) // energy drink
        return 63;
    if (id == 601003) // painkiller
        return 64;*/
    if (id == 101005 || classname.find("BP_Rifle_Groza_Wrapper_C") != std::string::npos)
        return 65;
    if (id == 502002 || classname.find("PickUp_BP_Helmet_Lv2") != std::string::npos)
        return 66;
    if (id == 502003 || classname.find("PickUp_BP_Helmet_Lv3") != std::string::npos)
        return 67;
    if (classname.find("P_BOT") != std::string::npos)
        return 68;
    if (classname.find("P_PLAYER") != std::string::npos)
        return 69;
    else
        return -1;
}
std::string Utilities::GetGrenadeType(std::string classname)
{
    if (classname.find("BP_Grenade_Smoke_C") != std::string::npos)
        return "[ALERT] !Smoke Granade";
    if (classname.find("BP_Grenade_Burn_C") != std::string::npos)
        return "[ALERT] !Burn Granade";
    if (classname.find("BP_Grenade_tun_C") != std::string::npos)
        return "[ALERT] !Flash Granade";
    if (classname.find("BP_Grenade_Shoulei_C") != std::string::npos)
        return "[ALERT] !Frag Granade";
    return "tatti";
}
std::string Utilities::GetImpItem(DWORD code,std::string classname)
{
    if(code == 103002 || classname.find("BP_Sniper_M24_Wrapper_C") != std::string::npos)
        return "M24";
    if (code == 103001 || classname.find("BP_Sniper_Kar98k_Wrapper_C") != std::string::npos)
        return "Kar98k";
    if (code == 101004 || classname.find("BP_Rifle_M416_Wrapper_C") != std::string::npos)
        return "M416";
    if (code == 101001 || classname.find("BP_Rifle_AKM_Wrapper_C") != std::string::npos)
        return "AKM";
    if (code == 302001 || classname.find("BP_Ammo_762mm_Pickup_C") != std::string::npos)
        return "7.62";
    if (code == 303001 || classname.find("BP_Ammo_556mm_Pickup_C") != std::string::npos)
        return "5.56";
    if (code == 201007 || classname.find("BP_QK_Sniper_Suppressor_Pickup_C") != std::string::npos)
        return "Suppressor Sniper";
    if (code == 201011 || classname.find("BP_QK_Large_Suppressor_Pickup_C") != std::string::npos)
        return "Suppressor AR";
    if (code == 203014 || classname.find("BP_MZJ_3X_Pickup_C") != std::string::npos)
        return "3X";
    if (code == 203015 || classname.find("BP_MZJ_6X_Pickup_C") != std::string::npos)
        return "6x";
    if (code == 203004 || classname.find("BP_MZJ_4X_Pickup_C") != std::string::npos)
        return "4x";
    if (code == 501006 || classname.find("PickUp_BP_Bag_Lv3_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 501006 || classname.find("PickUp_BP_Bag_Lv3_B_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 501003 || classname.find("PickUp_BP_Bag_Lv3_Inbox_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 503003 || classname.find("PickUp_BP_Armor_Lv3_C") != std::string::npos)
        return "Armour Lv.3";
    if (code == 503003 || classname.find("PickUp_BP_Armor_Lv3_B_C") != std::string::npos)
        return "Armour Lv.3";
    if (code == 308001 || classname.find("BP_Ammo_Flare_Pickup_C") != std::string::npos)
        return "Flaregun";
    if (code == 502003 || classname.find("PickUp_BP_Helmet_Lv3_C") != std::string::npos)
        return "Helmet Lv.3";
    if (code == 502003 || classname.find("PickUp_BP_Helmet_Lv3_B_C") != std::string::npos)
        return "Helmet Lv.3";
    if (code == 601003 || classname.find("Pills_Pickup_C") != std::string::npos)
        return "Painkiller";
    if (code == 601002 || classname.find("Injection_Pickup_C") != std::string::npos)
        return "Adrenaline Syringe";
    if (code == 601001 || classname.find("Drink_Pickup_C") != std::string::npos)
        return "Energy Drink";
    if (code == 601005 || classname.find("Firstaid_Pickup_C") != std::string::npos)
        return "FirstaidKit";
    if (code == 203005 || classname.find("BP_MZJ_8X_Pickup_C") != std::string::npos)
        return "8x";
    return "tatti";
}
std::string Utilities::GetBoxItemByboth(DWORD code, std::string classname)
{
    if (code == 103003 || classname.find("BP_Sniper_AWM_Wrapper_C") != std::string::npos)
        return "AWM";
    if (code == 103010 || classname.find("BP_Sniper_QBU_Wrapper_C") != std::string::npos)
        return "QBU";
    if (code == 103009 || classname.find("BP_Sniper_SLR_Wrapper_C") != std::string::npos)
        return "SLR";
    if (code == 103004 || classname.find("BP_Sniper_SKS_Wrapper_C") != std::string::npos)
        return "SKS";
    if (code == 103006 || classname.find("BP_Sniper_Mini14_Wrapper_C") != std::string::npos)
        return "Mini14";
    if (code == 103002 || classname.find("BP_Sniper_M24_Wrapper_C") != std::string::npos)
        return "M24";
    if (code == 103001 || classname.find("BP_Sniper_Kar98k_Wrapper_C") != std::string::npos)
        return "Kar98k";
    if (code == 103005 || classname.find("BP_Sniper_VSS_Wrapper_C") != std::string::npos)
        return "VSS";
    if (code == 103008 || classname.find("BP_Sniper_Win94_Wrapper_C") != std::string::npos)
        return "Win94";
    if (code == 101008 || classname.find("BP_Rifle_M762_Wrapper_C") != std::string::npos)
        return "M762";
    if (code == 101003 || classname.find("BP_Rifle_SCAR_Wrapper_C") != std::string::npos)
        return "SCAR-L";
    if (code == 101004 || classname.find("BP_Rifle_M416_Wrapper_C") != std::string::npos)
        return "M416";
    if (code == 101002 || classname.find("BP_Rifle_M16A4_Wrapper_C") != std::string::npos)
        return "M16A-4";
    if (code == 101009 || classname.find("BP_Rifle_Mk47_Wrapper_C") != std::string::npos)
        return "Mk47 Mutant";
    if (code == 101010 || classname.find("BP_Rifle_G36_Wrapper_C") != std::string::npos)
        return "G36C";
    if (code == 101007 || classname.find("BP_Rifle_QBZ_Wrapper_C") != std::string::npos)
        return "QBZ";
    if (code == 101001 || classname.find("BP_Rifle_AKM_Wrapper_C") != std::string::npos)
        return "AKM";
    if (code == 101005 || classname.find("BP_Rifle_Groza_Wrapper_C") != std::string::npos)
        return "Groza";
    if (code == 101006 || classname.find("BP_Rifle_AUG_Wrapper_C") != std::string::npos)
        return "AUG_A3";
    if (code == 104003 || classname.find("BP_ShotGun_S12K_Wrapper_C") != std::string::npos)
        return "S12K";
    if (code == 104004 || classname.find("BP_ShotGun_DP12_Wrapper_C") != std::string::npos)
        return "DBS";
    if (code == 104001 || classname.find("BP_ShotGun_S686_Wrapper_C") != std::string::npos)
        return "S686";
    if (code == 104002 || classname.find("BP_ShotGun_S1897_Wrapper_C") != std::string::npos)
        return "S1897";
    if (code == 106006 || classname.find("BP_ShotGun_SawedOff_Wrapper_C") != std::string::npos)
        return "SawedOff";
    if (code == 102005 || classname.find("BP_MachineGun_PP19_Wrapper_C") != std::string::npos)
        return "PP19 Bizon";
    if (code == 102004 || classname.find("BP_MachineGun_TommyGun_Wrapper_C") != std::string::npos)
        return "TommyGun";
    if (code == 102007 || classname.find("BP_MachineGun_MP5K_Wrapper_C") != std::string::npos)
        return "MP5K";
    if (code == 102002 || classname.find("BP_MachineGun_UMP9_Wrapper_C") != std::string::npos)
        return "UMP9";
    if (code == 102003 || classname.find("BP_MachineGun_Vector_Wrapper_C") != std::string::npos)
        return "Vector";
    if (code == 102001 || classname.find("BP_MachineGun_Uzi_Wrapper_C") != std::string::npos)
        return "Uzi";
    if (code == 106003 || classname.find("BP_Pistol_R1895_Wrapper_C") != std::string::npos)
        return "R1895";
    if (code == 106008 || classname.find("BP_Pistol_Vz61_Wrapper_C") != std::string::npos)
        return "Vz61";
    if (code == 106001 || classname.find("BP_Pistol_P92_Wrapper_C") != std::string::npos)
        return "P92";
    if (code == 106004 || classname.find("BP_Pistol_P18C_Wrapper_C") != std::string::npos)
        return "P18C";
    if (code == 106005 || classname.find("BP_Pistol_R45_Wrapper_C") != std::string::npos)
        return "R45";
    if (code == 106002 || classname.find("BP_Pistol_P1911_Wrapper_C") != std::string::npos)
        return "P1911";
    if (code == 106010 || classname.find("BP_Pistol_DesertEagle_Wrapper_C") != std::string::npos)
        return "DesertEagle";
    if (code == 108003 || classname.find("BP_WEP_Sickle_Pickup_C") != std::string::npos)
        return "Sickle";
    if (code == 108001 || classname.find("BP_WEP_Machete_Pickup_C") != std::string::npos)
        return "Machete";
    if (code == 107001 || classname.find("BP_WEP_Cowbar_Pickup_C") != std::string::npos)
        return "Cross Bow";
    if (code == 108004 || classname.find("BP_WEP_Pan_Pickup_C") != std::string::npos)
        return "Pan";
    if (code == 103007 || classname.find("BP_WEP_Mk14_Pickup_C") != std::string::npos)
        return "Mk14";
    if (code == 302001 || classname.find("BP_Ammo_762mm_Pickup_C") != std::string::npos)
        return "7.62";
    if (code == 305001 || classname.find("BP_Ammo_45ACP_Pickup_C") != std::string::npos)
        return "45ACP";
    if (code == 303001 || classname.find("BP_Ammo_556mm_Pickup_C") != std::string::npos)
        return "5.56";
    if (code == 301001 || classname.find("BP_Ammo_9mm_Pickup_C") != std::string::npos)
        return "9mm";
    if (code == 306001 || classname.find("BP_Ammo_300Magnum_Pickup_C") != std::string::npos)
        return "300Magnum";
    if (code == 304001 || classname.find("BP_Ammo_12Guage_Pickup_C") != std::string::npos)
        return "12Guage";
    if (code == 307001 || classname.find("BP_Ammo_Bolt_Pickup_C") != std::string::npos)
        return "Arrows";
    if (code == 201004 || classname.find("BP_QK_Mid_FlashHider_Pickup_C") != std::string::npos)
        return "Alev Gizl (Haf. Mak..)";
    if (code == 201010 || classname.find("BP_QK_Large_FlashHider_Pickup_C") != std::string::npos)
        return "Alev Gizl (Oto.)";
    if (code == 201009 || classname.find("BP_QK_Large_Compensator_Pickup_C") != std::string::npos)
        return "Otomatik Kompensator";
    if (code == 201004 || classname.find("BP_QK_Mid_Compensator_Pickup_C") != std::string::npos)
        return "Kompensator (Haf.Mak.)";
    if (code == 205002 || classname.find("BP_QT_A_Pickup_C") != std::string::npos)
        return "Taktik Dipcik";
    if (code == 201012 || classname.find("BP_QK_DuckBill_Pickup_C") != std::string::npos)
        return "Duckbill (Pompalı)";
    if (code == 201005 || classname.find("BP_QK_Sniper_FlashHider_Pickup_C") != std::string::npos)
        return "Alev Gizl. Sniper";
    if (code == 201006 || classname.find("BP_QK_Mid_Suppressor_Pickup_C") != std::string::npos)
        return "Susturucu (Haf. Mak. Tabanca)";
    if (code == 205003 || classname.find("BP_QT_Sniper_Pickup_C") != std::string::npos)
        return "Chekpad Sniper";
    if (code == 201001 || classname.find("BP_QK_Choke_Pickup_C") != std::string::npos)
        return "Choke";
    if (code == 205001 || classname.find("BP_QT_UZI_Pickup_C") != std::string::npos)
        return "Dipcik (Micro UZI)";
    if (code == 201003 || classname.find("BP_QK_Sniper_Compensator_Pickup_C") != std::string::npos)
        return "Sniper Kompensator";
    if (code == 201007 || classname.find("BP_QK_Sniper_Suppressor_Pickup_C") != std::string::npos)
        return "Suppressor Sniper";
    if (code == 201011 || classname.find("BP_QK_Large_Suppressor_Pickup_C") != std::string::npos)
        return "Suppressor AR";
    if (code == 204009 || classname.find("BP_DJ_Sniper_EQ_Pickup_C") != std::string::npos)
        return "Sniper Extended";
    if (code == 204004 || classname.find("BP_DJ_Mid_E_Pickup_C") != std::string::npos)
        return "Uz.Haf.Sarjor";
    if (code == 204005 || classname.find("BP_DJ_Mid_Q_Pickup_C") != std::string::npos)
        return "Hc.Haf.Sarjor";
    if (code == 204007 || classname.find("BP_DJ_Sniper_E_Pickup_C") != std::string::npos)
        return "Uz.Snip.Sarjor";
    if (code == 204008 || classname.find("BP_DJ_Sniper_Q_Pickup_C") != std::string::npos)
        return "Hc.Snip.Sarjor";
    if (code == 204012 || classname.find("BP_DJ_Large_Q_Pickup_C") != std::string::npos)
        return "Hc.Oto.Sarjor";
    if (code == 204013 || classname.find("BP_DJ_Large_EQ_Pickup_C") != std::string::npos)
        return "Exteded AR";
    if (code == 204011 || classname.find("BP_DJ_Large_E_Pickup_C") != std::string::npos)
        return "Uz.Oto.Sarjor";
    if (code == 204006 || classname.find("BP_DJ_Mid_EQ_Pickup_C") != std::string::npos)
        return "Hc.Uz.Haf.Sarjor";
    if (code == 205004 || classname.find("BP_ZDD_Crossbow_Q_Pickup_C") != std::string::npos)
        return "Sadak (Arrow)";
    if (code == 204014 || classname.find("BP_ZDD_Sniper_Pickup_C") != std::string::npos)
        return "Mermilik";
    if (code == 203005 || classname.find("BP_MZJ_8X_Pickup_C") != std::string::npos)
        return "8x";
    if (code == 203003 || classname.find("BP_MZJ_2X_Pickup_C") != std::string::npos)
        return "2x";
    if (code == 203001 || classname.find("BP_MZJ_HD_Pickup_C") != std::string::npos)
        return "Lazer";
    if (code == 203014 || classname.find("BP_MZJ_3X_Pickup_C") != std::string::npos)
        return "3X";
    if (code == 203002 || classname.find("BP_MZJ_QX_Pickup_C") != std::string::npos)
        return "Holo";
    if (code == 203015 || classname.find("BP_MZJ_6X_Pickup_C") != std::string::npos)
        return "6x";
    if (code == 203004 || classname.find("BP_MZJ_4X_Pickup_C") != std::string::npos)
        return "4x";
    if (code == 105002 || classname.find("BP_Other_DP28_Wrapper_C") != std::string::npos)
        return "DP28";
    if (code == 107001 || classname.find("BP_Other_CrossBow_Wrapper_C") != std::string::npos)
        return "CrossBow";
    if (code == 105001 || classname.find("BP_Other_M249_Wrapper_C") != std::string::npos)
        return "M249";
    if (code == 501006 || classname.find("PickUp_BP_Bag_Lv3_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 501006 || classname.find("PickUp_BP_Bag_Lv3_B_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 501004 || classname.find("PickUp_BP_Bag_Lv1_C") != std::string::npos)
        return "Bag Lv.1";
    if (code == 501004 || classname.find("PickUp_BP_Bag_Lv1_B_C") != std::string::npos)
        return "Bag Lv.1";
    if (code == 501005 || classname.find("PickUp_BP_Bag_Lv2_C") != std::string::npos)
        return "Bag Lv.2";
    if (code == 501005 || classname.find("PickUp_BP_Bag_Lv2_B_C") != std::string::npos)
        return "Bag Lv.2";
    if (code == 503002 || classname.find("PickUp_BP_Armor_Lv2_C") != std::string::npos)
        return "Armour Lv.2";
    if (code == 503002 || classname.find("PickUp_BP_Armor_Lv2_B_C") != std::string::npos)
        return "Armour Lv.2";
    if (code == 503001 || classname.find("PickUp_BP_Armor_Lv1_C") != std::string::npos)
        return "Armour Lv.1";
    if (code == 503001 || classname.find("PickUp_BP_Armor_Lv1_B_C") != std::string::npos)
        return "Armour Lv.1";
    if (code == 503003 || classname.find("PickUp_BP_Armor_Lv3_C") != std::string::npos)
        return "Armour Lv.3";
    if (code == 503003 || classname.find("PickUp_BP_Armor_Lv3_B_C") != std::string::npos)
        return "Armour Lv.3";
    if (code == 502002 || classname.find("PickUp_BP_Helmet_Lv2_C") != std::string::npos)
        return "Helmet Lv.2";
    if (code == 502002 || classname.find("PickUp_BP_Helmet_Lv2_B_C") != std::string::npos)
        return "Helmet Lv.2";
    if (code == 502001 || classname.find("PickUp_BP_Helmet_Lv1_C") != std::string::npos)
        return "Helmet Lv.1";
    if (code == 502001 || classname.find("PickUp_BP_Helmet_Lv1_B_C") != std::string::npos)
        return "Helmet Lv.1";
    if (code == 502003 || classname.find("PickUp_BP_Helmet_Lv3_C") != std::string::npos)
        return "Helmet Lv.3";
    if (code == 502003 || classname.find("PickUp_BP_Helmet_Lv3_B_C") != std::string::npos)
        return "Helmet Lv.3";
    if (code == 0 && classname.find("BP_VH_Buggy_2_C") != std::string::npos)
        return "Buggy";
    if (code == 0 && classname.find("BP_VH_Buggy_3_C") != std::string::npos)
        return "Buggy";
    if (code == 0 && classname.find("BP_VH_Tuk_1_C") != std::string::npos)
        return "Tuk";
    if (code == 602004 || classname.find("BP_Grenade_Shoulei_Weapon_Wrapper_C") != std::string::npos)
        return "Grenade";
    if (code == 0 && classname.find("BP_Grenade_Shoulei_C") != std::string::npos)
        return "Bomb!";
    if (code == 602002 || classname.find("BP_Grenade_Smoke_Weapon_Wrapper_C") != std::string::npos)
        return "Smoke";
    if (code == 602003 || classname.find("BP_Grenade_Burn_Weapon_Wrapper_C") != std::string::npos)
        return "Molotof";
    if (code == 0 && classname.find("BP_Grenade_Burn_C") != std::string::npos)
        return "Burn!";
    if (code == 602005 || classname.find("BP_Grenade_Apple_Weapon_Wrapper_C") != std::string::npos)
        return "Apple";
    if (code == 601003 || classname.find("Pills_Pickup_C") != std::string::npos)
        return "Painkiller";
    if (code == 601002 || classname.find("Injection_Pickup_C") != std::string::npos)
        return "Adrenaline Syringe";
    if (code == 601001 || classname.find("Drink_Pickup_C") != std::string::npos)
        return "Energy Drink";
    if (code == 601005 || classname.find("Firstaid_Pickup_C") != std::string::npos)
        return "FirstaidKit";
    if (code == 601004 || classname.find("Bandage_Pickup_C") != std::string::npos)
        return "Bandage";
    if (code == 0 && classname.find("BP_PlayerPawn_C") != std::string::npos)
        return "BP_PlayerPawn_C";
    if (code == 0 && classname.find("BP_PlayerPawn_ZNQ_C") != std::string::npos)
        return "BP_PlayerPawn_ZNQ_C";
    if (code == 202006 || classname.find("BP_WB_ThumbGrip_Pickup_C") != std::string::npos)
        return "Basparmaklik";
    if (code == 202007 || classname.find("BP_WB_Lasersight_Pickup_C") != std::string::npos)
        return "Silah Lazeri";
    if (code == 202001 || classname.find("BP_WB_Angled_Pickup_C") != std::string::npos)
        return "Acili El Tutamagi";
    if (code == 202004 || classname.find("BP_WB_LightGrip_Pickup_C") != std::string::npos)
        return "Hafif Tutamak";
    if (code == 0 && classname.find("BP_WB_HalfGrip_Pickup_C") != std::string::npos)
        return "Yarım Tutamak";
    if (code == 202002 || classname.find("BP_WB_Vertical_Pickup_C") != std::string::npos)
        return "DikeyTutamac";
    if (code == 0 && classname.find("VH_Motorcycle_C") != std::string::npos)
        return "Motor";
    if (code == 0 && classname.find("VH_Motorcycle_1_C") != std::string::npos)
        return "Motor";
    if (code == 0 && classname.find("Mirado_open_4_C") != std::string::npos)
        return "Mirado Open";
    if (code == 0 && classname.find("VH_Dacia_C") != std::string::npos)
        return "Toros";
    if (code == 0 && classname.find("VH_Dacia_1_C") != std::string::npos)
        return "Toros";
    if (code == 0 && classname.find("VH_Dacia_4_C") != std::string::npos)
        return "Toros";
    if (code == 0 && classname.find("Rony_01_C") != std::string::npos)
        return "Rony";
    if (code == 0 && classname.find("VH_Snowmobile_C") != std::string::npos)
        return "Snowmobile";
    if (code == 0 && classname.find("Mirado_close_3_C") != std::string::npos)
        return "Mirado Blue";
    if (code == 0 && classname.find("LadaNiva_01_C") != std::string::npos)
        return "Lada Niva";
    if (code == 0 && classname.find("VH_Scooter_C") != std::string::npos)
        return "Scooter";
    if (code == 0 && classname.find("VH_BRDM_C") != std::string::npos)
        return "Tank";
    if (code == 0 && classname.find("PickUp_02_C") != std::string::npos)
        return "PickUp";
    if (code == 0 && classname.find("VH_MiniBus_01_C") != std::string::npos)
        return "MiniBus";
    if (code == 0 && classname.find("VH_MotorcycleCart_C") != std::string::npos)
        return "Motor 3Teker";
    if (code == 0 && classname.find("VH_MotorcycleCart_1_C") != std::string::npos)
        return "Motor 3Teker";
    if (code == 0 && classname.find("VH_Snowbike_C") != std::string::npos)
        return "Snowbike";
    if (code == 0 && classname.find("VH_PG117_C") != std::string::npos)
        return "Boat";
    if (code == 0 && classname.find("VH_UAZ01_C") != std::string::npos)
        return "UAZ1";
    if (code == 0 && classname.find("VH_UAZ02_C") != std::string::npos)
        return "UAZ2";
    if (code == 0 && classname.find("VH_UAZ03_C") != std::string::npos)
        return "UAZ2";
    if (code == 0 && classname.find("VH_UAZ04_C") != std::string::npos)
        return "UAZ2";
    if (code == 0 && classname.find("AquaRail_1_C") != std::string::npos)
        return "JetSki";
    if (code == 106007 || classname.find("BP_Pistol_Flaregun_Wrapper_C") != std::string::npos)
        return "Flaregun";
    if (code == 0 && classname.find("BP_AirDropBox_C") != std::string::npos)
        return "AirDrop";
    if (code == 0 && classname.find("BP_AirDropPlane_C") != std::string::npos)
        return "Plane";
    if (code == 0 && classname.find("PlayerDeadInventoryBox_C") != std::string::npos)
        return "Player Box";
    if (code == 603001 || classname.find("GasCan_Destructible_Pickup_C") != std::string::npos)
        return "GasCan";
    if (code == 0 && classname.find("PickUpListWrapperActor") != std::string::npos)
        return "Create Box";
    if (code == 0 && classname.find("VH_Dacia_2_C") != std::string::npos)
        return "Toros";
    if (code == 0 && classname.find("VH_Dacia_3_C") != std::string::npos)
        return "Toros";
    if (code == 3000312 || classname.find("BP_GameCoin_Pickup_C") != std::string::npos)
        return "GameCoin";
    if (code == 0 && classname.find("BP_BlindBoxMachine_C") != std::string::npos)
        return "BlindBoxMachine";
    if (code == 0 && classname.find("BP_MiniGameMachine_C") != std::string::npos)
        return "MiniGameMachine";
    if (code == 0 && classname.find("BP_Grenade_ColorBall_C") != std::string::npos)
        return "ColorBall";
    if (code == 0 && classname.find("AirDropListWrapperActor") != std::string::npos)
        return "AirDrop";
    if (code == 601006 || classname.find("FirstAidbox_Pickup_C") != std::string::npos)
        return "Medkit";
    if (code == 308001 || classname.find("BP_Ammo_Flare_Pickup_C") != std::string::npos)
        return "Flaregun";
    if (code == 501003 || classname.find("PickUp_BP_Bag_Lv3_Inbox_C") != std::string::npos)
        return "Bag Lv.3";
    if (code == 501002 || classname.find("PickUp_BP_Bag_Lv2_Inbox_C") != std::string::npos)
        return "Bag Lv.2";
    if (code == 501001 || classname.find("PickUp_BP_Bag_Lv1_Inbox_C") != std::string::npos)
        return "Bag Lv.1";
    if (code == 201002 || classname.find("BP_QK_Mid_Compensator_Inbox_C") != std::string::npos)
        return "Kompensator (Haf.Mak.)";
    if (code == 502005 || classname.find("PickUp_BP_Helmet_Lv2_Inbox_C") != std::string::npos)
        return "Helmet Lv.2";
    if (code == 403989 || classname.find("PickUp_BP_Ghillie_4_C") != std::string::npos)
        return "Suit - Arctic";
    if (code == 403045 || classname.find("PickUp_BP_Ghillie_1_C") != std::string::npos)
        return "Suit - Woodland";
    if (code == 403187 || classname.find("PickUp_BP_Ghillie_2_C") != std::string::npos)
        return "Suit - Desert";
    if (code == 403188 || classname.find("PickUp_BP_Ghillie_3_C") != std::string::npos)
        return "Suit - Desert";
    return "tatti";
}
