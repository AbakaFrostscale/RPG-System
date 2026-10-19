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

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}

	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.6f, .6f);

	if (!InventoryItemTexture.loadFromFile("Assets/Environment/crafting_materials/resources_outlined.png"))
	{
		std::cout << "Material Texture failed to laod!" << std::endl;
	}

	InventoryItemTexture.setSmooth(false);

	InventoryItemSprite.setTexture(InventoryItemTexture);
	InventoryItemSprite.setScale(4.f, 4.f);

	InventoryItemSprite.setTextureRect(sf::IntRect(0, 0 * FrameHeight, FrameWidth, FrameHeight));
	InventoryItemBounds = InventoryItemSprite.getLocalBounds();

	if (!CursorMoveBuffer.loadFromFile("Assets/Audio/SFX/Select.mp3"))
	{
		std::cout << "Select sound failed to load!" << std::endl;
	}

	CursorMoveSound.setBuffer(CursorMoveBuffer);
	CursorMoveSound.setVolume(50.f);
}

void FInventoryScreen::HandleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			bChangeScreen = true;
		}

		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			if (CharacterSheet->GetInventory()->GetMaterials().empty()) { return; }

			SelectedIndex++;
			CursorMoveSound.play();

			if (SelectedIndex >= CharacterSheet->GetInventory()->GetMaterials().size())
			{
				SelectedIndex = 0;
				ScrollOffset = 0;
			}

			if (SelectedIndex >= ScrollOffset + MaxVisibleItems)
			{
				ScrollOffset++;
			}
		}

		if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
		{
			if (CharacterSheet->GetInventory()->GetMaterials().empty()) { return; }

			SelectedIndex--;
			CursorMoveSound.play();

			if (SelectedIndex < 0)
			{
				SelectedIndex = CharacterSheet->GetInventory()->GetMaterials().size() - 1;
				if (CharacterSheet->GetInventory()->GetMaterials().size() > MaxVisibleItems)
				{
					ScrollOffset = CharacterSheet->GetInventory()->GetMaterials().size() - MaxVisibleItems;
				}
			}

			if (SelectedIndex < ScrollOffset)
			{
				ScrollOffset--;
			}
		}
	}
}

void FInventoryScreen::Update(float DeltaTime)
{
	CursorTimer += DeltaTime;
	CursorOffset = std::sin(CursorTimer) * 2.f;
}

