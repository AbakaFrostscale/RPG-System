//MapLoader.cpp
//Responsible for implementing the tmx renderer
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <iostream>

#include "MapRenderer.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>


FMapRenderer::FMapRenderer()
{
}

void FMapRenderer::Draw(sf::RenderTarget& RenderTarget) const
{
	sf::Sprite TileToDraw;

	std::string PreviousPath;

	for (const auto& Tile : TileInfo)
	{
		if (Tile.TilePath != PreviousPath)
		{
		TileToDraw.setTexture(TextureInfo.at(Tile.TilePath));
		TileToDraw.setTextureRect(sf::IntRect(Tile.TilePosition.x, Tile.TilePosition.y, Tile.TileSize.x, Tile.TileSize.y));
		TileToDraw.setPosition(Tile.WorldPosition.x, Tile.WorldPosition.y);
		
		
		std::cout << "Path: " << Tile.TilePath
			<< "\nPosition: " << Tile.TilePosition.x << ":" << Tile.TilePosition.y
			<< "\nSize: " << Tile.TileSize.x << ":" << Tile.TileSize.y
			<< "\nWorld: " << Tile.WorldPosition.x << ":" << Tile.WorldPosition.y
			<< "\n\n";

		RenderTarget.draw(TileToDraw);
		PreviousPath = Tile.TilePath;
		}
	}
}

void FMapRenderer::LoadTilesets(const std::vector<tmx::Tileset>& CurrentTileset)
{
	Tilesets.clear();
	TileInfo.clear();
	TextureInfo.clear();

	for (const auto& TSet : CurrentTileset)
	{
		Tilesets.push_back({
		TSet.getFirstGID(),
		TSet.getLastGID(),
		TSet.getTiles()
		});
	}

	sf::Vector2u TilePosition;

	tmx::Vector2u TileSize = Map->getTileSize();
	std::uint32_t MapWidth = Map->getBounds().width / TileSize.x;
	std::uint32_t NonEmptyTiles = 0;

	for (const auto& Layer : Map->getLayers())
	{
		if (Layer->getType() != tmx::Layer::Type::Tile)
			continue;

		std::uint32_t TileIndex = 0;
		for (const auto& Tile : Layer->getLayerAs<tmx::TileLayer>().getTiles())
		{
			TilePosition.x = (TileIndex % MapWidth) * TileSize.x;
			TilePosition.y = (TileIndex / MapWidth) * TileSize.y;

			TileIndex++;
			if (Tile.ID == 0)
				continue;

			NonEmptyTiles++;

			for (const auto& Tileset : Tilesets)
			{
				if (Tile.ID >= Tileset.FirstGID && Tile.ID <= Tileset.LastGID)
				{
					std::uint32_t LocalID = Tile.ID - Tileset.FirstGID;
					for (const auto& TileDef : Tileset.Tiles)
					{
						if (TileDef.ID == LocalID)
						{
							auto [Iterator, Inserted] = TextureInfo.try_emplace(TileDef.imagePath);

							if (Inserted)
							{
								if (!Iterator->second.loadFromFile(Iterator->first))
								{
									std::cout << Iterator->first << " could not be found!" << std::endl;
								}
							}
							
							TileInfo.push_back({
							TileDef.imagePath,
							sf::Vector2u{ TileDef.imagePosition.x, TileDef.imagePosition.y },
							sf::Vector2u{ TileDef.imageSize.x, TileDef.imageSize.y },
							TilePosition});

							break;
						}
					}
					break;
				}
			}
		}
	}
}


