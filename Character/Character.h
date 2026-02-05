//Character.h
//Logic-only Character.h file holds all of the necessary variables and function for character.cpp to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <array>
#include "Core/Random.h"
#include "CharacterStats.h"
#include "Inventory/Crafting.h"
#include "Creation/CharacterCreation.h"



class FCharacter
{
public:
	FCharacter();

	class FRandom Random;

	class FCrafting Crafter;
	class FInventory Inventory;

	void CreateCharacter(std::string UIName, int UIRace, int UIClass, std::string UISkill, int UIAmount, EMode UIMode);

	void GatherMaterials(const FMaterial& MaterialNeeded);

	void CraftWeapon(const FWeapon& Weapon);
	void CraftArmour(const FArmour& Armour);

	void EquipWeapon(const FWeapon& Weapon);
	void EquipArmour(const FArmour& Armour);

private:
	
	FCharacterCreator Creator;
	FCharacterData Character;
	FWeapon EquippedWeapon;
	FArmour EquippedArmour;

};
