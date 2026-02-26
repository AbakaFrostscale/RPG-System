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

	ETeam Team = ETeam::ETPlayers;

	bool IsAlive() const { return CurrentHP > 0; } ; 
};

struct FCharacterData : public FCombatant
{
	FRaceData CharRace; 
	FClassData CharClass;

	std::map<EAbility, int> CharStats;
	std::map<EAbility, int> BaseStats;

	std::vector<FSpellData> Spells;
};

struct FEnemyData : public FCombatant
{
	int Damage = 0;
	int Armour = 0;
	std::map<EAbility, int> EnemyStats;

	EType Type = EType::ETMob;
	
	void FromCSVRow(const std::vector<std::string>& Columns)
	{
		CharName = Columns[0];
		MaxHP = std::stoi(Columns[1]);
		CurrentHP = MaxHP;
		MaxMP = std::stoi(Columns[2]);
		CurrentMP = MaxMP;
		Damage = std::stoi(Columns[3]);
		Armour = std::stoi(Columns[4]);

		EnemyStats[EAbility::EAStr] = std::stoi(Columns[5]);
		EnemyStats[EAbility::EADex] = std::stoi(Columns[6]);
		EnemyStats[EAbility::EACon] = std::stoi(Columns[7]);
		EnemyStats[EAbility::EAInt] = std::stoi(Columns[8]);
		EnemyStats[EAbility::EAWis] = std::stoi(Columns[9]);
		EnemyStats[EAbility::EACha] = std::stoi(Columns[10]);

		if (Columns[11] == "Boss")
		{
			Type = EType::ETBoss;
		}
	}
};

