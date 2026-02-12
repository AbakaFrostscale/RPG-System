//Items.h
//Database storage for all the items that tha game has access to for he crafting and invetory system
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <vector>
#include "Core/Types.h"

class FLoadExternalData;

class FItem
{
public:
	FItem();

	FWeapon CopperSword;
	FWeapon IronSword;
	FWeapon SteelSword;

	FArmour CopperChestPlate;
	FArmour IronChestPlate;
	FArmour SpiderSilkArmour;

	std::vector<FItemData> GetCraftableItems() { return AvailableItems; }
	std::vector<FWeapon> GetCraftableWeapons() { return AvailableWeapons; }
	std::vector<FArmour> GetCraftableArmour() { return AvailableArmour; }

private:
	FLoadExternalData* Loader;

	FItemData* FindItemData(std::string ItemName);

	std::vector<FItemData> AvailableItems; 	
	std::vector<FWeapon> AvailableWeapons;
	std::vector<FArmour> AvailableArmour;
};




