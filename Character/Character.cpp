//Character.cpp
//Logic-only Character.cpp file doe all of the work that the character would need to do implementing everything in character.h
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "Character.h"


FCharacter::FCharacter()
{
	Random.RandomGenerator = std::mt19937(Random.rd());
}

void FCharacter::GatherMaterials(const FMaterial& MaterialNeeded)
{
	std::uniform_int_distribution<int> AmountDist(1, 5);
	int RandomAmount = AmountDist(Random.RandomGenerator);

	Inventory.AddMaterials(MaterialNeeded, RandomAmount);
}

//receive input from UI notifying the system which weapon need to be crafted 
void FCharacter::CraftWeapon(const FWeapon& Weapon)
{
	Inventory.AddWeapons(Crafter.CraftWeapon(Weapon));
}

//receive input from UI notifying the system which armour need to be crafted 
void FCharacter::CraftArmour(const FArmour& Armour)
{
	Inventory.AddArmour(Crafter.CraftArmour(Armour));
}

void FCharacter::EquipWeapon(const FWeapon& Weapon)
{
	if (Inventory.HasWeapon(Weapon) != ECraftingResponse::ECRCanBeCrafted) { return; }

	EquippedWeapon = Weapon;
}

void FCharacter::EquipArmour(const FArmour& Armour)
{
	if (Inventory.HasArmour(Armour) != ECraftingResponse::ECRCanBeCrafted) { return; }

	if (Armour.RequiredModifier.Attributes >= CurrentCharacter.CharStats.Attributes)
	{
		EquippedArmour = Armour;
	}
}







