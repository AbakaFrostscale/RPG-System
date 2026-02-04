//Inventory.h
//Inventory.h system storing all the data to be used and manage by the inventory
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector>
#include "Core/Types.h"
#include "Items.h"


class FLoadExternalData;

struct FInventoryStorage
{
	std::vector<FMaterial> Materials;
	std::vector<FWeapon> Weapons;
	std::vector<FArmour> Armour;
};

class FInventory
{
public:
	FInventory();

	void RemoveMaterials(FMaterial Material, int AmountToRemove);
	void AddMaterials(FMaterial Material, int AmountToAdd);

	void RemoveWeapons(const FWeapon& Weapon);
	void AddWeapons(const FWeapon& Weapon);

	void RemoveArmour(const FArmour& Armour);
	void AddArmour(const FArmour& Armour);

	ECraftingResponse HasArmour(const FArmour& Armour);
	ECraftingResponse HasWeapon(const FWeapon& Weapon); 

	bool HasMaterial(const FMaterial& Material);
	ECraftingResponse HasRequiredMaterialsWeapon(const FWeapon& Weapon);
	ECraftingResponse HasRequiredMaterialsArmour(const FArmour& Armour);

	const std::vector<FMaterial>& GetMaterials() const { return Inventory.Materials; }
	const std::vector<FMaterialData>& GetAvailableMaterials() const { return AvailableMaterials; }
	const std::vector<FWeapon>& GetWeapons() const { return Inventory.Weapons; }
	const std::vector<FArmour>& GetArmour()const { return Inventory.Armour; }

private:
	FLoadExternalData* Loader;
	FInventoryStorage Inventory;

	std::vector<FMaterialData> AvailableMaterials;
	
};