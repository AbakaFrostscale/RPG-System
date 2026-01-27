//Crafting.h
//Crafting.h system storing all the data to be used and manage by the crafting system
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector>
#include "Inventory.h"



class FCrafting 
{
public:
	FCrafting();

	FWeapon CraftWeapon(const FWeapon& WeaponToCraft);
	FArmour CraftArmour(const FArmour& ArmourToCraft);

	ECraftingResponse CanWeaponBeCrafted(const FWeapon& WeaponToCraft);
	ECraftingResponse CanArmourBeCrafted(const FArmour& ArmourToCraft);

	FItem Items;
	FInventory Inventory;

private:

	std::vector<FWeapon> CraftableWeapons;
	std::vector<FArmour> CraftableArmour;
};