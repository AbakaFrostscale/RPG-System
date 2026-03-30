#include <iostream>
#include "CharacterCreationScreen.h"
#include "Core/LoadExternalData.h"
#include "Creation/CharacterCreation.h"

FCharacterCreator Creator;

FCharacterCreationScreen::FCharacterCreationScreen()
{
	Loader = std::make_unique<FLoadExternalData>();

	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Font failed to load!" << std::endl;
	}

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}


	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.8f, .8f);

	if (!CharacterTexture.loadFromFile("Assets/Sprites/Characters/Character Choice.png"))
	{
		std::cout << "Character failed to Load!" << std::endl;
	}

	CharacterSprite.setTexture(CharacterTexture);
	CharacterSprite.setScale(8.f, 8.f);
	CharacterSprite.setPosition(300.f, 200.f);

	Fields = { "Name", "Race", "Class", "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma", "Reset", "Confirm"};
	Attributes = { "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma" };
	RaceOptions = Loader->GetAvailableRaces();
	ClassOptions = Loader->GetAvailableClasses();

	if (!CharacterCreationMusic.openFromFile("Assets/Audio/Music/Loop/Shop_Loop.wav"))
	{
		std::cout << "Menu music not found" << std::endl;
	}

	CharacterCreationMusic.setLoop(true);
	CharacterCreationMusic.setVolume(50.f);

	if (!CursorMoveBuffer.loadFromFile("Assets/Audio/SFX/Select.mp3"))
	{
		std::cout << "Select sound failed to load!" << std::endl;
	}

	CursorMoveSound.setBuffer(CursorMoveBuffer);
	CursorMoveSound.setVolume(50.f);

	if (!ConfirmBuffer.loadFromFile("Assets/Audio/SFX/Accept.mp3"))
	{
		std::cout << "Confirm sound failed to load!" << std::endl;
	}

	ConfirmSound.setBuffer(ConfirmBuffer);
	ConfirmSound.setVolume(50.f);

	SelectedIndex = 0;
	SelectedClassIndex = 0;
	SelectedRaceIndex = 0;

	Name = "Grave";

}

