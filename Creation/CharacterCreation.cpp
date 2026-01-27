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
FCharacterData FCharacterCreator::CreateCharacter(std::string UIName, int UIRace, int UIClass, EAttributes UISkill, int UIAmount, EIncreaseOrDecrease Mode)
{
	for (int i = 0; i <= AvailableRaces.size() - 1; i++)
	{
		AvailableRaces[i].Race = StringToERace(AvailableRaces[i].RaceName);
	}
	
	for (int i = 0; i <= AvailableClasses.size() - 1; i++)
	{
		AvailableClasses[i].Class = StringToEClass(AvailableClasses[i].ClassName);
	}
	
	Character.CharName = UIName;

	ChooseRace(UIRace);
	ChooseClass(UIClass);
	
	Character.BaseStats = Character.CharStats;

	AllocateAttributePoints(UISkill, UIAmount, Mode);

	FinalizeCharacter();

	return Character;
}

//Chooses the race from AvailableRaces based on an index fed in from the UI
void FCharacterCreator::ChooseRace(int RaceIndex)
{	
	if(bIsFinalised) { return; }	

	if (RaceIndex < 0 || RaceIndex >= AvailableRaces.size())
	return;
	
	
	Character.CharRace = AvailableRaces[RaceIndex].Race;
	ApplyRaceBaseStats();
}

//Chooses the class from AvailableClasses based on an index fed from the UI
void FCharacterCreator::ChooseClass(int ClassIndex)
{
	if (bIsFinalised) { return; }

	if (ClassIndex < 0 || ClassIndex >= AvailableClasses.size())
	return;
	

	Character.CharClass = AvailableClasses[ClassIndex].Class;
	ApplyClassModifiers();
}

/**
Current, checks the Characters stat that need to be increased
Base, is used to compare the stat to the minimum amount to avoid dropping a stat too low (Base = Race.Stat + Class.Stat)
Amount is the value that a stat should be increased by which also deducts from AvailableAttributePoints
Mode determines whether a stat should be increased or decreases

Assumes Amount has been validatd by the caller
*/
bool FCharacterCreator::TryAllocatePoints(int& Current, int Base, int Amount, EIncreaseOrDecrease Mode)
{
	if (Mode == EIncreaseOrDecrease::EIIncrease)
			{ 
				Current += Amount;
				return true;	
			} 
			else if (Mode == EIncreaseOrDecrease::EIDecrease 
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

void FCharacterCreator::AllocateAttributePoints(EAttributes Skill, int Amount, EIncreaseOrDecrease Mode) 
{ 
	if (bIsFinalised) { return; }
	if (AvailableAttributePoints <= 0 && Mode == EIncreaseOrDecrease::EIIncrease) return;
		
	AvailableAttributePoints = std::min(AvailableAttributePoints, MaxAttributePoints);
	bool bStatChanged = false;

	if (Mode == EIncreaseOrDecrease::EIIncrease)
	{
		Amount = std::clamp(Amount, 0, AvailableAttributePoints);
	}
	else if (Mode == EIncreaseOrDecrease::EIDecrease)
	{
		Amount = std::clamp(Amount, 0, MaxAttributePoints);
	}


	switch (Skill) 
	{	 
		case EAttributes::EStr :
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::EStr],
					Character.BaseStats.Attributes[EAttributes::EStr],
					Amount,
					Mode);
			break;
			
		case EAttributes::EDex :
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::EDex],
					Character.BaseStats.Attributes[EAttributes::EDex],
					Amount,
					Mode);
			break;

		case EAttributes::ECon : 
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::ECon],
					Character.BaseStats.Attributes[EAttributes::ECon],
					Amount,
					Mode);
			break;

		case EAttributes::EInt :
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::EInt],
					Character.BaseStats.Attributes[EAttributes::EInt],
					Amount,
					Mode);
			break;

		case EAttributes::EWis : 
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::EWis],
					Character.BaseStats.Attributes[EAttributes::EWis],
					Amount,
					Mode);
			break;

		case EAttributes::ECha :
			bStatChanged = TryAllocatePoints(
					Character.CharStats.Attributes[EAttributes::ECha],
					Character.BaseStats.Attributes[EAttributes::ECha],
					Amount,
					Mode);
			break;

		default : 
			break; 
	}
	if (Mode == EIncreaseOrDecrease::EIIncrease && bStatChanged)
	{ 
		AvailableAttributePoints -= Amount; 		
	} 
	else if (Mode == EIncreaseOrDecrease::EIDecrease && bStatChanged)
	{
		AvailableAttributePoints += Amount; 
	}
	
}

//Applies the stats of Race to the Character
void FCharacterCreator::ApplyRaceBaseStats()
{
	for (const FRaceData& Race : AvailableRaces)
	{
		if (Race.Race == Character.CharRace)
		{
			Character.CharStats.Attributes = Race.BaseStat.Attributes;
			return;
		}
	}
}

//Adds the Class Stat modifiers to the Current Character
void FCharacterCreator::ApplyClassModifiers()
{
	for (FClassData& ClassData : AvailableClasses)
	{
		if (Character.CharClass == ClassData.Class)
		{
			Character.CharStats.Attributes[EAttributes::EStr] += ClassData.StatModifier.Attributes[EAttributes::EStr];
			Character.CharStats.Attributes[EAttributes::EDex] += ClassData.StatModifier.Attributes[EAttributes::EDex];
			Character.CharStats.Attributes[EAttributes::ECon] += ClassData.StatModifier.Attributes[EAttributes::ECon];
			Character.CharStats.Attributes[EAttributes::EInt] += ClassData.StatModifier.Attributes[EAttributes::EInt];
			Character.CharStats.Attributes[EAttributes::EWis] += ClassData.StatModifier.Attributes[EAttributes::EWis];
			Character.CharStats.Attributes[EAttributes::ECha] += ClassData.StatModifier.Attributes[EAttributes::ECha];
			return;
		}
	}
}

