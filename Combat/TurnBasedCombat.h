//TurnBasedCombat.h
//This file has all the necessary data types and stores used in combat.
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "Core/Random.h"
#include "Character/CharacterStats.h"

class FCharacter;

struct FInitiative
{
	FCombatant* Combatant;
	int InititiveRoll = 0;
};

class FLoadExtrenalData;
class FRandom;

class FTurnBasedCombat
{
public:
	FTurnBasedCombat();

	void SetEnemies(EDifficulty Difficulty);

	void CombatTurn(FCharacter& Character, FEnemyData& Enemy, EAction Action);

	void CalculateInitiative(std::vector<FInitiative>& CombatantInitiative,FCharacterData& Character);

	const std::vector<FEnemyData>& GetEnemyCombatants() const { return EnemyCombatants; }

private:
	std::unique_ptr<FLoadExternalData> Loader;
	std::unique_ptr<FRandom> Random;
	std::unique_ptr<FCharacter> Character;

	std::vector<FEnemyData> EnemyCombatants;

	std::vector<FEnemyData> EnemyMobs;
	std::vector<FEnemyData> EnemyBoss;


};