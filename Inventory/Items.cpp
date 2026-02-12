
#include <optional>
#include "Core/LoadExternalData.h"
#include "Items.h"

FItem::FItem()
{
	Loader->LoadCSV("DataBases/ItemsDatabase.csv", AvailableItems);

	CopperSword = 
	{	
		*FindItemData("Copper Sword"),
		4,
		EAbility::EADex, 
		2 
	};
	IronSword =
	{
	   *FindItemData("Iron Sword"),
	   6,
	   EAbility::EAStr,
	   4
	};
	SteelSword =
	{
		*FindItemData("Steel Sword"),
		8,
		EAbility::EAStr,
		4
	};
	
	AvailableWeapons.push_back(CopperSword);
	AvailableWeapons.push_back(IronSword);
	AvailableWeapons.push_back(SteelSword);

	CopperChestPlate = 
	{
		*FindItemData("Copper Chest Plate"),
		4,
		EAbility::EAStr,
		2
	};
	IronChestPlate = 
	{
		*FindItemData("Iron Chest Plate"),
		6,
		EAbility::EAStr,
		4
	};
	SpiderSilkArmour = 
	{
		*FindItemData("Spider Silk Armour"),
		6,
		EAbility::EANone,
		0
	};

	AvailableArmour.push_back(CopperChestPlate);
	AvailableArmour.push_back(IronChestPlate);
	AvailableArmour.push_back(SpiderSilkArmour);
}

FItemData* FItem::FindItemData(const std::string& ItemName)
{
	for (FItemData& Item : AvailableItems)
	{
		if (Item.ItemName == ItemName)
		{
			return &Item;
		}
	}
	return nullptr;
}





