// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Character/Character.h"
#include "Creation/CharacterCreation.h"

FCharacterCreator Creator;
FCharacter Character;





int main()
{
    return 0;
}

template<typename T>
inline void LoadCSV(const std::string& FilePath, std::vector<T>& OutVector)
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




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
