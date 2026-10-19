#include "CraftingScreen.h"
#include <iostream>
#include <cmath>
#include "Inventory/Crafting.h"
#include "Core/LoadExternalData.h"

FCraftingScreen::FCraftingScreen()
{
	Loader = std::make_shared<FLoadExternalData>();

	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}

	if (!CraftingMusic.openFromFile("Assets/Audio/Music/Loop/Village_Loop.wav"))
	{
		std::cout << "Failed to load Music!" << std::endl;
	}

	CraftingMusic.setLoop(true);
	CraftingMusic.play();
	CraftingMusic.setVolume(0.f);

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}
	
	CuresorSprite.setTexture(CursorTexture);
	CuresorSprite.setScale(.6f, .6f);

	if (!CraftingItemTexture.loadFromFile("Assets/Equipment/32x32.png"))
	{
		std::cout << "Item Texture failed to load!" << std::endl;
	}

	CraftingItemTexture.setSmooth(false);

	CraftingItemSprite.setTexture(CraftingItemTexture);
	CraftingItemSprite.setScale(2.75f, 2.75f);

	CraftingItemSprite.setTextureRect(sf::IntRect(0, 0 * FrameHeight, FrameWidth, FrameHeight));
	CraftignItemBounds = CraftingItemSprite.getLocalBounds();

	if (!CursorMoveBuffer.loadFromFile("Assets/Audio/SFX/Select.mp3"))
	{
		std::cout << "Selecte sound failed to load!" << std::endl;
	}

	CursorMoveSound.setBuffer(CursorMoveBuffer);
	CursorMoveSound.setVolume(50.f);

	YesText.setString(ToUpper("yes"));
	NoText.setString(ToUpper("no"));
}

void FCraftingScreen::HandleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			bChangeScreen = true;
		}

		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			SelectedIndex++;
			CursorMoveSound.play();

			if (SelectedIndex >= Loader->GetAvailableItems().size())
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
			SelectedIndex--;
			CursorMoveSound.play();

			if (SelectedIndex < 0)
			{
				SelectedIndex = Loader->GetAvailableItems().size() - 1;
				if (Loader->GetAvailableItems().size() > MaxVisibleItems)
				{
					ScrollOffset = Loader->GetAvailableItems().size() - MaxVisibleItems;
				}
			}

			if (SelectedIndex < ScrollOffset)
			{
				ScrollOffset--;
			}
		}

		if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::E)
		{
			bCraftItem = true;

			ConfirmBlock.setSize(sf::Vector2f(CraftingBlock.getSize().x - 350.f, CraftingBlock.getSize().y - 200.f));
			ConfirmBlock.setOrigin(ConfirmBlock.getSize() / 2.f);
			ConfirmBlock.setPosition(CraftingBlock.getPosition());
			ConfirmBlock.setOutlineColor(Theme.PrimaryColor);
			ConfirmBlock.setOutlineThickness(2.f);
			ConfirmBlock.setFillColor(Theme.BackgroundColor);
		}

	}
}

void FCraftingScreen::Update(float DeltaTime)
{
	CursorTimer += DeltaTime;
	CursorOffset = std::sin(CursorTimer) * 2.f;
}

