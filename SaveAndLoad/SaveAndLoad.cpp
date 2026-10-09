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
	Creator = std::make_shared<FCharacterCreator>();
}

bool FSaveAndLoad::SaveGame(FCharacterData& Character, FInventory& Inventory, sf::Vector2f PlayerPosition, int SelctedSpriteIndex)
{
	DataToSave.SavedCharacter = Character;
	DataToSave.CharacterInventory = Inventory;
	DataToSave.CharacterPosition = PlayerPosition;
	DataToSave.SelectedSpriteIndex = SelctedSpriteIndex;

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
		SaveFile["Inventory"]["Materials"][Mat.Material->MaterialName] = Mat.MaterialAmount;
	}

	SaveFile["World"]["Player"]["Position"]["x"] = DataToSave.CharacterPosition.x;
	SaveFile["World"]["Player"]["Position"]["y"] = DataToSave.CharacterPosition.y;
	SaveFile["World"]["Player"]["Sprite"] = DataToSave.SelectedSpriteIndex;

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
	bool bIsClassValid = false;
	bool bIsRaceValid = false;

	std::ifstream LoadFile(FilePath);
	if (!LoadFile.is_open())
	{
		std::cout << FilePath << " was not found!" << std::endl;
		return false;
	}

	json SaveFile;
	LoadFile >> SaveFile;

	TempData.SavedCharacter.CharName = SaveFile["Character"]["Name"];
	
	ClassName = SaveFile["Character"]["Class"];
	RaceName = SaveFile["Character"]["Race"];

	for (const FClassData& ClassData : Loader->GetAvailableClasses())
	{
		if (ClassData.ClassName == ClassName)
		{
			bIsClassValid = true;
			TempData.SavedCharacter.CharClass = ClassData;
		}
	}
	
	if (!bIsClassValid)
	{
		std::cout << ClassName << " is not a valid Class!" << std::endl;
		return false;
	}

	for (const FRaceData& RaceData : Loader->GetAvailableRaces())
	{
		if (RaceData.RaceName == RaceName)
		{
			bIsRaceValid = true;
			TempData.SavedCharacter.CharRace = RaceData;
		}
	}

	if (!bIsRaceValid)
	{
		std::cout << RaceName << " is not a valid Race!" << std::endl;
		return false;
	}

	if (SaveFile["Character"]["Char Stats"]["STR"].is_number_integer() &&
		SaveFile["Character"]["Char Stats"]["DEX"].is_number_integer()&&
		SaveFile["Character"]["Char Stats"]["CON"].is_number_integer()&&
		SaveFile["Character"]["Char Stats"]["INT"].is_number_integer()&&
		SaveFile["Character"]["Char Stats"]["WIS"].is_number_integer() &&
		SaveFile["Character"]["Char Stats"]["CHA"].is_number_integer())
	{
		TempData.SavedCharacter.CharStats[EAbility::EAStr] = SaveFile["Character"]["Char Stats"]["STR"];
		TempData.SavedCharacter.CharStats[EAbility::EADex] = SaveFile["Character"]["Char Stats"]["DEX"];
		TempData.SavedCharacter.CharStats[EAbility::EACon] = SaveFile["Character"]["Char Stats"]["CON"];
		TempData.SavedCharacter.CharStats[EAbility::EAInt] = SaveFile["Character"]["Char Stats"]["INT"];
		TempData.SavedCharacter.CharStats[EAbility::EAWis] = SaveFile["Character"]["Char Stats"]["WIS"];
		TempData.SavedCharacter.CharStats[EAbility::EACha] = SaveFile["Character"]["Char Stats"]["CHA"];
	}
	else
	{
		std::cout << "Stats are not valid" << std::endl;
		return false;
	}

	if (SaveFile["Character"]["HP"].is_number_integer() && 
		SaveFile["Character"]["HP"] >= 1 && 
		SaveFile["Character"]["HP"] <= Creator->CalculateCharacterMaxHP(TempData.SavedCharacter))
	{
		TempData.SavedCharacter.CurrentHP = SaveFile["Character"]["HP"];
	}
	else
	{
		std::cout << "HP is not a valid" << std::endl;
		return false;
	}

	if (SaveFile["Character"]["MP"].is_number_integer() &&
		SaveFile["Character"]["MP"] >= 0 &&
		SaveFile["Character"]["MP"] <= Creator->CalculateCharacterMaxMP(TempData.SavedCharacter))
	{
		TempData.SavedCharacter.CurrentMP = SaveFile["Character"]["MP"];
	}
	else 
	{
		std::cout << "MP is not a valid" << std::endl;
		return false;
	}

	TempData.CharacterInventory.GetMaterials().clear();
	
	for (auto& [key, val] : SaveFile["Inventory"]["Materials"].items())
	{
		bool bIsMaterialValid = false;
		
		for (const FMaterialData& Mat : Loader->GetAvailableMaterials())
		{
			if (Mat.MaterialName == key && val.is_number_integer() && val >= 1)
			{
				bIsMaterialValid = true;
				TempData.CharacterInventory.AddMaterials(&Mat, val);
			}
		}
		
		if (!bIsMaterialValid)
		{
			std::cout << "A material value is invalid" << std::endl;
			return false;
		}
	}

	if (SaveFile["World"]["Player"]["Position"]["x"].is_number_float() &&
		SaveFile["World"]["Player"]["Position"]["y"].is_number_float() &&
		SaveFile["World"]["Player"]["Position"]["x"] >= 0 &&
		SaveFile["World"]["Player"]["Position"]["x"] <= 4000 &&
		SaveFile["World"]["Player"]["Position"]["y"] >= 0 &&
		SaveFile["World"]["Player"]["Position"]["y"] <= 4000)
	{
		TempData.CharacterPosition.x = SaveFile["World"]["Player"]["Position"]["x"];
		TempData.CharacterPosition.y = SaveFile["World"]["Player"]["Position"]["y"];
	}
	else
	{
		std::cout << "Sprite Position is invalid!" << std::endl;
		return false;
	}


	if (SaveFile["World"]["Player"]["Sprite"].is_number_integer() &&
		SaveFile["World"]["Player"]["Sprite"] >= 0 &&
		SaveFile["World"]["Player"]["Sprite"] <= 11)
	{
		TempData.SelectedSpriteIndex = SaveFile["World"]["Player"]["Sprite"];
	}
	else
	{
		std::cout << " Selected sprite does not exist" << std::endl;
		return false;
	}

	DataToLoad = TempData;

	return true;
}