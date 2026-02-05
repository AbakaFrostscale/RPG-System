#include "Items.h"
#include "Core/LoadExternalData.h"

FItem::FItem()
{
	Loader->LoadCSV("DataBases/ItemsDatabase.csv", AvailableItems);
}


