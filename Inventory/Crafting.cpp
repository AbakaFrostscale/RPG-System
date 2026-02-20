//Crafting.cpp
//Crafting.cpp has all of the implementation that the crafting class will use
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <iostream>

#include "Core/LoadExternalData.h"
#include "Inventory/Items.h"
#include "Inventory/Inventory.h"
#include "Crafting.h"

FCrafting::FCrafting()
{

	Item = std::make_unique<FItem>();
	Inventory = std::make_unique<FInventory>();
}

const FWeapon FCrafting::CraftWeapon(const FWeapon& WeaponToCraft)
{
	if (CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRItemDoesNotExist	||
		CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRMaterialsMissing ||
		CanWeaponBeCrafted(WeaponToCraft) == ECraftingResponse::ECRItemAlreadyInInventory) 
		{ return {}; }	

	return WeaponToCraft;
}

const FArmour FCrafting::CraftArmour(const FArmour& ArmourToCraft)
{
	if (CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRItemDoesNotExist || 
		CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRMaterialsMissing ||
		CanArmourBeCrafted(ArmourToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
		{ return {}; }

	return ArmourToCraft;
}

ECraftingResponse FCrafting::CanWeaponBeCrafted(const FWeapon& WeaponToCraft)
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

	if (Inventory->HasWeapon(WeaponToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
	{
			return ECraftingResponse::ECRItemAlreadyInInventory;
	}

	if (Inventory->HasRequiredMaterialsWeapon(WeaponToCraft) == ECraftingResponse::ECRMaterialsMissing)
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

	if (Inventory->HasArmour(ArmourToCraft) == ECraftingResponse::ECRItemAlreadyInInventory)
	{
		return ECraftingResponse::ECRItemAlreadyInInventory;
	}

	if (Inventory->HasRequiredMaterialsArmour(ArmourToCraft) == ECraftingResponse::ECRMaterialsMissing)
	{
		//TODO notify UI which materials are missing

		return ECraftingResponse::ECRMaterialsMissing;
	}

	return ECraftingResponse::ECRCanBeCrafted;
}

