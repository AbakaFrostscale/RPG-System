#include "GameScreen.h"
#include <iostream>
#include <cmath>
#include <random>
#include <Core/LoadExternalData.h>
#include <Inventory/Inventory.h>

FGameScreen::FGameScreen()
{
	Loader = std::make_unique<FLoadExternalData>();

	if (!Font.loadFromFile("Assets/Fonts/FFScript.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;;
	}

	if (!PlayerTexture.loadFromFile("Assets/Sprites/Characters/Character Choice.png"))
	{
		std::cout << "Failed to load Character Sprite!" << std::endl;
	}

	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(2.f, 2.f);
	PlayerSprite.setPosition(PlayerPosition);

	PlayerSprite.setTextureRect(sf::IntRect(0, SelectedCharacterRow * FrameHeight, FrameWidth, FrameHeight));
	PlayerBounds = PlayerSprite.getLocalBounds();

	if (!GameMusic.openFromFile("Assets/Audio/Music/Loop/Field_Loop.wav"))
	{
		std::cout << "Failed to load Field_Loop.wav!" << std::endl;
	}

	GameMusic.setLoop(true);
	GameMusic.play();
	GameMusic.setVolume(0.f);

	bMusicFadingIn = true;

	if (!GroundTexture.loadFromFile("Assets/Environment/SeamlessGroundTextures/grass-bright-1.png"))
	{
		std::cout << "Failed to load grass-bright-1.png" << std::endl;
	}

	GroundTexture.setRepeated(true);
	GroundTexture.setSmooth(false);

	Ground.setSize(sf::Vector2f(WorldWidth, WorldHeight));
	Ground.setTexture(&GroundTexture);
	Ground.setTextureRect(sf::IntRect(0, 0, WorldWidth, WorldHeight));

	if (!PathTexture.loadFromFile("Assets/Environment/SeamlessGroundTextures/grass-red-1.png"))
	{
		std::cout << "Failed to load grass-red-1.png" << std::endl;
	}

	PathTexture.setRepeated(true);
	PathTexture.setSmooth(false);

	Path.setSize(sf::Vector2f(WorldWidth, 140));
	Path.setPosition(0, WorldHeight / 2.0f - 70);
	Path.setTexture(&PathTexture);
	Path.setTextureRect(sf::IntRect(0, 0, WorldWidth, 40));

	if (!TreeTexture.loadFromFile("Assets/Environment/Trees.png"))
	{
		std::cout << "Failed to load tree sheet!" << std::endl;
	}

	if (!RockTexture.loadFromFile("Assets/Environment/Rocks by Klyssilla_Tileset_32x32.png"))
	{
		std::cout << "Failed to load rocks sheet!" << std::endl;
	}


	Random.RandomGenerator = std::mt19937(Random.rd());

	GenerateForest();

	CurrentGameMode = EGameMode::EGMUnpaused;

	if (!CursorTexture.loadFromFile("Assets/Sprites/Cursors/03.png"))
	{
		std::cout << "Cursor failed to load!" << std::endl;
	}
	CursorSprite.setTexture(CursorTexture);
	CursorSprite.setScale(.8f, .8f);
	
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
					SelectedIndex = MenuText.size() - 1;
				}
			}

			if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
			{
				SelectedIndex++;
				CursorMoveSound.play();
				if (SelectedIndex >= MenuText.size())
				{
					SelectedIndex = 0;
				}
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				ConfirmSound.play();
			}
		}


		if (event.key.code == sf::Keyboard::E)
		{
			std::cout << "E Key Pressed" << std::endl;
			CollectItem(CurrentInteractableObjectIndex);
		}

		if (event.key.code == sf::Keyboard::Escape)
		{
			if (CurrentGameMode == EGameMode::EGMUnpaused)
			{
				std::cout << "Game Paused" << std::endl;
				CurrentGameMode = EGameMode::EGMPaused;
			}
			else if (CurrentGameMode == EGameMode::EGMPaused)
			{
				std::cout << "Game Unpaused" << std::endl;
				CurrentGameMode = EGameMode::EGMUnpaused;
			}
		}
	}
}

