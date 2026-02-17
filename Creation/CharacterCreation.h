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


class FLoadExternalData;
struct FCharacterData;

class FCharacterCreator
{
public:
	FCharacterCreator();

	void AllocateAttributePoints(FCharacterData& Character, std::string UISkill, int UIAmount, EMode UIMode);

	const int GetAttributePoints() const { return AvailableAttributePoints; }

	FRaceData ChooseRace(int RaceIndex);
	FClassData ChooseClass(int ClassIndex);

	void ApplyRaceBaseStats(FCharacterData& Character);
	void ApplyClassModifiers(FCharacterData& Character);

	int CalculateCharacterMaxHP(FCharacterData& Character);
	int CalculateCharacterMaxMP(FCharacterData& Character);

	bool TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode);
	const FLoadExternalData* GetLoader() { return Loader; }	//CharacterCreation
	const std::vector<FRaceData>& GetAvailableRaces() const { return AvailableRaces; }
	const std::vector<FClassData>& GetAvailableClasses() const { return AvailableClasses; }



private:
	//CharacterCreation
	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses;
	
	FLoadExternalData* Loader;

	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;

	const EAbility StringToEAbility(std::string String);
};


