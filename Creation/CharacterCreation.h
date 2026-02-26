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

	void CreateCharacter(FCharacterData& Character, std::string UIName, int UIRace, int UIClass);
	void AllocateAttributePoints(FCharacterData& Character, std::string UISkill, int UIAmount, EMode UIMode);
	void SetHPandMP(FCharacterData& Character);

	FRaceData ChooseRace(int RaceIndex);
	FClassData ChooseClass(int ClassIndex);

	void ApplyRaceBaseStats(FCharacterData& Character);
	void ApplyClassModifiers(FCharacterData& Character);

	int CalculateCharacterMaxHP(FCharacterData& Character);
	int CalculateCharacterMaxMP(FCharacterData& Character);

	void SetCharacterSpells(FCharacterData& Character);

	const int GetAttributePoints() const { return AvailableAttributePoints; }
	const std::shared_ptr<FLoadExternalData> GetLoader() { return Loader; }

private: 
	bool TryAllocatePoints(int& Current, int Base, int Amount, EMode Mode);	

	std::shared_ptr<FLoadExternalData> Loader;

	int AvailableAttributePoints = 10;
	int MaxAttributePoints = 10;

	const EAbility StringToEAbility(std::string String);
};


