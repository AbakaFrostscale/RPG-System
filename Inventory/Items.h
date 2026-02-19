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

	const std::vector<FWeapon>& GetCraftableWeapons() const { return AvailableWeapons; }
	const std::vector<FArmour>& GetCraftableArmour() const{ return AvailableArmour; }

	const std::shared_ptr<FLoadExternalData> GetLoader() const { return Loader; }

private:
	std::shared_ptr<FLoadExternalData> Loader;

	std::vector<FWeapon> AvailableWeapons;
	std::vector<FArmour> AvailableArmour;

};




