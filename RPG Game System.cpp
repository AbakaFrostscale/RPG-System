// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"

FCharacterCreator Creator;
FCharacter Character;

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

    std::cout << "Pick a race using numbers 1-6" << std::endl;
    std::cin >> Race;

    std::cout << "Pick a class using numbers 1-9" << std::endl;
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
