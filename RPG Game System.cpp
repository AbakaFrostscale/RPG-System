// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
<<<<<<< Updated upstream
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"
=======

#include "Core/LoadExternalData.h"
#include "Core/Random.h"

#include "Character/Character.h"
#include "Creation/CharacterCreation.h"

#include "Inventory/Inventory.h"  
>>>>>>> Stashed changes

FCharacterCreator Creator;
<<<<<<< Updated upstream
FCharacter Character;
=======
FItem MainItem;
FRandom Random;
>>>>>>> Stashed changes

FMaterial Iron{ EMaterial::EMIron };
FMaterial Stone{ EMaterial::EMStone };
FMaterial Cloth{ EMaterial::EMCloth };
FMaterial Leather{ EMaterial::EMLeather };
FMaterial Wood{ EMaterial::EMWood };

<<<<<<< Updated upstream
EAttributes StringToEAttribute(std::string Attribute)
=======

std::string EAbilityToString(EAbility Ability)
>>>>>>> Stashed changes
{
    if (Attribute == "Str")
    {
        return EAttributes::EStr;
    }
<<<<<<< Updated upstream
    else if (Attribute == "Dex")
=======
}

void PrintAvailableRaces()
{
    int Index = 1;
    for (const FRaceData& Race : Creator.GetLoader()->GetAvailableRaces())
>>>>>>> Stashed changes
    {
        return EAttributes::EDex;
    }
<<<<<<< Updated upstream
    else if (Attribute == "Con")
=======
    std::cout << std::endl;
}

void PrintAvailableClasses()
{
    int Index = 1;
    for (const FClassData& Class : Creator.GetLoader()->GetAvailableClasses())
>>>>>>> Stashed changes
    {
        return EAttributes::ECon;
    }
<<<<<<< Updated upstream
    else if (Attribute == "Int")
=======
    std::cout << std::endl;
}

void PrintAvailableMaterials(int Type)
{
    int Index = 1;
    for (const FMaterialData& Material : MainItem.GetLoader()->GetAvailableMaterials())
>>>>>>> Stashed changes
    {
        return EAttributes::EInt;
    }
<<<<<<< Updated upstream
    else if (Attribute == "Wis")
=======
    std::cout << std::endl;
}

