#include "GameScreen.h"
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <cctype>
#include <Core/LoadExternalData.h>
#include <Libraries/tmxlite/tmxlite/include/tmxlite/Map.hpp>
#include "World/MapLoader.h"
#include "World/MapRenderer.h"

FGameScreen::FGameScreen()
{
	Loader = std::make_unique<FLoadExternalData>();
	Creator = std::make_unique<FCharacterCreator>();
	MapLoader = std::make_unique<FMapLoader>();
	MapRenderer = std::make_unique<FMapRenderer>();

	if (!Font.loadFromFile("Assets/Fonts/Silkscreen-Regular.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;;
	}

	if (!GameMusic.openFromFile("Assets/Audio/Music/2. Town theme (Streets of the Common).wav"))
	{
		std::cout << "Failed to load Field_Loop.wav!" << std::endl;
	}

	GameMusic.setLoop(true);
	GameMusic.play();
	GameMusic.setVolume(0.f);

	bMusicFadingIn = true;

	LoadTown();

	Random.RandomGenerator = std::mt19937(Random.rd());

	GenerateForest();

	if (!CursorTexture.loadFromFile("/Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}
	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.8f, .8f);
	
	if (!CursorMoveBuffer.loadFromFile("Assets/Audio/SFX/Audio/toggle_001.ogg"))
	{
		std::cout << "Select sound failed to load!" << std::endl;
	}
	
	CursorMoveSound.setBuffer(CursorMoveBuffer);
	CursorMoveSound.setVolume(50.f);

	if (!ConfirmBuffer.loadFromFile("Assets/Audio/SFX/Audio.confirmation_001.ogg"))
	{
		std::cout << "Confirm sound failed to load!" << std::endl;
	}

	ConfirmSound.setBuffer(ConfirmBuffer);
	ConfirmSound.setVolume(50.f);

	Camera.setSize(ScreenWidth, ScreenHeight);
}

FGameScreen::~FGameScreen() = default;



void FGameScreen::HandleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (CurrentGameMode == EGameMode::EGMPaused)
		{
			if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
			{
				SelectedIndex--;
				CursorMoveSound.play();
				if (SelectedIndex < 0)
				{
					SelectedIndex = MenuSettings.size() - 1;
				}
			}

			if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
			{
				SelectedIndex++;
				CursorMoveSound.play();
				if (SelectedIndex >= MenuSettings.size())
				{
					SelectedIndex = 0;
				}
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				switch (MenuSettings[SelectedIndex])
				{
				case EMenuSetting::EMSResume:
					MenuResult = EMenuResult::EMRResume;
					break;
				case EMenuSetting::EMSInventory:
					MenuResult = EMenuResult::EMRInventory;
					break;
				case EMenuSetting::EMSCrafting:
					MenuResult = EMenuResult::EMRCrafting;
					break;
				case EMenuSetting::EMSSave:
					MenuResult = EMenuResult::EMRSave;
					break;
				case EMenuSetting::EMSLoad:
					MenuResult = EMenuResult::EMRLoad;
					break;
				case EMenuSetting::EMSOptions:
					MenuResult = EMenuResult::EMROptions;
					break;
				case EMenuSetting::EMSExit:
					MenuResult = EMenuResult::EMRExit;
					break;
				case EMenuSetting::EMSDefault:
					std::cout << "Something Broke \n";
					break;
				default:
					break;
				}
				ConfirmSound.play();
			}
		}

		if (CurrentGameMode == EGameMode::EGMUnpaused &&  event.key.code == sf::Keyboard::E)
		{
			if (ClosestObject != nullptr)
			{
				CollectItem(CurrentInteractableObjectIndex);
			}
		}

		if (event.key.code == sf::Keyboard::Escape)
		{
			if (CurrentGameMode != EGameMode::EGMPaused)
			{
				CurrentGameMode = EGameMode::EGMPaused;
			}
			else
			{
				CurrentGameMode = EGameMode::EGMUnpaused;
			}
		}
	}
}

