#pragma once
#include "Core/Types.h"	  

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character/CharacterStats.h"
#include "Character/Character.h"
#include "Core/Random.h"

class FLoadExternalData;

enum class EGameMode
{
	EGMPaused,
	EGMUnpaused
};

enum class EMenuSetting
{
	EMSResume,
	EMSInventory,
	EMSCrafting,
	EMSSave,
	EMSOptions,
	EMSExit,
	EMSDefault
};

enum class EMenuResult
{
	EMRResume,
	EMRInventory,
	EMRCrafting,
	EMRSave,
	EMROptions,
	EMRExit, 
	EMRDefault
};

enum class EObjectType
{
	EOTTree,
	EOTRock,
	EOTBush
};

enum class EFacingDirection
{
	EFDUp,
	EFDDown,
	EFDLeft,
	EFDRight
};

enum class ECollisionType
{
	ECTTree,
	ECTRock,
	ECTBush,
	ECTNone
};

struct FForestObject
{
	sf::Sprite Sprite;
	sf::FloatRect Collision;
	EObjectType ObjectType = EObjectType::EOTTree;
};

class FGameScreen
{
public:
	FGameScreen();

	void HandleInput(const sf::Event& event);
	void Update(float DeltaTime);
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	void SetSelectedCharacter(const int SelectedCharacter);
	void SetCharacter(const FCharacterData& Character);

	const FCharacter& GetCharacter() { return CharacterSheet; }

private:
	FTheme Theme;

	FCharacterData CurrentCharacter;
	FCharacter CharacterSheet;
	FRandom Random;

	EGameMode CurrentGameMode;

	void GenerateForest();
	void OverlappingObject();
	void CollectItem(int ObjectToCollect);
	void PlaceForestObjects(sf::Texture& Texture, const std::vector<sf::IntRect>& Variants, int Count, float MinDistance, float ClusterChance, float ClusterRadius, ECollisionType CollisionType);
	bool IsOnPath(sf::Vector2f position);

	sf::Font Font;
	sf::Text CharacterInforText;

	//pausemenu
	sf::SoundBuffer CursorMoveBuffer;
	sf::SoundBuffer ConfirmBuffer;

	sf::Sound CursorMoveSound;
	sf::Sound ConfirmSound;

	sf::RectangleShape PauseBackground;
	sf::RectangleShape PauseMenu;

	bool IsOptionSelected();
	EMenuResult MenuResult = EMenuResult::EMRDefault;
	
	std::vector<EMenuSetting> MenuSettings
	{
		EMenuSetting::EMSResume,
		EMenuSetting::EMSInventory,
		EMenuSetting::EMSCrafting,
		EMenuSetting::EMSSave,
		EMenuSetting::EMSOptions,
		EMenuSetting::EMSExit
	};

	int SelectedIndex = 0;
	EMenuSetting SelectedSetting = EMenuSetting::EMSDefault;
	bool bOptionChosen = false;

	sf::Texture CursorTexture;
	sf::Sprite CursorSprite;
	float CursorOffset = 0.f;
	float CursorTimer = 0.f;

	//player
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;
	sf::FloatRect PlayerBounds;
	sf::FloatRect PlayerReach;

	sf::Vector2f PlayerPosition = sf::Vector2f(300.f, 200.f);

	float MoveSpeed = 100.f;

	int SelectedCharacterRow = 0;
	int CurrentInteractableObjectIndex = 0;

	EFacingDirection FacingDirection = EFacingDirection::EFDDown;

	int CurrentFrame = 0;
	float AnimationTimer = 0.f;
	float AnimationSpeed = 0.25f;

	int FrameHeight = 20;
	int FrameWidth = 20;

	//sound
	sf::Music GameMusic;

	bool bMusicFadingIn = false;
	float MusicFadeSpeed = 40.f;

	//Animation movement indexes
	int DownRow = 0;
	int LeftRow = 2;
	int UpRow = 4;

	int CurrentAnimationRow = 0;

	// Camera
	sf::View Camera;
	sf::Vector2f CameraPos;

	// Game World

	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	const int WorldWidth = 4000;
	const int WorldHeight = 4000;

	sf::Texture TreeTexture;
	sf::Texture RockTexture;
	sf::Texture GroundTexture;
	sf::Texture PathTexture;

	std::vector<FForestObject> ForestObjects;
	std::vector<sf::Sprite*> DrawList;

	sf::RectangleShape Ground;
	sf::RectangleShape Path;

	FForestObject* ClosestObject = nullptr;
		
