#include "Items.h"

FItem::FItem()
{
<<<<<<< Updated upstream
	IronSword =
	{
		"Iron Sword",
		ERarity::ERCommon,
		{},
=======
	Loader = std::make_shared<FLoadExternalData>();

	CopperSword = 
	{	
		Loader->FindItemData("Copper Sword"),
		4,
		EAbility::EADex, 
		2 
	};
	IronSword =
	{
	   Loader->FindItemData("Iron Sword"),
	   6,
	   EAbility::EAStr,
	   4
	};
	SteelSword =
	{
		Loader->FindItemData("Steel Sword"),
>>>>>>> Stashed changes
		8,
		{{ EMaterial::EMIron, 2}, {EMaterial::EMWood, 1}, {EMaterial::EMLeather, 1}}
	};

	IronGreatsword =
	{
<<<<<<< Updated upstream
		"Iron Greatsword",
		ERarity::ERCommon,
		{},
		(6 + 6),
		{{EMaterial::EMIron, 4}, {EMaterial::EMWood, 2}, {EMaterial::EMLeather, 2}}
	};

	FWeapon IronBattleaxe =
	{
		"Iron Battleaxe",
		ERarity::ERCommon,
		{},
		6,
		{{EMaterial::EMIron, 2}, {EMaterial::EMWood, 2}}
	};

	FWeapon IronDagger =
	{
		"Iron Dagger",
		ERarity::ERCommon,
		{},
		4,
		{{EMaterial::EMIron, 1}, {EMaterial::EMWood, 1}, {EMaterial::EMLeather, 1}}
=======
		Loader->FindItemData("Copper Chest Plate"),
		4,
		EAbility::EAStr,
		2
	};
	IronChestPlate = 
	{
		Loader->FindItemData("Iron Chest Plate"),
		6,
		EAbility::EAStr,
		4
	};
	SpiderSilkArmour = 
	{
		Loader->FindItemData("Spider Silk Armour"),
		6,
		EAbility::EANone,
		0
>>>>>>> Stashed changes
	};

	FArmour IronCuirass =
	{
		"Iron Cuirass",
		ERarity::ERCommon,
		{},
		10,
		{{EMaterial::EMIron, 6}, {EMaterial::EMCloth, 2}, {EMaterial::EMLeather, 1}}
	};

	FArmour ClothRobe =
	{
		"Cloth Robe",
		ERarity::ERCommon,
		{},
		5,
		{{EMaterial::EMCloth, 6}, {EMaterial::EMIron, 1}, {EMaterial::EMLeather, 1}}
	};

	FArmour LeatherArmour
	{
		"Leather Armour",
		ERarity::ERCommon,
		{},
		8,
		{{EMaterial::EMLeather, 6}, {EMaterial::EMCloth, 2}, {EMaterial::EMIron, 1} }
	};
}
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
