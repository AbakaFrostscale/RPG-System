#include <iostream>

#include "External/catch_amalgamated.hpp"
#include "Creation/CharacterCreation.h"
#include "Character/CharacterStats.h"
#include "Core/LoadExternalData.h"


TEST_CASE("Checking CrateCharacter is setting the correct races(Human Fighter)", "[CharacterCreator]")
{
	FCharacterCreator Creator;
	FCharacterData Character;
	FLoadExternalData Loader;

	for (size_t j = 0; j < Loader.GetAvailableRaces().size(); j++)
	{
		for (size_t i = 0; i < Loader.GetAvailableClasses().size(); i++)
		{
			Creator.CreateCharacter(Character, "Grave", j, i);

			REQUIRE(Character.CharName == "Grave");
			REQUIRE(Character.CharRace.RaceName == Loader.GetAvailableRaces()[j].RaceName);
			REQUIRE(Character.CharClass.ClassName == Loader.GetAvailableClasses()[i].ClassName);
		}
	}
}

TEST_CASE("Increase Strength increases character Strength", "[CharacterCreator]")
{
	FCharacterCreator Creator;
	FCharacterData Character;

	bool bIsFinalized = false;
	Creator.CreateCharacter(Character, "Grave", 0, 0);

	int InitialStrength = Character.CharStats[EAbility::EAStr];

	while (!bIsFinalized)
	{
		Creator.AllocateAttributePoints(Character, "Str", 1, EMode::EMIncrease);

		if (Creator.GetAttributePoints() <= 0)
		{
			bIsFinalized = true;
		}
	}

	REQUIRE(Character.CharStats[EAbility::EAStr] == InitialStrength + 10);
}

TEST_CASE("Test AbilityScoreIncrease(), [CharacterCreator]")
{
	FCharacterCreator Creator;
	FCharacterData Character;

	Creator.CreateCharacter(Character, "Grave", 0, 0);

	
	
}