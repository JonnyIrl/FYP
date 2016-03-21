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
		checkDoor = 0;
		m_loadedRoom1 = m_loadedRoom2 = m_loadedRoom3 = m_loadedRoom4 = m_loadedRoom5 = m_loadedRoom6 = m_loadedRoom7 = m_loadedRoom8 = m_loadedRoom9 = false;
		InitCollisionRectangles();
		cout << "Finished Room Constructor" << endl;
	}
}

bool Room::CheckToGoToNextRoom(sf::RectangleShape playerRect)
{
	//1 = top door
	//2 = bottom door
	//3 = left door
	//4 = right door
	/*-------------------|----------------|--------------|
	  |                  |                |              |
	  |      Room 1      |     Room 2     |    Room 3    |
	  |                  |                |              |
	  |---------------------------------------------------
	  |                  |                |              |
	  |      Room 4      |      Room 5    |    Room 6    | 
	  |                  |                |              |
	  |---------------------------------------------------
	  |                  |                |              |
	  |      Room 7      |      Room 8    |    Room 9    | 
	  |                  |                |              |
	  |---------------------------------------------------

	*/
	switch (m_currentRoom)
	{
		//Top Left Room
	case ROOM1:
	{
		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{		
			m_currentRoom = ROOM4;
			std::cout << "Returning 1" << endl;
			checkDoor = 1;
			return true;
		}

		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM2;
			std::cout << "Returning 3" << endl;
			checkDoor = 3;
			return true;
		}

	}
	break;

	//Top Middle Room
	case ROOM2:
	{
		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM5;
			std::cout << "Returning 1" << endl;
			checkDoor = 1;
			return true;
		}

		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM3;
			std::cout << "Returning 3" << endl;
			checkDoor = 3;
			return true;
		}

		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM1;
			std::cout << "Returning 4" << endl;
			checkDoor = 4;
			return true;
		}
	}
	break;

	//Top Right Room
	case ROOM3:
	{
		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM2;
			std::cout << "Returning 4" << endl;
			checkDoor = 4;
			return true;
		}

		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM6;
			std::cout << "Returning 1" << endl;
			checkDoor = 1;
			return true;
		}
	}
	break;

	//Middle Left Room
	case ROOM4:
	{
		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM7;
			std::cout << "Returning 7" << endl;
			checkDoor = 1;
			return true;
		}

		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM5;
			std::cout << "Returning 5" << endl;
			checkDoor = 3;
			return true;
		}

		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM1;
			std::cout << "Returning 1" << endl;
			checkDoor = 2;
			return true;
		}
	}
	break;

	//Middle Room
	case ROOM5:
	{
		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM2;
			std::cout << "Returning 2" << endl;
			checkDoor = 2;
			return true;
		}

		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM8;
			std::cout << "Returning 8" << endl;
			checkDoor = 1;
			return true;
		}

		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM6;
			std::cout << "Returning 6" << endl;
			checkDoor = 3;
			return true;
		}

		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM4;
			std::cout << "Returning 4" << endl;
			checkDoor = 4;
			return true;
		}
	}
	break;

	//Middle Right Room
	case ROOM6:
	{
		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM3;
			std::cout << "Returning 3" << endl;
			checkDoor = 2;
			return true;
		}

		//Collision with the bottom door.
		if (playerRect.getGlobalBounds().intersects(m_collisionBottomDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM9;
			std::cout << "Returning 9" << endl;
			checkDoor = 1;
			return true;
		}

		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM5;
			std::cout << "Returning 5" << endl;
			checkDoor = 4;
			return true;
		}
	}
	break;

	//Bottom Left Room
	case ROOM7:
	{
		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM4;
			std::cout << "Returning 4" << endl;
			checkDoor = 2;
			return true;
		}
		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM8;
			std::cout << "Returning 8" << endl;
			checkDoor = 3;
			return true;
		}
	}
	break;

	//Bottom Middle Room
	case ROOM8:
	{
		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM5;
			std::cout << "Returning 5" << endl;
			checkDoor = 2;
			return true;
		}

		//Collision with the right door.
		if (playerRect.getGlobalBounds().intersects(m_collisionRightDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM9;
			std::cout << "Returning 9" << endl;
			checkDoor = 3;
			return true;
		}

		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM7;
			std::cout << "Returning 7" << endl;
			checkDoor = 4;
			return true;
		}
	}
	break;

	//Bottom Right Room
	case ROOM9:
	{
		//Collision with the top door.
		if (playerRect.getGlobalBounds().intersects(m_collisionTopDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM6;
			std::cout << "Returning 6" << endl;
			checkDoor = 2;
			return true;
		}

		//Collision with the left door.
		if (playerRect.getGlobalBounds().intersects(m_collisionLeftDoor.getGlobalBounds()))
		{
			m_currentRoom = ROOM8;
			std::cout << "Returning 8" << endl;
			checkDoor = 4;
			return true;
		}
	}
	break;
	}

	return false;
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
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom2 = true;
		}
		break;

		//Top Right Room
		case ROOM3:
		{
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom3 = true;
		}
		break;

		//Middle Left Room
		case ROOM4:
		{
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_loadedRoom4 = true;
		}
		break;

		//Middle Room
		case ROOM5:
		{
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom5 = true;
		}
		break;

		//Middle Right Room
		case ROOM6:
		{
			m_collisionBottomDoor.setPosition(sf::Vector2f(600, 675));
			m_collisionBottomDoor.setSize(sf::Vector2f(80, 40));
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom6 = true;
		}
		break;

		//Bottom Left Room
		case ROOM7:
		{
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_loadedRoom7 = true;
		}
		break;

		//Bottom Middle Room
		case ROOM8:
		{
			m_collisionRightDoor.setPosition(sf::Vector2f(1230, 320));
			m_collisionRightDoor.setSize(sf::Vector2f(40, 80));
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom8 = true;
		}
		break;

		//Bottom Right Room
		case ROOM9:
		{
			m_collisionTopDoor.setPosition(sf::Vector2f(600, 10));
			m_collisionTopDoor.setSize(sf::Vector2f(80, 40));
			m_collisionLeftDoor.setPosition(sf::Vector2f(10, 320));
			m_collisionLeftDoor.setSize(sf::Vector2f(40, 80));
			m_loadedRoom5 = true;
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
bool Room::CheckBoundingCollisions(sf::RectangleShape playerRect)
{
	switch (m_currentRoom)
	{
		//Top Left Room
	case ROOM1:
	{
		/*if (m_fullBottomRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			std::cout << "PLAYER HIT BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}*/

		if (m_fullTopRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT TOP WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_fullLeftRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

	}
	break;

	//Top Middle Room
	case ROOM2:
	{
		if (m_fullTopRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT TOP WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Top Right Room
	case ROOM3:
	{
		if (m_fullTopRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT TOP WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_fullRightRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Middle Left Room
	case ROOM4:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_fullLeftRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Middle Room
	case ROOM5:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Middle Right Room
	case ROOM6:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_fullRightRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_halfBottomRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1ST BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

		if (m_halfBottomRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2ND BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Bottom Left Room
	case ROOM7:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_fullLeftRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}


		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_fullBottomRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}

	}
	break;

	//Bottom Middle Room
	case ROOM8:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}


		if (m_halfRightRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_halfRightRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}


		if (m_fullBottomRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;

	//Bottom Right Room
	case ROOM9:
	{
		if (m_halfTopRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfTopRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd WALL" << std::endl;
			checkWall = 1;
			return true;
		}

		if (m_halfLeftRect1.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 1st LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}

		if (m_halfLeftRect2.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT 2nd LEFT WALL" << std::endl;
			checkWall = 3;
			return true;
		}


		if (m_fullRightRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT RIGHT WALL" << std::endl;
			checkWall = 4;
			return true;
		}

		if (m_fullBottomRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
		{
			//std::cout << "PLAYER HIT BOTTOM WALL" << std::endl;
			checkWall = 2;
			return true;
		}
	}
	break;
	}
	
	return false;
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

		}
		break;

		//Top Middle Room
		case ROOM2:
		{
			if (!m_loadedRoom2)
				LoadCollisionRectangles();

			window.draw(m_topMiddleRect);
			

		}
		break;

		//Top Right Room
		case ROOM3:
		{
			if (!m_loadedRoom3)
				LoadCollisionRectangles();

			window.draw(m_topRightRect);

		
		}
		break;

		//Middle Left Room
		case ROOM4:
		{
			if (!m_loadedRoom4)
				LoadCollisionRectangles();

			window.draw(m_middleLeftRect);

		}
		break;

		//Middle Room
		case ROOM5:
		{
			if (!m_loadedRoom5)
				LoadCollisionRectangles();

			window.draw(m_middleRect);

		}
		break;

		//Middle Right Room
		case ROOM6:
		{
			if (!m_loadedRoom6)
				LoadCollisionRectangles();

			window.draw(m_middleRightRect);

		}
		break;

		//Bottom Left Room
		case ROOM7:
		{
			if (!m_loadedRoom7)
				LoadCollisionRectangles();

			window.draw(m_bottomLeftRect);

		}
		break;

		//Bottom Middle Room
		case ROOM8:
		{
			if (!m_loadedRoom8)
				LoadCollisionRectangles();

			window.draw(m_bottomMiddleRect);

		}
		break;

		//Bottom Right Room
		case ROOM9:
		{
			if (!m_loadedRoom8)
				LoadCollisionRectangles();

			window.draw(m_bottomRightRect);

		}
		break;

	}
}


void Room::InitCollisionRectangles()
{
	//Full Sized Collision Rectangles
	m_fullTopRectangle.setSize(sf::Vector2f(1280, 50));
	m_fullLeftRectangle.setSize(sf::Vector2f(50, 720));
	m_fullRightRectangle.setSize(sf::Vector2f(50, 720));
	m_fullBottomRectangle.setSize(sf::Vector2f(1280, 50));

	m_fullTopRectangle.setPosition(sf::Vector2f(0, 16));
	m_fullLeftRectangle.setPosition(sf::Vector2f(16, 0));
	m_fullRightRectangle.setPosition(sf::Vector2f(1216, 0));
	m_fullBottomRectangle.setPosition(sf::Vector2f(0, 655));
	
	
	m_halfTopRect1.setSize(sf::Vector2f(590, 50));
	m_halfTopRect2.setSize(sf::Vector2f(590, 50));
	m_halfTopRect1.setPosition(sf::Vector2f(0, 16));
	m_halfTopRect2.setPosition(sf::Vector2f(690, 16));

	m_halfLeftRect1.setSize(sf::Vector2f(50, 310));
	m_halfLeftRect2.setSize(sf::Vector2f(50, 310));
	m_halfLeftRect1.setPosition(sf::Vector2f(16, 0));
	m_halfLeftRect2.setPosition(sf::Vector2f(16, 410));


	m_halfBottomRect1.setSize(sf::Vector2f(590, 50));
	m_halfBottomRect2.setSize(sf::Vector2f(590, 50));
	m_halfBottomRect1.setPosition(sf::Vector2f(0, 655));
	m_halfBottomRect2.setPosition(sf::Vector2f(690, 655));

	m_halfRightRect1.setSize(sf::Vector2f(50, 310));
	m_halfRightRect2.setSize(sf::Vector2f(50, 300));
	m_halfRightRect1.setPosition(sf::Vector2f(1216, 0));
	m_halfRightRect2.setPosition(sf::Vector2f(1216, 410));

	std::cout << "Initialised Room Collision Rectangles" << std::endl;
}

sf::Vector2f Room::SetTopDoor()
{
	return sf::Vector2f(620, 50);
}
sf::Vector2f Room::SetBottomDoor()
{
	return sf::Vector2f(620, 620);
}
sf::Vector2f Room::SetLeftDoor()
{
	return sf::Vector2f(50, 330);
}
sf::Vector2f Room::SetRightDoor()
{
	return sf::Vector2f(1180, 330);
}

sf::Vector2f Room::SetLeftWall()
{
	return sf::Vector2f(66, 0);
}
sf::Vector2f Room::SetRightWall()
{
	return sf::Vector2f(1170, 0);
}
sf::Vector2f Room::SetTopWall()
{
	return sf::Vector2f(0, 66);
}
sf::Vector2f Room::SetBottomWall()
{
	return sf::Vector2f(0, 605);
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