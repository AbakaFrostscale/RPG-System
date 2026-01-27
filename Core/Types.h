//Types.h
//Logic-only Types file that contains all the neccessary types that system will need to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <map>
#include <vector>

enum EAttributes
{
	EStr,
	EDex,
	ECon,
	EInt,
	EWis,
	ECha
};

struct FAttributes
{
	std::map<EAttributes, int> Attributes;
};

enum class ECraftingResponse
{
	ECRItemDoesNotExist,
	ECRMaterialsMissing,
	ECRItemAlreadyInInventory,
	ECRCanBeCrafted
};

enum class ERarity
{
	ERCommon,
	ERUncommon,
	ERRare,
	ERVeryRare,
	ERLegendary
};

enum class EMaterial
{
	EMWood,
	EMStone,
	EMIron,
	EMCloth,
	EMLeather
};

struct FMaterial
{
	EMaterial Material;
	int MaterialAmount;
};

struct FWeapon
{
	std::string ItemName;
	ERarity Rarity;
	FAttributes RequiredModifier;
	int Damage;
	std::vector<FMaterial> RequiredMaterials;
};

struct FArmour
{
	std::string ItemName;
	ERarity Rarity;
	FAttributes RequiredModifier;
	int Defence;
	std::vector<FMaterial> RequiredMaterials;
};

enum class EIncreaseOrDecrease
{ 
	EIIncrease, 
	EIDecrease 
};



enum class ETeam
{
	ETPlayers,
	ETEnemies
};

enum class ERace 
{
	ERHuman,
	ERElf,
	EROrc,
	ERDwarf,
	ERGnome,
	ERTiefling
};

enum class EClass 
{
	ECFighter,
	ECMonk,
	ECPaladin,
	ECWizard,
	ECCleric,
	ECSorcerer,
	ECBard,
	ECDruid,
	ECBarabarian,
	ECRogue
};

struct FRaceData
{
	ERace Race;
	std::string RaceName;
	FAttributes BaseStat;

	void FromCSVRow(const std::vector<std::string>& Columns)
	{
		RaceName = Columns[0];

		BaseStat.Attributes[EAttributes::EStr] = std::stoi(Columns[1]);
		BaseStat.Attributes[EAttributes::EDex] = std::stoi(Columns[2]);
		BaseStat.Attributes[EAttributes::ECon] = std::stoi(Columns[3]);
		BaseStat.Attributes[EAttributes::EInt] = std::stoi(Columns[4]);
		BaseStat.Attributes[EAttributes::EWis] = std::stoi(Columns[5]);
		BaseStat.Attributes[EAttributes::ECha] = std::stoi(Columns[6]);
	}
};

struct FClassData
{
	EClass Class;
	int BaseHealth = 0;
	std::string ClassName;
	FAttributes StatModifier;

	void FromCSVRow(const std::vector<std::string>& Columns)
	{
		ClassName = Columns[0];

		BaseHealth = std::stoi(Columns[1]),

		StatModifier.Attributes[EAttributes::EStr] = std::stoi(Columns[2]);
		StatModifier.Attributes[EAttributes::EDex] = std::stoi(Columns[3]);
		StatModifier.Attributes[EAttributes::ECon] = std::stoi(Columns[4]);
		StatModifier.Attributes[EAttributes::EInt] = std::stoi(Columns[5]);
		StatModifier.Attributes[EAttributes::EWis] = std::stoi(Columns[6]);
		StatModifier.Attributes[EAttributes::ECha] = std::stoi(Columns[7]);
	}
};