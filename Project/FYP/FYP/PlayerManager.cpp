#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::AddNewPlayer(string id)
{
	m_Players.push_back(new MultiPlayer());
	m_Players.at((m_Players.size() - 1))->SetPlayerID(id);
	cout << "Added new multi player, IP = " << id << endl;
}

MultiPlayer* PlayerManager::FindWhichPlayerToUpdate(string ip)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetPlayerID().find(ip) != string::npos)
		{
			return m_Players.at(i);
		}
	}
}

void PlayerManager::SetPlayersPosition(string playerID, sf::Vector2f position)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetPlayerID() == playerID)
		{
			m_Players.at(i)->SetPosition(position);
		}
	}
}

void PlayerManager::Update(sf::Time time)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		m_Players.at(i)->UpdateRoom1(time);
	}
}

void PlayerManager::Draw1(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 1)
		m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw2(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 2)
			m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw3(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 3)
			m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw4(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 4)
			m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw5(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 5)
			m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw6(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 6)
			m_Players.at(i)->Draw(window);
	}
}

void PlayerManager::Draw7(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		if (m_Players.at(i)->GetRoomNumber() == 7)
			m_Players.at(i)->Draw(window);
	}
}