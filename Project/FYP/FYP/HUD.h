#include "ExtraIncludes.h"
#include <vector>

using namespace std;

class HUD
{
public:
	HUD();
	bool LoadTexture();
	void Draw(sf::RenderWindow &window);
	void SetHighlight(int slotNumber);
	void SetHealth(int healthNumber);
	void SetEnergy(int enermyNumber);
	bool countDown = false;
	bool showScore = false;
	void SetScore(vector<pair<string, int>> players, string playerID, int playerScore);
	bool initScoreBoard = false;
	int FindHighlight(int number);
	bool gameOver = false;

private:
	sf::Texture m_hud1Texture;
	sf::Texture m_hud2Texture;
	sf::Texture m_hud3Texture;
	sf::Texture m_hud4Texture;
	sf::Texture m_hud5Texture;
	sf::Texture m_hud6Texture;

	sf::Texture m_blankTexture;

	sf::Texture m_health1Texture;
	sf::Texture m_health2Texture;
	sf::Texture m_health3Texture;
	sf::Texture m_health4Texture;
	sf::Texture m_health5Texture;
	sf::Texture m_health6Texture;
	sf::Texture m_health7Texture;
	sf::Texture m_health8Texture;
	sf::Texture m_health9Texture;
	sf::Texture m_health10Texture;

	sf::Texture m_energyBarTexture;

	sf::Texture m_scoreBoardTexture;

	sf::RectangleShape m_healthRectangle;
	sf::RectangleShape m_hudRectangle;
	sf::RectangleShape m_energyBarRectangle;
	sf::RectangleShape m_blankRectangle;
	sf::RectangleShape m_scoreRectangle;
	sf::RectangleShape m_gameOverRect;
	sf::Texture m_gameOverTexture;

	sf::Font font;
	sf::Text player0, player1, player2, player3, player4, player5, player6, player7, player8;
};
