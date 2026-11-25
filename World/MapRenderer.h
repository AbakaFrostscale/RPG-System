//MapRenderer.h
//Header file for responsible for rendering the map from tmx and MapLoader
//Author: Kaden Mann
//Description: Portfolio Prject demonstrating a full RPG system
//version 1.00

#pragma once

#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Libraries/tmxlite/tmxlite/include/tmxlite/Map.hpp>

namespace tmx
{
	class Map;
}

struct FTileSetData
{
	std::uint32_t FirstGID;
	std::uint32_t LastGID;
	const std::vector<tmx::Tileset::Tile>& Tiles;
};


class FMapRenderer
{
public:
	FMapRenderer();
	
	void SetMap(const tmx::Map& MapToRender) { Map = &MapToRender; }
	void Draw(sf::RenderTarget& RenderTarget) const;
	void LoadTilesets(const std::vector<tmx::Tileset>& CurrentTileset);

private:


	std::vector<FTileSetData> Tilesets;
	const tmx::Map* Map = nullptr;
};
