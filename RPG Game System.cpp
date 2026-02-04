// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"
#include "Inventory/Inventory.h"

FCharacter CurrentCharacter;
FCharacterCreator Creator;

int main()
{
    for (const FRaceData& Race : Creator.GetAvailableRaces())
    {
        std::cout << "Race: " << Race.RaceName << std::endl;

        std::cout << "Str: " << Race.BaseStat.at(EAbility::EAStr) << std::endl;
        std::cout << "Dex: " << Race.BaseStat.at(EAbility::EADex) << std::endl;
        std::cout << "Con: " << Race.BaseStat.at(EAbility::EACon) << std::endl;
        std::cout << "Int: " << Race.BaseStat.at(EAbility::EAInt) << std::endl;
        std::cout << "Wis: " << Race.BaseStat.at(EAbility::EAWis) << std::endl;
        std::cout << "Cha: " << Race.BaseStat.at(EAbility::EACha) << std::endl << std::endl;
    }

    for (const FClassData& Class : Creator.GetAvailableClasses())
    {
        std::cout << "Class: " << Class.ClassName << std::endl;

        std::cout << "Base Health: " << Class.BaseHealth << std::endl;

        std::cout << "Str Mod: " << Class.StatModifier.at(EAbility::EAStr) << std::endl;
        std::cout << "Str Dex: " << Class.StatModifier.at(EAbility::EADex) << std::endl;
        std::cout << "Str Con: " << Class.StatModifier.at(EAbility::EACon) << std::endl;
        std::cout << "Str Int: " << Class.StatModifier.at(EAbility::EAInt) << std::endl;
        std::cout << "Str Wis: " << Class.StatModifier.at(EAbility::EAWis) << std::endl;
        std::cout << "Str Cha: " << Class.StatModifier.at(EAbility::EACha) << std::endl << std::endl;
    }

    for (const FMaterialData& Material : CurrentCharacter.Inventory.GetAvailableMaterials())
    {
        std::cout << "Material: " << Material.MaterialName << std::endl;
        std::cout << "Material Type: " << Material.Type << std::endl;
        std::cout << "Weight: " << Material.Weight << std::endl << std::endl;
    }

    return 0;
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
