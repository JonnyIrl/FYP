#include "ExtraIncludes.h"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"

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
	void InitCollisionRectangles();
	bool CheckToGoToNextRoom(sf::RectangleShape playerRectangle);
	bool CheckBoundingCollisions(sf::RectangleShape playerRectangle);
	bool CheckStatueCollision(sf::RectangleShape playerRectangle);
	enum CURRENTROOM : int{ ROOM1, ROOM2, ROOM3, ROOM4, ROOM5, ROOM6, ROOM7, ROOM8, ROOM9 };
	sf::RectangleShape GetBottomRectangle();
	sf::RectangleShape GetTopRectangle();
	sf::RectangleShape GetLeftRectangle();
	sf::RectangleShape GetRightRectangle();
	sf::RectangleShape GetSummonerRectangleTop() { return m_summonerRockTop; }
	sf::RectangleShape GetSummonerRectangleBot() { return m_summonerRockBot; }
	sf::RectangleShape GetSummonerRectangleLeft() { return m_summonerRockLeft; }
	sf::RectangleShape GetSummonerRectangleRight() { return m_summonerRockRight; }
	sf::RectangleShape GetInteractingRock() { return m_interactSummonerRock; }
	bool IsSummoning() { return m_summoning; }
	void SetSummoning(bool state) { m_summoning = state; }
	void SetSummoningRectSize(sf::Vector2f position);
	void PlayAnimation(sf::Time time);
	void SetTimer(int num) { m_summonCount = num; }
	void ReduceTimer() { m_summonCount--; }
	int GetTimer() { return m_summonCount; }
	bool FinishedSummoning();

	int m_currentRoom;

	int checkStatue;
	int checkDoor;
	int checkWall;
	sf::Vector2f SetTopDoor();
	sf::Vector2f SetBottomDoor();
	sf::Vector2f SetLeftDoor();
	sf::Vector2f SetRightDoor();

	sf::Vector2f SetLeftWall();
	sf::Vector2f SetRightWall();
	sf::Vector2f SetTopWall();
	sf::Vector2f SetBottomWall();

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

	sf::Texture m_summoningTexture;
	sf::Clock summonClock;

	sf::Texture m_timer1, m_timer2, m_timer3, m_timer4;

	bool m_loadedRoom1, m_loadedRoom2, m_loadedRoom3, m_loadedRoom4, m_loadedRoom5, m_loadedRoom6, m_loadedRoom7, m_loadedRoom8, m_loadedRoom9;

	bool m_summoning = false;
	int m_summonCount = 4;

	//Each Bounding Box Collision with the walls.
	sf::RectangleShape m_fullTopRectangle, m_fullLeftRectangle, m_fullRightRectangle, m_fullBottomRectangle;
	sf::RectangleShape m_halfTopRect1, m_halfTopRect2, m_halfLeftRect1, m_halfLeftRect2, m_halfBottomRect1, m_halfBottomRect2, m_halfRightRect1, m_halfRightRect2;
	sf::RectangleShape m_summonerRockTop, m_summonerRockBot, m_summonerRockLeft, m_summonerRockRight;
	sf::RectangleShape m_interactSummonerRock;
	sf::RectangleShape m_summoningRect;

	Animation m_summoningAnimation;
	AnimatedSprite m_summoningAnimSprite;
};
