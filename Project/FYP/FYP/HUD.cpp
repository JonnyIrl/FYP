#include "HUD.h"


//Constructor
HUD::HUD()
{
	if (LoadTexture())
	{
		m_hudRectangle.setSize(sf::Vector2f(500, 100));
		m_hudRectangle.setTexture(&m_hud1Texture);
		m_hudRectangle.setPosition(sf::Vector2f(-40, 620));

		m_healthRectangle.setSize(sf::Vector2f(68, 77));
		m_healthRectangle.setTexture(&m_health1Texture);
		m_healthRectangle.setPosition(sf::Vector2f(9, 631));

		m_energyBarRectangle.setSize(sf::Vector2f(334, 12));
		m_energyBarRectangle.setTexture(&m_energyBarTexture);
		m_energyBarRectangle.setPosition(sf::Vector2f(85, 648));

		//Blank
		m_blankRectangle.setSize(sf::Vector2f(30, 36));
		m_blankRectangle.setTexture(&m_blankTexture);
		m_blankRectangle.setPosition(sf::Vector2f(239, 675));


		m_scoreRectangle.setSize(sf::Vector2f(500, 500));
		m_scoreRectangle.setTexture(&m_scoreBoardTexture);
		m_scoreRectangle.setPosition(sf::Vector2f(400, 100));

		player0.setPosition(sf::Vector2f(m_scoreRectangle.getPosition().x + 120, m_scoreRectangle.getPosition().y + 80));
		player1.setPosition(sf::Vector2f(player0.getPosition().x, player0.getPosition().y + 50));
		player2.setPosition(sf::Vector2f(player1.getPosition().x, player1.getPosition().y + 50));
		player3.setPosition(sf::Vector2f(player2.getPosition().x, player2.getPosition().y + 50));

		player0.setFont(font);
		player1.setFont(font);
		player2.setFont(font);
		player3.setFont(font);

		m_gameOverRect.setSize(sf::Vector2f(500, 50));
		m_gameOverRect.setPosition(sf::Vector2f(400, 50));
		m_gameOverRect.setTexture(&m_gameOverTexture);

		gameOverTextRectangle.setSize(sf::Vector2f(500, 100));
		gameOverTextRectangle.setPosition(sf::Vector2f(500, 600));
		gameOverTextRectangle.setTexture(&gameOverTextTexture);

	}
}

bool HUD::LoadTexture()
{
	if (!m_hud1Texture.loadFromFile("Assets/HUD/hud1.png"))
		return false;

	if (!m_hud2Texture.loadFromFile("Assets/HUD/hud2.png"))
		return false;

	if (!m_hud3Texture.loadFromFile("Assets/HUD/hud3.png"))
		return false;

	if (!m_hud4Texture.loadFromFile("Assets/HUD/hud4.png"))
		return false;

	if (!m_hud5Texture.loadFromFile("Assets/HUD/hud5.png"))
		return false;

	if (!m_hud6Texture.loadFromFile("Assets/HUD/hud6.png"))
		return false;

	if (!m_health1Texture.loadFromFile("Assets/HUD/Health/1.png"))
		return false;

	if (!m_health2Texture.loadFromFile("Assets/HUD/Health/2.png"))
		return false;

	if (!m_health3Texture.loadFromFile("Assets/HUD/Health/3.png"))
		return false;

	if (!m_health4Texture.loadFromFile("Assets/HUD/Health/4.png"))
		return false;

	if (!m_health5Texture.loadFromFile("Assets/HUD/Health/5.png"))
		return false;

	if (!m_health6Texture.loadFromFile("Assets/HUD/Health/6.png"))
		return false;

	if (!m_health7Texture.loadFromFile("Assets/HUD/Health/7.png"))
		return false;

	if (!m_health8Texture.loadFromFile("Assets/HUD/Health/8.png"))
		return false;

	if (!m_health9Texture.loadFromFile("Assets/HUD/Health/9.png"))
		return false;

	if (!m_health10Texture.loadFromFile("Assets/HUD/Health/10.png"))
		return false;

	if (!m_energyBarTexture.loadFromFile("Assets/HUD/energyBar.png"))
		return false;

	if (!m_scoreBoardTexture.loadFromFile("Assets/HUD/scoreBoard.png"))
		return false;

	if (!m_gameOverTexture.loadFromFile("Assets/HUD/gameover.png"))
		return false;

	if (!gameOverTextTexture.loadFromFile("Assets/Buttons/esc.png"))
		return false;

	if (!font.loadFromFile("Assets/Font/font.ttf")) {
		std::cout << "No font file found!" << std::endl;
	}

	if (!m_blankTexture.loadFromFile("Assets/Guns/Blank/blank.png")) {
		std::cout << "No blank texture found!" << std::endl;
	}
	
	return true;
}


int HUD::FindHighlight(int number)
{
	if (number == 6) return 1;

	else return number;
}

