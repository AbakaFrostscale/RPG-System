#pragma once
#include "Core/Types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character/Character.h"
#include "Inventory/Inventory.h"

class FInventoryScreen
{
public:
	FInventoryScreen();

	void HandleInput(const sf::Event& event);
	void Update(float DeltaTime);
	void Draw(sf::RenderWindow& window);

	void SetCharacter(FCharacter& Character) { CharacterSheet = &Character; }

	const bool GetbChangeScreen() const { return bChangeScreen; }
	void SetbChangeScreen(bool ChangeScreen) { bChangeScreen = ChangeScreen; }

private:
	//UI
	FTheme Theme;
	sf::Font Font;

	std::string ToUpper(const std::string& input);

	sf::RectangleShape InventoryBlock;
	sf::RectangleShape InventoryItemInfoBlock;

	sf::Text InventoryItemName;
	sf::Text InventoryItemAmount;
	sf::Text InventoryItemWeightInfo;
	sf::Text InventoryItemTypeInfo;

	int SelectedIndex = 0;
	int ScrollOffset = 0;
	int MaxVisibleItems = 0;

	sf::Texture InventoryItemTexture;
	sf::Sprite InventoryItemSprite;

	sf::FloatRect InventoryItemBounds;

	int FrameHeight = 24;
	int FrameWidth = 24;

	int InventoryItemColumn = 0;
	int InventoryItemRow = 0;

	//Cursor
	sf::Texture CursorTexture;
	sf::Sprite CursorSprite;

	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	//Music
	sf::Music InventoryMusic;
	
	sf::SoundBuffer CursorMoveBuffer;
	sf::Sound CursorMoveSound;

	//Character
	FCharacter* CharacterSheet = nullptr;

	//Variables
	bool bChangeScreen = false;
};