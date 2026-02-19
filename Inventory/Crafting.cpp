//Crafting.cpp
//Crafting.cpp has all of the implementation that the crafting class will use
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "Crafting.h"

FCrafting::FCrafting()
{
<<<<<<< Updated upstream
	CraftableWeapons.push_back(Items.IronSword);
	CraftableWeapons.push_back(Items.IronGreatsword);
	CraftableWeapons.push_back(Items.IronDagger);
	CraftableWeapons.push_back(Items.IronBattleaxe);


	CraftableArmour.push_back(Items.ClothRobe);
	CraftableArmour.push_back(Items.IronCuirass);
	CraftableArmour.push_back(Items.LeatherArmour);
=======
	Item = std::make_unique<FItem>();
	Inventory = std::make_unique<FInventory>();
>>>>>>> Stashed changes
}

FWeapon FCrafting::CraftWeapon(const FWeapon& WeaponToCraft)
{
	if (CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRItemDoesNotExist	||
		CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRMaterialsMissing ||
		CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRItemAlreadyInInventory) {
		return {};
	}						  

	for (const FMaterial& MaterialIndex : WeaponToCraft.RequiredMaterials)
	{
		Inventory.RemoveMaterials(MaterialIndex, MaterialIndex.MaterialAmount);
	}

	return WeaponToCraft;
}

FArmour FCrafting::CraftArmour(const FArmour& ArmourToCraft)
{
	if (CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRItemDoesNotExist || 
		CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRMaterialsMissing ||
		CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
		{ return {}; }

	for (const FMaterial& MaterialIndex : ArmourToCraft.RequiredMaterials)
	{
		Inventory.RemoveMaterials(MaterialIndex, MaterialIndex.MaterialAmount);
	}

	return ArmourToCraft;
}

ECraftingResponse FCrafting::CanWeaponBeCrafted(const FWeapon& WeaponToCraft)
{
	bool bWeaponExists = false;

	std::vector<FWeapon> Weapons = Item->GetCraftableWeapons();
	//Check if the weapon exists and is craftable
<<<<<<< Updated upstream
	for (FWeapon& WeaponIndex : CraftableWeapons)
=======
	for (const FWeapon& WeaponIndex : Weapons)
>>>>>>> Stashed changes
	{
		if (WeaponIndex.ItemName == WeaponToCraft.ItemName)
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

ECraftingResponse FCrafting::CanArmourBeCrafted(const FArmour& ArmourToCraft)
{
	bool bArmourExists = false;
	//Check if the weapon exists and is craftable
<<<<<<< Updated upstream
	for (FArmour& ArmourIndex : CraftableArmour)
=======
	for (const FArmour& ArmourIndex : Item->GetCraftableArmour())
>>>>>>> Stashed changes
	{
		if (ArmourIndex.ItemName == ArmourToCraft.ItemName)
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