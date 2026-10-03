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

	void SaveGame(FCharacterData& Character, FInventory& Inventory, sf::Vector2f PlayerPosition);
	bool LoadGame(const std::string& FilePath);

	FSaveData GetSaveData() { return DataToSave; }
	FSaveData GetLoadData() { return DataToLoad; }

private:

	FSaveData DataToSave;
	FSaveData DataToLoad;

	std::string ClassName;
	std::string RaceName;

	int CurrentHP = 0;
	int CurrentMP = 0;
	int Initiative = 0;

	int CharSTR = 0;
	int CharDEX = 0;
	int CharCON = 0;
	int CharINT = 0;
	int CharWIS = 0;
	int CharCHA = 0;

	int BaseSTR = 0;
	int BaseDEX = 0;
	int BaseCON = 0;
	int BaseINT = 0;
	int BaseWIS = 0;
	int BaseCHA = 0;

	std::shared_ptr<FLoadExternalData> Loader;
};