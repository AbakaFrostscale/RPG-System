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
#include "Creation/CharacterCreation.h"

class FCrafting;
class FInventory;

class FCharacter
{
public:
	FCharacter();

	class FRandom Random;

		

	FCharacterData CurrentCharacter;

	void GatherMaterials(const FMaterialData* MaterialNeeded);

	void CraftWeapon(const FWeapon& Weapon);
	void CraftArmour(const FArmour& Armour);

	void EquipWeapon(const FWeapon& Weapon);
	void EquipArmour(const FArmour& Armour);


	const FCharacterData GetCharacter() const { return Character; }
	FCharacterData& GetCharacterReference() { return Character; }
	const std::unique_ptr<FInventory>& GetInventory() const { return Inventory; }

private:
	std::shared_ptr<FCrafting> Crafter;
	std::unique_ptr<FInventory> Inventory;
	
	FCharacterCreator Creator;
	FCharacterData Character;
	FWeapon EquippedWeapon;
	FArmour EquippedArmour;

};
