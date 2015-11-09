#include "Room.h"

using namespace std;

Room::Room()
{
	if (LoadTextures())
	{
		CreateLeftRooms();
		CreateRightRooms();
		CreateMiddleRooms();
		m_currentRoom = ROOM1;
		m_loadedRoom1 = m_loadedRoom2 = m_loadedRoom3 = m_loadedRoom4 = m_loadedRoom5 = m_loadedRoom6 = m_loadedRoom7 = m_loadedRoom8 = m_loadedRoom9 = false;
		cout << "Finished Room Constructor" << endl;
	}
}

void Room::CheckToGoToNextRoom(sf::RectangleShape playerRect)
{
	switch (m_currentRoom)
	{
		//Top Left Room
	case ROOM1:
	{
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
			m_currentRoom = ROOM4;

		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
			m_currentRoom = ROOM2;

	}
	break;

	//Top Middle Room
	case ROOM2:
	{
	}
	break;

	//Top Right Room
	case ROOM3:
	{
	}
	break;

	//Middle Left Room
	case ROOM4:
	{
	}
	break;

	//Middle Room
	case ROOM5:
	{
	}
	break;

	//Middle Right Room
	case ROOM6:
	{
	}
	break;

	//Bottom Left Room
	case ROOM7:
	{
	}
	break;

	//Bottom Middle Room
	case ROOM8:
	{
	}
	break;

	//Bottom Right Room
	case ROOM9:
	{

	}
	break;
	}
}

void Room::LoadCollisionRectangles()
{
	switch (m_currentRoom)
	{
		//Top Left Room
		case ROOM1:
		{
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom1 = true;
		}
		break;

		//Top Middle Room
		case ROOM2:
		{
		}
		break;

		//Top Right Room
		case ROOM3:
		{
		}
		break;

		//Middle Left Room
		case ROOM4:
		{
		}
		break;

		//Middle Room
		case ROOM5:
		{
		}
		break;

		//Middle Right Room
		case ROOM6:
		{
		}
		break;

		//Bottom Left Room
		case ROOM7:
		{
		}
		break;

		//Bottom Middle Room
		case ROOM8:
		{
		}
		break;

		//Bottom Right Room
		case ROOM9:
		{

		}
		break;
	}
}
bool Room::LoadTextures()
{
	//Top Textures
	if (!m_topLeftTexture.loadFromFile("Assets/Room/TopLeftRoom.png"))
		return false;

	if (!m_topMiddleTexture.loadFromFile("Assets/Room/TopMiddleRoom.png"))
		return false;

	if (!m_topRightTexture.loadFromFile("Assets/Room/TopRightRoom.png"))
		return false;

	//Bottom Textures
	if (!m_bottomLeftTexture.loadFromFile("Assets/Room/BottomLeftRoom.png"))
		return false;

	if (!m_bottomMiddleTexture.loadFromFile("Assets/Room/BottomMiddleRoom.png"))
		return false;

	if (!m_bottomRightTexture.loadFromFile("Assets/Room/BottomRightRoom.png"))
		return false;

	//Middle Textures
	if (!m_middleLeftTexture.loadFromFile("Assets/Room/MiddleLeftRoom.png"))
		return false;

	if (!m_middleTexture.loadFromFile("Assets/Room/MiddleRoom.png"))
		return false;

	if (!m_middleRightTexture.loadFromFile("Assets/Room/MiddleRightRoom.png"))
		return false;

	return true;
}

void Room::CreateLeftRooms()
{
	m_topLeftRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_middleLeftRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_bottomLeftRect = sf::RectangleShape(sf::Vector2f(1280, 720));

	m_topLeftRect.setPosition(sf::Vector2f(0, 0));
	m_middleLeftRect.setPosition(sf::Vector2f(0, 0));
	m_bottomLeftRect.setPosition(sf::Vector2f(0, 0));

	m_topLeftRect.setTexture(&m_topLeftTexture);
	m_middleLeftRect.setTexture(&m_middleLeftTexture);
	m_bottomLeftRect.setTexture(&m_bottomLeftTexture);
}
void Room::CreateMiddleRooms()
{
	m_topMiddleRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_middleRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_bottomMiddleRect = sf::RectangleShape(sf::Vector2f(1280, 720));

	m_topMiddleRect.setPosition(sf::Vector2f(0, 0));
	m_middleRect.setPosition(sf::Vector2f(0, 0));
	m_bottomMiddleRect.setPosition(sf::Vector2f(0, 0));

	m_topMiddleRect.setTexture(&m_topMiddleTexture);
	m_middleRect.setTexture(&m_middleTexture);
	m_bottomMiddleRect.setTexture(&m_bottomMiddleTexture);
}
void Room::CreateRightRooms()
{
	m_topRightRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_middleRightRect = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_bottomRightRect = sf::RectangleShape(sf::Vector2f(1280, 720));

	m_topRightRect.setPosition(sf::Vector2f(0, 0));
	m_middleRightRect.setPosition(sf::Vector2f(0, 0));
	m_bottomRightRect.setPosition(sf::Vector2f(0, 0));

	m_topRightRect.setTexture(&m_topRightTexture);
	m_middleRightRect.setTexture(&m_middleRightTexture);
	m_bottomRightRect.setTexture(&m_bottomRightTexture);
}

void Room::Draw(sf::RenderWindow &window)
{
	switch (m_currentRoom)
	{
		//Top Left Room
		case ROOM1:
		{
			if (!m_loadedRoom1)
				LoadCollisionRectangles();

			window.draw(m_topLeftRect);
			window.draw(m_collisionBottomDoor);
			window.draw(m_collisionRightDoor);
		}
		break;

		//Top Middle Room
		case ROOM2:
		{
			window.draw(m_topMiddleRect);
		}
		break;

		//Top Right Room
		case ROOM3:
		{
			window.draw(m_topRightRect);
		}
		break;

		//Middle Left Room
		case ROOM4:
		{
			window.draw(m_middleLeftRect);
		}
		break;

		//Middle Room
		case ROOM5:
		{
			window.draw(m_middleRect);
		}
		break;

		//Middle Right Room
		case ROOM6:
		{
			window.draw(m_middleRightRect);
		}
		break;

		//Bottom Left Room
		case ROOM7:
		{
			window.draw(m_bottomLeftRect);
		}
		break;

		//Bottom Middle Room
		case ROOM8:
		{
			window.draw(m_bottomMiddleRect);
		}
		break;

		//Bottom Right Room
		case ROOM9:
		{
			window.draw(m_bottomRightRect);
		}
		break;

	}
}

sf::RectangleShape Room::GetBottomRectangle()
{
	return m_collisionBottomDoor;
}
sf::RectangleShape Room::GetTopRectangle()
{
	return m_collisionTopDoor;
}
sf::RectangleShape Room::GetLeftRectangle()
{
	return m_collisionLeftDoor;
}
sf::RectangleShape Room::GetRightRectangle()
{
	return m_collisionRightDoor;
}