void FGameScreen::Update(float DeltaTime)
{
	sf::Vector2f Direction(0.f, 0.f);
	CameraPos = PlayerPosition;

	HandleMenu();

	bool bMoving = false;

	if (ShowNotification && NotificationClock.getElapsedTime().asSeconds() >= 2.f)
	{
		ShowNotification = false;
	}

	if (CurrentGameMode == EGameMode::EGMPaused) 
	{
		CursorTimer += DeltaTime;
		CursorOffset = std::sin(CursorTimer) * 2.f;
	}

	if (CurrentGameMode == EGameMode::EGMUnpaused && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Direction.y -= 1.f;
		CurrentAnimationRow = UpRow;
		FacingDirection = EFacingDirection::EFDUp;
		PlayerSprite.setScale(sf::Vector2f(1.f, 1.f));
		bMoving = true;
	}

	if (CurrentGameMode == EGameMode::EGMUnpaused && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Direction.y += 1.f;
		CurrentAnimationRow = DownRow;
		FacingDirection = EFacingDirection::EFDDown;
		PlayerSprite.setScale(sf::Vector2f(1.f, 1.f));
		bMoving = true;
	}

	if (CurrentGameMode == EGameMode::EGMUnpaused && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Direction.x -= 1.f;
		CurrentAnimationRow = LeftRow;
		FacingDirection = EFacingDirection::EFDLeft;
		PlayerSprite.setScale(sf::Vector2f(1.f, 1.f));
		bMoving = true;
	}

	if (CurrentGameMode == EGameMode::EGMUnpaused && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Direction.x += 1.f;
		CurrentAnimationRow = RightRow;
		FacingDirection = EFacingDirection::EFDRight;
		PlayerSprite.setScale(sf::Vector2f(1.f, 1.f));
		bMoving = true;
	}

	if (Direction.x != 0.f || Direction.y != 0.f)
	{
		float Length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);

		Direction.x /= Length;
		Direction.y /= Length;
	}

	sf::Vector2f NewPosition = PlayerPosition;

	NewPosition.x += Direction.x * MoveSpeed * DeltaTime;
	NewPosition.y += Direction.y * MoveSpeed * DeltaTime;

	bool bBlocked = false;

	if (NewPosition.x <= 0 + 10.f)
		bBlocked = true;
	if (NewPosition.y <= 0 + 10.f)
		bBlocked = true;
	if (NewPosition.x >= WorldWidth - 10.f)
		bBlocked = true;
	if (NewPosition.y >= WorldHeight - 10.f)
		bBlocked = true;

	sf::FloatRect NewPlayerBounds(NewPosition.x - 10.f, NewPosition.y - 10.f, 20.f, 20.f);

	OverlappingObject();

	for (const FForestObject& ForestObject : ForestObjects)
	{
		if (NewPlayerBounds.intersects(ForestObject.Collision))
		{
			bBlocked = true;
			break;
		}
	}

	if (!bBlocked)
	{
		PlayerPosition = NewPosition;
		PlayerSprite.setPosition(PlayerPosition);
	}

	if (bMusicFadingIn)
	{
		float NewVolume = GameMusic.getVolume() + MusicFadeSpeed * DeltaTime;

		if (NewVolume >= 50.f)
		{
			NewVolume = 50.f;
			bMusicFadingIn = false;
		}

		GameMusic.setVolume(NewVolume);
	}
	
	if (bMoving)
	{
		AnimationTimer += DeltaTime;

		if (AnimationTimer >= AnimationSpeed)
		{
			AnimationTimer = 0.f;

			CurrentFrame++;

			if (CurrentFrame > 2)
			{
				CurrentFrame = 0;
			}
		}
	}
	else
	{
		CurrentFrame = 0;
	}

	PlayerSprite.setTextureRect(sf::IntRect(FrameWidth * CurrentFrame, FrameHeight* CurrentAnimationRow, FrameWidth, FrameHeight));
	PlayerSprite.setOrigin(PlayerBounds.width / 2.f, PlayerBounds.height / 2.f);
	
	float HalfWidth = ScreenWidth / 2.f;
	float HalfHeight = ScreenHeight / 2.f;


	if (CameraPos.x < HalfWidth)
		CameraPos.x = HalfWidth;
	if (CameraPos.y < HalfHeight)
		CameraPos.y = HalfHeight;
	if (CameraPos.x > WorldWidth - HalfWidth)
		CameraPos.x = WorldWidth - HalfWidth;
	if (CameraPos.y > WorldHeight - HalfHeight)
		CameraPos.y = WorldHeight - HalfHeight;

	Camera.setCenter(CameraPos);
}