	std::vector<sf::IntRect> TreeSize
	{
		sf::IntRect{0, 5, 75, 90}, //Tree 1
		sf::IntRect{320, 10, 70, 85}, //Tree 2
		sf::IntRect{0, 95, 75, 85}, //Tree 3
		sf::IntRect{320, 95, 70, 85}, //Tree 4
		sf::IntRect{0, 180, 75, 90}, //Tree 5
		sf::IntRect{320, 185, 80, 90},  //Tree 6
		sf::IntRect{0, 280, 65, 110}, //Tree 7
		sf::IntRect{260, 280, 55, 110}, //Tree 8
		sf::IntRect{0, 390, 55, 75}, //Tree 9
		sf::IntRect{190, 390, 55, 75}, //Tree 10
		sf::IntRect{380, 400, 50, 70}, //Tree 11
	};

	std::vector<sf::IntRect> Stumps
	{
		sf::IntRect{630, 0, 65, 45}, //Stump 1
		sf::IntRect{700, 0, 65, 45}, //Stump 2
		sf::IntRect{630, 60, 65, 38}, //Stump 3
		sf::IntRect{700, 60, 65, 38}, //Stump 4
		sf::IntRect{640, 95, 50, 35}, //Stump 5
		sf::IntRect{687, 95, 50, 35},  //Stump 6
		sf::IntRect{735, 95, 50, 35}, //Stump 7
		sf::IntRect{640, 165, 30, 30}, //Stump 8
		sf::IntRect{670, 165, 30, 30}, //Stump 9
		sf::IntRect{640, 200, 25, 25}, //Stump 10
		sf::IntRect{670, 200, 25, 25} //Stump 11
	};

	std::vector<sf::IntRect> Bushes
	{
		sf::IntRect{640, 225, 32, 32}, //Bush 1
		sf::IntRect{672, 225, 32, 32}, //Bush 2
		sf::IntRect{704, 225, 32, 32}, //Bush 3
		sf::IntRect{736, 225, 32, 32}, //Bush 4
		sf::IntRect{768, 225, 32, 32}, //Bush 5

		sf::IntRect{640, 260, 32, 31}, //Bush 6
		sf::IntRect{672, 260, 32, 32}, //Bush 7
		sf::IntRect{704, 260, 32, 32}, //Bush 8
		sf::IntRect{736, 260, 32, 32}, //Bush 9
		sf::IntRect{768, 260, 32, 32}, //Bush 10

		sf::IntRect{640, 293, 32, 32}, //Bush 11
		sf::IntRect{672, 293, 32, 32}, //Bush 12
		sf::IntRect{704, 293, 32, 32}, //Bush 13
		sf::IntRect{736, 293, 32, 32}, //Bush 14
		sf::IntRect{768, 293, 32, 32}, //Bush 15

		sf::IntRect{640, 324, 32, 32}, //Bush 16
		sf::IntRect{672, 324, 32, 32}, //Bush 17
		sf::IntRect{704, 324, 32, 32}, //Bush 18
		sf::IntRect{736, 324, 32, 32}, //Bush 19
		sf::IntRect{768, 324, 32, 32}, //Bush 20

		sf::IntRect{640, 355, 32, 32}, //Bush 21
		sf::IntRect{672, 355, 32, 32}, //Bush 22
		sf::IntRect{704, 355, 32, 32}, //Bush 23
		sf::IntRect{736, 355, 32, 32}, //Bush 24
		sf::IntRect{768, 355, 32, 32}, //Bush 25

		sf::IntRect{640, 387, 32, 32}, //Bush 26
		sf::IntRect{672, 387, 32, 32}, //Bush 27
		sf::IntRect{704, 387, 32, 32}, //Bush 28
		sf::IntRect{736, 387, 32, 32}, //Bush 29
		sf::IntRect{768, 387, 32, 32}, //Bush 30

		sf::IntRect{640, 421, 32, 32}, //Bush 31
		sf::IntRect{672, 421, 32, 32}, //Bush 32
		sf::IntRect{704, 421, 32, 32}, //Bush 33
		sf::IntRect{736, 421, 32, 32}, //Bush 34
		sf::IntRect{768, 421, 32, 32}, //Bush 35
	};

	std::vector<sf::IntRect> Rocks
	{
		sf::IntRect{0, 0, 32, 32}, //Rock 1
		sf::IntRect{32, 0, 32, 32}, //Rock 2
		sf::IntRect{64, 0, 32, 32}, //Rock 3
		sf::IntRect{96, 0, 64, 64}, //Rock 4
		sf::IntRect{0, 32, 32, 32}, //Rock 5
		sf::IntRect{32, 32, 32, 32},  //Rock 6
		sf::IntRect{64, 32, 32, 32}, //Rock 7
		sf::IntRect{0, 64, 32, 32}, //Rock 8
		sf::IntRect{32, 64, 32, 32}, //Rock 9
		sf::IntRect{64, 64, 32, 32}, //Rock 10
		sf::IntRect{96, 64, 64, 32} //Rock 11
	};

	std::unique_ptr<FLoadExternalData> Loader;
};
