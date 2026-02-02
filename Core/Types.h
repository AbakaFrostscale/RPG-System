//Types.h
//Logic-only Types file that contains all the neccessary types that system will need to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <map>
#include <vector>

//enum to define stats that exist in the game for the characaters
enum class EAbility
{
	EAStr,
	EADex,
	EACon,
	EAInt,
	EAWis,
	EACha
};

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

		int index = 0;
		for (size_t i = 2; i < ItemID.size(); i++)
		{
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
	EAbility RequiredStat;
	int RequiredStatAmount = 0;
};

struct FArmour
{
	FItemData ArmourData;
	int Defence = 0;
	EAbility RequiredStat;
	int RequiredStatAmount;
};

struct FRaceData
{
	std::string RaceName;
	std::map<EAbility, int> BaseStat;

	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& StatIDs)
	{
		RaceName = Columns[0];

		BaseStat[EAbility::EAStr] = std::stoi(Columns[1]);
		BaseStat[EAbility::EADex] = std::stoi(Columns[3]);
		BaseStat[EAbility::EACon] = std::stoi(Columns[4]);
		BaseStat[EAbility::EAInt] = std::stoi(Columns[5]);
		BaseStat[EAbility::EAWis] = std::stoi(Columns[6]);
		BaseStat[EAbility::EACha] = std::stoi(Columns[7]);
	}
};

struct FClassData
{
	int BaseHealth = 0;
	std::string ClassName;
	std::map<EAbility, int> StatModifier;

	void FromCSVRow(const std::vector<std::string>& Columns, const std::vector<std::string>& StatIDs)
	{
		ClassName = Columns[0];

		BaseHealth = std::stoi(Columns[1]);

		StatModifier[EAbility::EAStr] = std::stoi(Columns[1]);
		StatModifier[EAbility::EADex] = std::stoi(Columns[3]);
		StatModifier[EAbility::EACon] = std::stoi(Columns[4]);
		StatModifier[EAbility::EAInt] = std::stoi(Columns[5]);
		StatModifier[EAbility::EAWis] = std::stoi(Columns[6]);
		StatModifier[EAbility::EACha] = std::stoi(Columns[7]);
	}
};

std::vector<FMaterialData> AvailableMaterials;