void FGameScreen::Draw(sf::RenderWindow& window)
{
	float HalfWidth = ScreenWidth / 2.f;
	float HalfHeight = ScreenHeight / 2.f;

	if (CameraPos.x < HalfWidth)
		CameraPos.x = HalfWidth;
	if (CameraPos.y < HalfHeight)
		CameraPos.y = HalfHeight;
	if (CameraPos.x > WorldWidth - HalfWidth)
		CameraPos.x = WorldWidth - HalfWidth;
	if (CameraPos.y > WorldHeight - HalfHeight)
		CameraPos.y = WorldHeight - HalfHeight;
	
	Camera.setCenter(CameraPos);

	window.setView(Camera);


	window.draw(PlayerSprite);

	window.setView(window.getDefaultView());

	CharacterInforText.setFont(Font);
	CharacterInforText.setCharacterSize(16);
	CharacterInforText.setFillColor(sf::Color::White);
	CharacterInforText.setPosition(ScreenWidth / 1.2f, ScreenHeight - 100.f);
	
	window.draw(CharacterInforText);
	
	PauseBackground.setSize(window.getView().getSize());
	PauseBackground.setOrigin(PauseBackground.getSize() / 2.f);
	PauseBackground.setPosition(window.getView().getCenter());
	PauseBackground.setFillColor(ScreenBackgroundColour);

	PauseMenu.setSize(sf::Vector2f(200.f, 450.f));
	PauseMenu.setOrigin(PauseMenu.getSize() / 2.f);
	PauseMenu.setPosition(window.getView().getCenter());
	PauseMenu.setOutlineColor(Theme.PrimaryColor);
	PauseMenu.setOutlineThickness(2.f);
	PauseMenu.setFillColor(Theme.BackgroundColor);

	if (CurrentGameMode == EGameMode::EGMPaused)
	{
		window.draw(PauseBackground);
		window.draw(PauseMenu);

		sf::Text MenuOptionText;
		float StartY = PauseMenu.getPosition().y - 175.f;

		for (int i = 0; i < MenuSettings.size(); i++)
		{
			switch (MenuSettings[i])
			{
			case EMenuSetting::EMSResume:
				MenuOptionText.setString("RESUME");
				break;
			case EMenuSetting::EMSInventory:
				MenuOptionText.setString("INVENTORY");
				break;
			case EMenuSetting::EMSCrafting:
				MenuOptionText.setString("CRAFT");
				break;
			case EMenuSetting::EMSSave:
				MenuOptionText.setString("SAVE");
				break;
			case EMenuSetting::EMSLoad:
				MenuOptionText.setString("LOAD");
				break;
			case EMenuSetting::EMSOptions:
				MenuOptionText.setString("OPTIONS");
				break;
			case EMenuSetting::EMSExit:
				MenuOptionText.setString("EXIT");
				break;
			default:
				break;
			}

			MenuOptionText.setFont(Font);
			MenuOptionText.setFillColor(Theme.PrimaryColor);
			MenuOptionText.setCharacterSize(20.f);

			sf::FloatRect TextBounds = MenuOptionText.getLocalBounds();
			MenuOptionText.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
			
			MenuOptionText.setPosition(PauseMenu.getPosition().x, StartY + i * 60.f);
			
			if (i == SelectedIndex)
			{
				CursorSprite.setPosition(MenuOptionText.getPosition().x - TextBounds.width / 2.f - 40.f, MenuOptionText.getPosition().y - TextBounds.height / 2.f + CursorOffset);

				MenuOptionText.setFillColor(Theme.HighlightColor);

				window.draw(CursorSprite);
			}
			
			window.draw(MenuOptionText);
		}
	}

	if (CurrentGameMode == EGameMode::EGMCrafting)
	{
		DrawScreen(window, CraftingText, CraftingBackground, CraftingMenu);
	}

	if (CurrentGameMode == EGameMode::EGMOptions)
	{
		DrawScreen(window, OptionsText, OptionsBackground, OptionsMenu);
	}

	if (ShowNotification)
	{
		Notification(window, SaveLoadText, SaveLoadSuccessMenu);
	}
}

