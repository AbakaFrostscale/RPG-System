//MapRenderer.h
//Header file for responsible for rendering the map from tmx and MapLoader
//Author: Kaden Mann
//Description: Portfolio Prject demonstrating a full RPG system
//version 1.00

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <tmxlite/Tileset.hpp>
#include <SFML/Graphics.hpp>

namespace tmx
{
	class Map;
}

struct FTileSetData
{
	std::uint32_t FirstGID;
	std::uint32_t LastGID;
	const std::vector<tmx::Tileset::Tile>& Tiles;
	sf::Vector2f TileOffset;
};

struct FTileInfo
{
	std::string TilePath;
	sf::Vector2u TilePosition;
	sf::Vector2u TileSize;
	sf::Vector2f WorldPosition;
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
	std::vector<FTileInfo> TileInfo;

	std::unordered_map<std::string, sf::Texture> TextureInfo;

	const tmx::Map* Map = nullptr;
};
