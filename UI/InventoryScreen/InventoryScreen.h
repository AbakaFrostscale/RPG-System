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
	sf::Text InventoryItemName;
	sf::Text InventoryItemAmount;

	//Cursor
	sf::Texture CursorTexture;
	sf::Sprite CursorSprite;

	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	int SelectedIndex = 0;

	//Music
	sf::Music InventoryMusic;
	
	sf::SoundBuffer CursorMoveBuffer;
	sf::Sound CursorMoveSound;

	sf::SoundBuffer ConfirmSoundBuffer;
	sf::Sound ConfirmSound;

	bool bMusicFadingIn = false;
	float MusicFadeSpeed = 40.f;

	//Character
	FCharacter* CharacterSheet = nullptr;

	//Variables
	bool bChangeScreen = false;
};