std::string FGameScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}

void FGameScreen::SetCharacter(FCharacter& Character)
{
	CharacterSheet = &Character;

	CharacterInforText.setString
	(ToUpper("Name: " + CharacterSheet->GetCharacterReference().CharName) +
		ToUpper("\nRace: " + CharacterSheet->GetCharacterReference().CharRace.RaceName) +
		ToUpper("\nClass: " + CharacterSheet->GetCharacterReference().CharClass.ClassName));
}

void FGameScreen::LoadGame()
{
	bool SaveLoadSuccess = SaveAndLoad.LoadGame("SaveFile.json");

	if (SaveLoadSuccess)
	{
		SaveLoadText.setString(ToUpper("Load Successful"));
		Creator->LoadCharacter(CharacterSheet->GetCharacterReference(), SaveAndLoad.GetLoadData().SavedCharacter);

		CharacterSheet->GetInventory()->SetInventory(SaveAndLoad.GetLoadData().CharacterInventory.GetInventory());

		SetSelectedCharacter(SaveAndLoad.GetLoadData().SelectedSpriteIndex);
		PlayerPosition = SaveAndLoad.GetLoadData().CharacterPosition;
		PlayerSprite.setPosition(PlayerPosition);

		UpdateCharacter();

		LoadForest(SaveAndLoad.GetLoadData().ForestObjectIDs);
	}
	else
	{
		SaveLoadText.setString(ToUpper("Load Failed"));
	}
}

void FGameScreen::SetSelectedCharacter(const int SelectedCharacter)
{
	SelectedCharacterRow = SelectedCharacter;

	if (!PlayerTexture.loadFromFile(Loader->GetSpriteFile()[SelectedCharacterRow]))
	{
		std::cout << "Failed to load Character Sprite!" << std::endl;
	}

	PlayerTexture.setSmooth(true);

	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(1.f, 1.f);
	PlayerSprite.setPosition(PlayerPosition);

	PlayerSprite.setTextureRect(sf::IntRect(FrameWidth, DownRow * FrameHeight, FrameWidth, FrameHeight));
	PlayerBounds = PlayerSprite.getLocalBounds();
}

void FGameScreen::UpdateCharacter()
{
	CharacterInforText.setString
	(ToUpper("Name: " + CharacterSheet->GetCharacterReference().CharName) +
		ToUpper("\nRace: " + CharacterSheet->GetCharacterReference().CharRace.RaceName) +
		ToUpper("\nClass: " + CharacterSheet->GetCharacterReference().CharClass.ClassName));
}

void FGameScreen::GenerateForest()
{
	ForestObjects.clear();
	ForestObjectID = 0;

	std::sort(ForestObjects.begin(), ForestObjects.end(), [](const FForestObject& A,const FForestObject& B)
		{
			return A.Sprite.getPosition().y < B.Sprite.getPosition().y;
		});
}

