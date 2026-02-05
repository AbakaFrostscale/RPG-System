// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"
#include "Inventory/Inventory.h"

FCharacter CurrentCharacter;
FCharacterCreator Creator;

void PrintAvailableRaces()
{
    int Index = 1;
    for (const FRaceData& Race : Creator.GetAvailableRaces())
    {
        std::cout << Index << " : Race: " << Race.RaceName << std::endl;

        std::cout << "    Str: " << Race.BaseStat.at(EAbility::EAStr) << std::endl;
        std::cout << "    Dex: " << Race.BaseStat.at(EAbility::EADex) << std::endl;
        std::cout << "    Con: " << Race.BaseStat.at(EAbility::EACon) << std::endl;
        std::cout << "    Int: " << Race.BaseStat.at(EAbility::EAInt) << std::endl;
        std::cout << "    Wis: " << Race.BaseStat.at(EAbility::EAWis) << std::endl;
        std::cout << "    Cha: " << Race.BaseStat.at(EAbility::EACha) << std::endl;

        ++Index;
    }
    std::cout << std::endl;
}

void PrintAvailableClasses()
{
    int Index = 1;
    for (const FClassData& Class : Creator.GetAvailableClasses())
    {
        std::cout << Index << " : Class: " << Class.ClassName << std::endl;

        std::cout << "    Base Health: " << Class.BaseHealth << std::endl;

        std::cout << "    Str Mod: " << Class.StatModifier.at(EAbility::EAStr) << std::endl;
        std::cout << "    Str Dex: " << Class.StatModifier.at(EAbility::EADex) << std::endl;
        std::cout << "    Str Con: " << Class.StatModifier.at(EAbility::EACon) << std::endl;
        std::cout << "    Str Int: " << Class.StatModifier.at(EAbility::EAInt) << std::endl;
        std::cout << "    Str Wis: " << Class.StatModifier.at(EAbility::EAWis) << std::endl;
        std::cout << "    Str Cha: " << Class.StatModifier.at(EAbility::EACha) << std::endl;

        ++Index;
    }
    std::cout << std::endl;
}

void PrintAvailableMaterials(int Type)
{
    int Index = 1;
    for (const FMaterialData& Material : CurrentCharacter.Inventory.GetAvailableMaterials())
    {
        switch (Type)
        {
        case 1:
            if (Material.Type == "Wood")
            {
                std::cout << Index << " : Material: " << Material.MaterialName << std::endl;
                std::cout << "    Weight: " << Material.Weight << std::endl;
            }
            break;
        case 2:
            if (Material.Type == "Metal")
            {
                std::cout << Index << " : Material: " << Material.MaterialName << std::endl;
                std::cout << "    Weight: " << Material.Weight << std::endl;
            }
            break;
        case 3:
            if (Material.Type == "Cloth")
            {
                std::cout << Index << " : Material: " << Material.MaterialName << std::endl;
                std::cout << "    Weight: " << Material.Weight << std::endl;
            }
            break;
        default:
            {
                std::cout << Index << " : Material: " << Material.MaterialName << std::endl;
                std::cout << "    Material Type: " << Material.Type << std::endl;
                std::cout << "    Weight: " << Material.Weight << std::endl;
            }
        }

        ++Index;
    }
    std::cout << std::endl;
}

//void PrintCraftableItems()
//{
//    int Index = 1;
//
//    for (const FItemData& Item : GetCraftableItems())
//    {
//        std::cout << Index << " : Item: " << Item.ItemName << std::endl;
//        std::cout << "    Item Type: " << Item.ItemType << std::endl;
//        std::cout << "    Required Materials: " << std::endl;
//        for (const FMaterialData& Material : CurrentCharacter.Inventory.GetAvailableMaterials())
//        {
//           for (auto& key : Item.RequiredMaterials)
//           {
//               if (key.first == Material.MaterialName)
//               {
//                   std::cout << "    " << key.first << " : " << Item.RequiredMaterials.at(key.first) << std::endl;
//               }
//           }
//        }
//
//        ++Index;
//    }
//    std::cout << std::endl;
//}


int main()
{
    PrintAvailableRaces();

    PrintAvailableClasses();

    PrintAvailableMaterials(4);

    //PrintCraftableItems();


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
