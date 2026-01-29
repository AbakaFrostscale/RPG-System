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

	void CreateCharacter(std::string UIName, int UIRace, int UIClass);
	void AllocateAttributePoints(EAttributes UISkill, int UIAmount, EIncreaseOrDecrease UIMode);

	std::string ERaceToString(ERace Race) const;
	std::string EClassToString(EClass Class) const;

	bool IsCharacterValid() const;
	FCharacterData FinalizeCharacter();

	int GetAttributePoints() { return AvailableAttributePoints; }
	std::vector<FRaceData> GetAvailableRaces() { return AvailableRaces; }
	std::vector<FClassData> GetAvailableClasses() { return AvailableClasses; }

private:
	void ChooseRace(int RaceIndex);
	void ChooseClass(int ClassIndex);

	void ApplyRaceBaseStats();
	void ApplyClassModifiers();

	void SetCharacterHP();
	void SetCharacterMP();

	bool TryAllocatePoints(int& Current, int Base, int Amount, EIncreaseOrDecrease Mode);


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


