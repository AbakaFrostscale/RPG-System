
#include <optional>
#include <iostream>
#include "Inventory/Inventory.h"
#include "Core/LoadExternalData.h"
#include "Items.h"

FItem::FItem()
{
	Loader = std::make_shared<FLoadExternalData>();

	CopperSword = 
	{	
		FindItemData("Copper Sword"),
		4,
		EAbility::EADex, 
		2 
	};
	IronSword =
	{
	   FindItemData("Iron Sword"),
	   6,
	   EAbility::EAStr,
	   4
	};
	SteelSword =
	{
		FindItemData("Steel Sword"),
		8,
		EAbility::EAStr,
		4
	};
	
	AvailableWeapons.push_back(CopperSword);
	AvailableWeapons.push_back(IronSword);
	AvailableWeapons.push_back(SteelSword);

	CopperChestPlate = 
	{
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
	};

  AvailableArmour.push_back(CopperChestPlate);
	AvailableArmour.push_back(IronChestPlate);
	AvailableArmour.push_back(SpiderSilkArmour);
}
  

const FItemData* FItem::FindItemData(const std::string& ItemName)
{
	for (const FItemData& Item : GetAvailableItems())
	{
		if (Item.ItemName == ItemName)
		{
			return &Item;
		}
	}
	return nullptr;
}

void FItem::ResolveMaterials(std::vector<FItemData>& Items)
{
	for (size_t i = 0; i < Items.size(); i++)
  {
		Items[i].RequiredMaterial.clear();
		for (const auto& key : Items[i].RawRequiredMaterials)
		{
			for (FMaterialData& ReqMaterial : AvailableMaterials)
			{
				if (ReqMaterial.MaterialName == key.first)
				{
					Items[i].RequiredMaterial.push_back({ &ReqMaterial, key.second });
					break;
				}
			}
		}
	}
}
