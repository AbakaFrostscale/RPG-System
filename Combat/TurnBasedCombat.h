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

struct FInitiative
{
	FCombatant* Combatant;
	int InititiveRoll = 0;
};

class FLoadExtrenalData;
class FRandom;
class FCharacter;

class FTurnBasedCombat
{
public:
	FTurnBasedCombat();

	void SetEnemies(EDifficulty Difficulty);

	void CombatRound(FInitiative& Combatants, FCombatant* Target, EAction UIAction, FCharacterData& Player);

	void PlayerTurn(FCombatant* Attacker, FCombatant* Target, EAction Action);
	void EnemyTurn(FCombatant* Attacker, FCombatant* Target, EAction Action);

	void CalculateInitiative(std::vector<FInitiative>& CombatantInitiative,FCharacterData& Character);

	const std::vector<FEnemyData>& GetEnemyCombatants() const { return EnemyCombatants; }

private:
	std::unique_ptr<FLoadExternalData> Loader;
	std::unique_ptr<FRandom> Random;

	std::vector<FEnemyData> EnemyCombatants;
	std::vector<FCharacterData*> PlayerCombatants;

	std::vector<FEnemyData> EnemyMobs;
	std::vector<FEnemyData> EnemyBoss;
};