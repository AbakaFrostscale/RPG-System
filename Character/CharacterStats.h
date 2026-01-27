//CharacterStats.h
//Logic-only CharacterStats file that contains all the neccessary stas and types the chracter will need to access
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include "Core/Types.h" 

struct FCharacterData 
{ 
	std::string CharName; 
	int MaxHP = 0;
	int CurrentHP = 0; 
	int MaxMP = 0;
	int CurrentMP = 0; 
	ERace CharRace = ERace::ERHuman; 
	EClass CharClass = EClass::ECFighter; 
	FAttributes CharStats;
	FAttributes BaseStats;

	bool IsAlive() const { return CurrentHP > 0; } ; 
};

