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

<<<<<<< Updated upstream
	FArmour IronCuirass;
	FArmour ClothRobe;
	FArmour LeatherArmour;
=======
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
>>>>>>> Stashed changes
};




