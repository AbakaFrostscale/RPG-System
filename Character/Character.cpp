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
	Inventory = std::make_shared<FInventory>();
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
	Inventory->AddWeapons(Crafter->CraftWeapon(Weapon, *Inventory));
}

//receive input from UI notifying the system which armour need to be crafted 
void FCharacter::CraftArmour(const FArmour& Armour)
{
	Inventory->AddArmour(Crafter->CraftArmour(Armour, *Inventory));
}

void FCharacter::EquipWeapon(const FWeapon& Weapon)
{
	if (Inventory->HasWeapon(Weapon) == ECraftingResponse::ECRItemAlreadyInInventory
		&& Character.CharStats.at(Weapon.RequiredStat) >= Weapon.RequiredStatAmount)
	{
		EquippedWeapon = Weapon;
	}
	else
	{
		return;
	}
}

void FCharacter::EquipArmour(const FArmour& Armour)
{
	if (Inventory->HasArmour(Armour) == ECraftingResponse::ECRItemAlreadyInInventory
		&& Character.CharStats.at(Armour.RequiredStat) >= Armour.RequiredStatAmount)
	{
		EquippedArmour = Armour;
	}
	else
	{ 
		return; 
	}
}

int FCharacter::HitEnemy(std::optional<FWeapon> Weapon)
{
	if (!Weapon)
	{
		return 0;
	}

	std::uniform_int_distribution<int> DamageDist(1, Weapon->Damage);
	return DamageDist(Random.RandomGenerator);
}

void FCharacter::TakeDamage(int Damage)
{
	Character.CurrentHP -= Damage;
}

FSpellData FCharacter::CastSpell(int Spell)
{
	return Character.Spells[Spell];
}
