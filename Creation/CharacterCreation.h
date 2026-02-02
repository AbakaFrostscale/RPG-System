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

class FCharacterData;
class FLoadExternalData;

class FCharacterCreator
{
public:
	FCharacterCreator();


	void AllocateAttributePoints(std::string UISkill, int UIAmount, EMode UIMode);

	int GetAttributePoints() { return AvailableAttributePoints; }

private:
	FRaceData ChooseRace(int RaceIndex);
	FClassData ChooseClass(int ClassIndex);

	void ApplyRaceBaseStats(FRaceData& Race, FCharacterData& Character);
	void ApplyClassModifiers(FClassData& Class, FCharacterData& Character);

	int SetCharacterMaxHP(FCharacterData& Character);
	int SetCharacterMaxMP(FCharacterData& Character);

	bool TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode);


private:
	FLoadExternalData Loader;

	FCharacterData Character;

	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses;

	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;
	
	bool bIsFinalised;
};


