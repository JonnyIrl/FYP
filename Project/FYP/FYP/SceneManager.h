#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <list>

using namespace std;

class SceneManager
{
public:
	SceneManager();
	byte GetCurrentScene();
	bool LoadTexture();
	enum GAMESTATE : byte{ MENU, PLAY_GAME, GAME_OVER, OPTIONS, TUTORIAL, PLAYEROPTIONS, LOBBY };
	byte m_currentScene;
	void Draw(sf::RenderWindow& window);
	void ChangeBackground(sf::Event Event, sf::Time time);
	sf::RectangleShape GetPlayRectangle();
	sf::RectangleShape GetOptionsRectangle();
	sf::RectangleShape GetCreditsRectangle();
	sf::RectangleShape GetCollisionPlayRect();
	sf::RectangleShape GetSFXPlusRect();
	sf::RectangleShape GetMasterPlusRect();
	sf::RectangleShape GetSFXMinusRect();
	sf::RectangleShape GetMasterMinusRect();
	sf::RectangleShape GetConfirmRectangle();
	sf::RectangleShape GetSendRectangle();
	sf::RectangleShape GetConnectRectangle();
	sf::RectangleShape GetReadyRectangle() { return m_CollisionReadyRectangle; }
	bool IsPlayerConnected() { return m_playerConnected; }
	bool IsPlayerReady() { return m_playerReady; }
	void SetPlayerReady(bool state) { m_playerReady = state; }
	void SetPlayerConnected(bool state) { m_playerConnected = state; }
	bool GetPlayerChangingName() { return m_changeNameSelected; }
	void SetPlayerChangingName(bool state) { m_changeNameSelected = state; }
	sf::RectangleShape GetNameRectangle() { return m_NameRectangle; }
	sf::RectangleShape GetSaveNameRectangle() { return m_SaveNameRectangle; }
	int currentSfx;
	int currentMaster;


	void GoBack() { tutorialPage--; }
	void GoForward() { tutorialPage++; }
	sf::RectangleShape nextRectangle;
	sf::RectangleShape backRectangle;
	sf::Texture nextTexture, backTexture, selectNextTexture, selectBackTexture;

	sf::Texture tut1Text, tut2Text, tut3Text, tut4Text, tut5Text, tut6Text, tut7Text;
	sf::RectangleShape tut1Rect, tut2Rect, tut3Rect, tut4Rect, tut5Rect, tut6Rect, tut7Rect;
	int tutorialPage = 1;

	bool wasInTut = false;

private:
	sf::Texture m_mainMenuTexture;
	sf::Texture m_gameOverTexture;
	sf::Texture m_optionsTexture;
	sf::Texture m_creditsTexture;
	sf::Texture m_gameSettingTexture;
	sf::Texture m_chatLobbyTexture;

	//Buttons Textures
	sf::Texture m_optionsText, m_optionsSelectText;
	sf::Texture m_creditsText, m_creditsSelectText;
	sf::Texture m_playGameText, m_playGameSelectText;
	sf::Texture m_quitText, m_quitSelectText;

	//Buttons Rectangles
	sf::RectangleShape m_PlayGameButtonRect, m_SelectPlayGameButtonRect;
	sf::RectangleShape m_OptionsButtonRect, m_SelectOptionsButtonRect;
	sf::RectangleShape m_CreditsButtonRect, m_SelectCreditsButtonRect;
	sf::RectangleShape m_QuitButtonRect, m_SelectQuitButtonRect;

	//Mouse Rectangle
	sf::RectangleShape m_mouseRect;

	sf::RectangleShape m_sceneRect;
	sf::RectangleShape m_playRect;
	sf::RectangleShape m_optionsRect;
	sf::RectangleShape m_creditsRect;
	sf::RectangleShape m_quitRect;
	sf::RectangleShape m_collisionPlayRect;
	sf::RectangleShape m_gameSettingRect;
	sf::RectangleShape m_chatLobbyRect;
	sf::RectangleShape m_sendRect;
	sf::RectangleShape m_CollisionConnectRect;


	//Volume Indicators
	//Slight hack for now until I get some better code to get it working more efficiently.
	sf::Texture volumeBarTexture;
	sf::RectangleShape sfxVolume1;
	sf::RectangleShape sfxVolume2;
	sf::RectangleShape sfxVolume3;
	sf::RectangleShape sfxVolume4;
	sf::RectangleShape sfxPlusRect;
	sf::RectangleShape sfxMinusRect;

	sf::RectangleShape masterVolume1;
	sf::RectangleShape masterVolume2;
	sf::RectangleShape masterVolume3;
	sf::RectangleShape masterVolume4;
	sf::RectangleShape masterPlusRect;
	sf::RectangleShape masterMinusRect;
	sf::RectangleShape confirmButton;

	bool m_quitGame = false;


	//Lobby variables
	bool m_playerConnected = false;
	bool m_playerReady = false;
	bool m_changeNameSelected = false;
	sf::Texture m_NotReadyScreen, m_ReadyScreen, m_ConnectScreen;
	sf::RectangleShape m_NotReadyRectangle, m_ReadyRectangle, m_ConnectRectangle, m_NameRectangle, m_SaveNameRectangle;
	sf::RectangleShape m_CollisionReadyRectangle;
};
