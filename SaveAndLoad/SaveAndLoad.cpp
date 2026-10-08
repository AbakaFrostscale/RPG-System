//SaveAndLoad.h
//SaveAndLoad.h system creates a save stat to load and make sure the player can store tand save their progress
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG System
//version 1.00

#include <fstream>
#include <iostream>
#include <External/json.hpp>
#include "Core/LoadExternalData.h"
#include "SaveAndLoad/SaveAndLoad.h"
#include "UI/GameScreen/GameScreen.h"

using json = nlohmann::json;

FSaveAndLoad::FSaveAndLoad()
{
	Loader = std::make_shared<FLoadExternalData>();
}

bool FSaveAndLoad::SaveGame(FCharacterData& Character, FInventory& Inventory, sf::Vector2f PlayerPosition)
{
	DataToSave.SavedCharacter = Character;
	DataToSave.CharacterInventory = Inventory;
	DataToSave.CharacterPosition = PlayerPosition;

	json SaveFile;

	SaveFile["Character"]["Name"] = DataToSave.SavedCharacter.CharName;
	SaveFile["Character"]["Class"] = DataToSave.SavedCharacter.CharClass.ClassName;
	SaveFile["Character"]["Race"] = DataToSave.SavedCharacter.CharRace.RaceName;

	SaveFile["Character"]["HP"] = DataToSave.SavedCharacter.CurrentHP;
	SaveFile["Character"]["MP"] = DataToSave.SavedCharacter.CurrentMP;

	SaveFile["Character"]["Char Stats"]["STR"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EAStr);
	SaveFile["Character"]["Char Stats"]["DEX"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EADex);
	SaveFile["Character"]["Char Stats"]["CON"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EACon);
	SaveFile["Character"]["Char Stats"]["INT"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EAInt);
	SaveFile["Character"]["Char Stats"]["WIS"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EAWis);
	SaveFile["Character"]["Char Stats"]["CHA"] = DataToSave.SavedCharacter.CharStats.at(EAbility::EACha);

	for (const FMaterial& Mat : Inventory.GetMaterials())
	{
		SaveFile["Inventory"][Mat.Material->MaterialName] = Mat.MaterialAmount;
	}

	SaveFile["World"]["Player Position"]["x"] = DataToSave.CharacterPosition.x;
	SaveFile["World"]["Player Position"]["y"] = DataToSave.CharacterPosition.y;

	std::ofstream File("SaveFile.json");

	if (!File.is_open())
	{
		std::cout << "SaveFile.json was not found!" << std::endl;
		return false;
	}

	File << SaveFile.dump(4);

	File.close();

	std::cout << "Save Successful" << std::endl;
	return !File.fail();
}

bool FSaveAndLoad::LoadGame(const std::string& FilePath)
{
	std::ifstream LoadFile(FilePath);
	if (!LoadFile.is_open())
	{
		std::cout << FilePath << " was not found!" << std::endl;
		return false;
	}

	json SaveFile;
	LoadFile >> SaveFile;

	DataToLoad.SavedCharacter.CharName = SaveFile["Character"]["Name"];
	
	ClassName = SaveFile["Character"]["Class"];
	RaceName = SaveFile["Character"]["Race"];

	for (const FClassData& ClassData : Loader->GetAvailableClasses())
	{
		if (ClassData.ClassName == ClassName)
		{
			DataToLoad.SavedCharacter.CharClass = ClassData;
		}
	}

	for (const FRaceData& RaceData : Loader->GetAvailableRaces())
	{
		if (RaceData.RaceName == RaceName)
		{
			DataToLoad.SavedCharacter.CharRace = RaceData;
		}
	}

	DataToLoad.SavedCharacter.CurrentHP = SaveFile["Character"]["HP"];
	DataToLoad.SavedCharacter.CurrentMP = SaveFile["Character"]["MP"];

	DataToLoad.SavedCharacter.CharStats[EAbility::EAStr] = SaveFile["Character"]["Char Stats"]["STR"];
	DataToLoad.SavedCharacter.CharStats[EAbility::EADex] = SaveFile["Character"]["Char Stats"]["DEX"];
	DataToLoad.SavedCharacter.CharStats[EAbility::EACon] = SaveFile["Character"]["Char Stats"]["CON"];
	DataToLoad.SavedCharacter.CharStats[EAbility::EAInt] = SaveFile["Character"]["Char Stats"]["INT"];
	DataToLoad.SavedCharacter.CharStats[EAbility::EAWis] = SaveFile["Character"]["Char Stats"]["WIS"];
	DataToLoad.SavedCharacter.CharStats[EAbility::EACha] = SaveFile["Character"]["Char Stats"]["CHA"];

	return true;
}
