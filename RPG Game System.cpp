// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Core/LoadExternalData.h"
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"
#include "Inventory/Inventory.h"

FCharacter CurrentCharacter;
FCharacterCreator Creator;
FItem MainItem;

bool bIsFinalised;

std::string EAbilityToString(EAbility Ability)
{
    switch (Ability)
    {
    case EAbility::EAStr: return "Strength";
    case EAbility::EADex: return "Dexterity";
    case EAbility::EACon: return "Constitution";
    case EAbility::EAInt: return "Intelligence";
    case EAbility::EAWis: return "Wisdom";
    case EAbility::EACha: return "Charisma";
    default: return "None";
    }
}

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
    for (const FMaterialData& Material : MainItem.GetAvailableMaterials())
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

void PrintCraftableItems()
{
    int Index = 1;

    for (const FItemData& Item : MainItem.GetAvailableItems())
    {
        std::cout << Index << " : Item: " << Item.ItemName << std::endl;
        std::cout << "    Item Type: " << Item.ItemType << std::endl;
     
        ++Index;
    }
    std::cout << std::endl;
}

void  PrintAvailableWeapons()
{
    int Index = 1;

    for (const FWeapon& Weapon : MainItem.GetCraftableWeapons())
    {
        std::cout << Index << " : Item: " << Weapon.WeaponData->ItemName << std::endl;
        std::cout << "    Required Materials: " << std::endl;
        for (const FMaterialData& Material : MainItem.GetAvailableMaterials())
        {
            for (const FMaterial& WepMateral : Weapon.WeaponData->RequiredMaterial)
            {
                if (Material.MaterialName == WepMateral.Material->MaterialName)
                {
                    std::cout << "       " << Material.MaterialName << " : " << WepMateral.MaterialAmount << std::endl;
                    break;
                }
            }
        }
        std::cout << "    Damage: " << Weapon.Damage << std::endl;
        std::cout << "    Required Stat:" << std::endl;
        std::cout << "       " << EAbilityToString(Weapon.RequiredStat) << " : " << Weapon.RequiredStatAmount << std::endl;
        ++Index;
    }
    std::cout << std::endl;
}     

void PrintAvailableArmour()
{
    int Index = 1;

    for (const FArmour& Armour : MainItem.GetCraftableArmour())
    {
        std::cout << Index << " : Item: " << Armour.ArmourData->ItemName << std::endl;
        std::cout << "    Required Materials: " << std::endl;
        for (const FMaterialData& Material : MainItem.GetAvailableMaterials())
        {
            for (const FMaterial& ArmMateral : Armour.ArmourData->RequiredMaterial)
            {
                if (Material.MaterialName == ArmMateral.Material->MaterialName)
                {
                    std::cout << "       " << Material.MaterialName << " : " << ArmMateral.MaterialAmount << std::endl;
                    break;
                }
            }
        }
        std::cout << "    Defence: " << Armour.Defence << std::endl;
        std::cout << "    Required Stat:" << std::endl;
        std::cout << "       " << EAbilityToString(Armour.RequiredStat) << " : " << Armour.RequiredStatAmount << std::endl;
        ++Index;
    }
    std::cout << std::endl;
}

void PrintCharacter(FCharacterData Character)
{
    std::cout << Character.CharName << std::endl;;
    std::cout << Character.CharRace.RaceName << std::endl;
    std::cout << Character.CharClass.ClassName << std::endl;
    
    std::cout << "Str: " << Character.CharStats[EAbility::EAStr] << std::endl;
    std::cout << "Dex: " << Character.CharStats[EAbility::EADex] << std::endl;
    std::cout << "Con: " << Character.CharStats[EAbility::EACon] << std::endl;
    std::cout << "Int: " << Character.CharStats[EAbility::EAInt] << std::endl;
    std::cout << "Wis: " << Character.CharStats[EAbility::EAWis] << std::endl;
    std::cout << "Cha: " << Character.CharStats[EAbility::EACha] << std::endl;
    
    std::cout << Character.CurrentHP << "/" << Character.MaxHP << std::endl;
    std::cout << Character.CurrentMP << "/" << Character.MaxMP << std::endl;
}

std::string SelectAbility(int Skill)
{
    switch (Skill)
    {
    case 1: return "Str";
    case 2: return "Dex";
    case 3: return "Con";
    case 4: return "Int";
    case 5: return "Wis";
    case 6: return "Cha";
    default: return "None";
   }
}

EMode SelectMode(int Mode)
{
    switch (Mode)
    {
    case 1: return EMode::EMIncrease;
    case 2: return EMode::EMDecrease;
    default: return EMode::EMIncrease;
    }
}

int main()
{
    bIsFinalised = false;
   /*
    PrintAvailableMaterials(4);

    PrintAvailableWeapons();

    PrintAvailableArmour();*/

    std::string CharName = "Toby";
    int RaceIndex = 0;
    int ClassIndex = 0;

    std::string Skill = "Str";
    int SkillIndex = 0;
    
    int Amount = 0;
    
    EMode Mode = EMode::EMIncrease;
    int ModeIndex;

    std::cout << "Please choose a name for your characeter : ";
    std::cin >> CharName;

    std::cout << "Next select a race for your character (1-" << Creator.GetAvailableRaces().size() << ")" << std::endl ;
    PrintAvailableRaces();
    std::cin >> RaceIndex;

    std::cout << "Next you will have to select what class your character is (1-" << Creator.GetAvailableClasses().size() << ")" << std::endl;
    PrintAvailableClasses();
    std::cin >> ClassIndex;

    CurrentCharacter.CreateCharacter(CharName, RaceIndex - 1, ClassIndex - 1, Skill, Amount, Mode);

    while (Creator.GetAttributePoints() >= 0)
    {
        if (bIsFinalised) { break; }
       
        std::cout << "Please choose a skill to increase (1-6)" << std::endl;
        std::cout << "1: Strength" << std::endl;
        std::cout << "2: Dexterity" << std::endl;
        std::cout << "3: Constitution" << std::endl;
        std::cout << "4: Intelligence" << std::endl;
        std::cout << "5: Wisdom" << std::endl;
        std::cout << "6: Charisma" << std::endl; 
        std::cin >> SkillIndex;
        Skill = SelectAbility(SkillIndex);

        std::cout << "Would you like to Increase(1) or Decrease(2) the ability?" << std::endl;
        std::cin >> ModeIndex;
        Mode = SelectMode(ModeIndex);
        

        std::cout << "Select by how much no more than: " << Creator.GetAttributePoints() << std::endl;
        std::cin >> Amount;


        Creator.AllocateAttributePoints(CurrentCharacter.GetCharacterReference(),Skill, Amount, Mode);


        if (Creator.GetAttributePoints() <= 0)
        {
            bIsFinalised = true;
        }
    }


    if (bIsFinalised)
    {
        PrintCharacter(CurrentCharacter.GetCharacter());
    }
    else
    {
        std::cerr << "Somtehing went wrong with Character Creation" << std::endl << "Please restart the game";
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
