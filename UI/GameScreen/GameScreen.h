#pragma once
#include "Core/Types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character/CharacterStats.h"

struct FTree
{
	sf::Sprite Sprite;
	sf::FloatRect Collision;
};



class FGameScreen
{
public:
	FGameScreen();

	void HandleInput(const sf::Event& event);
	void Update(float DeltaTime);
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	void SetCharacter(const FCharacterData& Character);
	void SetSelectedCharacter(const int SelectedCharacter);

private:
	FTheme Theme;

	FCharacterData CurrentCharacter;

	sf::Font Font;
	sf::Text TitleText;
	sf::Text CharacterInforText;

	//player
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	sf::FloatRect PlayerBounds;

	sf::Vector2f PlayerPosition = sf::Vector2f(300.f, 200.f);

	float MoveSpeed = 100.f;

	int SelectedCharacterRow = 0;

	int CurrentFrame = 0;
	float AnimationTimer = 0.f;
	float AnimationSpeed = 0.25f;

	int FrameHeight = 20;
	int FrameWidth = 20;

	//sound
	sf::Music GameMusic;

	bool bMusicFadingIn = false;
	float MusicFadeSpeed = 40.f;

	//Animation movement indexes
	int DownRow = 0;
	int LeftRow = 2;
	int UpRow = 4;

	int CurrentAnimationRow = 0;

	// Camera
	sf::View Camera;

	// Game World
	sf::Texture TreeTexture;
	std::vector<FTree> Trees;
	sf::RectangleShape Ground;

	std::vector<sf::IntRect> TreeSize
	{
		sf::IntRect{0, 5, 75, 90}, //Tree Type 0
		sf::IntRect{320, 10, 70, 85}, //Tree Type 1
		sf::IntRect{0, 95, 75, 85}, //Tree Type 2
		sf::IntRect{320, 95, 70, 85}, //Tree Type 3
		sf::IntRect{0, 180, 75, 90}, //Tree Type 4
		sf::IntRect{320, 185, 80, 90}  //Tree Type 5
	};
};
