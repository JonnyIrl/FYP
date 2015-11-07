#include "Room.h"

using namespace std;

Room::Room()
{
	cout << "Finished Room Constructor" << endl;
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

}

void Room::CreateLeftRooms()
{

}