void FGameScreen::Update(float DeltaTime)
{
	sf::Vector2f Direction(0.f, 0.f);

	bool bMoving = false;

	if (CurrentGameMode == EGameMode::EGMPaused) 
	{
		CursorTimer += DeltaTime;
		CursorOffset = std::sin(CursorTimer) * 2.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Direction.y -= 1.f;
		CurrentAnimationRow = UpRow;
		FacingDirection = EFacingDirection::EFDUp;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Direction.y += 1.f;
		CurrentAnimationRow = DownRow;
		FacingDirection = EFacingDirection::EFDDown;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Direction.x -= 1.f;
		CurrentAnimationRow = LeftRow;
		FacingDirection = EFacingDirection::EFDLeft;
		PlayerSprite.setScale(sf::Vector2f(2.f, 2.f));
		bMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Direction.x += 1.f;
		CurrentAnimationRow = LeftRow;
		FacingDirection = EFacingDirection::EFDRight;
		PlayerSprite.setScale(sf::Vector2f(-2.f, 2.f));
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

			if (CurrentFrame >= 2)
			{
				CurrentFrame = 0;
			}
		}
	}
	else
	{
		CurrentFrame = 0;
	}

	PlayerSprite.setTextureRect(sf::IntRect((CurrentFrame + CurrentAnimationRow) * FrameWidth, SelectedCharacterRow * FrameHeight, FrameWidth, FrameHeight));
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
	Camera.setSize(ScreenWidth, ScreenHeight);
	CameraPos = PlayerPosition;

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


	window.draw(Ground);
	window.draw(Path);

	for (FForestObject& Object : ForestObjects)
	{
		if (Object.Sprite.getPosition().y < PlayerSprite.getPosition().y)
		{
				window.draw(Object.Sprite);
		}
	}

	sf::RectangleShape debugBox;
	debugBox.setPosition(PlayerReach.getPosition());
	debugBox.setSize(PlayerReach.getSize());
	debugBox.setFillColor(sf::Color(255, 0, 0, 100));

	window.draw(PlayerSprite);
	window.draw(debugBox);

	for (FForestObject& Object : ForestObjects)
	{
		if (Object.Sprite.getPosition().y >= PlayerSprite.getPosition().y)
		{
			window.draw(Object.Sprite);
		}
	}

	window.setView(window.getDefaultView());

	CharacterInforText.setFont(Font);
	CharacterInforText.setCharacterSize(32);
	CharacterInforText.setFillColor(sf::Color::White);
	CharacterInforText.setPosition(ScreenWidth / 2.f, ScreenHeight - 250.f);

	window.draw(CharacterInforText);

	sf::Color ScreenBackground = sf::Color(30, 5, 5, 255/2);

	PauseBackground.setSize(window.getView().getSize());
	PauseBackground.setOrigin(PauseBackground.getSize() / 2.f);
	PauseBackground.setPosition(window.getView().getCenter());
	PauseBackground.setFillColor(ScreenBackground);

	PauseMenu.setSize(sf::Vector2f(200.f, 400.f));
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
		float StartY = PauseMenu.getPosition().y - 150.f;

		for (int i = 0; i < MenuText.size(); i++)
		{
			MenuOptionText.setFont(Font);
			MenuOptionText.setFillColor(Theme.PrimaryColor);
			MenuOptionText.setString(MenuText[i]);
			MenuOptionText.setCharacterSize(40);

			sf::FloatRect TextBounds = MenuOptionText.getLocalBounds();
			MenuOptionText.setOrigin(TextBounds.left + TextBounds.width / 2.f, TextBounds.top + TextBounds.height / 2.f);
			
			MenuOptionText.setPosition(PauseMenu.getPosition().x, StartY + i * 60.f);
			
			if (i == SelectedIndex)
			{
				CursorSprite.setPosition(MenuOptionText.getPosition().x - TextBounds.width / 2.f - 40.f, MenuOptionText.getPosition().y - TextBounds.height / 2.f + CursorOffset);

				MenuOptionText.setFillColor(sf::Color(Theme.HighlightColor));

				window.draw(CursorSprite);
			}
			
			window.draw(MenuOptionText);
		}
	}
}

std::string FGameScreen::ToUpper(const std::string& input)
{
	std::string result = input;

	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });

	return result;
}

