//CharacterCreator.cpp
//CharacterCreator.cpp file that does all the functionality of Building a character
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

#include "CharacterCreation.h"
#include "Character/CharacterStats.h"
#include "Core/LoadExternalData.h"


//Constructor for CharacterCreator to set default values for vectors and CurretnCharacter
FCharacterCreator::FCharacterCreator()
{
	Loader->LoadCSV("DataBases/RaceDatabase.csv", AvailableRaces);
	Loader->LoadCSV("DataBases/ClassDatabase.csv", AvailableClasses);
}

/** 
Call to Create the character to be used by other classes 
UIName - variable for receiving data from the UI in string format
UIRace/UIClass - variable received from a dropdown or slider for selecting race/class
UISkill - Determines the skill from FAttributes struct that need to be modified using the Mode enum
UIAmount - Determines the amount of AttributesPoints to use with upgrading the skill
*/

//Chooses the race from AvailableRaces based on an index fed in from the UI
FRaceData FCharacterCreator::ChooseRace(int RaceIndex)
{
	return AvailableRaces[RaceIndex];
}

//Chooses the class from AvailableClasses based on an index fed from the UI
FClassData FCharacterCreator::ChooseClass(int ClassIndex)
{
	return AvailableClasses[ClassIndex];
}

/**
Current, checks the Characters stat that need to be increased
Base, is used to compare the stat to the minimum amount to avoid dropping a stat too low (Base = Race.Stat + Class.Stat)
Amount is the value that a stat should be increased by which also deducts from AvailableAttributePoints
Mode determines whether a stat should be increased or decreases

Assumes Amount has been validatd by the caller
*/
bool FCharacterCreator::TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode)
{
	if (Mode == EMode::EMIncrease)
			{ 
				Current += Amount;
				return true;	
			} 
			else if (Mode == EMode::EMDecrease 
					&& (Current - Amount) >= Base)
			{
				Current -= Amount;
				return true;
			}
	return false;
}

const EAbility FCharacterCreator::StringToEAbility(std::string String)
{
	std::string Ability;
	int count = std::min(3, static_cast<int>(String.length()));

	for (int i = 0; i < count; i++)
	{
		Ability += std::toupper(static_cast<unsigned char>(String[i]));
	}

	if (Ability == "STR")
	{
		return EAbility::EAStr;
	}
	if (Ability == "DEX")
	{
		return EAbility::EADex;
	}
	if (Ability == "CON")
	{
		return EAbility::EACon;
	}
	if (Ability == "INT")
	{
		return EAbility::EAInt;
	}
	if (Ability == "WIS")
	{
		return EAbility::EAWis;
	}
	if (Ability == "Cha")
	{
		return EAbility::EACha;
	}

	return EAbility::EANone;
}

/**
Skill refers the the Character.CharStat that needs to be increased
Amount is the values that a stat should be increased by which also deducts from AvailableAttributePoints
Mode determines whether the Skill should be increased or decreased, this will be fed in from the UI
*/

void FCharacterCreator::AllocateAttributePoints(std::string UISkill, int UIAmount, EMode UIMode) 
{ 
	if (bIsFinalised) { return; }
	if (AvailableAttributePoints <= 0 && UIMode == EMode::EMIncrease) { return; }
	if (StringToEAbility(UISkill) == EAbility::EANone) { return; }
		
	AvailableAttributePoints = std::min(AvailableAttributePoints, MaxAttributePoints);
	bool bStatChanged = false;

	if (UIMode == EMode::EMIncrease)
	{
		UIAmount = std::clamp(UIAmount, 0, AvailableAttributePoints);
	}
	else if (UIMode == EMode::EMDecrease)
	{
		UIAmount = std::clamp(UIAmount, 0, MaxAttributePoints);
	}

	
	switch (StringToEAbility(UISkill))
	{
		case EAbility::EAStr: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EAStr), 
							Character->BaseStats.at(EAbility::EAStr), 
							UIAmount, 
							UIMode);
			bStatChanged = true;
		case EAbility::EADex: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EADex),
							Character->BaseStats.at(EAbility::EADex),
							UIAmount,
							UIMode);
			bStatChanged = true;
		case EAbility::EACon: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EACon),
							Character->BaseStats.at(EAbility::EACon),
							UIAmount,
							UIMode);
			bStatChanged = true;
		case EAbility::EAInt: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EAInt),
							Character->BaseStats.at(EAbility::EAInt),
							UIAmount,
							UIMode);
			bStatChanged = true;
		case EAbility::EAWis: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EAWis),
							Character->BaseStats.at(EAbility::EAWis),
							UIAmount,
							UIMode);
			bStatChanged = true;
		case EAbility::EACha: 
			TryAllocatePoints(Character->CharStats.at(EAbility::EACha),
							Character->BaseStats.at(EAbility::EACha),
							UIAmount,
							UIMode);
			bStatChanged = true;
		default: 
			bStatChanged = false;
	}

	if (UIMode == EMode::EMIncrease && bStatChanged)
	{ 
		AvailableAttributePoints -= UIAmount; 		
	} 
	else if (UIMode == EMode::EMDecrease && bStatChanged)
	{
		AvailableAttributePoints += UIAmount; 
	}
}

//Applies the stats of Race to the Character
void FCharacterCreator::ApplyRaceBaseStats(FCharacterData& Character)
{
	Character.BaseStats = Character.CharRace.BaseStat;
}

//Adds the Class Stat modifiers to the Current Character
void FCharacterCreator::ApplyClassModifiers(FCharacterData& Character)
{
	for (auto& key : Character.CharClass.StatModifier)
	{
		Character.BaseStats[key.first] += Character.CharClass.StatModifier[key.first];
	}
}

int FCharacterCreator::CalculateCharacterMaxHP(FCharacterData& Character)
{
	return Character.CharClass.BaseHealth + Character.CharStats[EAbility::EACon];
}

//Sets the character MP based on class, according to the ability they use to cast spells
int FCharacterCreator::CalculateCharacterMaxMP(FCharacterData& Character)
{
	if (Character.CharClass.ClassName == "Paladin")
	{
		return Character.CharStats[EAbility::EACha] * 2;
	}
	else if (Character.CharClass.ClassName == "Cleric")
	{
		return Character.CharStats[EAbility::EAWis] * 2;
	}
	else if (Character.CharClass.ClassName == "Wizard")
	{
		return Character.CharStats[EAbility::EAInt] * 2;
	}
	else if (Character.CharClass.ClassName == "Bard")
	{
		return Character.CharStats[EAbility::EACha] * 2;
	}
	else if (Character.CharClass.ClassName == "Sorcerer")
	{
		return Character.CharStats[EAbility::EACha] * 2;
	}
	else if (Character.CharClass.ClassName == "Druid")
	{
		return Character.CharStats[EAbility::EAWis] * 2;
	}
	else
	{
		return 0;
	}
}





