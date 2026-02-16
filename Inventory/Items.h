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
	const FItemData* FindItemData(const std::string& ItemName);
	void ResolveMaterials(std::vector<FItemData>& Items);

	FWeapon CopperSword;
	FWeapon IronSword;
	FWeapon SteelSword;

	FArmour CopperChestPlate;
	FArmour IronChestPlate;
	FArmour SpiderSilkArmour;

	std::vector<FWeapon> GetCraftableWeapons() { return AvailableWeapons; }
	std::vector<FArmour> GetCraftableArmour() { return AvailableArmour; }
	const std::vector<FItemData>& GetAvailableItems() const { return AvailableItems; }
	const std::vector<FMaterialData>& GetAvailableMaterials() const { return AvailableMaterials; }

private:
	FLoadExternalData* Loader;
	//Items		
	std::vector<FMaterialData> AvailableMaterials;
	std::vector<FItemData> AvailableItems;

	std::vector<FWeapon> AvailableWeapons;
	std::vector<FArmour> AvailableArmour;
};




