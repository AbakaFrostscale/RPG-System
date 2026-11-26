#pragma once
#include "Core/Types.h"	  

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "Character/CharacterStats.h"
#include "Character/Character.h"
#include "Inventory/Inventory.h"
#include "Core/Random.h"
#include "SaveAndLoad/SaveAndLoad.h"

class FLoadExternalData;
class FMapLoader;
class FMapRenderer;
class FCharacterCreator;

enum class EGameMode
{
	EGMPaused,
	EGMUnpaused,
	EGMInventory,
	EGMCrafting,
	EGMOptions
};

enum class EMenuSetting
{
	EMSResume,
	EMSInventory,
	EMSCrafting,
	EMSSave,
	EMSLoad,
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
	EMRLoad,
	EMROptions,
	EMRExit, 
	EMRDefault
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

class FGameScreen
{
public:
	FGameScreen();
	~FGameScreen();

	void HandleInput(const sf::Event& event);
	void Update(float DeltaTime);
	void Draw(sf::RenderWindow& window);

	std::string ToUpper(const std::string& input);

	void SetSelectedCharacter(const int SelectedCharacter);
	void SetCharacter(FCharacter& Character);
	bool bIsExitRequested() const { return bExitRequest; }

	bool GetbChangeScreenInventory() const { return bChangeScreenInventory; }
	void SetbChangeScreenInventory(bool ChangeScreen) { bChangeScreenInventory = ChangeScreen; }

	bool GetbChangeScreenCrafting() const { return bChangeScreenCrafting; }
	void SetbChangeScreenCrafting(bool ChangeScreen) { bChangeScreenCrafting = ChangeScreen; }

	void LoadGame();

	const FCharacter* GetCharacter() const { return CharacterSheet; }

private:
	sf::Color ScreenBackgroundColour = sf::Color(30, 5, 5, 255 / 2);

	FTheme Theme;

	FCharacter* CharacterSheet = nullptr;
	FSaveAndLoad SaveAndLoad;
	FRandom Random;

	EGameMode CurrentGameMode = EGameMode::EGMUnpaused;
	bool bChangeScreenInventory = false;
	bool bChangeScreenCrafting = false;

	void GenerateForest();
	void LoadForest(const std::vector<int>& GatheredItems);

	void LoadTown();

	void OverlappingObject();
	void CollectItem(int ObjectToCollect);
	
	void DrawScreen(sf::RenderWindow& window, sf::Text& ScreenText, sf::RectangleShape& ScreenBackground, sf::RectangleShape& ScreenMenu);
	void HandleMenu();
	void Notification(sf::RenderWindow& window, sf::Text& NotifyText, sf::RectangleShape& NotifyBackgrond);

	void UpdateCharacter();

	sf::Font Font;
	sf::Text CharacterInforText;

	//pausemenu
	sf::RectangleShape PauseBackground;
	sf::RectangleShape PauseMenu;
	
	sf::SoundBuffer CursorMoveBuffer;
	sf::SoundBuffer ConfirmBuffer;

	sf::Sound CursorMoveSound;
	sf::Sound ConfirmSound;

	EMenuResult MenuResult = EMenuResult::EMRDefault;
	
	std::vector<EMenuSetting> MenuSettings
	{
		EMenuSetting::EMSResume,
		EMenuSetting::EMSInventory,
		EMenuSetting::EMSCrafting,
		EMenuSetting::EMSSave,
		EMenuSetting::EMSLoad,
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

	bool bExitRequest = false;

	//crafting
	sf::Text CraftingText;

	sf::RectangleShape CraftingBackground;
	sf::RectangleShape CraftingMenu;

	//option
	sf::Text OptionsText;

	sf::RectangleShape OptionsBackground;
	sf::RectangleShape OptionsMenu;

	//save
	sf::Text SaveLoadText;
	sf::RectangleShape SaveLoadSuccessMenu;
	sf::Clock NotificationClock;
	bool ShowNotification = false;

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
	float AnimationSpeed = 0.2f;

	int FrameHeight = 36;
	int FrameWidth = 32;

	//sound
	sf::Music GameMusic;

	bool bMusicFadingIn = false;
	float MusicFadeSpeed = 40.f;

	//Animation movement indexes
	int DownRow = 2;
	int LeftRow = 3;
	int UpRow = 0;
	int RightRow = 1;

	int CurrentAnimationRow = 0;

	// Camera
	sf::View Camera;
	sf::Vector2f CameraPos;

	// Game World
	const int ScreenWidth = 800;
	const int ScreenHeight = 600;

	int WorldWidth = 0;
	int WorldHeight = 0;

	int ForestObjectID = 0;

	std::vector<FForestObject> ForestObjects;
	std::vector<int> GatheredObjectID;

	FForestObject* ClosestObject = nullptr;

	std::unique_ptr<FCharacterCreator> Creator;
	std::unique_ptr<FLoadExternalData> Loader;
	std::unique_ptr<FMapLoader> MapLoader;
	std::unique_ptr<FMapRenderer> MapRenderer;
};
