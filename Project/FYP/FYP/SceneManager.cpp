#include "SceneManager.h"

using namespace std;

//Constructor
SceneManager::SceneManager()
{
	if (LoadTexture())
	{
		m_currentScene = MENU;
		m_sceneRect.setSize(sf::Vector2f(1280, 720));
		m_sceneRect.setPosition(sf::Vector2f(0, 0));
		m_sceneRect.setTexture(&m_mainMenuTexture);
		cout << "SceneManager Constructor Finished" << endl;
		m_animtionToPlay = 0;

		//Play Game Rectangle
		m_playRect.setSize(sf::Vector2f(95, 80));
		m_playRect.setPosition(sf::Vector2f(440, 240));
		m_playRect.setTexture(&m_blankDoorTexture);

		//Options Rectangle
		m_optionsRect.setSize(sf::Vector2f(95, 80));
		m_optionsRect.setPosition(sf::Vector2f(622, 240));
		m_optionsRect.setTexture(&m_blankDoorTexture);

		//Credits Rectangle
		m_creditsRect.setSize(sf::Vector2f(95, 80));
		m_creditsRect.setPosition(sf::Vector2f(803, 240));
		m_creditsRect.setTexture(&m_blankDoorTexture);


		//Play Game Door Animation.
		m_playGameAnimation.setSpriteSheet(m_doorTexture);
		m_playGameAnimation.addFrame(sf::IntRect(0, 0, 95, 80));
		m_playGameAnimation.addFrame(sf::IntRect(0, 96, 95, 80));
		m_playGameAnimation.addFrame(sf::IntRect(0, 192, 95, 80));
		m_playGameAnimation.addFrame(sf::IntRect(0, 288, 95, 80));

		//Options Door Animation
		m_optionsAnimation.setSpriteSheet(m_doorTexture);
		m_optionsAnimation.addFrame(sf::IntRect(0, 0, 95, 80));
		m_optionsAnimation.addFrame(sf::IntRect(0, 96, 95, 80));
		m_optionsAnimation.addFrame(sf::IntRect(0, 192, 95, 80));
		m_optionsAnimation.addFrame(sf::IntRect(0, 288, 95, 80));

		//Credits Door Animation
		m_creditsAnimation.setSpriteSheet(m_doorTexture);
		m_creditsAnimation.addFrame(sf::IntRect(0, 0, 95, 80));
		m_creditsAnimation.addFrame(sf::IntRect(0, 96, 95, 80));
		m_creditsAnimation.addFrame(sf::IntRect(0, 192, 95, 80));
		m_creditsAnimation.addFrame(sf::IntRect(0, 288, 95, 80));


		m_doorAnimation = AnimatedSprite(sf::seconds(0.5f), false, false, true);
		//m_doorAnimation.setAnimation(m_playGameAnimation);

	}
}

void SceneManager::ChangeBackground(sf::Time time)
{
	switch (m_currentScene)
	{
		case MENU:
		{			
			if (m_sceneRect.getTexture() != &m_mainMenuTexture)
				m_sceneRect.setTexture(&m_mainMenuTexture);


			if (m_doorAnimation.getAnimation() == &m_playGameAnimation)
			m_doorAnimation.setPosition(m_playRect.getPosition());

			else if (m_doorAnimation.getAnimation() == &m_optionsAnimation)
				m_doorAnimation.setPosition(m_optionsRect.getPosition());

			else if (m_doorAnimation.getAnimation() == &m_creditsAnimation)
				m_doorAnimation.setPosition(m_creditsRect.getPosition());

			m_doorAnimation.update(time);
				
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

	if (!m_doorTexture.loadFromFile("Assets/Door/doorAnimation.png"))
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
	window.draw(m_optionsRect);
	window.draw(m_creditsRect);
	window.draw(m_doorAnimation);
}

//Getters and Setters
void SceneManager::AnimationToPlay(int animation)
{
	//1 = Play Game Door Animation
	if (animation == 1)
	{
		if (m_doorAnimation.getAnimation() != &m_playGameAnimation)
		{
			m_doorAnimation.setAnimation(m_playGameAnimation);

			if (!m_doorAnimation.isPlaying())
			{
				m_doorAnimation.play();
			}
		}

		else
			m_doorAnimation.play();
	}

	//2 = Options Door Animation
	if (animation == 2)
	{
		if (m_doorAnimation.getAnimation() != &m_optionsAnimation)
		{
			m_doorAnimation.setAnimation(m_optionsAnimation);

			if (!m_doorAnimation.isPlaying())
			{
				m_doorAnimation.play();
			}
		}

		else
			m_doorAnimation.play();
	}

	//3 = Credits Door Animation
	if (animation == 3)
	{
		if (m_doorAnimation.getAnimation() != &m_creditsAnimation)
		{
			m_doorAnimation.setAnimation(m_creditsAnimation);

			if (!m_doorAnimation.isPlaying())
			{
				m_doorAnimation.play();
			}
		}

		else
			m_doorAnimation.play();
	}
}
byte SceneManager::GetCurrentScene()
{
	return m_currentScene;
}
sf::RectangleShape SceneManager::GetCreditsRectangle()
{
	return m_creditsRect;
}
sf::RectangleShape SceneManager::GetPlayRectangle()
{
	return m_playRect;
}
sf::RectangleShape SceneManager::GetOptionsRectangle()
{
	return m_optionsRect;
}
