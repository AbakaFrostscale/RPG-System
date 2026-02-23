//Crafting.h
//Crafting.h system storing all the data to be used and manage by the crafting system
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector> 
#include <optional>
#include "Inventory.h"

class FItem;

class FCrafting 
{
public:
	FCrafting();

	std::optional<FWeapon> CraftWeapon(std::optional<FWeapon> WeaponToCraft, FInventory& Inventory);
	std::optional<FArmour> CraftArmour(std::optional<FArmour> ArmourToCraft, FInventory& Inventory);

	ECraftingResponse CanWeaponBeCrafted(const FWeapon& WeaponToCraft, FInventory& Inventory);
	ECraftingResponse CanArmourBeCrafted(const FArmour& ArmourToCraft, FInventory& Inventory);


	std::vector<FWeapon> GetCraftableWeapons() { return CraftableWeapons; }
	std::vector<FArmour> GetCraftableArmour() { return CraftableArmour; }

private:
	std::unique_ptr<FItem> Item;

	std::vector<FWeapon> CraftableWeapons;
	std::vector<FArmour> CraftableArmour;
};