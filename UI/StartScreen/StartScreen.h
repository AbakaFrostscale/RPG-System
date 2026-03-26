#pragma once
#include <vector>
#include <string>

#include "SFML/Graphics.hpp"

class FStartScreen
{
public:
	FStartScreen();

	void HandleInput(const sf::Event& event);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void ResetTransition();

	bool IsTransitionFinished() const;
	int GetSelectedOption() const;
	bool IsOptionSelected();

private:
	sf::Font Font;

	float FadeAlpha = 0.f;
	float FadeSpeed = 200.f;

	bool bTransitioning = false;
	bool bTranisitionFinised = false;

	std::vector<std::string> Options = { "NEW GAME", "LOAD GAME", "EXIT" };

	int SelectedIndex = 0;
	bool bOptionChosen = false;

};