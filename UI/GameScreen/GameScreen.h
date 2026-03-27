#pragma once
#include "Core/Types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character/CharacterStats.h"

class FGameScreen
{
public:
	FGameScreen();

	void HandleInput(const sf::Event& event);
	void Update(float DeltaTime);
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	void SetCharacter(const FCharacterData& Character);

private:
	FTheme Theme;

	FCharacterData CurrentCharacter;

	sf::Font Font;
	sf::Text TitleText;
	sf::Text CharacterInforText;

	//player
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;

	sf::Vector2f PlayerPosition = sf::Vector2f(640.f, 360.f);

	float MoveSpeed = 200.f;

	int SelectedCharacterRow = 0;

	int CurrentFrame;
	float AnimationTimer = 0.f;
	float AnimationSpeed = 0.25f;

	int FrameHeight = 18;
	int FrameWidth = 18;

	//Animation movement indexes
	int DownRow = 0;
	int LeftRow = 1;
	int RightRow = 1;
	int UpRow = 2;

	int CurrentAnimationRow = 0;
};