void HUD::SetHighlight(int slotNumber)
{
	if (slotNumber == 1)
	{
		if (m_hudRectangle.getTexture() != &m_hud1Texture)
		m_hudRectangle.setTexture(&m_hud1Texture);
	}

	else if (slotNumber == 2)
	{
		if (m_hudRectangle.getTexture() != &m_hud2Texture)
		m_hudRectangle.setTexture(&m_hud2Texture);
	}

	else if (slotNumber == 3)
	{
		if (m_hudRectangle.getTexture() != &m_hud3Texture)
		m_hudRectangle.setTexture(&m_hud3Texture);
	}

	else if (slotNumber == 4)
	{
		if (m_hudRectangle.getTexture() != &m_hud4Texture)
		m_hudRectangle.setTexture(&m_hud4Texture);
	}

	else if (slotNumber == 5)
	{
		if (m_hudRectangle.getTexture() != &m_hud5Texture)
		m_hudRectangle.setTexture(&m_hud5Texture);
	}

	else if (slotNumber == 6)
	{
		if (m_hudRectangle.getTexture() != &m_hud6Texture)
		m_hudRectangle.setTexture(&m_hud6Texture);
	}

}

void HUD::SetHealth(int health)
{
	if (health >= 90 && health <= 100)
	{
		if (m_healthRectangle.getTexture() != &m_health1Texture)
			m_healthRectangle.setTexture(&m_health1Texture);
	}

	else if (health >= 80 && health < 90)
	{
		if (m_healthRectangle.getTexture() != &m_health2Texture)
			m_healthRectangle.setTexture(&m_health2Texture);
	}

	else if (health >= 70 && health < 80)
	{
		if (m_healthRectangle.getTexture() != &m_health3Texture)
			m_healthRectangle.setTexture(&m_health3Texture);
	}

	else if (health >= 60 && health < 70)
	{
		if (m_healthRectangle.getTexture() != &m_health4Texture)
			m_healthRectangle.setTexture(&m_health4Texture);
	}

	else if (health >= 50 && health < 60)
	{
		if (m_healthRectangle.getTexture() != &m_health5Texture)
			m_healthRectangle.setTexture(&m_health5Texture);
	}

	else if (health >= 40 && health < 50)
	{
		if (m_healthRectangle.getTexture() != &m_health6Texture)
			m_healthRectangle.setTexture(&m_health6Texture);
	}

	else if (health >= 30 && health < 40)
	{
		if (m_healthRectangle.getTexture() != &m_health7Texture)
			m_healthRectangle.setTexture(&m_health7Texture);
	}

	else if (health >= 20 && health < 30)
	{
		if (m_healthRectangle.getTexture() != &m_health8Texture)
			m_healthRectangle.setTexture(&m_health8Texture);
	}

	else if (health >= 10 && health < 20)
	{
		if (m_healthRectangle.getTexture() != &m_health9Texture)
			m_healthRectangle.setTexture(&m_health9Texture);
	}

	else if (health < 10)
	{
		if (m_healthRectangle.getTexture() != &m_health10Texture)
			m_healthRectangle.setTexture(&m_health10Texture);
	}
}

void HUD::SetEnergy(int energyAmount)
{	
	if ((3.3 *energyAmount) > 334)
	{
		m_energyBarRectangle.setTextureRect(sf::IntRect(m_energyBarRectangle.getPosition().x, m_energyBarRectangle.getPosition().y, 334, 12));
	}

	else
	m_energyBarRectangle.setTextureRect(sf::IntRect(m_energyBarRectangle.getPosition().x, m_energyBarRectangle.getPosition().y, (3.3 * energyAmount), 12));
}

void HUD::SetScore(vector<pair<string, int>> players, string playerID, int playerScore)
{

	player0.setString(playerID + " - " + to_string(playerScore));

	for (int i = 0; i < players.size(); i++)
	{
		//Populate first box
		if (i == 0)
		{
			player1.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 1)
		{
			player2.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 2)
		{
			player3.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 3)
		{
			player4.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 4)
		{
			player5.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 5)
		{
			player6.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 6)
		{
			player7.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}

		if (i == 7)
		{
			player8.setString(players.at(i).first + " - " + to_string(players.at(i).second));
		}
	}
}

void HUD::Draw(sf::RenderWindow &window)
{
	if (gameOver == false)
	{
		window.draw(m_healthRectangle);
		window.draw(m_energyBarRectangle);
		window.draw(m_hudRectangle);
		if (countDown)
		{
			window.draw(m_blankRectangle);
		}
	}

	else
	{
		window.draw(m_gameOverRect);
		window.draw(gameOverTextRectangle);
	}

	if (showScore)
	{
		window.draw(m_scoreRectangle);
		if (player0.getString().getSize() > 0)
		{
			window.draw(player0);
		}

		if (player1.getString().getSize() > 0)
		{
			window.draw(player1);
		}

		if (player2.getString().getSize() > 0)
		{
			window.draw(player2);
		}

		if (player3.getString().getSize() > 0)
		{
			window.draw(player3);
		}

		if (player4.getString().getSize() > 0)
		{
			window.draw(player4);
		}

		if (player5.getString().getSize() > 0)
		{
			window.draw(player5);
		}

		if (player6.getString().getSize() > 0)
		{
			window.draw(player6);
		}

		if (player7.getString().getSize() > 0)
		{
			window.draw(player7);
		}

		if (player8.getString().getSize() > 0)
		{
			window.draw(player8);
		}
	}

}