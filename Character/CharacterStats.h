//CharacterStats.h
//Logic-only CharacterStats file that contains all the neccessary stas and types the chracter will need to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include "Core/Types.h" 

struct FCombatant 
{ 
	std::string CharName; 
	int MaxHP = 0;
	int CurrentHP = 0; 
	int MaxMP = 0;
	int CurrentMP = 0; 
	FRaceData CharRace; 
	FClassData CharClass; 
	std::map<EAbility, int> CharStats;
	std::map<EAbility, int> BaseStats;

	ETeam Team = ETeam::ETPlayers;

	bool IsAlive() const { return CurrentHP > 0; } ; 
};

struct FCharacterData : public FCombatant{};
struct FEnemyData : public FCombatant{};

