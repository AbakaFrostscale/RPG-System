//CharacterStats.h
//Files used to Load the external data from any other data source
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00


#include "LoadExternalData.h"
#include "Character/CharacterStats.h"

FLoadExternalData::FLoadExternalData()
{
	//CharacterCreation
	LoadCSV("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/RaceDatabase.csv", AvailableRaces);
	LoadCSV("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/ClassDatabase.csv", AvailableClasses);

	//Items
	LoadCSV("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/MaterialDatabase.csv", AvailableMaterials);
	LoadCSV("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/ItemsDatabase.csv", AvailableItems);
	ResolveMaterials(AvailableItems);

	//Combat
	LoadCSV("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/EnemiesDatabase.csv", Enemy);
	LoadJSON("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/DataBases/Spells.json", AvailableSpells);
}

const FItemData* FLoadExternalData::FindItemData(const std::string& ItemName)
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

void FLoadExternalData::ResolveMaterials(std::vector<FItemData>& Items)
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
					Items[i].RequiredMaterial.push_back( {&ReqMaterial, key.second} );
					break;
				}
			}
		}
	}
}


