//Character.h
//Logic-only Character.h file holds all of the necessary variables and function for character.cpp to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <array>
#include <optional>
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

	void GatherMaterials(const FMaterialData* MaterialNeeded);

	void CraftWeapon(const FWeapon& Weapon);
	void CraftArmour(const FArmour& Armour);

	void EquipWeapon(const FWeapon& Weapon);
	void EquipArmour(const FArmour& Armour);

	int HitEnemy(std::optional<FWeapon> Weapon);
	void TakeDamage(int Damage);
	FSpellData CastSpell(int Spell);


	const FCharacterData GetCharacter() const { return Character; }
	FCharacterData& GetCharacterReference() { return Character; }
	const std::shared_ptr<FInventory>& GetInventory() const { return Inventory; }

	const std::optional<FWeapon>& GetEquippedWeapon() const{ return EquippedWeapon; }
	const std::optional<FArmour>& GetEquippedArmour() const { return EquippedArmour; }

private:
	std::shared_ptr<FCrafting> Crafter;
	std::shared_ptr<FInventory> Inventory;
	
	FCharacterCreator Creator;
	FCharacterData Character;
	std::optional<FWeapon> EquippedWeapon;
	std::optional<FArmour> EquippedArmour;

};
