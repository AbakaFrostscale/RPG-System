//CharacterStats.h
//HeaderFile for loading all the external data from files
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00


#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class FLoadExternalData
{
public:
	template<typename T>
	bool LoadCSV(const std::string& FilePath, std::vector<T>& OutVector)
	{
		std::ifstream File(FilePath);

		if (!File.is_open())
		{
			//TODO, notify the UI that the file is not open
			return false;
		}

		std::string Line;
		bool bReadHeader = false;
		std::vector<std::string> Header;

		while (std::getline(File, Line))
		{
			if (Line.empty()) continue;

			std::vector<std::string> Columns;
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

			if (Columns.size() != Header.size())
			{
				return false;
			}

			try
			{
				T Row;
				Row.FromCSVRow(Columns);
				OutVector.push_back(Row);
			}
			catch (const std::exception& e)
			{
				return false;
			}
		}

		return true;
	}
};