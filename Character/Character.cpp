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



void FCharacter::CreateCharacter(std::string UIName, int UIRace, int UIClass, std::string UISkill, int UIAmount, EMode UIMode)
{
	Character.CharName = UIName;
	
	Character.CharRace = Creator.ChooseRace(UIRace);
	Creator.ApplyRaceBaseStats(Character);

	Character.CharClass = Creator.ChooseClass(UIClass);
	Creator.ApplyClassModifiers(Character);

	Character.CharStats = Character.BaseStats;
	
	Character.MaxHP = Creator.CalculateCharacterMaxHP(Character);
	Character.MaxMP = Creator.CalculateCharacterMaxMP(Character);

	Character.CurrentHP = Character.MaxHP;
	Character.CurrentMP = Character.MaxMP;
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

	EquippedArmour = Armour;
}