void FCraftingScreen::Draw(sf::RenderWindow & window)
{
	sf::FloatRect TextBounds;
	sf::Text Title;

	Title.setFont(Font);
	Title.setFillColor(Theme.AccentColor);
	Title.setString(ToUpper("Crating"));
	Title.setCharacterSize(80.f);
	TextBounds = Title.getLocalBounds();
	Title.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
	Title.setPosition(window.getView().getCenter().x, Title.getCharacterSize());

	window.draw(Title);

	CraftingBlock.setSize(sf::Vector2f(window.getView().getSize().x - 100.f, window.getView().getSize().y - 200.f));
	MaxVisibleItems = CraftingBlock.getSize().y / 60.f;
	CraftingBlock.setOrigin(CraftingBlock.getSize() / 2.f);
	CraftingBlock.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 50.f);
	CraftingBlock.setOutlineColor(Theme.PrimaryColor);
	CraftingBlock.setOutlineThickness(2.f);
	CraftingBlock.setFillColor(Theme.BackgroundColor);

	window.draw(CraftingBlock);

	CraftingItemInfoBlock.setSize(sf::Vector2f(CraftingBlock.getSize().x - 450.f, CraftingBlock.getSize().y));
	CraftingItemInfoBlock.setOrigin(CraftingItemInfoBlock.getSize() / 2.f);
	CraftingItemInfoBlock.setPosition(CraftingBlock.getPosition().x + 250.f, CraftingBlock.getPosition().y);
	CraftingItemInfoBlock.setOutlineColor(Theme.PrimaryColor);
	CraftingItemInfoBlock.setOutlineThickness(2.f);
	CraftingItemInfoBlock.setFillColor(Theme.BackgroundColor);

	window.draw(CraftingItemInfoBlock);

	CraftingItemName.setFont(Font);
	CraftingItemName.setCharacterSize(40.f);
	CraftingItemName.setColor(Theme.PrimaryColor);

	CraftingItemInfo.setFont(Font);
	CraftingItemInfo.setCharacterSize(30.f);
	CraftingItemInfo.setFillColor(Theme.PrimaryColor);
	CraftingItemInfo.setPosition(CraftingItemInfoBlock.getPosition().x, CraftingItemInfoBlock.getPosition().y);

	CraftingItemMaterialsName.setFont(Font);
	CraftingItemMaterialsName.setCharacterSize(30.f);
	CraftingItemMaterialsName.setFillColor(Theme.PrimaryColor);
	CraftingItemMaterialsName.setPosition(CraftingItemInfoBlock.getPosition().x - 80.f, CraftingItemInfoBlock.getPosition().y + 30.f);

	CraftingItemMaterialsAmount.setFont(Font);
	CraftingItemMaterialsAmount.setCharacterSize(30.f);
	CraftingItemMaterialsAmount.setFillColor(Theme.PrimaryColor);
	CraftingItemMaterialsAmount.setPosition(CraftingItemInfoBlock.getPosition().x + 100.f, CraftingItemInfoBlock.getPosition().y + 30.f);

	CraftingItemSprite.setPosition(CraftingItemInfoBlock.getPosition().x, CraftingItemInfoBlock.getPosition().y - 100.f);

	float TextHeight = CraftingBlock.getOrigin().y;
	int CurrentIndex = 0;
	int VisibleIndex = 0;
	
	for (const FItemData& Item : Loader->GetAvailableItems())
	{
		VisibleIndex = CurrentIndex - ScrollOffset;
		float ItemY = TextHeight + (60.f * VisibleIndex);

		CraftingItemName.setPosition(CraftingBlock.getOrigin().x / 2.f - 20.f, ItemY);

		CraftingItemName.setString(ToUpper(Item.ItemName));
		TextBounds = CraftingItemName.getLocalBounds();
		CraftingItemName.setOrigin(TextBounds.left + 30.f, TextBounds.top + TextBounds.height / 2.f);
		
		CuresorSprite.setPosition(CraftingItemName.getPosition().x - 70.f, CraftingItemName.getPosition().y - TextBounds.height / 2.f - CursorOffset);
		CraftingItemSprite.setOrigin(CraftignItemBounds.left + CraftignItemBounds.width / 2.f, CraftignItemBounds.top + CraftignItemBounds.height / 2.f);

		if (CurrentIndex == SelectedIndex)
		{
			CraftingItemName.setColor(Theme.HighlightColor);

			CraftingItemInfo.setString(ToUpper("Type: ") + ToUpper(Item.ItemType));
			TextBounds = CraftingItemInfo.getLocalBounds();
			CraftingItemInfo.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);

			CraftingItemRow = Item.Row;
			CraftingItemColumn = Item.Column;

			CraftingItemSprite.setTextureRect(sf::IntRect(CraftingItemRow * FrameWidth, CraftingItemColumn * FrameHeight, FrameWidth, FrameHeight));

			if (!CharacterSheet->GetInventory()->HasRequiredMaterials(*CharacterSheet->GetInventory(), Item))
			{
				CraftingItemSprite.setColor(sf::Color(50.f, 50.f, 50.f));
			}
			else
			{
				CraftingItemSprite.setColor(sf::Color::White);
			}

			float CraftedItemY = CraftingItemMaterialsName.getPosition().y;

			for (const FMaterial& Material : Item.RequiredMaterial)
			{
				CraftingItemMaterialsName.setString(ToUpper(Material.Material->MaterialName));
				TextBounds = CraftingItemMaterialsName.getLocalBounds();
				CraftingItemMaterialsName.setOrigin(TextBounds.left, TextBounds.top + TextBounds.height / 2.f);
				CraftingItemMaterialsName.setPosition(CraftingItemMaterialsName.getPosition().x, CraftedItemY);

				CraftingItemMaterialsAmount.setString(std::to_string(Material.MaterialAmount));
				TextBounds = CraftingItemMaterialsAmount.getLocalBounds();
				CraftingItemMaterialsAmount.setOrigin(TextBounds.left, TextBounds.top + TextBounds.height / 2.f);
				CraftingItemMaterialsAmount.setPosition(CraftingItemMaterialsAmount.getPosition().x, CraftedItemY);

				CraftedItemY += 30.f;

				window.draw(CraftingItemMaterialsName);
				window.draw(CraftingItemMaterialsAmount);
			}
				
			window.draw(CuresorSprite);
		}
		else
		{
			if (!CharacterSheet->GetInventory()->HasRequiredMaterials(*CharacterSheet->GetInventory(), Item))
			{
				CraftingItemName.setFillColor(sf::Color(50.f, 50.f, 50.f));
			}
			else
			{
				CraftingItemName.setFillColor(Theme.PrimaryColor);
			}
		}

		if (bCraftItem)
		{
			ConfirmText.setString(ToUpper("Are you sure you want to craft ") + ToUpper(Item.ItemName));
			TextBounds = ConfirmText.getLocalBounds();
			ConfirmText.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
			ConfirmText.setPosition(ConfirmBlock.getPosition().x, ConfirmBlock.getPosition().y - 50.f);

			window.draw(ConfirmBlock);
			window.draw(ConfirmText);
		}

		if (CurrentIndex >= ScrollOffset && CurrentIndex < ScrollOffset + MaxVisibleItems)
		{
			window.draw(CraftingItemName);
		}

		CurrentIndex++;
	}


	window.draw(CraftingItemInfo);
	window.draw(CraftingItemSprite);
}

std::string FCraftingScreen::ToUpper(const std::string & input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}
