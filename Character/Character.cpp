//Character.cpp
//Logic-only Character.cpp file doe all of the work that the character would need to do implementing everything in character.h
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "Character.h"	
#include "Inventory/Crafting.h"	 
#include "Inventory/Inventory.h"


FCharacter::FCharacter()
{
	Crafter = std::make_shared<FCrafting>();
	Inventory = std::make_unique<FInventory>();
	Random.RandomGenerator = std::mt19937(Random.rd());
}

void FCharacter::GatherMaterials(const FMaterialData* MaterialNeeded)
{
	std::uniform_int_distribution<int> AmountDist(1, 5);
	int RandomAmount = AmountDist(Random.RandomGenerator);

	Inventory->AddMaterials(MaterialNeeded, RandomAmount);
}

//receive input from UI notifying the system which weapon need to be crafted 
void FCharacter::CraftWeapon(const FWeapon& Weapon)
{
	const FWeapon CraftedWeapon = Crafter->CraftWeapon(Weapon);

	Inventory->AddWeapons(CraftedWeapon);
}

//receive input from UI notifying the system which armour need to be crafted 
void FCharacter::CraftArmour(const FArmour& Armour)
{
	const FArmour& CraftedArmour = Crafter->CraftArmour(Armour);

	Inventory->AddArmour(Crafter->CraftArmour(CraftedArmour));
}

void FCharacter::EquipWeapon(const FWeapon& Weapon)
{
	if (Inventory->HasWeapon(Weapon) != ECraftingResponse::ECRCanBeCrafted) { return; }

	EquippedWeapon = Weapon;
}

void FCharacter::EquipArmour(const FArmour& Armour)
{
	if (Inventory->HasArmour(Armour) != ECraftingResponse::ECRCanBeCrafted) { return; }

	EquippedArmour = Armour;
}
