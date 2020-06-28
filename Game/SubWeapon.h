#pragma once
#include "GameObject.h"
#include <unordered_map>

using namespace std;

enum class SubWeapon
{
	UNKNOWN = -1,
	DAGGER = 7,
	BOOMERANG = 71,
	HOLYWATER = 72
};

/*
	Manage subweapons database
*/
class CSubWeapon
{
private:
	unordered_map<int, vector<LPGAMEOBJECT>> subweapons;
	static CSubWeapon* __instance;
public:
	void Select(int weapon);
	void UseDagger();
	void UseBoomerang();
	void UseHolyWater();
	LPGAMEOBJECT GetWeapon(int weapon);
	void Add(int weapon, LPGAMEOBJECT obj);
	CSubWeapon() { ; }
	static CSubWeapon* GetInstance();
};

