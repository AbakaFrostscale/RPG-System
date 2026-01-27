#include "Items.h"

FItem::FItem()
{
	IronSword =
	{
		"Iron Sword",
		ERarity::ERCommon,
		{},
		8,
		{{ EMaterial::EMIron, 2}, {EMaterial::EMWood, 1}, {EMaterial::EMLeather, 1}}
	};

	IronGreatsword =
	{
		"Iron Greatsword",
		ERarity::ERCommon,
		{},
		12,
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
