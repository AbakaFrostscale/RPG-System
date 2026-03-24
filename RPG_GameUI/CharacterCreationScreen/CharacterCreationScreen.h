#pragma once
#include "vector"
#include "string"

#include <SFML/Graphics.hpp>
#include <Character/CharacterStats.h>

class CharacterCreationScreen
{
public:
	CharacterCreationScreen();

	void HandleInput(const sf::Event& event);
	void Update();
	void Draw(sf::RenderWindow& window);

private:
	int SelectedIndex;
	int SelectedClassIndex;
	int SelectedRaceIndex;

	bool IsEditingName = false;
	bool IsFinalised = false;
	bool ISFinished = false;

	//Temp Character being built
	FCharacterData CurrentCharacter;

	//Options (simplified)
	std::vector<std::string> Fields;
	std::vector<std::string> ClassOptions;
	std::vector<std::string> RaceOptions;

	//Font and text for rendering
	sf::Font Font;

	std::string Name;
};