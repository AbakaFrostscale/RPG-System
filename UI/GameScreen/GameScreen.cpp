#include "GameScreen.h"
#include <iostream>
#include <cmath>

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
	sf::Vector2f Direction(0.f, 0.f);

	bool bMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Direction.y -= 1.f;
		CurrentAnimationRow = UpRow;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Direction.y += 1.f;
		CurrentAnimationRow = DownRow;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Direction.x -= 1.f;
		CurrentAnimationRow = LeftRow;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Direction.x += 1.f;
		CurrentAnimationRow = LeftRow;
		PlayerSprite.setScale(sf::Vector2f(-2.f, 2.f));
		bMoving = true;
	}

	if (Direction.x != 0.f || Direction.y != 0.f)
	{
		float Length = std::sqrt(Direction.x * Direction.x + Direction.y + Direction.y);
	}

	PlayerPosition.x += Direction.x * MoveSpeed * DeltaTime;
	PlayerPosition.y += Direction.y * MoveSpeed * DeltaTime;

	PlayerSprite.setPosition(PlayerPosition);

	
	if (bMoving)
	{
		AnimationTimer += DeltaTime;

		if (AnimationTimer >= AnimationSpeed)
		{
			AnimationTimer = 0.f;

			CurrentFrame++;

			if (CurrentFrame >= 2)
			{
				CurrentFrame = 0;
			}
		}
	}
	else
	{
		CurrentFrame = 0;
	}

	PlayerSprite.setTextureRect(sf::IntRect((CurrentFrame + CurrentAnimationRow) * FrameWidth, SelectedCharacterRow * FrameHeight, FrameWidth, FrameHeight));
	PlayerSprite.setOrigin(FrameWidth / 2.f, FrameHeight / 2.f);
	
	Camera.setCenter(PlayerPosition);
}

void FGameScreen::Draw(sf::RenderWindow& window)
{
	Camera.setSize(window.getSize().x, window.getSize().y);
	Camera.setCenter(PlayerPosition);
	
	window.setView(Camera);

	std::cout << "Character Drawn at " << PlayerPosition.x << ", " << PlayerPosition.y << std::endl;
	window.draw(PlayerSprite);

	window.setView(window.getDefaultView());

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

void FGameScreen::SetSelectedCharacter(const int SelectedCharacter)
{
	SelectedCharacterRow = SelectedCharacter;
}
