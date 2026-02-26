//LoadExternalData.h
//HeaderFile for loading all the external data from files
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Types.h" 
#include "External/json.hpp"
#include "Character/CharacterStats.h"

using json = nlohmann::json;

class FLoadExternalData
{
public:
	FLoadExternalData();

	//CharacterCreation
	const std::vector<FRaceData>& GetAvailableRaces() const { return AvailableRaces; }
	const std::vector<FClassData>& GetAvailableClasses() const { return AvailableClasses; }
	const std::vector<FSpellData>& GetAvailableSpells()	const { return AvailableSpells; }

	//Items
	const std::vector<FItemData>& GetAvailableItems() const { return AvailableItems; }
	const std::vector<FMaterialData>& GetAvailableMaterials() const { return AvailableMaterials; }

	const FItemData* FindItemData(const std::string& ItemName);
	void ResolveMaterials(std::vector<FItemData>& Items);

	//Enemies
	const std::vector<FEnemyData>& GetEnemies() const { return Enemy; }
	

private: 

	std::vector<FEnemyData> Enemy;
	
	//CharacterCreation
	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses; 

	//Items		
	std::vector<FMaterialData> AvailableMaterials;
	std::vector<FItemData> AvailableItems;

	std::vector<FSpellData> AvailableSpells;

	template<typename T>
	bool LoadJSON(const std::string& FilePath, std::vector<T>& OutVector)
	{
		std::ifstream file(FilePath);
		if (!file.is_open())
		{
			return false;
		}

		json data;
		file >> data;


		for (const auto& Element: data)
		{
			T obj;
			obj.FromJson(Element);
			OutVector.push_back(obj);
		}
		return true;
	}

	template<typename T>
	bool LoadCSV(const std::string& FilePath, std::vector<T>& OutVector)
	{
		std::ifstream File(FilePath);

		if (!File.is_open())
		{
			//TODO, notify the UI that the file is not open
			return false;
		}

		std::string Line;
		bool bReadHeader = false;
		std::vector<std::string> Header;

		while (std::getline(File, Line))
		{
			if (Line.empty()) continue;

			std::vector<std::string> Columns;
			std::stringstream ss(Line);
			std::string Cell;

			while (std::getline(ss, Cell, ','))
			{
				Cell.erase(Cell.find_last_not_of("\r\n") + 1);
				Columns.push_back(Cell);
			}

			if (!bReadHeader)
			{
				Header = Columns;
				bReadHeader = true;
				continue;
			}

			if (Columns.size() != Header.size())
			{
				return false;
			}

			try
			{
				T Row;
				Row.FromCSVRow(Columns);
				OutVector.push_back(Row);
			}
			catch (const std::exception& e)
			{
				return false;
			}
		}

		return true;
	}


};

