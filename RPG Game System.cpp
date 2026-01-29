// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"

FCharacterCreator Creator;
FCharacter Character;

FMaterial Iron{ EMaterial::EMIron };
FMaterial Stone{ EMaterial::EMStone };
FMaterial Cloth{ EMaterial::EMCloth };
FMaterial Leather{ EMaterial::EMLeather };
FMaterial Wood{ EMaterial::EMWood };

EAttributes StringToEAttribute(std::string Attribute)
{
    if (Attribute == "Str")
    {
        return EAttributes::EStr;
    }
    else if (Attribute == "Dex")
    {
        return EAttributes::EDex;
    }
    else if (Attribute == "Con")
    {
        return EAttributes::ECon;
    }
    else if (Attribute == "Int")
    {
        return EAttributes::EInt;
    }
    else if (Attribute == "Wis")
    {
        return EAttributes::EWis;
    }
    else if (Attribute == "Cha")
    {
        return EAttributes::ECha;
    }
    else
    {
        return EAttributes::EStr;
    }
}

EIncreaseOrDecrease StringToMode(std::string Mode)
{
    if (Mode == "i")
    {
        return EIncreaseOrDecrease::EIIncrease;
    }
    else if (Mode == "d")
    {
        return EIncreaseOrDecrease::EIDecrease;
    }
    else
    {
        Mode = "Increase";
        return EIncreaseOrDecrease::EIIncrease;
    }
}

void PrintCharacter()
{
    std::cout << Character.CurrentCharacter.CharName << std::endl;

    std::cout << Creator.ERaceToString(Character.CurrentCharacter.CharRace) << std::endl;
    std::cout << Creator.EClassToString(Character.CurrentCharacter.CharClass) << std::endl;

    std::cout << "HP: " << Character.CurrentCharacter.CurrentHP << "/" << Character.CurrentCharacter.MaxHP << std::endl;
    std::cout << "MP: " << Character.CurrentCharacter.CurrentMP << "/" << Character.CurrentCharacter.MaxMP << std::endl;

    std::cout << "STR:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::EStr] << std::endl;
    std::cout << "DEX:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::EDex] << std::endl;
    std::cout << "CON:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::ECon] << std::endl;
    std::cout << "INT:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::EInt] << std::endl;
    std::cout << "WIS:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::EWis] << std::endl;
    std::cout << "CHA:" << Character.CurrentCharacter.CharStats.Attributes[EAttributes::ECha] << std::endl;
}



int main()
{

    std::string Name = "";
    std::string sAttribute;
    std::string sMode;
    
    int Race = 1;
    int Class = 1;
    EAttributes Attribute;
    int Amount;
    EIncreaseOrDecrease mode;

    std::cout << "What is your name adventurer" << std::endl;
    std::cin >> Name;

    std::cout << "Pick a race using numbers" << std::endl;
    int RaceIndex = 1;
    for (FRaceData& Race : Creator.GetAvailableRaces())
    {
        std::cout << RaceIndex << " : " << Race.RaceName << std::endl;
        ++RaceIndex;
    }
    std::cin >> Race;

    std::cout << "Pick a class using numbers 1-9" << std::endl;
    int ClassIndex = 1;
    for (FClassData& Class : Creator.GetAvailableClasses())
    {
        std::cout << ClassIndex << " : " << Class.ClassName << std::endl;
        ++ClassIndex;
    }
    std::cin >> Class;

   Creator.CreateCharacter(Name, Race, Class);

    while (Creator.GetAttributePoints() > 0)
    {
        std::cout << "Which stat would you like to modify?" << std::endl;
        std::cin >> sAttribute;
        Attribute = StringToEAttribute(sAttribute);

        std::cout << "Would you like to Increase(i) or Decrease(d) your " << sAttribute << std::endl;
        std::cin >> sMode;
        mode = StringToMode(sMode);

        std::cout << "By how much would you like to " << sMode << " your " << sAttribute << std::endl;
        std::cin >> Amount;

        Creator.AllocateAttributePoints(Attribute, Amount, mode);

        std::cout << sAttribute << " " << sMode << " by " << Amount << std::endl;
        std::cout << Creator.GetAttributePoints() << " attribute points available" << std::endl;
    }

    Character.CurrentCharacter = Creator.FinalizeCharacter();

    PrintCharacter();

    while (Character.CurrentCharacter.IsAlive())
    {
        std::string Action;
        std::cout << "What do you feel like doing? Craft(c), Equip(e) Battle(b), Gather(g)" << std::endl;
        std::cin >> Action;

        if (Action == "g")
        {
            std::string Material;
            std::cout << "What would you like to gather?" << std::endl;
            std::cout << "Iron(i), Stone(s), Cloth(c), Leather(l), Wood(w)";
            std::cin >> Material;
            if (Material == "i")
            {
                Character.GatherMaterials(Iron);
            }
            else if (Material == "s")
            {
                Character.GatherMaterials(Stone);
            }
            else if (Material == "l")
            {
                Character.GatherMaterials(Leather);
            }
            else if (Material == "w")
            {
                Character.GatherMaterials(Wood);
            }
        }

        if (Action == "c")
        {
            std::string Craft;
            int CraftChoice;
            std::cout << "Would you like to craft a Weapon(w) or Armour(a)?" << std::endl;
            
            std::cin >> Craft;
            if (Craft == "w")
            { 
                int CraftIndex = 1;
                for (FWeapon& Item : Character.Crafter.GetCraftableWeapons())
                {
                    std::cout << CraftIndex << " : " << Item.ItemName << std::endl;
                    ++CraftIndex;
                }
                std::cin >> CraftChoice;
                Character.CraftWeapon(Character.Crafter.GetCraftableWeapons()[CraftChoice]);

                std::cout << Character.Crafter.GetCraftableWeapons()[CraftChoice].ItemName << " added to the inventory";
            }
            else
            {
                int CraftIndex = 1;
                for (FArmour& Item : Character.Crafter.GetCraftableArmour())
                {
                    std::cout << CraftIndex << " : " << Item.ItemName << std::endl;
                    ++CraftIndex;
                }
                std::cin >> CraftChoice;
                Character.CraftArmour(Character.Crafter.GetCraftableArmour()[CraftChoice]);

                std::cout << Character.Crafter.GetCraftableArmour()[CraftChoice].ItemName << " added to the inventory";
            }
        }
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
