// RPG Game System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Core/LoadExternalData.h"
#include "Core/Random.h"
#include "SFML/Graphics.hpp"

#include "UI/CharacterCreationScreen/CharacterCreationScreen.h"
#include "UI/StartScreen/StartScreen.h"
#include "UI/GameScreen/GameScreen.h"
#include "UI/InventoryScreen/InventoryScreen.h"
#include "UI/CraftingScreen/CraftingScreen.h"

#include "Character/Character.h"
#include "Inventory/Inventory.h"

#include "Combat/TurnBasedCombat.h"

enum class EGameState
{
	EGSStartMenu,
	EGSCharacterCreation,
	EGSGame,
	EGSInventory,
	EGSCrafting
};

FCharacterCreationScreen CreationScreen;
FStartScreen StartScreen;
FGameScreen GameScreen;
FInventoryScreen InventoryScreen;
FCraftingScreen CraftingScreen;

FTheme Theme;

FTurnBasedCombat Combat;
FCharacter CurrentCharacter;
FItem MainItem;

EGameState CurrentState = EGameState::EGSStartMenu;

bool bCharacterCreated;
bool bLoadFromStart;
sf::Font GameFont;
sf::Clock Clock;

static void LoadFont()
{
	if (!GameFont.loadFromFile("Assets/Fonts/Silkscreen-Bold.ttf"))
	{
		std::cout << "Font failed to load!" << std::endl;
	}
}

int main()
{
	LoadFont();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Wayfarer's Oath");

	while (window.isOpen())
	{
		float deltaTime = Clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (CurrentState == EGameState::EGSStartMenu)
			{
				StartScreen.HandleInput(event);
			}

			if (CurrentState == EGameState::EGSCharacterCreation)
			{
				CreationScreen.HandleInput(event);
			}

			if (CurrentState == EGameState::EGSGame)
			{
				GameScreen.HandleInput(event);
			}

			if (CurrentState == EGameState::EGSInventory)
			{
				InventoryScreen.HandleInput(event);
			}

			if (CurrentState == EGameState::EGSCrafting)
			{
				CraftingScreen.HandleInput(event);
			}
				
		}

		if (CurrentState == EGameState::EGSStartMenu)
		{
			StartScreen.Update(deltaTime);

			if (StartScreen.IsTransitionFinished())
			{
				int choice = StartScreen.GetSelectedOption();

				if (choice == 0) //New Game
				{
					CurrentState = EGameState::EGSCharacterCreation;
					CreationScreen.StartFadeIn();
				}
				else if (choice == 1) //Load Game
				{					
					CraftingScreen.SetCharacter(CurrentCharacter);
					InventoryScreen.SetCharacter(CurrentCharacter);
					GameScreen.SetCharacter(CurrentCharacter);
					GameScreen.LoadGame();
					
					StartScreen.ResetTransition();
				
					CurrentState = EGameState::EGSGame;
				}
				else if (choice == 2) //Exit
				{
					window.close();
				}
			}
		}
		sf::RectangleShape panel;

		if (CurrentState == EGameState::EGSCharacterCreation)
		{
			CreationScreen.Update(deltaTime);
			
			panel.setSize(sf::Vector2f(600.f, 400.f));
			panel.setPosition(40.f, 100.f);

			panel.setFillColor(sf::Color(50, 10, 10));
			panel.setOutlineThickness(2.f);
			panel.setOutlineColor(sf::Color(Theme.PrimaryColor));


			if (CreationScreen.IsFinalised())
			{
				CurrentCharacter.SetCharacter(CreationScreen.GetCharacter());

				CraftingScreen.SetCharacter(CurrentCharacter);
				InventoryScreen.SetCharacter(CurrentCharacter);
				GameScreen.SetCharacter(CurrentCharacter);
				GameScreen.SetSelectedCharacter(CreationScreen.GetSelectedCharacter());

				CurrentState = EGameState::EGSGame;
			}
		}

		if (CurrentState == EGameState::EGSGame)
		{
			GameScreen.Update(deltaTime);

			if (GameScreen.GetbChangeScreenInventory())
			{
				GameScreen.SetbChangeScreenInventory(false);
				CurrentState = EGameState::EGSInventory;
			}

			if (GameScreen.GetbChangeScreenCrafting())
			{
				GameScreen.SetbChangeScreenCrafting(false);
				CurrentState = EGameState::EGSCrafting;
			}

			if (GameScreen.bIsExitRequested())
			{
				window.close();
			}
		}

		if (CurrentState == EGameState::EGSInventory)
		{
			InventoryScreen.Update(deltaTime);

			if (InventoryScreen.GetbChangeScreen())
			{
				InventoryScreen.SetbChangeScreen(false);
				CurrentState = EGameState::EGSGame;
			}
		}

		if (CurrentState == EGameState::EGSCrafting)
		{
			CraftingScreen.Update(deltaTime);

			if (CraftingScreen.GetbChangeScreen())
			{
				CraftingScreen.SetbChangeScreen(false);
				CurrentState = EGameState::EGSGame;
			}
		}

		window.clear(sf::Color(Theme.BackgroundColor));

		if (CurrentState == EGameState::EGSStartMenu)
		{
			StartScreen.Draw(window);
		} 
		else if (CurrentState == EGameState::EGSCharacterCreation)
		{
			window.draw(panel);
			CreationScreen.Draw(window);
		}
		else if (CurrentState == EGameState::EGSGame)
		{
			GameScreen.Draw(window);
		}
		else if (CurrentState == EGameState::EGSInventory)
		{
			InventoryScreen.Draw(window);
		}
		else if (CurrentState == EGameState::EGSCrafting)
		{
			CraftingScreen.Draw(window);
		}

		
		window.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
