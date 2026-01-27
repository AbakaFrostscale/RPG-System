//Items.h
//Database storage for all the items that tha game has access to for he crafting and invetory system
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <vector>
#include <Core/Types.h>


class FItem
{
public:
	FItem();

	FWeapon IronSword;
	FWeapon IronGreatsword;
	FWeapon IronBattleaxe;
	FWeapon IronDagger;

	FArmour IronCuirass;
	FArmour ClothRobe;
	FArmour LeatherArmour;
};