void FGameScreen::OverlappingObject()
{
	ClosestObject = nullptr;

	switch (FacingDirection)
	{
	case EFacingDirection::EFDUp:
		PlayerReach = sf::FloatRect(PlayerPosition.x - PlayerBounds.width, PlayerPosition.y - PlayerBounds.height,
			PlayerBounds.width + 20.f, 
			PlayerBounds.height + 30.f);
		break;
	case EFacingDirection::EFDDown:
		PlayerReach = sf::FloatRect(PlayerPosition.x - PlayerBounds.width, PlayerPosition.y + PlayerBounds.height,
			PlayerBounds.width + 20.f,
			PlayerBounds.height + 10.f);
		break;
	case EFacingDirection::EFDLeft:
		PlayerReach = sf::FloatRect(PlayerPosition.x - PlayerBounds.width, PlayerPosition.y - PlayerBounds.height,
			PlayerBounds.width + 30.f,
			PlayerBounds.height + 20.f);
		break;
	case EFacingDirection::EFDRight:
		PlayerReach = sf::FloatRect(PlayerPosition.x + PlayerBounds.width, PlayerPosition.y - PlayerBounds.height,
			PlayerBounds.width + 10.f,
			PlayerBounds.height + 20.f);
		break;
	default:
		break;
	}

	int ClosestObjectIndex = 0;

	for (size_t i = 0; i < ForestObjects.size(); i++)
	{
		if (PlayerReach.intersects(ForestObjects[i].Collision))
		{
			if (!ClosestObject)
			{
				ClosestObject = &ForestObjects[i];
				ClosestObjectIndex = i;
															  
				continue;
			}

			float DistanceToClosestObject = (PlayerPosition.x - ClosestObject->Sprite.getPosition().x) * (PlayerPosition.x - ClosestObject->Sprite.getPosition().x) +
												(PlayerPosition.y - ClosestObject->Sprite.getPosition().y) * (PlayerPosition.y - ClosestObject->Sprite.getPosition().y);
			float DistanceToCurrentObject = (PlayerPosition.x - ForestObjects[i].Sprite.getPosition().x) * (PlayerPosition.x - ForestObjects[i].Sprite.getPosition().x) +
												(PlayerPosition.y - ForestObjects[i].Sprite.getPosition().y) * (PlayerPosition.y - ForestObjects[i].Sprite.getPosition().y);

			if (DistanceToCurrentObject < DistanceToClosestObject)
			{
				ClosestObject = &ForestObjects[i];
				ClosestObjectIndex = i;
			}
		}
	}
	if (ClosestObject == nullptr)
		return;
		
	switch (ClosestObject->ObjectType)
	{
	case EObjectType::EOTTree:
		CurrentInteractableObjectIndex = ClosestObjectIndex;
		break;
	case EObjectType::EOTRock:
		CurrentInteractableObjectIndex = ClosestObjectIndex;
		break;
	case EObjectType::EOTBush:
		CurrentInteractableObjectIndex = ClosestObjectIndex;
		break;
	default:
		break;
	}
}

void FGameScreen::DrawScreen(sf::RenderWindow& window, sf::Text& ScreenText, sf::RectangleShape& ScreenBackground, sf::RectangleShape& ScreenMenu)
{
	ScreenBackground.setSize(window.getView().getSize());
	ScreenBackground.setOrigin(ScreenBackground.getSize() / 2.f);
	ScreenBackground.setPosition(window.getView().getCenter());
	ScreenBackground.setFillColor(ScreenBackgroundColour);

	ScreenMenu.setSize(sf::Vector2f(window.getView().getSize().x - 100.f, window.getView().getSize().y - 100.f));
	ScreenMenu.setOrigin(ScreenMenu.getSize() / 2.f);
	ScreenMenu.setPosition(window.getView().getCenter());
	ScreenMenu.setOutlineColor(Theme.PrimaryColor);
	ScreenMenu.setOutlineThickness(2.f);
	ScreenMenu.setFillColor(Theme.BackgroundColor);

	window.draw(ScreenText);
	window.draw(ScreenBackground);
	window.draw(ScreenMenu);
}

void FGameScreen::Notification(sf::RenderWindow& window, sf::Text& NotifyText, sf::RectangleShape& NotifyBackgrond)
{
	NotifyBackgrond.setSize(sf::Vector2f(300, 100));
	NotifyBackgrond.setOrigin(NotifyBackgrond.getSize() / 2.f);
	NotifyBackgrond.setPosition(window.getView().getCenter());
	NotifyBackgrond.setOutlineColor(Theme.PrimaryColor);
	NotifyBackgrond.setOutlineThickness(2.f);
	NotifyBackgrond.setFillColor(Theme.BackgroundColor);

	NotifyText.setFont(Font);
	NotifyText.setFillColor(Theme.PrimaryColor);
	NotifyText.setCharacterSize(20.f);
	
	sf::FloatRect TextBounds = NotifyText.getLocalBounds();
	NotifyText.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);

	NotifyText.setPosition(NotifyBackgrond.getPosition());

	window.draw(NotifyBackgrond);
	window.draw(NotifyText);
}

