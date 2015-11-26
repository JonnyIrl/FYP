#include "ExtraIncludes.h"

class Room
{
public:
	Room();
	void CreateLeftRooms();
	void CreateMiddleRooms();
	void CreateRightRooms();
	bool LoadTextures();
	void Draw(sf::RenderWindow& window);
	void LoadCollisionRectangles();
	bool CheckToGoToNextRoom(sf::RectangleShape playerRectangle);
	enum CURRENTROOM : byte{ ROOM1, ROOM2, ROOM3, ROOM4, ROOM5, ROOM6, ROOM7, ROOM8, ROOM9 };
	sf::RectangleShape GetBottomRectangle();
	sf::RectangleShape GetTopRectangle();
	sf::RectangleShape GetLeftRectangle();
	sf::RectangleShape GetRightRectangle();
	byte m_currentRoom;


	int checkDoor;
	sf::Vector2f SetTopDoor();
	sf::Vector2f SetBottomDoor();
	sf::Vector2f SetLeftDoor();
	sf::Vector2f SetRightDoor();

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

	//Each door rectangle
	sf::RectangleShape m_collisionBottomDoor;
	sf::RectangleShape m_collisionTopDoor;
	sf::RectangleShape m_collisionLeftDoor;
	sf::RectangleShape m_collisionRightDoor;

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

	bool m_loadedRoom1, m_loadedRoom2, m_loadedRoom3, m_loadedRoom4, m_loadedRoom5, m_loadedRoom6, m_loadedRoom7, m_loadedRoom8, m_loadedRoom9;
};
