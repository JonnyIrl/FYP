#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::AddNewPlayer(string id)
{
	m_Players.push_back(new Player());
	m_Players.at((m_Players.size() - 1))->SetPlayerID(id);
	cout << "Added new player, ID = " << id << endl;
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
		m_Players.at(i)->Update(time);
	}
}

void PlayerManager::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < m_Players.size(); i++)
	{
		m_Players.at(i)->Draw(window);
	}
}