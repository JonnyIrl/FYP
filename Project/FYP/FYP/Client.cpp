#include "Client.h"

Client::Client(const string &IP, const string &Name, int count, bool ready)
{
	m_IPAddress = IP;
	m_Name = Name;
	m_readySquare.setSize(sf::Vector2f(20, 20));
	m_readySquare.setFillColor(sf::Color::Red);
	m_Ready = ready;
	AssignPosition(count);
}

void Client::AssignPosition(int count)
{
	if (count == 1)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (18 * count)));
	}

	if (count == 2)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 3)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 4)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 5)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 6)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 7)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}

	if (count == 8)
	{
		m_readySquare.setPosition(sf::Vector2f(850, 195 + (28 * count)));
	}
}

void Client::SetReady(bool state)
{
	m_Ready = state;

	if (m_Ready)
	{
		m_readySquare.setFillColor(sf::Color::Green);
	}

	else
	{
		m_readySquare.setFillColor(sf::Color::Red);
	}
}