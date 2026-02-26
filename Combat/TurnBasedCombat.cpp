//TurnBasedCombat.cpp
//Manages the full extent of comabt calling all of the necessary functions from Character and The rest of the program 
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "Core/LoadExternalData.h"
#include "Core/Random.h"
#include "Combat/TurnBasedCombat.h"

FTurnBasedCombat::FTurnBasedCombat()
{
	Loader = std::make_unique<FLoadExternalData>();

	Random = std::make_unique<FRandom>();
	Random->RandomGenerator = std::mt19937(Random->rd());

	for (const FEnemyData& Enemy : Loader->GetEnemies())
	{
		if (Enemy.Type == EType::ETMob)
		{
			EnemyMobs.push_back(Enemy);
		}
		else
		{
			EnemyBoss.push_back(Enemy);
		}
	}
}

void FTurnBasedCombat::SetEnemies(EDifficulty Difficulty)
{
	EnemyCombatants.clear();

	int AmountEnemies = 0;

	switch (Difficulty)
	{
		case EDifficulty::EDEasy :
		{
			std::uniform_int_distribution<int> AmountDistEnemies(2, 3);
			AmountEnemies = AmountDistEnemies(Random->RandomGenerator);


			for (int i = 0; i < AmountEnemies; i++)
			{
				std::uniform_int_distribution<int> AmountDistMobs(0, EnemyMobs.size() - 1);
				int RandomMob = AmountDistMobs(Random->RandomGenerator);
				
				EnemyCombatants.emplace_back(EnemyMobs[RandomMob]);
			}
			break;
		}
		case EDifficulty::EDMedium :
		{
			std::uniform_int_distribution<int> AmountDistEnemies(2, 6);
			AmountEnemies = AmountDistEnemies(Random->RandomGenerator);

			std::uniform_int_distribution<int> AmountDistMobs(0, EnemyMobs.size() - 1);
			int RandomMob = AmountDistMobs(Random->RandomGenerator);

			std::uniform_int_distribution<int> AmountDistBossChance(0, 10);
			int RandomChance = AmountDistBossChance(Random->RandomGenerator);

			if (RandomChance == 10)
			{
				std::uniform_int_distribution<int> AmountDistBoss(0, EnemyMobs.size() - 1);
				int RandomBoss = AmountDistBoss(Random->RandomGenerator);

				EnemyCombatants.push_back(EnemyBoss[RandomBoss]);
			}

			for (int i = 0; i < AmountEnemies; i++)
			{
				EnemyCombatants.push_back(EnemyMobs[RandomMob]);
			}
			break;
		}
		case EDifficulty::EDHard :
		{
			std::uniform_int_distribution<int> AmountDistEnemies(2, 4);
			AmountEnemies = AmountDistEnemies(Random->RandomGenerator);

			std::uniform_int_distribution<int> AmountDistMobs(0, EnemyMobs.size());
			int RandomMob = AmountDistMobs(Random->RandomGenerator);

			std::uniform_int_distribution<int> AmountDistBoss(0, EnemyMobs.size());
			int RandomBoss = AmountDistBoss(Random->RandomGenerator);

			EnemyCombatants.push_back(EnemyBoss[RandomBoss]);

			for (int i = 0; i < AmountEnemies; i++)
			{
				EnemyCombatants.push_back(EnemyMobs[RandomMob]);
			}	
			break;
		}
	}
}

void FTurnBasedCombat::CombatTurn(FCharacterData& Character, FEnemyData& Enemy)
{
}








