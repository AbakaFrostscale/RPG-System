//CharacterCreator.h
//CharacterCreator.h file hold all the information for CharacterCreator.cpp to build a character
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "Core/Types.h"
#include "Character/CharacterStats.h"

class FCharacterCreator
{
public:
	FCharacterCreator();
	FCharacterData CreateCharacter(std::string UIName, int UIRace, int UIClass, EAttributes UISkill, int UIAmount, EIncreaseOrDecrease Mode);

	std::string ERaceToString(ERace Race) const;
	std::string EClassToString(EClass Class) const;

private:
	void ChooseRace(int RaceIndex);
	void ChooseClass(int ClassIndex);

	void AllocateAttributePoints(EAttributes Skill, int Amount, EIncreaseOrDecrease Mode);
	void ApplyRaceBaseStats();
	void ApplyClassModifiers();

	void SetCharacterHP();
	void SetCharacterMP();

	bool TryAllocatePoints(int& Current, int Base, int Amount, EIncreaseOrDecrease Mode);

	bool IsCharacterValid() const;
	bool FinalizeCharacter();

private:

	FCharacterData Character;
	template<typename T>
	void LoadCSV(const std::string& FilePath, std::vector<T>& OutVector);

	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses;

	ERace StringToERace(std::string Race) const;
	EClass	StringToEClass(std::string Class) const;

	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;
	
	bool bIsFinalised;
};


