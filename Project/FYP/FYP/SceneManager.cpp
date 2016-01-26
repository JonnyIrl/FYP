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
		m_animtionToPlay = 0;

		//Collision Rectangle to go to Play Game Menu scene.
		m_collisionPlayRect.setSize(sf::Vector2f(80, 40));
		m_collisionPlayRect.setPosition(sf::Vector2f(450, 250));


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

		//Game Settings Window
		m_gameSettingRect.setSize(sf::Vector2f(500, 500));
		m_gameSettingRect.setTexture(&m_gameSettingTexture);
		m_gameSettingRect.setPosition(sf::Vector2f(400, 100));

		currentMaster = 4;
		currentSfx = 4;

		//Load all the volume rectangles etc.
		sfxVolume1.setSize(sf::Vector2f(25, 40));
		sfxVolume1.setTexture(&volumeBarTexture);
		sfxVolume2 = sfxVolume1;
		sfxVolume3 = sfxVolume1;
		sfxVolume4 = sfxVolume1;

		masterVolume1.setSize(sf::Vector2f(25, 40));
		masterVolume1.setTexture(&volumeBarTexture);
		masterVolume2 = masterVolume1;
		masterVolume3 = masterVolume1;
		masterVolume4 = masterVolume1;

		sfxVolume1.setPosition(sf::Vector2f(605, 368));
		sfxVolume2.setPosition(sf::Vector2f(635, 368));
		sfxVolume3.setPosition(sf::Vector2f(665, 368));
		sfxVolume4.setPosition(sf::Vector2f(695, 368));

		masterVolume1.setPosition(sf::Vector2f(605, 297));
		masterVolume2.setPosition(sf::Vector2f(635, 297));
		masterVolume3.setPosition(sf::Vector2f(665, 297));
		masterVolume4.setPosition(sf::Vector2f(695, 297));

		confirmButton.setSize(sf::Vector2f(120, 40));
		confirmButton.setPosition(sf::Vector2f(590, 425));

		//Load plus and minus buttons
		sfxPlusRect.setSize(sf::Vector2f(40, 40));
		sfxPlusRect.setPosition(sf::Vector2f(735, 368));

		sfxMinusRect.setSize(sf::Vector2f(40, 40));
		sfxMinusRect.setPosition(sf::Vector2f(560, 368));

		masterPlusRect.setSize(sf::Vector2f(40, 40));
		masterPlusRect.setPosition(sf::Vector2f(735, 297));

		masterMinusRect.setSize(sf::Vector2f(40, 40));
		masterMinusRect.setPosition(sf::Vector2f(560, 297));

		//Pre Game Lobby Main Texture + Send Rectangle
		m_chatLobbyRect.setTexture(&m_chatLobbyTexture);
		m_chatLobbyRect.setPosition(sf::Vector2f(0, 0));
		m_chatLobbyRect.setSize(sf::Vector2f(1280, 720));

		m_sendRect.setPosition(925, 602);
		m_sendRect.setSize(sf::Vector2f(260, 35));

		m_text.setPosition(sf::Vector2f(100, 600));
		m_text.setFont(m_font);
		m_text.setColor(sf::Color::White);

		m_currentMessage = "";
		messagesSent = 0;


		cout << "SceneManager Constructor Finished" << endl;


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

		case LOBBY:
		{
			if (m_chatLobbyRect.getTexture() != &m_chatLobbyTexture)
				m_sceneRect.setTexture(&m_chatLobbyTexture);
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

	//Game Settings Texture
	if (!m_gameSettingTexture.loadFromFile("Assets/Menu/gameSettings.png"))
	{
		std::cout << "Couldn't load game settings texture" << std::endl;
		return false;
	}

	//Audio Volume Bars
	if (!volumeBarTexture.loadFromFile("Assets/Menu/volumeBar.png"))
	{
		std::cout << "Couldn't load volume bar texture" << std::endl;
		return false;
	}

	if (!m_chatLobbyTexture.loadFromFile("Assets/Pregame/chatLobby.png"))
	{
		std::cout << "Couldn't load chat lobby png" << std::endl;
		return false;
	}

	if (!m_font.loadFromFile("Assets/Pregame/font.ttf"))
	{
		std::cout << "Couldn't load FONT" << std::endl;
		return false;
	}


	else
		return true;
}

void SceneManager::Draw(sf::RenderWindow &window)
{
	switch (m_currentScene)
	{
	case MENU:
	{
		window.draw(m_sceneRect);
		window.draw(m_playRect);
		window.draw(m_optionsRect);
		window.draw(m_creditsRect);
		window.draw(m_doorAnimation);
	}
	break;

	case OPTIONS:
	{
		window.draw(m_sceneRect);
		window.draw(m_gameSettingRect);

		if (currentMaster == 4)
		{
			window.draw(masterVolume1);
			window.draw(masterVolume2);
			window.draw(masterVolume3);
			window.draw(masterVolume4);
		}

		if (currentMaster == 3)
		{
			window.draw(masterVolume1);
			window.draw(masterVolume2);
			window.draw(masterVolume3);
		}

		if (currentMaster == 2)
		{
			window.draw(masterVolume1);
			window.draw(masterVolume2);
		}

		if (currentMaster == 1)
		{
			window.draw(masterVolume1);
		}

		if (currentSfx == 4)
		{
			window.draw(sfxVolume1);
			window.draw(sfxVolume2);
			window.draw(sfxVolume3);
			window.draw(sfxVolume4);
		}

		if (currentSfx == 3)
		{
			window.draw(sfxVolume1);
			window.draw(sfxVolume2);
			window.draw(sfxVolume3);
		}

		if (currentSfx == 2)
		{
			window.draw(sfxVolume1);
			window.draw(sfxVolume2);
		}

		if (currentSfx == 1)
		{
			window.draw(sfxVolume1);
		}
	}
	break;

	case PLAY_GAME:
	{
	}
	break;

	case LOBBY:
	{
		window.draw(m_chatLobbyRect);
		window.draw(m_text);
		//Draw Chat String
	}
	break;

	}
	
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
sf::RectangleShape SceneManager::GetCollisionPlayRect()
{
	return m_collisionPlayRect;
}
sf::RectangleShape SceneManager::GetSFXPlusRect()
{
	return sfxPlusRect;
}
sf::RectangleShape SceneManager::GetSFXMinusRect()
{
	return sfxMinusRect;
}
sf::RectangleShape SceneManager::GetMasterPlusRect()
{
	return masterPlusRect;
}
sf::RectangleShape SceneManager::GetMasterMinusRect()
{
	return masterMinusRect;
}
sf::RectangleShape SceneManager::GetConfirmRectangle()
{
	return confirmButton;
}
sf::RectangleShape SceneManager::GetSendRectangle()
{
	return m_sendRect;
}
void SceneManager::SetChatMessage(string message)
{
	m_currentMessage += message;
	m_text.setString(m_currentMessage);
}
void SceneManager::ResetText()
{
	historyMessages.push_back(m_currentMessage);
	m_currentMessage = "";
	SetChatMessage("");
	messagesSent++;
}

