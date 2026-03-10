// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Core/LoadExternalData.h"
#include "Core/Random.h"

#include "Character/Character.h"
#include "Creation/CharacterCreation.h"
#include "Inventory/Inventory.h"

#include "Combat/TurnBasedCombat.h"

FTurnBasedCombat Combat;
FCharacter CurrentCharacter;
FCharacterCreator Creator;
FItem MainItem;

bool bIsFinalised;


static std::string EAbilityToString(EAbility Ability)

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

static std::string ETypeToString(EType Type)
{
	switch (Type)
	{
	case EType::ETMob: return "Mob";
	case EType::ETBoss: return "Boss";
	default: return "Mob";
	}
}

static EDifficulty IntToEDifficulty(int Difficuty)
{
	switch (Difficuty)
	{
	case 1: return EDifficulty::EDEasy;
	case 2: return EDifficulty::EDMedium;
	case 3: return EDifficulty::EDHard;
	default: return EDifficulty::EDEasy;
	}
}

static void PrintAvailableRaces()
{
	int Index = 1;

	for (const FRaceData& Race : Creator.GetLoader()->GetAvailableRaces())
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

static void PrintAvailableClasses()
{
	int Index = 1;

	for (const FClassData& Class : Creator.GetLoader()->GetAvailableClasses())
	{
		std::cout << Index << " : Class: " << Class.ClassName << std::endl;

		std::cout << "    Str: " << Class.StatModifier.at(EAbility::EAStr) << std::endl;
		std::cout << "    Dex: " << Class.StatModifier.at(EAbility::EADex) << std::endl;
		std::cout << "    Con: " << Class.StatModifier.at(EAbility::EACon) << std::endl;
		std::cout << "    Int: " << Class.StatModifier.at(EAbility::EAInt) << std::endl;
		std::cout << "    Wis: " << Class.StatModifier.at(EAbility::EAWis) << std::endl;
		std::cout << "    Cha: " << Class.StatModifier.at(EAbility::EACha) << std::endl;

		++Index;
	}
	std::cout << std::endl;
}

static void PrintAvailableMaterials(int Type)
{
	int Index = 1;
	for (const FMaterialData& Material : MainItem.GetLoader()->GetAvailableMaterials())
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

static void PrintCraftableItems()
{
	int Index = 1;

	for (const FItemData& Item : MainItem.GetLoader()->GetAvailableItems())
	{
		std::cout << Index << " : Item: " << Item.ItemName << std::endl;
		std::cout << "    Item Type: " << Item.ItemType << std::endl;

		++Index;
	}
	std::cout << std::endl;
}


static void  PrintAvailableWeapons()
{
	int Index = 1;

	for (const FWeapon& Weapon : MainItem.GetCraftableWeapons())
	{
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

static void PrintAvailableArmour()
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
};

static void PrintInventoryMaterials(FCharacter& Character)
{
	std::cout << "Materials:" << std::endl;
	for (const FMaterial& Mat : Character.GetInventory()->GetMaterials())
	{
		std::cout << Mat.Material->MaterialName << " : " << Mat.MaterialAmount << std::endl;
	}
}

static void PrintInventoryWeapons(FCharacter& Character)
{
	int Index = 1;
	std::cout << std::endl << "Weapons: " << std::endl;
	for (const FWeapon& Wep : Character.GetInventory()->GetWeapons())
	{
		std::cout << Index << " : " << Wep.WeaponData->ItemName << std::endl;
		std::cout << "   " << EAbilityToString(Wep.RequiredStat) << " : " << Wep.RequiredStatAmount << std::endl;
		std::cout << "   Damage: " << Wep.Damage << std::endl;

		++Index;
	}
}

static void PrintInventoryArmour(FCharacter& Character)
{
	int Index = 1;
	std::cout << std::endl << "Armour: " << std::endl;
	for (const FArmour& Arm : Character.GetInventory()->GetArmour())
	{
		std::cout << Index << " : " << Arm.ArmourData->ItemName << std::endl;
		std::cout << "   " << EAbilityToString(Arm.RequiredStat) << " : " << Arm.RequiredStatAmount << std::endl;
		std::cout << "   Defence: " << Arm.Defence << std::endl;

		++Index;
	}
}


static void PrintCharacter(const FCharacterData& Character)
{
	std::cout << Character.CharName << " the " << Character.CharRace.RaceName << " " << Character.CharClass.ClassName << std::endl;
	
	std::cout << "Str: " << Character.CharStats.at(EAbility::EAStr) << std::endl;
	std::cout << "Dex: " << Character.CharStats.at(EAbility::EADex) << std::endl;
	std::cout << "Con: " << Character.CharStats.at(EAbility::EACon) << std::endl;
	std::cout << "Int: " << Character.CharStats.at(EAbility::EAInt) << std::endl;
	std::cout << "Wis: " << Character.CharStats.at(EAbility::EAWis) << std::endl;
	std::cout << "Cha: " << Character.CharStats.at(EAbility::EACha) << std::endl;

	std::cout << "Initiative: " << Character.InitiativeMod << std::endl;

	std::cout << "HP: " << Character.CurrentHP << "/" << Character.MaxHP << std::endl;
	std::cout << "MP: " << Character.CurrentMP << "/" << Character.MaxMP << std::endl;

	if (!Character.Spells.empty())
	{
		std::cout << "Spells: " << std::endl;
		for (const FSpellData& Spell : Character.Spells)
		{
			std::cout << Spell.SpellName << std::endl;
			std::cout << "	Damage: " << Spell.Damage << std::endl;
			std::cout << "	MP Cost: " << Spell.MPCost << std::endl;
		}
	}

	std::cout << std::endl;
}

static std::string SelectAbility(int Skill)
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

static EMode SelectMode(int Mode)
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

	std::string CharName = "Toby";
	int RaceIndex = 0;
	int ClassIndex = 0;

	std::string Skill = "Str";
	int SkillIndex = 0;

	int Amount = 0;

	EMode Mode = EMode::EMIncrease;
	int ModeIndex;

	int ActionIndex = 0;

	std::cout << "Please choose a name for your characeter : ";
	std::cin >> CharName;

	std::cout << "Next select a race for your character (1-" << Creator.GetLoader()->GetAvailableRaces().size() << ")" << std::endl;
	PrintAvailableRaces();
	std::cin >> RaceIndex;

	std::cout << "Next you must choose a class for your character (1-" << Creator.GetLoader()->GetAvailableClasses().size() << ")" << std::endl;
	PrintAvailableClasses();
	std::cin >> ClassIndex;


	Creator.CreateCharacter(CurrentCharacter.GetCharacterReference(), CharName, RaceIndex - 1, ClassIndex - 1);

	while (!bIsFinalised)
	{
		std::cout << "Please choose an ability to modify (1-6)" << std::endl;
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

		Creator.AllocateAttributePoints(CurrentCharacter.GetCharacterReference(), Skill, Amount, Mode);


		if (Creator.GetAttributePoints() <= 0)
		{
			bIsFinalised = true;
		}
	}

	if (bIsFinalised)
	{
		Creator.SetHPandMP(CurrentCharacter.GetCharacterReference());
		PrintCharacter(CurrentCharacter.GetCharacter());
	}
	else
	{
		std::cerr << "Somtehing went wrong with Character Creation" << std::endl << "Please restart the game";
	}

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

			for (const FMaterial& Materials : CurrentCharacter.GetInventory()->GetMaterials())
			{
				if (Materials.Material->MaterialName == Material.MaterialName)
				{
					std::cout << "You now have " << Materials.MaterialAmount << " " << Materials.Material->MaterialName << std::endl;
					break;
				}
			}
			break;
		}
		case 2:
		{
			int ItemTypeIndex = 0;
			int ItemIndex = 0;

			if (CurrentCharacter.GetInventory()->GetMaterials().empty())
			{
				std::cout << "You have no materials, go gather some!" << std::endl << std::endl;
				break;
			}
			else
			{
				PrintInventoryMaterials(CurrentCharacter);
			}

			std::cout << "Would you like to craft Weapons(1) or Armour(2)" << std::endl;
			std::cin >> ItemTypeIndex;
			std::cout << std::endl << "Which item would you like to craft?" << std::endl;

			switch (ItemTypeIndex)
			{
			case 1:
			{
				PrintAvailableWeapons();
				std::cin >> ItemIndex;

				CurrentCharacter.CraftWeapon(MainItem.GetCraftableWeapons()[ItemIndex - 1]);

				if (CurrentCharacter.GetInventory()->GetWeapons().empty())
				{
					std::cout << "The item was not crafted" << std::endl;
				}

				for (const FWeapon& Weapon : CurrentCharacter.GetInventory()->GetWeapons())
				{
					if (Weapon.WeaponData->ItemName == MainItem.GetCraftableWeapons()[ItemIndex - 1].WeaponData->ItemName)
					{
						std::cout << "You now have a " << Weapon.WeaponData->ItemName << " in your inventory!" << std::endl;
					}
				}
				break;
			}
			case 2:
			{
				PrintAvailableArmour();
				std::cin >> ItemIndex;

				CurrentCharacter.CraftArmour(MainItem.GetCraftableArmour()[ItemIndex - 1]);

				if (CurrentCharacter.GetInventory()->GetArmour().empty())
				{
					std::cout << "The item was not crafted" << std::endl;
					break;
				}

				for (const FArmour& Armour : CurrentCharacter.GetInventory()->GetArmour())
				{
					if (Armour.ArmourData->ItemName == MainItem.GetCraftableArmour()[ItemIndex - 1].ArmourData->ItemName)
					{
						std::cout << "You now have a " << Armour.ArmourData->ItemName << " in your inventory!" << std::endl;
					}
				}
				break;
			}
			default:
			{
				std::cout << "That is not a valid selection try again!" << std::endl << std::endl;
				break;
			}
			break;
			}
			break;
		}
		case 3:
		{
			int EquipmentIndexType = 0;
			int EquipmentIndex = 0;

			if (CurrentCharacter.GetInventory()->GetWeapons().empty() && CurrentCharacter.GetInventory()->GetArmour().empty())
			{
				std::cout << "You need to make some equipment first!" << std::endl << std::endl;
				break;
			}

			std::cout << "What would you like to equip Weapons(1) or Armour (2)" << std::endl;
			std::cin >> EquipmentIndexType;

			switch (EquipmentIndexType)
			{
			case 1:
			{
				std::cout << "Which weapon woudl you like to equip?" << std::endl;
				PrintInventoryWeapons(CurrentCharacter);
				std::cin >> EquipmentIndex;

				CurrentCharacter.EquipWeapon(CurrentCharacter.GetInventory()->GetWeapons()[EquipmentIndex - 1]);

				if (CurrentCharacter.GetEquippedWeapon() == std::nullopt)
				{
					std::cout << "You were unable to equip the item" << std::endl;
					break;
				}

				std::cout << "You equipped a " << CurrentCharacter.GetEquippedWeapon()->WeaponData->ItemName << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "Which armour set would you like to equip" << std::endl;
				PrintInventoryArmour(CurrentCharacter);
				std::cin >> EquipmentIndex;

				CurrentCharacter.EquipArmour(CurrentCharacter.GetInventory()->GetArmour()[EquipmentIndex - 1]);

				if (CurrentCharacter.GetEquippedArmour() == std::nullopt)
				{
					std::cout << "You were unable to equip the item" << std::endl;
					break;
				}

				std::cout << "You equipped a set of " << CurrentCharacter.GetEquippedArmour()->ArmourData->ItemName << std::endl;
				break;
			}
			default:
				std::cout << "That is not a valid selection try again!" << std::endl << std::endl;
				break;
			}
			break;
		}
		case 4:
		{
			int Difficulty = 0;

			std::cout << "What difficulty do you want to try? Easy(1), Medium(2), Hard(3)" << std::endl;
			std::cin >> Difficulty;

			Combat.SetEnemies(IntToEDifficulty(Difficulty));
			int EnemyIndex = 1;

			std::cout << "You are attacked by: " << std::endl;

			for (const FEnemyData& Enemy : Combat.GetEnemyCombatants())
			{
				std::cout << EnemyIndex << " : " << Enemy.CharName << std::endl;
				std::cout << "   " << Enemy.CurrentHP << "/" << Enemy.MaxHP << std::endl;
				std::cout << "   " << Enemy.Damage << std::endl;
				std::cout << "   " << Enemy.Armour << std::endl;
				std::cout << "   " << Enemy.InitiativeMod << std::endl;
				std::cout << ETypeToString(Enemy.Type) << std::endl << std::endl;

				++EnemyIndex;
			}

			std::vector<FInitiative> TurnOrder;

			Combat.CalculateInitiative(TurnOrder, CurrentCharacter.GetCharacterReference());

			std::cout << "The turn order will be: " << std::endl;

			for (const FInitiative& Turn : TurnOrder)
			{
				std::cout << Turn.InititiveRoll << " : " << Turn.Combatant->CharName << std::endl;
			}

			for (const FInitiative& Turn : TurnOrder)
			{
				Combat.CombatRound(Turn.Combatant, 1, 1);
			}
			
			break;
		}
		default:
			std::cout << "That is not a valid selection try again!" << std::endl << std::endl;
			break;
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
