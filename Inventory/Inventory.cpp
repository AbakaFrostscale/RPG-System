//Inventory.cpp
//Inventory.cpp has all of the implementation that the inventory class will use
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <vector>
#include "Inventory.h"

FInventory::FInventory()
{
	
}

void FInventory::RemoveMaterials(FMaterial Material, int AmountToRemove)
{
	for (auto It = Inventory.Materials.begin(); It != Inventory.Materials.end();)
	{
		if (It->Material == Material.Material)
		{
			It->MaterialAmount -= AmountToRemove;
			if (It->MaterialAmount <= 0)
			{
				It = Inventory.Materials.erase(It);
				break;
			}
			else
			{
				++It;
			}
		}
		else
		{
			++It;
		}
	}
}

void FInventory::AddMaterials(FMaterial Material, int AmountToAdd)
{
	for (FMaterial& MaterialIndex : Inventory.Materials)
	{
		if (MaterialIndex.Material == Material.Material)
		{
			MaterialIndex.MaterialAmount += AmountToAdd;
			return;
		}
		
	}
	Material.MaterialAmount = AmountToAdd;
	Inventory.Materials.push_back(Material);
}

void FInventory::RemoveWeapons(const FWeapon& Weapon)
{
	if (HasWeapon(Weapon) != ECraftingResponse::ECRCanBeCrafted) { return; }

	for (auto It = Inventory.Weapons.begin(); It != Inventory.Weapons.end(); )
	{
		if (It->ItemName == Weapon.ItemName)
		{
			It = Inventory.Weapons.erase(It);
			break;
	    }
		else
		{
			++It;
		}
	}
}

void FInventory::AddWeapons(const FWeapon& Weapon)
{
	if (HasWeapon(Weapon) != ECraftingResponse::ECRCanBeCrafted) { return; }

	Inventory.Weapons.push_back(Weapon);
}

void FInventory::RemoveArmour(const FArmour& Armour)
{
	if (HasArmour(Armour) != ECraftingResponse::ECRCanBeCrafted) { return; }

	for (auto It = Inventory.Armour.begin(); It != Inventory.Armour.end(); )
	{
		if (It->ItemName == Armour.ItemName)
		{
			It = Inventory.Armour.erase(It);
			break;
		}
		else
		{
			++It;
		}
	}
}

void FInventory::AddArmour(const FArmour& Armour)
{
	if (HasArmour(Armour) != ECraftingResponse::ECRCanBeCrafted) { return; }

	Inventory.Armour.push_back(Armour);
}

ECraftingResponse FInventory::HasArmour(const FArmour& Armor)
{
	for (const FArmour& ArmourIndex : Inventory.Armour)
	{
		if (ArmourIndex.ItemName == Armor.ItemName)
		{
			return ECraftingResponse::ECRItemAlreadyInInventory;
		}
	}
	return ECraftingResponse::ECRCanBeCrafted;
}

ECraftingResponse FInventory::HasWeapon(const FWeapon& Weapon)
{
	for (const FWeapon& WeaponIndex : Inventory.Weapons)
	{
		if (WeaponIndex.ItemName == Weapon.ItemName)
		{
			return ECraftingResponse::ECRItemAlreadyInInventory;
		}
	}
	return ECraftingResponse::ECRCanBeCrafted;
}

bool FInventory::HasMaterial(const FMaterial& Material)
{
	for (const FMaterial& MaterialIndex : Inventory.Materials)
	{
		if (MaterialIndex.Material == Material.Material)
		{
			return true;
		}
	}
	return false;
}
ECraftingResponse FInventory::HasRequiredMaterialsWeapon(const FWeapon& Weapon)
{
	for (const FMaterial& ItemMaterialIndex : Weapon.RequiredMaterials)
	{
		bool bRequirementsMet = false;
		for (const FMaterial& MaterialIndex : Inventory.Materials)
		{
			if (MaterialIndex.Material == ItemMaterialIndex.Material && MaterialIndex.MaterialAmount >= ItemMaterialIndex.MaterialAmount)
			{
				bRequirementsMet = true;
				break;
			}
		}
		if (!bRequirementsMet)
		{
			return ECraftingResponse::ECRMaterialsMissing;
		}
	}
	return ECraftingResponse::ECRCanBeCrafted;
}

ECraftingResponse FInventory::HasRequiredMaterialsArmour(const FArmour& Armour)
{
	for (const FMaterial& ItemMaterialIndex : Armour.RequiredMaterials)
	{
		bool bRequirementMet = false;
		for (const FMaterial& MaterialIndex : Inventory.Materials)
		{
			if (MaterialIndex.Material == ItemMaterialIndex.Material && MaterialIndex.MaterialAmount >= ItemMaterialIndex.MaterialAmount)
			{
				bRequirementMet = true;
				break;
			}
		}
		if (!bRequirementMet)
		{
			return ECraftingResponse::ECRMaterialsMissing;
		}
	}
	return ECraftingResponse::ECRCanBeCrafted;
}