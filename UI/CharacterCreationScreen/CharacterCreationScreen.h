#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include "SFML/Graphics.hpp"
#include <Character/Character.h>

class FLoadExternalData;

struct Theme
{
	sf::Color PrimaryColor = sf::Color(180, 220, 255);
};

class CharacterCreationScreen
{
public:
	CharacterCreationScreen();

	void HandleInput(const sf::Event& event);
	void Update();
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	FCharacterData GetCharacter() { return CurrentCharacter; }
	bool IsFinalised() { return bIsFinalised; }

private:
	std::string GetSelectedAttribute();

	int SelectedIndex;
	int SelectedClassIndex;
	int SelectedRaceIndex;
	int AttributeStartIndex = 3;

	bool IsEditingName = false;
	bool bIsFinalised = false;
	bool bIsCharacterCreated = false;
	bool IsFinished = false;

	//Temp Character being built
	FCharacterData CurrentCharacter;

	//Options (simplified)
	std::vector<std::string> Fields;
	std::vector<std::string> Attributes;
	std::vector<FClassData> ClassOptions;
	std::vector<FRaceData> RaceOptions;

	//Font and text for rendering
	sf::Font Font;

	std::string Name;

	std::unique_ptr<FLoadExternalData> Loader;
};