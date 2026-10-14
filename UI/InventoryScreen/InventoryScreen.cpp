#include "InventoryScreen.h"
#include <iostream>
#include <cmath>

FInventoryScreen::FInventoryScreen()
{
	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Failed to load Font!" << std::endl;
	}

	if (!InventoryMusic.openFromFile("Assets/Audio/Music/Loop/Village_Loop.wav"))
	{
		std::cout << "Failed to load Music!" << std::endl;
	}

	InventoryMusic.setLoop(true);
	InventoryMusic.play();
	InventoryMusic.setVolume(0.f);

	bMusicFadingIn = true;

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}

	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.5f, .5f);

	if (!CursorMoveBuffer.loadFromFile("Assets/Audio/SFX/Select.mp3"))
	{
		std::cout << "Select sound failed to load!" << std::endl;
	}

	CursorMoveSound.setBuffer(CursorMoveBuffer);
	CursorMoveSound.setVolume(50.f);

	if (!ConfirmSoundBuffer.loadFromFile("Assets/Audio/SFX/Accept.mp3"))
	{
		std::cout << "Confirm sound failed to load!" << std::endl;
	}

	ConfirmSound.setBuffer(ConfirmSoundBuffer);
	ConfirmSound.setVolume(50.f);
}

void FInventoryScreen::HandleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			bChangeScreen = true;
		}
	}
}

void FInventoryScreen::Update(float DeltaTime)
{

}

void FInventoryScreen::Draw(sf::RenderWindow & window)
{
	sf::FloatRect TextBounds;
	sf::Text Title;

	Title.setFont(Font);
	Title.setFillColor(Theme.PrimaryColor);
	Title.setString(ToUpper("Inventory"));
	Title.setCharacterSize(80.f);
	TextBounds = Title.getLocalBounds();
	Title.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
	Title.setPosition(window.getView().getCenter().x, Title.getCharacterSize());

	window.draw(Title);

	InventoryBlock.setSize(sf::Vector2f(window.getView().getSize().x - 100.f, window.getView().getSize().y - 200.f));
	InventoryBlock.setOrigin(InventoryBlock.getSize() / 2.f);
	InventoryBlock.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 50.f);
	InventoryBlock.setOutlineColor(Theme.PrimaryColor);
	InventoryBlock.setOutlineThickness(2.f);
	InventoryBlock.setFillColor(Theme.BackgroundColor);
	
	window.draw(InventoryBlock);

	InventoryItemName.setFont(Font);
	InventoryItemName.setFillColor(Theme.PrimaryColor);
	InventoryItemName.setCharacterSize(40.f);
	TextBounds = InventoryItemName.getLocalBounds();
	InventoryItemName.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
	InventoryItemName.setPosition(InventoryBlock.getOrigin().x / 2 - 20.f, InventoryBlock.getOrigin().y);

	InventoryItemName.setString(CharacterSheet->GetInventory()->GetMaterials()[0].Material->MaterialName);

	window.draw(InventoryItemName);

	InventoryItemAmount.setFont(Font);
	InventoryItemAmount.setFillColor(Theme.PrimaryColor);
	InventoryItemAmount.setCharacterSize(40.f);
	TextBounds = InventoryItemAmount.getLocalBounds();
	InventoryItemAmount.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
	InventoryItemAmount.setPosition(InventoryBlock.getOrigin().x / 2 + 300.f, InventoryBlock.getOrigin().y);

	InventoryItemAmount.setString(std::to_string(CharacterSheet->GetInventory()->GetMaterials()[0].MaterialAmount));

	window.draw(InventoryItemAmount);
}

std::string FInventoryScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}


