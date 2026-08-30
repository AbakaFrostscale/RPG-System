#include <iostream>

#include "StartScreen.h"

FStartScreen::FStartScreen()
{
	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Font Failed to Load!" << std::endl;
	}

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}
	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.8f, .8f);

	if (!MenuMusic.openFromFile("Assets/Audio/Music/Loop/Menu_Loop.wav"))
	{
		std::cout << "Menu music not found" << std::endl;
	}

	MenuMusic.setLoop(true);
	MenuMusic.setVolume(0.f);
	MenuMusic.play();
	bMusicFadingIn = true;

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

}

void FStartScreen::HandleInput(const sf::Event & event)
{
	if (bTransitioning)
		return;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			SelectedIndex--;
			CursorMoveSound.play();
			if (SelectedIndex < 0)
				SelectedIndex = Options.size() - 1;
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			SelectedIndex++;
			CursorMoveSound.play();
			if (SelectedIndex >= Options.size())
				SelectedIndex = 0;
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			ConfirmSound.play();
			bTransitioning = true;
			bMusicFadingOut = true;
		}
	}

}

void FStartScreen::Update(float deltaTime)
{
	CursorTimer += deltaTime;
	CursorOffset = std::sin(CursorTimer) * 2.f;

	if (bMusicFadingIn)
	{
		float NewVolume = MenuMusic.getVolume() + MusicFadeSpeed * deltaTime;

		if (NewVolume >= 50.f)
		{
			NewVolume = 50.f;
			bMusicFadingIn = false;
		}

		MenuMusic.setVolume(NewVolume);
	}

	if (bMusicFadingOut)
	{
		float NewVolume = MenuMusic.getVolume() - MusicFadeSpeed * deltaTime;

		if (NewVolume <= 0.f)
		{
			NewVolume = 0.f;
			MenuMusic.stop();
			bMusicFadingOut = false;
		}

		MenuMusic.setVolume(NewVolume);
	}

	if (bTransitioning)
	{
		FadeAlpha += deltaTime * FadeSpeed;

		if (FadeAlpha >= 255.f)
		{
			FadeAlpha = 255.f;
			bTranisitionFinished = true;
		}
	}
}

void FStartScreen::Draw(sf::RenderWindow & window)
{
	sf::Text title;

	title.setFont(Font);
	title.setString("PLACEHOLDER NAME");
	title.setCharacterSize(100);
	sf::FloatRect titleBounds = title.getLocalBounds();
	title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
	title.setPosition(window.getSize().x / 2.f, 100.f);

	window.draw(title);


	float startY = 250.f;

	for (int i = 0; i < Options.size(); i++)
	{
		sf::Text text;

		text.setFont(Font);
		text.setString(Options[i]);
		text.setCharacterSize(40);

		sf::FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

		text.setPosition(window.getSize().x / 2.f, startY + i * 60.f);

		if (i == SelectedIndex)
		{
			CursorSprite.setPosition(text.getPosition().x - textBounds.width / 2.f - 40.f, text.getPosition().y - textBounds.height / 2.f + CursorOffset);

			text.setFillColor(sf::Color(Theme.HighlightColor));

			window.draw(CursorSprite);
		}

		window.draw(text);
	}

	if (bTransitioning)
	{
		sf::RectangleShape fade;
		fade.setSize(sf::Vector2f(window.getSize()));
		fade.setFillColor(sf::Color(50, 0, 0, FadeAlpha));

		window.draw(fade);
	}
}

void FStartScreen::ResetTransition()
{
	bTransitioning = false;
	bTranisitionFinished = false;
	bMusicFadingIn = true;
	FadeAlpha = 0.f;
}

bool FStartScreen::IsTransitionFinished() const
{
	return bTranisitionFinished;
}

int FStartScreen::GetSelectedOption() const
{
	return SelectedIndex;
}

bool FStartScreen::IsOptionSelected()
{
	if (bOptionChosen)
	{
		bOptionChosen = false;
		return true;
	}

	return false;
}