void PrintCraftableItems()
{
    int Index = 1;

    for (const FItemData& Item : MainItem.GetLoader()->GetAvailableItems())
>>>>>>> Stashed changes
    {
        return EAttributes::EWis;
    }
    else if (Attribute == "Cha")
    {
<<<<<<< Updated upstream
        return EAttributes::ECha;
=======
        std::cout << Index << " : Item: " << Weapon.WeaponData->ItemName << std::endl;
        std::cout << "    Required Materials: " << std::endl;
        for (const FMaterialData& Material : MainItem.GetLoader()->GetAvailableMaterials())
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
        for (const FMaterialData& Material : MainItem.GetLoader()->GetAvailableMaterials())
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

void PrintInventory(FCharacter& Character)
{
    std::cout << "Materials: " << std::endl;
    for (const FMaterial& Mat : Character.Inventory.GetMaterials())
    {
        std::cout << Mat.Material->MaterialName << " : " << Mat.MaterialAmount << std::endl;
    }

    std::cout << std::endl << "Weapons: " << std::endl;
    for (const FWeapon& Wep : Character.Inventory.GetWeapons())
    {
        std::cout << Wep.WeaponData->ItemName << std::endl;
        std::cout << EAbilityToString(Wep.RequiredStat) << " : " << Wep.RequiredStatAmount << std::endl;
        for (const FMaterial& WepMat : Wep.WeaponData->RequiredMaterial)
        {
            std::cout << WepMat.Material->MaterialName << " : " << WepMat.MaterialAmount << std::endl;
        }
        std::cout << "Damage: " << Wep.Damage << std::endl;
    }

    std::cout << std::endl << "Armour:" << std::endl;
    for (const FArmour& Arm : Character.Inventory.GetArmour())
    {
        std::cout << Arm.ArmourData->ItemName << std::endl;
        std::cout << EAbilityToString(Arm.RequiredStat) << " : " << Arm.RequiredStatAmount << std::endl;
        for (const FMaterial& ArmMat : Arm.ArmourData->RequiredMaterial)
        {
            std::cout << ArmMat.Material->MaterialName << " : " << ArmMat.MaterialAmount << std::endl;
        }
        std::cout << "Defence: " << Arm.Defence << std::endl;
    }

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
    Random.RandomGenerator = std::mt19937(Random.rd());
   /*
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

    std::cout << "Next select a race for your character (1-" << Creator.GetLoader()->GetAvailableRaces().size() << ")" << std::endl ;
    PrintAvailableRaces();
    std::cin >> RaceIndex;

    std::cout << "Next you will have to select what class your character is (1-" << Creator.GetLoader()->GetAvailableClasses().size() << ")" << std::endl;
    PrintAvailableClasses();
    std::cin >> ClassIndex;

    Creator.CreateCharacter(CurrentCharacter.GetCharacterReference(), CharName, RaceIndex - 1, ClassIndex - 1, Skill, Amount, Mode);

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
        std::cout << std::endl;

        std::cout << "Would you like to Increase(1) or Decrease(2) the ability?" << std::endl;
        std::cin >> ModeIndex;
        Mode = SelectMode(ModeIndex);
        std::cout << std::endl;
        

        std::cout << "Select by how much no more than: " << Creator.GetAttributePoints() << std::endl;
        std::cin >> Amount;
        std::cout << std::endl;


        Creator.AllocateAttributePoints(CurrentCharacter.GetCharacterReference(),Skill, Amount, Mode);
        std::cout << std::endl;

        if (Creator.GetAttributePoints() <= 0)
        {
            bIsFinalised = true;
        }
    }


    if (bIsFinalised)
    {
        CurrentCharacter.SetHPandMP();
        std::cout << "This is you:" << std::endl;
        PrintCharacter(CurrentCharacter.GetCharacter());
>>>>>>> Stashed changes
    }
    else
    {
        return EAttributes::EStr;
    }
}

<<<<<<< Updated upstream
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
=======
    int ActionIndex = 0;

    while (CurrentCharacter.GetCharacter().IsAlive())
    {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "Gather Materials(1), Craft Items(2), Equip Items(3), Fight(4)?" << std::endl;
        std::cin >> ActionIndex;


        switch (ActionIndex)
        {
        case 1:
            {
                int MaterialIndex = 0;
                int MaterialTypeIndex = 0;

                std::cout << "What material type are you looking for Wood(1), Metal(2), Cloth(3), All(4)" << std::endl;
                std::cin >> MaterialTypeIndex;
                PrintAvailableMaterials(MaterialTypeIndex);

                std::cout << "What material would you like to gather?" << std::endl;
                std::cin >> MaterialIndex;

                const FMaterialData& Material = MainItem.GetLoader()->GetAvailableMaterials()[MaterialIndex - 1];
                CurrentCharacter.GatherMaterials(&Material);

                for (const FMaterial& Materials : CurrentCharacter.Inventory.GetMaterials())
                {
                    if (Materials.Material->MaterialName == Material.MaterialName)
                    {
                        std::cout << "You now have " << Materials.MaterialAmount << " " << Materials.Material->MaterialName << std::endl;
                    }
                }
                break;
            }
        case 2:
            {
                int ItemTypeIndex = 0;
                int ItemIndex = 0;
                
                std::cout << "You currently have: ";
                PrintInventory(CurrentCharacter);

                if (CurrentCharacter.Inventory.GetMaterials().empty())
                {
                    std::cout << "You have no materials, go gather some!" << std::endl << std::endl;
                    break;
                }

                std::cout << "Would you like to craft Weapons(1) or Armour(2)" << std::endl;
                std::cin >> ItemTypeIndex;
                std::cout << std::endl << "Which item would you like to craft?" << std::endl;
                
                switch (ItemTypeIndex)
                {
                    case 1:
                        PrintAvailableWeapons();
                        std::cin >> ItemIndex;
                        CurrentCharacter.CraftWeapon(MainItem.GetCraftableWeapons().at(ItemIndex - 1));

                        for (const FWeapon & Weapon : CurrentCharacter.Inventory.GetWeapons())
                        {
                           if (!CurrentCharacter.Inventory.GetWeapons().empty())
                           {
                                std::cout << "You now have a " << Weapon.WeaponData->ItemName << " in your inventory!" << std::endl;
                           }
                           else
                           {
                               std::cout << "The item was not crafted" << std::endl;
                           }
                       }

                        break;
                    case 2: 
                        PrintAvailableArmour();
                        std::cin >> ItemIndex;
                        CurrentCharacter.CraftArmour(MainItem.GetCraftableArmour().at(ItemIndex - 1));

                        for (const FArmour& Armour : CurrentCharacter.Inventory.GetArmour())
                        {
                            std::cout << "You now have a " << Armour.ArmourData->ItemName << " in your inventory!" << std::endl;
                        }
                        break;
                    default:
                        std::cout << "That is not a valid selection try again!" << std::endl << std::endl;
                        break;
                }
                break;
            }
        case 3:
            {

                break;
            }
        case 4:
            {

                break;
            }
        default:
            {

                break;
            }
        }

    }
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream


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

=======
>>>>>>> Stashed changes
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
