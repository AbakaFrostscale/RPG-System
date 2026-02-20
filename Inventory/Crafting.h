//Crafting.h
//Crafting.h system storing all the data to be used and manage by the crafting system
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector> 

class FItem;
class FInventory;

class FCrafting 
{
public:
	FCrafting();

	FWeapon CraftWeapon(const FWeapon& WeaponToCraft);
	FArmour CraftArmour(const FArmour& ArmourToCraft);

	ECraftingResponse CanWeaponBeCrafted(const FWeapon& WeaponToCraft);
	ECraftingResponse CanArmourBeCrafted(const FArmour& ArmourToCraft);


	std::vector<FWeapon> GetCraftableWeapons() { return CraftableWeapons; }
	std::vector<FArmour> GetCraftableArmour() { return CraftableArmour; }

private:
	std::unique_ptr<FItem> Item;
	std::unique_ptr<FInventory> Inventory;

	std::vector<FWeapon> CraftableWeapons;
	std::vector<FArmour> CraftableArmour;
};