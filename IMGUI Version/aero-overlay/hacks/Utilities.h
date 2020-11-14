#pragma once
#include <string>
#include <vector>
#include "kernelinterface.hpp"
// Vectors

extern class Vector2 {
public:
	float x = 0;
	float y = 0;
};
extern class Vector3 {
public:
	float x = 0;
	float y = 0;
	float z = 0;
};
extern class Result
{
public:
	bool hasResult=false;
	float a=0;
	float b=0;
};
extern class Vector4 {
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};
extern class VectorRect {
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

// its for Player Inventory Box Item
struct Item {
	std::string displayName;
	Vector3 Position;
	int picid;
};
struct Vehicle {
	std::string displayName;
	Vector3 Position;
	int picid;
};
// its for entity player weapon details
extern struct playerWeapon {
	int ammoCur = 0,itmid = 0;
	std::string displayName = "";
};
// its for world to screen
extern struct D3DMatrix {
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};
extern struct FTTransform2_t {
	Vector4 Rotation;
	Vector3 Translation;
	float ddd;
	Vector3 Scale3D;
};
class Utilities
{
public :
    static bool IsPlayer(std::string str);
	static Vector3 Readvector3(KeInterface drv, DWORD adds, DWORD ProcessId);
	static std::string GetBoxItemByboth(DWORD code, std::string classname);
	static std::string GetVehicleType(std::string str);
	static std::string GetGrenadeType(std::string classname);
	static bool IsBox(std::string classname);
	static std::string GetImpItem(DWORD code,std::string classname);
	static int GetNameByIDSprite(DWORD id, std::string classname);
};
struct Itemb {
	std::string Displayname;
};
struct Lootbox {
	Vector3 Position;
	std::vector<Itemb> boxitem;
};
struct playerData
{
	DWORD Address,Pose;
	Vector3 Position,velocity;
	int Status, TeamID, Health;
	bool IsRobot;
	std::string Name, Type;
	float energy;
	playerWeapon playerW1, playerW2;
};