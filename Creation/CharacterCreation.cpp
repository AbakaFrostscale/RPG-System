//CharacterCreator.cpp
//CharacterCreator.cpp file that does all the functionality of Building a character
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <string>
#include <sstream>
#include <algorithm>
#include "CharacterCreation.h"


//Constructor for CharacterCreator to set default values for vectors and CurretnCharacter
FCharacterCreator::FCharacterCreator()
{
	LoadCSV("DataBases/RaceDatabase.csv", AvailableRaces);
	LoadCSV("DataBases/ClassDatabase.csv", AvailableClasses);
}

/** 
Call to Create the character to be used by other classes 
UIName - variable for receiving data from the UI in string format
UIRace/UIClass - variable received from a dropdown or slider for selecting race/class
UISkill - Determines the skill from FAttributes struct that need to be modified using the Mode enum
UIAmount - Determines the amount of AttributesPoints to use with upgrading the skill
*/

//Chooses the race from AvailableRaces based on an index fed in from the UI
FRaceData FCharacterCreator::ChooseRace(std::string RaceIndex)
{
	
}

//Chooses the class from AvailableClasses based on an index fed from the UI
void FCharacterCreator::ChooseClass(std::string ClassIndex)
{
	ApplyClassModifiers();
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

/**
Skill refers the the Character.CharStat that needs to be increased
Amount is the values that a stat should be increased by which also deducts from AvailableAttributePoints
Mode determines whether the Skill should be increased or decreased, this will be fed in from the UI
*/

void FCharacterCreator::AllocateAttributePoints(std::string UISkill, int UIAmount, EMode UIMode) 
{ 
	if (bIsFinalised) { return; }
	if (AvailableAttributePoints <= 0 && UIMode == EMode::EMIncrease) return;
		
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
void FCharacterCreator::ApplyRaceBaseStats()
{
	
}

//Adds the Class Stat modifiers to the Current Character
void FCharacterCreator::ApplyClassModifiers()
{

}

void FCharacterCreator::SetCharacterHP()
{
	Character.CurrentHP = Character.MaxHP;
}

//Sets the character MP based on class, according to the ability they use to cast spells
void FCharacterCreator::SetCharacterMP()
{
	Character.CurrentMP = Character.MaxMP;
}

bool FCharacterCreator::IsCharacterValid() const
{
	if (Character.CharName.empty()) {return false; }

	if (AvailableAttributePoints != 0) { return  false; }

	return true;
}

FCharacterData FCharacterCreator::FinalizeCharacter()
{
	if (!IsCharacterValid()) { return {}; }

	SetCharacterHP();
	SetCharacterMP();

	bIsFinalised = true;
	return Character;
}





