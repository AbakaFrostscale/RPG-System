//Types.h
//Logic-only Types file that contains all the neccessary types that system will need to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <map>
#include <vector>

//enum to be used for stat mode, wheter to increase or decrease the stat, mostly for UI input
enum class EMode
{ 
	EMIncrease, 
	EMDecrease 
};

enum class ETeam
{
	ETPlayers,
	ETEnemies
};

// This is to check what the response would be for a craftable Item, for error logging
enum class ECraftingResponse
{
	ECRItemDoesNotExist,
	ECRMaterialsMissing,
	ECRItemAlreadyInInventory,
	ECRCanBeCrafted
};

//Information on materials to be referneced by the FMaterial struct, always initialized in GatherableMaterials
struct FMaterialData
{
	std::string MaterialName;
	std::string Type;
	int Weight = 0;

	//new variables can be added later
	
	//MaterialID is here if ever a loopable item is needed to connect to a header (see RaceData for reasoning)
	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& MaterialID)
	{
		MaterialName = Columns[0];
		Type = Columns[1];
		Weight = std::stoi(Columns[2]);
	}


};

// Used to hold a specific metrial in an inventory or crafting requirement
struct FMaterial
{
	FMaterialData* Material;
	int MaterialAmount;
};

struct FItemData
{
	std::string ItemName;
	std::string ItemType;
	std::vector<FMaterial> RequiredMaterials;

	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& ItemID)
	{
		ItemName = Columns[0];
		ItemType = Columns[1];

		for (size_t i = 2; i < ItemID.size(); i++)
		{
			int index = 0;
			if (i < Columns.size())
			{
				RequiredMaterials[index].Material->MaterialName = ItemID[i];
				RequiredMaterials[index].MaterialAmount = std::stoi(Columns[i]);
			}
			++index;
		}
	}
};

struct FWeapon
{
	FItemData WeaponData;
	int Damage = 0;
	std::string RequiredStat;
	int RequiredStatAmount = 0;
};

struct FArmour
{
	FItemData ArmourData;
	int Defence = 0;
	std::string RequiredStat;
	int RequiredStatAmount;
};

struct FRaceData
{
	std::string RaceName;
	std::map<std::string, int> BaseStat;

	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& StatIDs)
	{
		RaceName = Columns[0];
		
		for (size_t i = 1; i < StatIDs.size(); i++)
		{
			if (i < Columns.size())
			{
				BaseStat[StatIDs[i]] = std::stoi(Columns[i]);
			}
		}
	}
};

struct FClassData
{
	int BaseHealth = 0;
	std::string ClassName;
	std::map<std::string, int> StatModifier;

	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& StatIDs)
	{
		ClassName = Columns[0];
		BaseHealth = std::stoi(Columns[1]);

		for (size_t i = 2; i < StatIDs.size(); i++)
		{
			if (i < Columns.size())
			{
				StatModifier[StatIDs[i]] = std::stoi(Columns[i]);
			}
		}
	}
};

template<typename T>
void LoadCSV(const std::string& FilePath, std::vector<T>& OutVector);

std::vector<FRaceData> AvailableRaces;
std::vector<FClassData> AvailableClasses;
std::vector<FMaterialData> AvailableMaterials;