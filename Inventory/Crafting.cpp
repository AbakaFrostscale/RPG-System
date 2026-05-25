//Crafting.cpp
//Crafting.cpp has all of the implementation that the crafting class will use
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "Core/LoadExternalData.h"
#include "Inventory/Items.h"
#include "Crafting.h"

FCrafting::FCrafting()
{
	Item = std::make_unique<FItem>();
}

std::optional<FWeapon> FCrafting::CraftWeapon(std::optional<FWeapon> WeaponToCraft, FInventory& Inventory)
{
	// checks ti see if weapon exists, materials are suffficient and it is not in the inventory
	if (CanWeaponBeCrafted(*WeaponToCraft, Inventory) != ECraftingResponse::ECRCanBeCrafted) { return std::nullopt; }

	for (const FMaterial& Material : WeaponToCraft->WeaponData->RequiredMaterial)
	{
		Inventory.RemoveMaterials(Material, Material.MaterialAmount);
	}

	return WeaponToCraft;
}

std::optional<FArmour> FCrafting::CraftArmour(std::optional<FArmour> ArmourToCraft, FInventory& Inventory)
{
	// checks ti see if armour exists, materials are suffficient and it is not in the inventory
	if (CanArmourBeCrafted(*ArmourToCraft, Inventory) != ECraftingResponse::ECRCanBeCrafted) { return std::nullopt; }

	for (const FMaterial& Material : ArmourToCraft->ArmourData->RequiredMaterial)
	{
		Inventory.RemoveMaterials(Material, Material.MaterialAmount);
	}

	return ArmourToCraft;
}

ECraftingResponse FCrafting::CanWeaponBeCrafted(const FWeapon& WeaponToCraft, FInventory& Inventory)
{
	bool bWeaponExists = false;
	
	//Check if the weapon exists and is craftable
	for (const FWeapon& WeaponIndex : Item->GetCraftableWeapons())
	{
		if (WeaponIndex.WeaponData->ItemName == WeaponToCraft.WeaponData->ItemName)
		{
			bWeaponExists = true;
			break;
		}
	}

	if (!bWeaponExists)
	{
		return ECraftingResponse::ECRItemDoesNotExist;
	}

	if (Inventory.HasWeapon(WeaponToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
	{
			return ECraftingResponse::ECRItemAlreadyInInventory;
	}

	if (Inventory.HasRequiredMaterialsWeapon(WeaponToCraft) == ECraftingResponse::ECRMaterialsMissing)
	{
		//TODO notify UI which materials are missing

		return ECraftingResponse::ECRMaterialsMissing;
	}

	return ECraftingResponse::ECRCanBeCrafted;
}

ECraftingResponse FCrafting::CanArmourBeCrafted(const FArmour& ArmourToCraft, FInventory& Inventory)
{
	bool bArmourExists = false;
	//Check if the weapon exists and is craftable
	for (const FArmour& ArmourIndex : Item->GetCraftableArmour())
	{
		if (ArmourIndex.ArmourData->ItemName == ArmourToCraft.ArmourData->ItemName)
		{
			bArmourExists = true;
			break;
		}
	}

	if (!bArmourExists)
	{
		return ECraftingResponse::ECRItemDoesNotExist;
	}

	if (Inventory.HasArmour(ArmourToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
	{
		return ECraftingResponse::ECRItemAlreadyInInventory;
	}

	if (Inventory.HasRequiredMaterialsArmour(ArmourToCraft) == ECraftingResponse::ECRMaterialsMissing)
	{
		//TODO notify UI which materials are missing

		return ECraftingResponse::ECRMaterialsMissing;
	}

	return ECraftingResponse::ECRCanBeCrafted;
}