void FInventoryScreen::Draw(sf::RenderWindow & window)
{
	sf::FloatRect TextBounds;
	sf::Text Title;

	Title.setFont(Font);
	Title.setFillColor(Theme.AccentColor);
	Title.setString(ToUpper("Inventory"));
	Title.setCharacterSize(80.f);
	TextBounds = Title.getLocalBounds();
	Title.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
	Title.setPosition(window.getView().getCenter().x, Title.getCharacterSize());

	window.draw(Title);

	InventoryBlock.setSize(sf::Vector2f(window.getView().getSize().x - 100.f, window.getView().getSize().y - 200.f));
	MaxVisibleItems = InventoryBlock.getSize().y / 60.f;
	InventoryBlock.setOrigin(InventoryBlock.getSize() / 2.f);
	InventoryBlock.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 50.f);
	InventoryBlock.setOutlineColor(Theme.PrimaryColor);
	InventoryBlock.setOutlineThickness(2.f);
	InventoryBlock.setFillColor(Theme.BackgroundColor);
	
	window.draw(InventoryBlock);

	InventoryItemInfoBlock.setSize(sf::Vector2f(InventoryBlock.getSize().x - 450, InventoryBlock.getSize().y));
	InventoryItemInfoBlock.setOrigin(InventoryItemInfoBlock.getSize() / 2.f);
	InventoryItemInfoBlock.setPosition(InventoryBlock.getPosition().x + 250, InventoryBlock.getPosition().y);
	InventoryItemInfoBlock.setOutlineColor(Theme.PrimaryColor);
	InventoryItemInfoBlock.setOutlineThickness(2.f);
	InventoryItemInfoBlock.setFillColor(Theme.BackgroundColor);

	window.draw(InventoryItemInfoBlock);

	InventoryItemName.setFont(Font);
	InventoryItemName.setCharacterSize(40.f);
	InventoryItemName.setColor(Theme.PrimaryColor);
	
	InventoryItemAmount.setFont(Font);
	InventoryItemAmount.setCharacterSize(40.f);
	InventoryItemAmount.setColor(Theme.PrimaryColor);

	InventoryItemWeightInfo.setFont(Font);
	InventoryItemWeightInfo.setCharacterSize(30.f);
	InventoryItemWeightInfo.setFillColor(Theme.PrimaryColor);
	InventoryItemWeightInfo.setPosition(InventoryItemInfoBlock.getPosition().x, InventoryItemInfoBlock.getPosition().y);

	InventoryItemTypeInfo.setFont(Font);
	InventoryItemTypeInfo.setCharacterSize(30.f);
	InventoryItemTypeInfo.setFillColor(Theme.PrimaryColor);
	InventoryItemTypeInfo.setPosition(InventoryItemInfoBlock.getPosition().x, InventoryItemInfoBlock.getPosition().y - 30.f);

	InventoryItemSprite.setPosition(InventoryItemInfoBlock.getPosition().x, InventoryItemInfoBlock.getPosition().y - 100.f);
	InventoryItemSprite.setOrigin(InventoryItemBounds.left + InventoryItemBounds.width / 2.f, InventoryItemBounds.top + InventoryItemBounds.height / 2.f);

	float TextHeight = InventoryBlock.getOrigin().y;
	int CurrentIndex = 0;
	int VisibleIndex = 0;

	if (CharacterSheet->GetInventory()->GetMaterials().empty())
	{	
		InventoryItemName.setPosition(InventoryBlock.getOrigin().x / 2.f - 20.f, TextHeight);
		InventoryItemName.setString(ToUpper("EMPTY"));
		TextBounds = InventoryItemName.getLocalBounds();
		InventoryItemName.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);

		window.draw(InventoryItemName);
	}
	else
	{
		for (const FMaterial& Material : CharacterSheet->GetInventory()->GetMaterials())
		{
			VisibleIndex = CurrentIndex - ScrollOffset;
			float ItemY = TextHeight + (60.f * VisibleIndex);

			InventoryItemName.setPosition(InventoryBlock.getOrigin().x / 2.f - 20.f, ItemY);
			InventoryItemAmount.setPosition(InventoryBlock.getOrigin().x / 2.f + 250.f, ItemY);

			InventoryItemName.setString(ToUpper(Material.Material->MaterialName));
			TextBounds = InventoryItemName.getLocalBounds();
			InventoryItemName.setOrigin(TextBounds.left + 30.f, TextBounds.top + TextBounds.height / 2.f);
			
			CursorSprite.setPosition(InventoryItemName.getPosition().x - 70.f, InventoryItemName.getPosition().y - TextBounds.height / 2.f - CursorOffset);

			InventoryItemAmount.setString(std::to_string(Material.MaterialAmount));
			TextBounds = InventoryItemAmount.getLocalBounds();
			InventoryItemAmount.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);


			if (CurrentIndex == SelectedIndex)
			{
				InventoryItemAmount.setColor(Theme.HighlightColor);

				InventoryItemName.setColor(Theme.HighlightColor);

				InventoryItemWeightInfo.setString(ToUpper("Weight: ") + std::to_string(Material.Material->Weight * Material.MaterialAmount));
				TextBounds = InventoryItemWeightInfo.getLocalBounds();
				InventoryItemWeightInfo.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);

				InventoryItemTypeInfo.setString(ToUpper("Type: ") + Material.Material->Type);
				TextBounds = InventoryItemTypeInfo.getLocalBounds();
				InventoryItemTypeInfo.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);

				InventoryItemColumn = Material.Material->Column;
				InventoryItemRow = Material.Material->Row;

				InventoryItemSprite.setTextureRect(sf::IntRect(InventoryItemRow * FrameWidth, InventoryItemColumn * FrameHeight, FrameWidth, FrameHeight));
				
				window.draw(CursorSprite);
			}
			else
			{
				InventoryItemAmount.setColor(Theme.PrimaryColor);
				InventoryItemName.setColor(Theme.PrimaryColor);
			}

			if (CurrentIndex >= ScrollOffset && CurrentIndex < ScrollOffset + MaxVisibleItems)
			{
				window.draw(InventoryItemName);
				window.draw(InventoryItemAmount);
			}

			CurrentIndex++;
		}
	}

	window.draw(InventoryItemTypeInfo);
	window.draw(InventoryItemWeightInfo);

	if (!CharacterSheet->GetInventory()->GetMaterials().empty())
	{
		window.draw(InventoryItemSprite);
	}
}

std::string FInventoryScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}