void FGameScreen::SetCharacter(const FCharacterData& Character)
{
	CurrentCharacter = Character;

	CharacterSheet.SetCharacter(Character);

	CharacterInforText.setString
	(ToUpper("Name: " + CurrentCharacter.CharName) +
		ToUpper("\nRace: " + CurrentCharacter.CharRace.RaceName) +
		ToUpper("\nClass: " + CurrentCharacter.CharClass.ClassName));
}

void FGameScreen::SetSelectedCharacter(const int SelectedCharacter)
{
	SelectedCharacterRow = SelectedCharacter;
}

void FGameScreen::GenerateForest()
{
	ForestObjects.clear();

	PlaceForestObjects(TreeTexture, TreeSize, 250, 120.f, 0.3f, 150.f, ECollisionType::ECTTree);
	PlaceForestObjects(RockTexture, Rocks, 90, 70.f, 0.7f, 150.f, ECollisionType::ECTRock);
	PlaceForestObjects(TreeTexture, Bushes, 300, 40.f, 0.5f, 50.f, ECollisionType::ECTBush);

	std::sort(ForestObjects.begin(), ForestObjects.end(), [](FForestObject A, FForestObject B)
		{
			return A.Sprite.getPosition().y < B.Sprite.getPosition().y;
		});
}

