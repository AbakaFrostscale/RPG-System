//MapLoader.cpp
//Responsible for implementing the tmx renderer
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#include <iostream>

#include "MapRenderer.h"
#include "Libraries/tmxlite/tmxlite/include/tmxlite/Map.hpp"


FMapRenderer::FMapRenderer()
{
}

void FMapRenderer::Draw(sf::RenderTarget& RenderTarget) const
{
}

void FMapRenderer::LoadTilesets(const std::vector<tmx::Tileset>& CurrentTileset)
{
	Tilesets.clear();

	for (const auto& TSet : CurrentTileset)
	{
		Tilesets.push_back({
		TSet.getFirstGID(),
		TSet.getLastGID(),
		TSet.getTiles()
		});
	}
}


