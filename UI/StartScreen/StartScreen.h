#pragma once
#include <vector>
#include <string>
#include "Core/Types.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"



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
	FTheme Theme;

	sf::Font Font;

	//sound
	sf::Music MenuMusic;
	sf::SoundBuffer CursorMoveBuffer;
	sf::SoundBuffer ConfirmBuffer;

	sf::Sound CursorMoveSound;
	sf::Sound ConfirmSound;

	bool bMusicFading = false;
	float MusicFadeSpeed = 40.f;

	//Cursor 
	sf::Texture CursorTexture;
	sf::Sprite CursorSprite;
	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	float FadeAlpha = 0.f;
	float FadeSpeed = 200.f;

	bool bTransitioning = false;
	bool bTranisitionFinished = false;

	std::vector<std::string> Options = { "NEW GAME", "LOAD GAME", "EXIT" };

	int SelectedIndex = 0;
	bool bOptionChosen = false;

};