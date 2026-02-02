//CharacterStats.h
//Files used to Load the external data from any other data source
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00



#include "LoadExternalData.h"



template<typename T>
inline void FLoadExternalData::LoadCSV(const std::string& FilePath, std::vector<T>& OutVector)
{
	std::ifstream File(FilePath);

	if (!File.is_open())
	{
		//TODO, notify the UI that the file is not open
		return;
	}

	std::string Line;
	bool bReadHeader = false;

	while (std::getline(File, Line))
	{
		if (Line.empty()) continue;

		std::vector<std::string> Columns;
		std::vector<std::string> Header;
		std::stringstream ss(Line);
		std::string Cell;

		while (std::getline(ss, Cell, ','))
		{
			Cell.erase(Cell.find_last_not_of("\r\n") + 1);
			Columns.push_back(Cell);
		}

		if (!bReadHeader)
		{
			Header = Columns;
			bReadHeader = true;
			continue;
		}

		if (Columns.size() < Header.size())
		{
			continue;
		}

		try
		{
			T Row;
			Row.FromCSVRow(Columns, Header);
			OutVector.push_back(Row);
		}
		catch (const std::exception& e)
		{
			return;
		}
	}
}
