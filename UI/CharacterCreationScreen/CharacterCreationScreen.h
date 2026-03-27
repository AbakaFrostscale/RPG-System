#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "Core/Types.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <Character/Character.h>

class FLoadExternalData;

class FCharacterCreationScreen
{
public:
	FCharacterCreationScreen();

	void HandleInput(const sf::Event& event);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	FCharacterData GetCharacter() { return CurrentCharacter; }
	bool IsFinalised() { return bIsFinalised; }

	void StartFadeIn();

private:
	FTheme Theme;

	//sound
	sf::Music CharacterCreationMusic;
	sf::SoundBuffer CursorMoveBuffer;
	sf::SoundBuffer ConfirmBuffer;

	sf::Sound CursorMoveSound;
	sf::Sound ConfirmSound;

	//Cursor 
	sf::Texture CursorTexture;
	sf::Sprite CursorSprite;
	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	bool bFadingIn = true;
	float FadeAlpha = 255.f;
	float FadeSpeed = 200.f;

	std::string GetSelectedAttribute();
	bool CanSelectFields(int index) const;

	int SelectedIndex;
	int SelectedClassIndex;
	int SelectedRaceIndex;
	int AttributeStartIndex = 3;

	bool IsEditingName = false;
	bool bIsFinalised = false;
	bool bIsCharacterCreated = false;
	bool IsFinished = false;
	
	//Character
	sf::Texture CharacterTexture;
	sf::Sprite CharacterSprite;

	int FrameWidth = 20;
	int FrameHeight = 20;

	int CurrentFrame = 0;
	float AnimationTimer = 0.f;
	float AnimationSpeed = 0.25f;

	int FramesPerAnimation = 2;
	int CurrentAnimationIndex = 0;
	int SelectedCharacterIndex = 0;
	int MaxCharacters = 12;

	//Temp Character being built
	FCharacterData CurrentCharacter;

	//Options
	std::vector<std::string> Fields;
	std::vector<std::string> Attributes;
	std::vector<FClassData> ClassOptions;
	std::vector<FRaceData> RaceOptions;

	//Font and text for rendering
	sf::Font Font;
	std::string Name;

	std::unique_ptr<FLoadExternalData> Loader;
};