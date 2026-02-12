
#include <optional>
#include "Core/LoadExternalData.h"
#include "Items.h"

FItem::FItem()
{
	Loader->LoadCSV("DataBases/ItemsDatabase.csv", AvailableItems);
}

FItemData* FItem::FindItemData(std::string ItemName)
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

