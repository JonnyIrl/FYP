#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

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

private:
	sf::Texture m_mainMenuTexture;
	sf::Texture m_gameOverTexture;
	sf::Texture m_optionsTexture;
	sf::Texture m_creditsTexture;
	sf::Texture m_doorTexture;
	sf::Texture m_blankDoorTexture;
	sf::RectangleShape m_sceneRect;
	sf::RectangleShape m_playRect;


	Animation m_playGameAnimation;
	Animation m_optionsAnimation;
	Animation m_creditsAnimation;
	AnimatedSprite m_doorAnimation;
};
