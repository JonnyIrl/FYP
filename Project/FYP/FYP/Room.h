#include "ExtraIncludes.h"

class Room
{
public:
	Room();
	void CreateLeftRooms();
	void CreateMiddleRooms();
	void CreateRightRooms();
	bool LoadTextures();

private:
	//Each Room Rectangle
	sf::RectangleShape m_topLeftRect;
	sf::RectangleShape m_middleLeftRect;
	sf::RectangleShape m_bottomLeftRect;

	sf::RectangleShape m_topMiddleRect;
	sf::RectangleShape m_middleRect;
	sf::RectangleShape m_bottomMiddleRect;

	sf::RectangleShape m_topRightRect;
	sf::RectangleShape m_middleRightRect;
	sf::RectangleShape m_bottomRightRect;

	//Each room texture
	sf::Texture m_topLeftTexture;
	sf::Texture m_topMiddleTexture;
	sf::Texture m_topRightTexture;

	sf::Texture m_bottomLeftTexture;
	sf::Texture m_bottomMiddleTexture;
	sf::Texture m_bottomRightTexture;

	sf::Texture m_middleLeftTexture;
	sf::Texture m_middleTexture;
	sf::Texture m_middleRightTexture;
};
