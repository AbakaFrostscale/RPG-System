//TurnBasedCombat.h
//This file has all the necessary data types and stores used in combat.
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector>
#include <string>
#include "Core/Random.h"
#include "Character/CharacterStats.h"

class FLoadExtrenalData;

class FTurnBasedCombat
{
public:
	FTurnBasedCombat();

private:
	std::unique_ptr<FLoadExternalData> Loader;


};