void FCharacterCreator::SetCharacterHP()
{
	for (FClassData& ClassData :AvailableClasses)
	{
		if (Character.CharClass == ClassData.Class)
		{
			Character.MaxHP = ClassData.BaseHealth + Character.CharStats.Attributes[EAttributes::ECon] * 2;
		}
	}

	Character.CurrentHP = Character.MaxHP;
}

//Sets the character MP based on class, according to the ability they use to cast spells
void FCharacterCreator::SetCharacterMP()
{
	switch (Character.CharClass)
	{
		case EClass::ECWizard : 
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::EInt] * 2;
			break;
		case EClass::ECPaladin :
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::ECha] * 2;
			break;
		case EClass::ECCleric :
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::EWis] * 2;
			break;
		case EClass::ECSorcerer :
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::ECha] * 2;
			break;
		case EClass::ECBard :
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::ECha] * 2;
			break;
		case EClass::ECDruid : 	
			Character.MaxMP = Character.CharStats.Attributes[EAttributes::EWis] * 2;
			break;
		default :
			Character.MaxMP = 0;
	}

	Character.CurrentMP = Character.MaxMP;

}

//Changes ERace to string for any form of printing to console (redundant, but for debugging)
std::string FCharacterCreator::ERaceToString(ERace Race) const
{
	switch (Race)
	{
		case ERace::ERHuman : return "Human";
		case ERace::ERElf : return "Elf";
		case ERace::EROrc : return "Orc";
		case ERace::ERDwarf : return "Dwarf";
		case ERace::ERGnome : return "Gnome";
		case ERace::ERTiefling : return "Tiefling";
		default : return "No Race Selected!";
	}
}

//Changes EClass to string for any form of printing to console (redundant, but for debugging)
std::string FCharacterCreator::EClassToString(EClass Class) const
{
	switch (Class)
	{
		case EClass::ECFighter : return "Fighter";
		case EClass::ECMonk : return "Monk";
		case EClass::ECPaladin : return "Paladin";
		case EClass::ECWizard : return "Wizard";
		case EClass::ECCleric : return "Cleric";
		case EClass::ECSorcerer : return "Sorcerer";
		case EClass::ECBard : return "Bard";
		case EClass::ECDruid : return "Druid";
		case EClass::ECBarabarian: return "Barbarian";
		case EClass::ECRogue: return "Rogue";
		default : return "No Class Selected!";
	}
}

ERace FCharacterCreator::StringToERace(std::string Race) const
{
	if (Race == "Human")
	{
		return ERace::ERHuman;
	}
	else if (Race == "Elf")
	{
		return ERace::ERElf;
	}
	else if (Race == "Orc")
	{
		return ERace::EROrc;
	}
	else if (Race == "Dwarf")
	{
		return ERace::ERDwarf;
	}
	else if (Race == "Gnome")
	{
		return ERace::ERGnome;
	}
	else
	{
		return ERace::ERTiefling;
	}
}

//Changes EClass to string for any form of printing to console (redundant, but for debugging)
EClass FCharacterCreator::StringToEClass(std::string Class) const
{
	if (Class == "Fighter")
	{
		return EClass::ECFighter;
	}
	else if (Class == "Monk")
	{
		return EClass::ECMonk;
	}
	else if (Class == "Paladin")
	{
		return EClass::ECPaladin;
	}
	else if (Class == "Wizard")
	{
		return EClass::ECWizard;
	}
	else if (Class == "Cleric")
	{
		return EClass::ECCleric;
	}
	else if (Class == "Sorcerer")
	{
		return EClass::ECSorcerer;
	}
	else if (Class == "Bard")
	{
		return EClass::ECBard;
	}
	else if (Class == "Druid")
	{
		return EClass::ECDruid;
	}
	else if (Class == "Barbarian")
	{
		return EClass::ECBarabarian;
	}
	else
	{
		return EClass::ECRogue;
	}
}


bool FCharacterCreator::IsCharacterValid() const
{
	if (Character.CharName.empty()) {return false; }

	if (AvailableAttributePoints != 0) { return  false; }

	return true;
}

bool FCharacterCreator::FinalizeCharacter()
{
	if (!IsCharacterValid()) { return false; }

	SetCharacterHP();
	SetCharacterMP();

	bIsFinalised = true;
	return true;
}

template<typename T>
inline void FCharacterCreator::LoadCSV(const std::string& FilePath, std::vector<T>& OutVector)
{
	std::ifstream File(FilePath);

	if (!File.is_open())
	{
		//TODO, notify the UI that the file is not open
		return;
	}

	std::string Line;
	bool bSkipHeader = true;

	while (std::getline(File, Line))
	{
		if (bSkipHeader) { bSkipHeader = false; continue; }

		if (Line.empty()) continue;

		std::vector<std::string> Columns;
		std::stringstream ss(Line);
		std::string Cell;

		while (std::getline(ss, Cell, ','))
		{
			Cell.erase(Cell.find_last_not_of("\r\n") + 1);
			Columns.push_back(Cell);
		}

		if (Columns.size() < 7)
		{
			continue;
		}

		try
		{
			T Row;
			Row.FromCSVRow(Columns);
			OutVector.push_back(Row);
		}
		catch (const std::exception& e)
		{
			return;
		}
	}
}



