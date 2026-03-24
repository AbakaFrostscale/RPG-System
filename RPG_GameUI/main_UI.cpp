#include <SFML/Graphics.hpp>
#include <RPG_GameUI/CharacterCreationScreen/CharacterCreationScreen.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "RPG UI Test");

	CharacterCreationScreen screen;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{							  
			if (event.type == sf::Event::Closed)
				window.close();

				screen.HandleInput(event);
		}

		screen.Update();

		window.clear();
		screen.Draw(window);
		window.display();
	}
	return 0;
}