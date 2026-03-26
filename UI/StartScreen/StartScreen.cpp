#include <iostream>

#include "StartScreen.h"

FStartScreen::FStartScreen()
{
	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Font Failed to Load!" << std::endl;
	}
}

void FStartScreen::HandleInput(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			SelectedIndex--;
			if (SelectedIndex < 0)
				SelectedIndex = Options.size() - 1;
		}

		if (event.key.code == sf::Keyboard::Down)
		{
			SelectedIndex++;
			if (SelectedIndex >= Options.size())
				SelectedIndex = 0;
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			bTransitioning = true;
		}
	}

}

void FStartScreen::Update(float deltaTime)
{
	if (bTransitioning)
	{
		FadeAlpha += deltaTime * FadeSpeed;

		if (FadeAlpha >= 255.f)
		{
			FadeAlpha = 255.f;
			bTranisitionFinised = true;
		}
	}
}

void FStartScreen::Draw(sf::RenderWindow & window)
{
	sf::Text title;

	title.setFont(Font);
	title.setString("PLACEHOLDER NAME");
	title.setCharacterSize(100);
	title.setPosition(150.f, 100.f);

	window.draw(title);


	float startY = 250.f;

	for (int i = 0; i < Options.size(); i++)
	{
		sf::Text text;

		text.setFont(Font);
		text.setString(Options[i]);
		text.setCharacterSize(40);
		text.setPosition(350.f, startY + i * 60.f);

		if (i == SelectedIndex)
		{
			text.setFillColor(sf::Color::Red);
		}
		else
		{
			text.setFillColor(sf::Color::White);
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
	bTranisitionFinised = false;
	FadeAlpha = 0.f;
}

bool FStartScreen::IsTransitionFinished() const
{
	return bTranisitionFinised;
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
