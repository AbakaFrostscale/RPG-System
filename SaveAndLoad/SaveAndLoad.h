//SaveAndLoad.h
//SaveAndLoad.h system creates a save stat to load and make sure the player can store tand save their progress
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG System
//version 1.00

#pragma once

#include "Core/Types.h"
#include "SaveAndLoad/SaveData.h"
#include "Character/Character.h"
#include "Character/CharacterStats.h"
#include "Inventory/Inventory.h"

class FGameScreen;

class FLoadExternalData;

enum class ELoadState
{
	ELSCharacter,
	ELSInventory,
	ELSWorld,
	ELSDefault
};

class FSaveAndLoad
{
public:
	
	FSaveAndLoad();

	bool SaveGame(FCharacterData& Character, FInventory& Inventory, sf::Vector2f PlayerPosition, int SelctedSpriteIndex);
	bool LoadGame(const std::string& FilePath);

	FSaveData GetSaveData() { return DataToSave; }
	FSaveData GetLoadData() { return DataToLoad; }

private:

	FSaveData DataToSave;
	FSaveData DataToLoad;
	FSaveData TempData;

	std::string ClassName;
	std::string RaceName;

	std::shared_ptr<FLoadExternalData> Loader;
	std::shared_ptr<FCharacterCreator> Creator;
};