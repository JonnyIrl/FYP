#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <SFML/Audio.hpp>

class SceneManager
{
public:
	SceneManager();
	byte GetCurrentScene();
	bool LoadTexture();
	enum GAMESTATE : byte{ MENU, PLAY_GAME, GAME_OVER, OPTIONS, CREDITS, PLAYEROPTIONS };
	byte m_currentScene;
	void Draw(sf::RenderWindow& window);
	void ChangeBackground(sf::Time time);
	sf::RectangleShape GetPlayRectangle();
	sf::RectangleShape GetOptionsRectangle();
	sf::RectangleShape GetCreditsRectangle();
	sf::RectangleShape GetCollisionPlayRect();
	sf::RectangleShape GetSFXPlusRect();
	sf::RectangleShape GetMasterPlusRect();
	sf::RectangleShape GetSFXMinusRect();
	sf::RectangleShape GetMasterMinusRect();
	sf::RectangleShape GetConfirmRectangle();
	void AnimationToPlay(int animation);
	int currentSfx;
	int currentMaster;

private:
	sf::Texture m_mainMenuTexture;
	sf::Texture m_gameOverTexture;
	sf::Texture m_optionsTexture;
	sf::Texture m_creditsTexture;
	sf::Texture m_doorTexture;
	sf::Texture m_blankDoorTexture;
	sf::Texture m_gameSettingTexture;

	sf::RectangleShape m_sceneRect;
	sf::RectangleShape m_playRect;
	sf::RectangleShape m_optionsRect;
	sf::RectangleShape m_creditsRect;
	sf::RectangleShape m_collisionPlayRect;
	sf::RectangleShape m_gameSettingRect;
	int m_animtionToPlay;

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
	//Animations
	Animation m_playGameAnimation;
	Animation m_optionsAnimation;
	Animation m_creditsAnimation;
	AnimatedSprite m_doorAnimation;
};
