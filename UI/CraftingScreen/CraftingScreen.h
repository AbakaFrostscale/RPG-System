#pragma once
#include "Core/Types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Character/Character.h>

class FCrafting;
class FLoadExtrenalData;

class FCraftingScreen
{
public:
	FCraftingScreen();

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

	sf::RectangleShape CraftingBlock;
	sf::RectangleShape CraftingItemInfoBlock;
	sf::RectangleShape CraftingItemType;

	sf::RectangleShape ConfirmBlock;
	sf::RectangleShape YesBlock;
	sf::RectangleShape NoBlock;

	sf::Text CraftingItemName;
	sf::Text CraftingItemInfo;

	sf::Text CraftingItemMaterialsName;
	sf::Text CraftingItemMaterialsAmount;

	sf::Text ConfirmText;
	sf::Text YesText;
	sf::Text NoText;

	
	int SelectedIndex = 0;
	int ScrollOffset = 0;
	int MaxVisibleItems = 0;

	sf::Texture CraftingItemTexture;
	sf::Sprite CraftingItemSprite;

	sf::FloatRect CraftignItemBounds;

	int FrameHeight = 32;
	int FrameWidth = 32;

	int CraftingItemColumn = 0;
	int CraftingItemRow = 0;

	//Cursor
	sf::Texture CursorTexture;
	sf::Sprite CuresorSprite;

	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	//Music
	sf::Music CraftingMusic;

	sf::SoundBuffer CursorMoveBuffer;
	sf::Sound CursorMoveSound;

	//Character
	FCharacter* CharacterSheet = nullptr;

	//Variables
	bool bChangeScreen = false;
	bool bCraftItem = false;

	std::shared_ptr<FLoadExternalData> Loader;
};