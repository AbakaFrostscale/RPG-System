//CharacterStats.h
//HeaderFile for loading all the external data from files
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00


#pragma once

#include <string>
#include <vector>

class FLoadExternalData
{
	template<typename T>
	void LoadCSV(const std::string& FilePath, std::vector<T>& OutVector);
};