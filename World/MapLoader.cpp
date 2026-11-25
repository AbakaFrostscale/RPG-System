//MapLoader.cpp
//Responsible for implementing the tmx loader for maps
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include "MapLoader.h"
#include "Libraries/tmxlite/tmxlite/include/tmxlite/Map.hpp"


FMapLoader::FMapLoader()
{
	Map = std::make_unique<tmx::Map>();
}

FMapLoader::~FMapLoader() = default;

bool FMapLoader::LoadMap(const std::string& MapFile)
{
	bool MapLoaded = Map->load(MapFile);
	
	if (MapLoaded)
	{
		std::cout << MapFile << " loaded successfully" << std::endl;
	}
	else
	{
		std::cout << MapFile << " failed to load" << std::endl;
	}

	return MapLoaded;
}