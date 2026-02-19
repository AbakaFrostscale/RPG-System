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

	void ApplyRaceBaseStats();
	void ApplyClassModifiers();



private:
	//CharacterCreation
	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses;
  
	void CreateCharacter(FCharacterData& Character, std::string UIName, int UIRace, int UIClass, std::string UISkill, int UIAmount, EMode UIMode);

	bool TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode);	

	std::shared_ptr<FLoadExternalData> GetLoader() { return Loader; }


private:
	std::shared_ptr<FLoadExternalData> Loader;


	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;

	const EAbility StringToEAbility(std::string String);
};


