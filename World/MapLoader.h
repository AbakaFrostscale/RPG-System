//MapLoader.h
//Header file for responsible for utilising the tmx file
//Author: Kaden Mann
//Description: Portfolio Prject demonstrating a full RPG system
//version 1.00

#pragma once

#include <string>
#include <memory>

namespace tmx
{
	class Map;
}

class FMapLoader
{
public:
	FMapLoader();
	~FMapLoader();

	bool LoadMap(const std::string& MapFile);
	const tmx::Map* GetMap() const { return Map.get(); };

private:
	std::unique_ptr<tmx::Map> Map;
};

