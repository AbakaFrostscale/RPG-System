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

	void AllocateAttributePoints(std::string UISkill, int UIAmount, EMode UIMode);

	bool IsCharacterValid() const;
	FCharacterData FinalizeCharacter();

	int GetAttributePoints() { return AvailableAttributePoints; }

private:
	FRaceData ChooseRace(std::string RaceIndex);
	void ChooseClass(std::string ClassIndex);

	void ApplyRaceBaseStats();
	void ApplyClassModifiers();

	void SetCharacterHP();
	void SetCharacterMP();

	bool TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode);


private:

	FCharacterData Character;



	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;
	
	bool bIsFinalised;
};