void FGameScreen::CollectItem(int ObjectToCollect)
{
	if (ObjectToCollect < 0 || ObjectToCollect >= ForestObjects.size())
		return;

	switch (ForestObjects[ObjectToCollect].ObjectType)
	{
	case EObjectType::EOTTree:
		{
			// Add random Wood to inventory
			std::uniform_int_distribution<int> GatheredDist(0, 3);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet->GatherMaterials(&Material);

			break;
		}
	case EObjectType::EOTRock:
		{
			// Add random Ore to inventory
			std::uniform_int_distribution<int> GatheredDist(4, 7);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet->GatherMaterials(&Material);

			break;
		}
	case EObjectType::EOTBush:
		{
			// Add random Cloth to inventory	   

			std::uniform_int_distribution<int> GatheredDist(8, 11);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet->GatherMaterials(&Material);

			break;
		}
	default:
		break;
	}

	GatheredObjectID.push_back(ForestObjects[ObjectToCollect].ObjectID);
	ForestObjects.erase(ForestObjects.begin() + ObjectToCollect);
	ClosestObject = nullptr;
	CurrentInteractableObjectIndex = -1;
}

void FGameScreen::LoadForest(const std::vector<int>& GatheredItems)
{
	GenerateForest();

	for (const int& ObjectID : GatheredItems)
	{
		GatheredObjectID.push_back(ObjectID);
	}

	std::erase_if(ForestObjects, [&GatheredItems](const FForestObject& ForestObject) {
		return std::find(GatheredItems.begin(), GatheredItems.end(), ForestObject.ObjectID)
			!= GatheredItems.end(); });
}

void FGameScreen::LoadTown()
{
	if (!MapLoader->LoadMap("Assets/Environment/Maps/Maps/Frontier_Town.tmx"))
	{
		std::cout << "Town Map failed to load!";
		return;
	}

	const tmx::Map* CurrentMap = MapLoader->GetMap();

	WorldWidth = CurrentMap->getBounds().width;
	WorldHeight = CurrentMap->getBounds().height;

	for (const auto& Layer : CurrentMap->getLayers())
	{
		if (Layer->getName() != "PlayerSpawn")
			continue;

		if (Layer->getType() != tmx::Layer::Type::Object)
			continue;
		
		for (const auto& Object : Layer->getLayerAs<tmx::ObjectGroup>().getObjects())
		{
			if (Object.getName() != "MainSpawn")
				continue;

			PlayerPosition = sf::Vector2f(Object.getPosition().x, Object.getPosition().y);
			break;
		}
		break;
	}

	MapRenderer->SetMap(*CurrentMap);
	MapRenderer->LoadTilesets(CurrentMap->getTilesets());
}

void FGameScreen::HandleMenu()
{
	bool SaveLoadSuccess = false;

	switch (MenuResult)
	{
	case EMenuResult::EMRResume:
		//Pause and Unpause Game
		CurrentGameMode = EGameMode::EGMUnpaused;
		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRInventory:
		// Open Inventory Screen
		bChangeScreenInventory = true;
		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRCrafting:
		// Open Crafting Screen
		bChangeScreenCrafting = true;
		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRSave:
		// Save the Game
		SaveLoadSuccess = SaveAndLoad.SaveGame(CharacterSheet->GetCharacterReference(), *CharacterSheet->GetInventory(), PlayerPosition, SelectedCharacterRow, GatheredObjectID);
		
		if (SaveLoadSuccess)
		{
			SaveLoadText.setString(ToUpper("Save Successful"));
		}
		else 
		{
			SaveLoadText.setString(ToUpper("Save Failed"));
		}

		ShowNotification = true;
		NotificationClock.restart();

		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRLoad:
		// Load Game
		
		LoadGame();

		ShowNotification = true;
		NotificationClock.restart();

		std::cout << CharacterSheet->GetCharacterReference().CharName << std::endl;

		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMROptions:
		// Open the options menu
		CurrentGameMode = EGameMode::EGMOptions;
		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRExit:
		// Double check to make sure people want to exit...
		bExitRequest = true;
		MenuResult = EMenuResult::EMRDefault;
		break;
	case EMenuResult::EMRDefault:
		break;
	default:
		break;
	}
}