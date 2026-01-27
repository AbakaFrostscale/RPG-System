// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"

FCharacterCreator Creator;
FCharacter Character;

int main()
{

    std::string Name = "Steve";
    int Race = 3;
    int Class = 4;
    EAttributes Attribute = EStr;
    int Amount = 10;
    EIncreaseOrDecrease mode = EIncreaseOrDecrease::EIIncrease;

    Character.CurrentCharacter = Creator.CreateCharacter(Name, Race, Class, Attribute, Amount, mode);

    std::cout << Character.CurrentCharacter.CharName << std::endl;

    std::cout << Creator.ERaceToString(Character.CurrentCharacter.CharRace) << std::endl;
    std::cout << Creator.EClassToString(Character.CurrentCharacter.CharClass) << std::endl;

    std::cout << "HP: " << Character.CurrentCharacter.CurrentHP << "/" << Character.CurrentCharacter.MaxHP << std::endl;
    std::cout << "MP: " << Character.CurrentCharacter.CurrentMP << "/" << Character.CurrentCharacter.MaxMP << std::endl;

    std::cout << "STR:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::EStr] << std::endl;
    std::cout << "DEX:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::EDex] << std::endl;
    std::cout << "CON:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::ECon] << std::endl;
    std::cout << "INT:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::EInt] << std::endl;
    std::cout << "WIS:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::EWis] << std::endl;
    std::cout << "CHA:" << Character.CurrentCharacter.BaseStats.Attributes[EAttributes::ECha] << std::endl;

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
