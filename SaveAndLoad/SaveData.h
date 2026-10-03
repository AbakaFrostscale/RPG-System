//SaveData.h
//Stores all the detail to save the game
//Author: Kaden Mann
//Description: Portfolio project demonstrating a full RPG system
//version 1.00

#pragma once

#include "Character/CharacterStats.h"
#include "Character/Character.h"
#include "Inventory/Inventory.h"
#include <SFML/Graphics.hpp>


struct FSaveData
{
	FCharacterData SavedCharacter;
	FInventory CharacterInventory;
	sf::Vector2f CharacterPosition;
};
