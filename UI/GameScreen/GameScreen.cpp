#include "GameScreen.h"
#include <iostream>

FGameScreen::FGameScreen()
{
	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;;
	}

	if (!PlayerTexture.loadFromFile("Assets/Sprites/Characters/Character Choice.png"))
	{
		std::cout << "Failed to load Character Sprite!" << std::endl;
	}

	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(2.f, 2.f);
	PlayerSprite.setPosition(PlayerPosition);

	PlayerSprite.setTextureRect(sf::IntRect(0, SelectedCharacterRow * FrameHeight, FrameWidth, FrameHeight));
}

void FGameScreen::HandleInput(const sf::Event& event)
{

}

void FGameScreen::Update(float DeltaTime)
{

}

void FGameScreen::Draw(sf::RenderWindow& window)
{
	TitleText.setFont(Font);
	TitleText.setString(ToUpper("Game Screen"));
	TitleText.setCharacterSize(60);
	TitleText.setFillColor(Theme.HighlightColor);

	sf::FloatRect TitleBounds = TitleText.getLocalBounds();
	TitleText.setOrigin(TitleBounds.left + TitleBounds.width / 2.f, TitleBounds.top + TitleBounds.height / 2.f);
	TitleText.setPosition(window.getSize().x / 2.f, 80.f);

	window.draw(TitleText);

	CharacterInforText.setFont(Font);
	CharacterInforText.setCharacterSize(32);
	CharacterInforText.setFillColor(sf::Color::White);
	CharacterInforText.setPosition(window.getSize().x / 30.f, window.getSize().y - 150.f);

	window.draw(CharacterInforText);
}



std::string FGameScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}

void FGameScreen::SetCharacter(const FCharacterData& Character)
{
	CurrentCharacter = Character;

	CharacterInforText.setString
	(ToUpper("Name: " + CurrentCharacter.CharName) +
		ToUpper("\nRace: " + CurrentCharacter.CharRace.RaceName) +
		ToUpper("\nClass: " + CurrentCharacter.CharClass.ClassName));
}