void FCharacterCreationScreen::HandleInput(const sf::Event & event)
{
	bool IsAttributeSelected = SelectedIndex >= AttributeStartIndex && SelectedIndex < AttributeStartIndex + Attributes.size();

	if (bIsFinalised)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			std::cout << "Proceeding... " << std::endl;
			IsFinished = true;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (bIsFinalised)
			return;

		if (event.key.code == sf::Keyboard::Up)
		{
			do
			{

				SelectedIndex--;
				CursorMoveSound.play();

				if (SelectedIndex < 0)
					SelectedIndex = Fields.size() - 1;
			} while (!CanSelectFields(SelectedIndex));
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			do
			{
				SelectedIndex++;
				CursorMoveSound.play();

				if (SelectedIndex >= Fields.size())
					SelectedIndex = 0;
			} while (!CanSelectFields(SelectedIndex));
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			if (!bIsCharacterCreated)
			{
				if (Fields[SelectedIndex] == "Race")
				{
					SelectedRaceIndex++;
					CursorMoveSound.play();
					if (SelectedRaceIndex >= RaceOptions.size())
						SelectedRaceIndex = 0;
				}
				else if (Fields[SelectedIndex] == "Class")
				{
					SelectedClassIndex++;
					CursorMoveSound.play();
					if (SelectedClassIndex >= ClassOptions.size())
						SelectedClassIndex = 0;
				}
			}
			else if (bIsCharacterCreated && IsAttributeSelected && Creator.GetAttributePoints() > 0)
			{
				std::string attr = GetSelectedAttribute();

				Creator.AllocateAttributePoints(CurrentCharacter, attr, 1, EMode::EMIncrease);
			}
		}

		if (event.key.code == sf::Keyboard::Left)
		{
			if (!bIsCharacterCreated)
			{
				if (Fields[SelectedIndex] == "Race")
				{
					SelectedRaceIndex--;
					CursorMoveSound.play();
					if (SelectedRaceIndex < 0)
						SelectedRaceIndex = RaceOptions.size() - 1;
				}
				else if (Fields[SelectedIndex] == "Class")
				{
					SelectedClassIndex--;
					CursorMoveSound.play();
					if (SelectedClassIndex < 0)
						SelectedClassIndex = ClassOptions.size() - 1;
				}
			}
			else if (bIsCharacterCreated && IsAttributeSelected)
			{
				std::string attr = GetSelectedAttribute();

				Creator.AllocateAttributePoints(CurrentCharacter, attr, 1, EMode::EMDecrease);
			}
		}

		if (event.key.code == sf::Keyboard::A)
		{
			if (bIsCharacterCreated)
			{
				SelectedCharacterIndex--;
				CursorMoveSound.play();

				if (SelectedCharacterIndex < 0)
				{
					SelectedCharacterIndex = MaxCharacters - 1;
				}

				CurrentFrame = 0;
				AnimationTimer = 0.f;
			}
		}

		if (event.key.code == sf::Keyboard::D)
		{
			if (bIsCharacterCreated)
			{
				SelectedCharacterIndex++;
				CursorMoveSound.play();

				if (SelectedCharacterIndex >= MaxCharacters)
				{
					SelectedCharacterIndex = 0;
				}


				CurrentFrame = 0;
				AnimationTimer = 0.f;
			}
		}
	}
	
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (Fields[SelectedIndex] == "Name")
			{
				if (bIsCharacterCreated)
					return;
				CursorMoveSound.play();
				IsEditingName = !IsEditingName;
			}
			else if (Fields[SelectedIndex] == "Confirm")
			{
				if (Name.empty())
				{
					std::cout << "Name cannot be empty" << std::endl;
					return;
				}

				ConfirmSound.play();

				if (!bIsCharacterCreated)
				{
					Creator.CreateCharacter(CurrentCharacter, Name, SelectedRaceIndex, SelectedClassIndex);
					bIsCharacterCreated = true;
				}

				if (Creator.GetAttributePoints() > 0)
					return;

				if (bIsCharacterCreated && !bIsFinalised)
				{
					Creator.SetHPandMP(CurrentCharacter);
					StopMusic();
					bFadingOut = true;
				}
			}
			else if (Fields[SelectedIndex] == "Reset")
			{
				Creator.CreateCharacter(CurrentCharacter, Name, SelectedRaceIndex, SelectedClassIndex);
				Creator.SetAttributePoints(Creator.GetMaxAttributePoints());

				bIsCharacterCreated = false;
				ConfirmSound.play();

				std::cout << "Character Reset!" << std::endl;
			}
		}
	}


	if (event.type == sf::Event::TextEntered && IsEditingName)
	{
		if (bIsFinalised)
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

void FCharacterCreationScreen::Update(float deltaTime)
{
	CursorTimer += deltaTime;
	CursorOffset = std::sin(CursorTimer) * 2.f;

	AnimationTimer += deltaTime;

	if (AnimationTimer >= AnimationSpeed)
	{
		AnimationTimer = 0.f;

		CurrentFrame += AnimDirection;

		if (CurrentFrame >= 8)
		{
			CurrentFrame = 8;
			AnimDirection = -1;
		}
		else if (CurrentFrame <= 7)
		{
			CurrentFrame = 7;
			AnimDirection = 1;
		}
	}

	CharacterSprite.setTextureRect(sf::IntRect(CurrentFrame * FrameWidth, SelectedCharacterIndex * FrameHeight, FrameWidth, FrameHeight));

	if (bFadingIn)
	{
		FadeInAlpha -= FadeSpeed * deltaTime;

		if (FadeInAlpha <= 0.f)
		{
			FadeInAlpha = 0.f;
			bFadingIn = false;
		}
	}

	if (bFadingOut)
	{
		FadeOutAlpha += deltaTime * FadeSpeed;

		if (FadeOutAlpha >= 255.f)
		{
			FadeOutAlpha = 255.f;
			IsFadeOutFinished = true;
		}
	}
}

void FCharacterCreationScreen::Draw(sf::RenderWindow & window)
{
	if (bIsFinalised)
	{
		sf::Text doneText;
		sf::Text instructText;

		doneText.setFont(Font);
		instructText.setFont(Font);

		doneText.setFillColor(Theme.PrimaryColor);
		instructText.setFillColor(Theme.PrimaryColor);
		
		doneText.setString(ToUpper("Character Created!"));
		instructText.setString(ToUpper("Press Enter to continue..."));
		
		doneText.setCharacterSize(80);
		instructText.setCharacterSize(32);
		
		doneText.setPosition(50.f, 50.f);
		instructText.setPosition(50.f, 200.f);

		window.draw(doneText);
		window.draw(instructText);
		return;
	}

	//====================================================================== TITLE ================================================================================
	sf::Text title;
	
	title.setFont(Font);
	title.setFillColor(Theme.AccentColor);
	title.setString(ToUpper("Character Creation"));
	title.setCharacterSize(80);
	title.setPosition(30.f, 0.f);

	window.draw(title);

	//=================================================================== BASIC FIELDS ============================================================================
	float startY = 120.f;

	for (size_t i = 0; i < Fields.size(); i++)
	{
		if (!bIsCharacterCreated)
		{
			if (std::find(Attributes.begin(), Attributes.end(), Fields[i]) != Attributes.end())
			{
				continue;
			}
		}

		sf::Text text;
		text.setFont(Font);
		text.setFillColor(Theme.PrimaryColor);
		text.setCharacterSize(32);
		text.setPosition(80.f, startY + i * 30.f);

		std::string displayText = Fields[i];

		if (Fields[i] == "Name")
		{
			displayText += ": " + Name;
		}
		else if (Fields[i] == "Race")
		{
			displayText += ": " + RaceOptions[SelectedRaceIndex].RaceName;
		}
		else if (Fields[i] == "Class")
		{
			displayText += ": " + ClassOptions[SelectedClassIndex].ClassName;
			
		}
		else if (bIsCharacterCreated && std::find(Attributes.begin(), Attributes.end(), Fields[i]) != Attributes.end())
		{
			int value = CurrentCharacter.CharStats.at(Creator.StringToEAbility(Fields[i]));

			displayText += ": " + std::to_string(value);
		}

		if (i == SelectedIndex)
		{
			CursorSprite.setPosition(text.getPosition().x - 30.f, text.getPosition().y + CursorOffset);

			text.setFillColor(Theme.HighlightColor);
		
			window.draw(CursorSprite);
		}

		if (bIsCharacterCreated && (Fields[i] == "Name" || Fields[i] == "Race" || Fields[i] == "Class"))
		{
			text.setFillColor(sf::Color(150, 150, 150));
		}

		text.setString(ToUpper(displayText));
		window.draw(text);

	}
	//================================================================== POINTS DISPLAY ===========================================================================
		
	if (bIsCharacterCreated)
	{
		sf::Text pointsText;

		pointsText.setFont(Font);
		pointsText.setFillColor(Theme.PrimaryColor);
		pointsText.setCharacterSize(32);
		pointsText.setPosition(300.f, 120.f);

		pointsText.setString(ToUpper("Available Attribute Points: " + std::to_string(Creator.GetAttributePoints())));

		window.draw(pointsText);

		sf::Text charText;
		charText.setFont(Font);
		charText.setFillColor(Theme.PrimaryColor);
		charText.setCharacterSize(32);
		charText.setPosition(380.f, 350.f);

		charText.setString(std::to_string(SelectedCharacterIndex + 1) + " / " + std::to_string(MaxCharacters));

		window.draw(charText);
		window.draw(CharacterSprite);
	}

	//=================================================================== FADE ====================================================================================
	if (bFadingIn)
	{
		sf::RectangleShape Fade;
		Fade.setSize(sf::Vector2f(window.getSize()));
		Fade.setFillColor(sf::Color(50, 0, 0, static_cast<sf::Uint8>(FadeInAlpha)));

		window.draw(Fade);
	}	

	if (bFadingOut)
	{
		sf::RectangleShape Fade;
		Fade.setSize(sf::Vector2f(window.getSize()));
		Fade.setFillColor(sf::Color(50, 0, 0, static_cast<float>(FadeOutAlpha)));

		window.draw(Fade);
		Transition();
	}
}

std::string FCharacterCreationScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}

void FCharacterCreationScreen::StartFadeIn()
{
	CharacterCreationMusic.play();
	bFadingIn = true;
	FadeInAlpha = 255.f;
}

void FCharacterCreationScreen::Transition()
{
	if (IsFadeOutFinished)
	{
		bIsFinalised = true;
	}
}

void FCharacterCreationScreen::StopMusic()
{
	CharacterCreationMusic.stop();
}

std::string FCharacterCreationScreen::GetSelectedAttribute()
{
	return Fields[SelectedIndex];
}

bool FCharacterCreationScreen::CanSelectFields(int index) const
{
	if (!bIsCharacterCreated)
	{
		if (std::find(Attributes.begin(), Attributes.end(), Fields[index]) != Attributes.end())
		{
			return false;
		}
	}
	return true;
}