void FGameScreen::OverlappingObject()
{
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

	FForestObject* ClosestObject = nullptr;

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

void FGameScreen::CollectItem(int ObjectToCollect)
{
	if (ObjectToCollect < 0 || ObjectToCollect >= ForestObjects.size())
		return;

	switch (ForestObjects[ObjectToCollect].ObjectType)
	{
	case EObjectType::EOTTree:
		{
			std::cout << "You collected Wood from Tree " << ObjectToCollect << std::endl;


			// Add random Wood to inventory
			std::uniform_int_distribution<int> GatheredDist(0, 3);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet.GatherMaterials(&Material);

			// Notify how much of item was added to inventory
			std::cout << "You collected " << Material.MaterialName << std::endl;

			std::cout << "Materials:" << std::endl;
			for (const FMaterial& Mat : CharacterSheet.GetInventory()->GetMaterials())
			{
				std::cout << Mat.Material->MaterialName << " : " << Mat.MaterialAmount << std::endl;
			}

			break;
		}
	case EObjectType::EOTRock:
		{
			std::cout << "You collected Ore from a Rock " << ObjectToCollect << std::endl;

			// Add random Ore to inventory
			std::uniform_int_distribution<int> GatheredDist(4, 7);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet.GatherMaterials(&Material);

			// Notify how much of item was added to inventory
			std::cout << "You collected " << Material.MaterialName << std::endl;

			std::cout << "Materials:" << std::endl;
			for (const FMaterial& Mat : CharacterSheet.GetInventory()->GetMaterials())
			{
				std::cout << Mat.Material->MaterialName << " : " << Mat.MaterialAmount << std::endl;
			}
			break;
		}
	case EObjectType::EOTBush:
		{
			std::cout << "You collected Leaves from a Bush " << ObjectToCollect << std::endl;

			// Add random Cloth to inventory	   

			std::uniform_int_distribution<int> GatheredDist(8, 11);
			int GatheredMaterial = GatheredDist(Random.RandomGenerator);

			const FMaterialData& Material = Loader->GetAvailableMaterials()[GatheredMaterial];
			CharacterSheet.GatherMaterials(&Material);

			// Notify how much of item was added to inventory
			std::cout << "You collected " << Material.MaterialName << std::endl;

			std::cout << "Materials:" << std::endl;
			for (const FMaterial& Mat : CharacterSheet.GetInventory()->GetMaterials())
			{
				std::cout << Mat.Material->MaterialName << " : " << Mat.MaterialAmount << std::endl;
			}
			break;
		}
	default:
		break;
	}

	ForestObjects.erase(ForestObjects.begin() + ObjectToCollect);
	CurrentInteractableObjectIndex = -1;
}

void FGameScreen::PlaceForestObjects(sf::Texture& Texture, const std::vector<sf::IntRect>& Variants, int Count, float MinDistance, float ClusterChance, float ClusterRadius, ECollisionType CollisionType)
{
	std::mt19937 Random(12345);

	std::uniform_int_distribution <int> VariantDist(0, Variants.size() - 1);
	std::uniform_real_distribution<float> XDist(100.f, WorldWidth - 100.f);
	std::uniform_real_distribution<float> YDist(100.f, WorldHeight - 100.f);
	std::uniform_real_distribution<float> ChanceDist(0.f, 1.f);

	sf::Vector2f ClusterCentre;
	bool bHasClusterCentre = false;

	for (int i = 0; i < Count; i++)
	{
		int VariantType = VariantDist(Random);

		float X;
		float Y;


		if (bHasClusterCentre && ChanceDist(Random) < ClusterChance)
		{
			//Spawn near existing cluster
			std::uniform_real_distribution<float> OffsetDist(-ClusterRadius, ClusterRadius);

			X = ClusterCentre.x + OffsetDist(Random);
			Y = ClusterCentre.y + OffsetDist(Random);
		}
		else
		{
			//Start a new cluster
			X = XDist(Random);
			Y = YDist(Random);

			ClusterCentre = { X, Y };
			bHasClusterCentre = true;
		}

		FForestObject ForestObject;

		ForestObject.Sprite.setTexture(Texture);
		ForestObject.Sprite.setTextureRect(Variants[VariantType]);

		sf::FloatRect Bounds = ForestObject.Sprite.getLocalBounds();

		ForestObject.Sprite.setOrigin(Bounds.width / 2.f, Bounds.height);

		ForestObject.Sprite.setPosition(X, Y);

		sf::FloatRect CollisionBounds = ForestObject.Sprite.getGlobalBounds();

		float Width = 0.f;
		float Height = 0.f;

		float CollisionX = 0.f;
		float CollisionY = 0.f;

		switch (CollisionType)
		{
		case ECollisionType::ECTTree:
			Width = CollisionBounds.width * 0.5f;
			Height = CollisionBounds.height * 0.3f;

			CollisionX = CollisionBounds.left + (CollisionBounds.width - Width) / 2.f;
			CollisionY = CollisionBounds.top + CollisionBounds.height - Height;

			ForestObject.ObjectType = EObjectType::EOTTree;
			break;
		case ECollisionType::ECTRock:
			Width = CollisionBounds.width * 0.8f;
			Height = CollisionBounds.height * 0.8f;

			CollisionX = CollisionBounds.left + (CollisionBounds.width - Width) / 2.f;
			CollisionY = CollisionBounds.top + CollisionBounds.height - Height;

			ForestObject.ObjectType = EObjectType::EOTRock;
			break;
		case ECollisionType::ECTBush:
			Width = CollisionBounds.width * 0.9f;
			Height = CollisionBounds.height * 0.8f;

			CollisionX = CollisionBounds.left + (CollisionBounds.width - Width) / 2.f;
			CollisionY = CollisionBounds.top + CollisionBounds.height - Height;

			ForestObject.ObjectType = EObjectType::EOTBush;
			break;
		default:
			break;
		}

		ForestObject.Collision = sf::FloatRect(CollisionX, CollisionY, Width, Height);

		bool bTooClose = false;
																									
		for (const FForestObject& ExistingObject : ForestObjects)
		{
			float DX = ExistingObject.Sprite.getPosition().x - X;
			float DY = ExistingObject.Sprite.getPosition().y - Y;

			float Distance = std::sqrt(DX * DX + DY * DY);

			if (Distance < MinDistance)
			{
				bTooClose = true;
				break;
			}
		}

		if (!bTooClose && !IsOnPath(ForestObject.Sprite.getPosition()))
		{
			ForestObjects.push_back(ForestObject);
		}
	}
}

bool FGameScreen::IsOnPath(sf::Vector2f position)
{
	float PathTop = WorldHeight / 2.f - 70;
	float PathBottom = WorldHeight / 2.f + 70;

	return position.y >= PathTop && position.y <= PathBottom;
}

bool FGameScreen::IsOptionSelected()
{
	if (bOptionChosen)
	{
		bOptionChosen = false;
		return true;
	}
	return false;
}

int FGameScreen::GetSelectedOption()
{
	return SelectedIndex;
}

