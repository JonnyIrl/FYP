#include "SceneManager.h"

using namespace std;
SceneManager::SceneManager()
{
	if (LoadTexture())
	{
		m_currentScene = MENU;
		m_sceneRect.setSize(sf::Vector2f(1280, 720));
		m_sceneRect.setPosition(sf::Vector2f(0, 0));
		m_sceneRect.setTexture(&m_mainMenuTexture);
		cout << "SceneManager Constructor Finished" << endl;

		m_playRect.setSize(sf::Vector2f(95, 80));
		m_playRect.setPosition(sf::Vector2f(440, 240));
		m_playRect.setTexture(&m_blankDoorTexture);

		m_playGameAnimation.setSpriteSheet(m_doorTexture);
		m_playGameAnimation.addFrame(sf::IntRect(0, 0, 95, 80));
		m_playGameAnimation.addFrame(sf::IntRect(95, 0, 95, 80));
		m_playGameAnimation.addFrame(sf::IntRect(190, 0, 95, 80));


		m_doorAnimation = AnimatedSprite(sf::seconds(1.0f));
		m_doorAnimation.setAnimation(m_playGameAnimation);

	}
}

void SceneManager::ChangeBackground(sf::Time time)
{
	switch (m_currentScene)
	{
		case MENU:
		{
			m_doorAnimation.update(time);
			m_doorAnimation.setPosition(m_playRect.getPosition());

			if (m_sceneRect.getTexture() != &m_mainMenuTexture)
				m_sceneRect.setTexture(&m_mainMenuTexture);		
		}
		break;

		case OPTIONS:
		{
			if (m_sceneRect.getTexture() != &m_optionsTexture)
				m_sceneRect.setTexture(&m_optionsTexture);
		}
		break;

		case PLAY_GAME:
		{
		}
		break;
	}
}

bool SceneManager::LoadTexture()
{
	if (!m_creditsTexture.loadFromFile("Assets/Menu/creditsScreen.png"))
	{
		std::cout << "Couldn't load credits texture" << std::endl;
		return false;
	}

	if (!m_gameOverTexture.loadFromFile("Assets/Menu/emptyRoom.png"))
	{
		std::cout << "Couldn't load Game Over texture" << std::endl;
		return false;
	}

	if (!m_mainMenuTexture.loadFromFile("Assets/Menu/mainScreen.png"))
	{
		std::cout << "Couldn't load Main Menu texture" << std::endl;
		return false;
	}

	if (!m_optionsTexture.loadFromFile("Assets/Menu/optionsScreen.png"))
	{
		std::cout << "Couldn't load options texture" << std::endl;
		return false;
	}

	if (!m_doorTexture.loadFromFile("Assets/Door/door.png"))
	{
		std::cout << "Couldn't load door texture" << std::endl;
		return false;
	}

	if (!m_blankDoorTexture.loadFromFile("Assets/Door/doorblank.png"))
	{
		std::cout << "Couldn't load door texture" << std::endl;
		return false;
	}

	else
		return true;
}

void SceneManager::Draw(sf::RenderWindow &window)
{
	window.draw(m_sceneRect);
	window.draw(m_playRect);
	window.draw(m_doorAnimation);
}

byte SceneManager::GetCurrentScene()
{
	return m_currentScene;
}
