#include <iostream>
#include "CharacterCreationScreen.h"
#include "Core/LoadExternalData.h"

CharacterCreationScreen::CharacterCreationScreen()
{

	if (!Font.loadFromFile("C:/Users/Admin/Desktop/Coding/ProjectGetAJob/RPG-System/Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Font failed to load!" << std::endl;
	}
	else
	{
		std::cout << "Font loaded!" << std::endl;
	}

	Fields = { "Name", "Race", "Class", "Confirm"};
	RaceOptions = { "Human", "Elf", "Dwarf" };
	ClassOptions = { "Fighter", "Bard", "Wizard" };

	SelectedIndex = 0;
	SelectedClassIndex = 0;
	SelectedRaceIndex = 0;

	Name = "Grave";
}

void CharacterCreationScreen::HandleInput(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (IsFinalised)
			return;

		if (event.key.code == sf::Keyboard::Up)
		{
			SelectedIndex--;

			if (SelectedIndex < 0)
				SelectedIndex = Fields.size() - 1;
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			SelectedIndex++;

			if (SelectedIndex >= Fields.size())
				SelectedIndex = 0;
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			if (Fields[SelectedIndex] == "Race")
			{
				SelectedRaceIndex++;
				if (SelectedRaceIndex >= RaceOptions.size())
					SelectedRaceIndex = 0;
			}
			else if (Fields[SelectedIndex] == "Class")
			{
				SelectedClassIndex++;
				if (SelectedClassIndex >= ClassOptions.size())
					SelectedClassIndex = 0;
			}
		}

		if (event.key.code == sf::Keyboard::Left)
		{
			if (Fields[SelectedIndex] == "Race")
			{
				SelectedRaceIndex--;
				if (SelectedRaceIndex < 0)
					SelectedRaceIndex = RaceOptions.size() - 1;
			}
			else if (Fields[SelectedIndex] == "Class")
			{
				SelectedClassIndex--;
				if (SelectedClassIndex < 0)
					SelectedClassIndex = ClassOptions.size() - 1;
			}


		}
	}
	
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (Fields[SelectedIndex] == "Name")
			{
				if (IsFinalised)
					return;
				IsEditingName = !IsEditingName;
			}
			else if (Fields[SelectedIndex] == "Confirm")
			{
				IsFinalised = true;
				std::cout << "Character Created!" << std::endl;
				std::cout << "Name: " << Name << std::endl;
				std::cout << "Race: " << RaceOptions[SelectedRaceIndex] << std::endl;
				std::cout << "Class: " << ClassOptions[SelectedClassIndex] << std::endl;
			}
		}
	}


	if (event.type == sf::Event::TextEntered && IsEditingName)
	{
		if (IsFinalised)
			return;

		if (event.text.unicode == 13)
			return;

		char c = static_cast<char>(event.text.unicode);
		if (event.text.unicode == 8)
		{
			if (!Name.empty())
				Name.pop_back();
		}
		else if (event.text.unicode < 128)
		{
			Name += c;
		}
	}
}

void CharacterCreationScreen::Update()
{
	
}

void CharacterCreationScreen::Draw(sf::RenderWindow & window)
{
	sf::Text title;
	title.setFont(Font);
	title.setString("Character Creation");
	title.setCharacterSize(80);
	title.setPosition(30.f, 0.f);

	window.draw(title);

	float startY = 80.f;

	for (size_t i = 0; i < Fields.size(); i++)
	{
		sf::Text text;
		text.setFont(Font);
		text.setString(Fields[i]);
		text.setCharacterSize(32);
		text.setPosition(60.f, startY + i * 60.f);

		std::string displayText = Fields[i];

		if (Fields[i] == "Name")
		{
			displayText += ": " + Name;
		}
		else if (Fields[i] == "Race")
		{
			displayText += ": " + RaceOptions[SelectedRaceIndex];
		}
		else if (Fields[i] == "Class")
		{
			displayText += ": " + ClassOptions[SelectedClassIndex];
		}

		text.setString(displayText);


		if (i == SelectedIndex)
		{
			if (Fields[i] == "Name")
			{
				displayText += ": " + Name;
				text.setCharacterSize(40);
			}
			else if (Fields[i] == "Race")
			{
				displayText += ": " + RaceOptions[SelectedRaceIndex];
				text.setCharacterSize(40);
			}
			else if (Fields[i] == "Class")
			{
				displayText += ": " + ClassOptions[SelectedClassIndex];
				text.setCharacterSize(40);
			}
			else if (Fields[i] == "Confirm")
			{
				text.setCharacterSize(40);
			}
		}
		
		window.draw(text);
	}
}
