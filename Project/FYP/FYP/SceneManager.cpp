#include "SceneManager.h"
#include "PacketType.h"

using namespace std;

//Constructor
SceneManager::SceneManager()
{
	if (LoadTexture())
	{
		m_currentScene = LOBBY;
		m_sceneRect.setSize(sf::Vector2f(1280, 720));
		m_sceneRect.setPosition(sf::Vector2f(0, 0));
		m_sceneRect.setTexture(&m_mainMenuTexture);		

		//Collision Rectangle to go to Play Game Menu scene.
		m_collisionPlayRect.setSize(sf::Vector2f(80, 40));
		m_collisionPlayRect.setPosition(sf::Vector2f(450, 250));

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

		m_CollisionConnectRect.setPosition(420, 220);
		m_CollisionConnectRect.setSize(sf::Vector2f(350, 250));

		//Main Menu Buttons
		m_PlayGameButtonRect.setPosition(480, 150);
		m_PlayGameButtonRect.setSize(sf::Vector2f(332, 68));
		m_PlayGameButtonRect.setTexture(&m_playGameText);

		m_OptionsButtonRect.setPosition(480, 250);
		m_OptionsButtonRect.setSize(sf::Vector2f(332, 68));
		m_OptionsButtonRect.setTexture(&m_optionsText);

		m_CreditsButtonRect.setPosition(480, 350);
		m_CreditsButtonRect.setSize(sf::Vector2f(332, 68));
		m_CreditsButtonRect.setTexture(&m_creditsText);

		m_QuitButtonRect.setPosition(480, 450);
		m_QuitButtonRect.setSize(sf::Vector2f(332, 68));
		m_QuitButtonRect.setTexture(&m_quitText);

		//MAIN MENU SELECT BUTTONS
		m_SelectPlayGameButtonRect.setPosition(480, 150);
		m_SelectPlayGameButtonRect.setSize(sf::Vector2f(332, 68));
		m_SelectPlayGameButtonRect.setTexture(&m_playGameSelectText);

		m_SelectOptionsButtonRect.setPosition(480, 250);
		m_SelectOptionsButtonRect.setSize(sf::Vector2f(332, 68));
		m_SelectOptionsButtonRect.setTexture(&m_optionsSelectText);

		m_SelectCreditsButtonRect.setPosition(480, 350);
		m_SelectCreditsButtonRect.setSize(sf::Vector2f(332, 68));
		m_SelectCreditsButtonRect.setTexture(&m_creditsSelectText);

		m_SelectQuitButtonRect.setPosition(480, 450);
		m_SelectQuitButtonRect.setSize(sf::Vector2f(332, 68));
		m_SelectQuitButtonRect.setTexture(&m_quitSelectText);

		//Mouse Rect
		m_mouseRect.setPosition(0, 0);
		m_mouseRect.setSize(sf::Vector2f(1, 1));

		//LOBBY
		//NOT READY SCREEN
		m_NotReadyRectangle.setSize(sf::Vector2f(1280, 720));
		m_NotReadyRectangle.setTexture(&m_NotReadyScreen);
		m_NotReadyRectangle.setPosition(sf::Vector2f(0, 0));

		//READY SCREEN
		m_ReadyRectangle.setSize(sf::Vector2f(1280, 720));
		m_ReadyRectangle.setTexture(&m_ReadyScreen);
		m_ReadyRectangle.setPosition(sf::Vector2f(0, 0));

		//CONNECT SCREEN
		m_ConnectRectangle.setSize(sf::Vector2f(1280, 720));
		m_ConnectRectangle.setTexture(&m_ConnectScreen);
		m_ConnectRectangle.setPosition(sf::Vector2f(0, 0));

		//SAVE RECTANGLE FOR CHANGING NAME
		m_SaveNameRectangle.setSize(sf::Vector2f(140, 50));
		m_SaveNameRectangle.setPosition(sf::Vector2f(540, 105));
		
		//RECTANGLE FOR CLICKING TO CHANGE NAME
		m_NameRectangle.setSize(sf::Vector2f(350, 45));
		m_NameRectangle.setPosition(sf::Vector2f(160, 108));

		m_CollisionReadyRectangle.setSize(sf::Vector2f(370, 42));
		m_CollisionReadyRectangle.setPosition(sf::Vector2f(770, 665));


		cout << "SceneManager Constructor Finished" << endl;
	}
}

void SceneManager::ChangeBackground(sf::Event Event, sf::Time time)
{
	switch (m_currentScene)
	{
		case MENU:
		{			

			if (m_sceneRect.getTexture() != &m_mainMenuTexture)
				m_sceneRect.setTexture(&m_mainMenuTexture);

			//Check Mouse rectangle with the play button
			if (m_mouseRect.getGlobalBounds().intersects(m_PlayGameButtonRect.getGlobalBounds()) && Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
			{
				m_currentScene = PLAY_GAME;
			}


			//Check Mouse rectangle with the options button
			else if (m_mouseRect.getGlobalBounds().intersects(m_OptionsButtonRect.getGlobalBounds()) && Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
			{
				m_currentScene = OPTIONS;
			}



			//Check Mouse rectangle with the credits button
			else if (m_mouseRect.getGlobalBounds().intersects(m_CreditsButtonRect.getGlobalBounds()) && Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
			{
				m_currentScene = CREDITS;
			}

			//Check Mouse rectangle with the quit button
			else if (m_mouseRect.getGlobalBounds().intersects(m_QuitButtonRect.getGlobalBounds()) && Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
			{
				m_quitGame = true;
			}

				
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

	if (!m_mainMenuTexture.loadFromFile("Assets/Menu/mainMenu.png"))
	{
		std::cout << "Couldn't load Main Menu texture" << std::endl;
		return false;
	}

	if (!m_optionsTexture.loadFromFile("Assets/Menu/optionsScreen.png"))
	{
		std::cout << "Couldn't load options texture" << std::endl;
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

	if (!m_chatLobbyTexture.loadFromFile("Assets/Pregame/connect.png"))
	{
		std::cout << "Couldn't load chat lobby png" << std::endl;
		return false;
	}

	//BUTTONS TEXTURE
	if (!m_playGameText.loadFromFile("Assets/Buttons/playgame.png"))
	{
		std::cout << "Couldn't load PLAY GAME png" << std::endl;
		return false;
	}

	if (!m_optionsText.loadFromFile("Assets/Buttons/options.png"))
	{
		std::cout << "Couldn't load options button png" << std::endl;
		return false;
	}
	if (!m_creditsText.loadFromFile("Assets/Buttons/credits.png"))
	{
		std::cout << "Couldn't load credits png" << std::endl;
		return false;
	}

	if (!m_quitText.loadFromFile("Assets/Buttons/quit.png"))
	{
		std::cout << "Couldn't load quit png" << std::endl;
		return false;
	}

	//SELECT TEXTURES BUTTONS
	if (!m_playGameSelectText.loadFromFile("Assets/Buttons/selectPlayGame.png"))
	{
		std::cout << "Couldn't load PLAY GAME Select png" << std::endl;
		return false;
	}

	if (!m_optionsSelectText.loadFromFile("Assets/Buttons/selectOptions.png"))
	{
		std::cout << "Couldn't load options Select button png" << std::endl;
		return false;
	}
	if (!m_creditsSelectText.loadFromFile("Assets/Buttons/selectCredits.png"))
	{
		std::cout << "Couldn't load credits Select png" << std::endl;
		return false;
	}

	if (!m_quitSelectText.loadFromFile("Assets/Buttons/selectQuit.png"))
	{
		std::cout << "Couldn't load quit Select png" << std::endl;
		return false;
	}


	/*if (!m_chatLobbyTexture.loadFromFile("Assets/Pregame/chatLobby.png"))
	{
		std::cout << "Couldn't load chat lobby png" << std::endl;
		return false;
	}*/


	//LOBBY TEXTURES
	if (!m_NotReadyScreen.loadFromFile("Assets/Pregame/NotReady.png"))
	{
		std::cout << "Couldn't load not ready lobby png" << std::endl;
		return false;
	}

	if (!m_ReadyScreen.loadFromFile("Assets/Pregame/Ready.png"))
	{
		std::cout << "Couldn't load ready lobby png" << std::endl;
		return false;
	}

	if (!m_ConnectScreen.loadFromFile("Assets/Pregame/connectToLobby.png"))
	{
		std::cout << "Couldn't load connectToLobby png" << std::endl;
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
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		sf::Vector2f converted = window.mapPixelToCoords(mousepos);
		m_mouseRect.setPosition(converted);
		window.draw(m_sceneRect);

		if (m_quitGame)
			window.close();

		//Check Mouse rectangle with the play button
		if (m_mouseRect.getGlobalBounds().intersects(m_PlayGameButtonRect.getGlobalBounds()))
		{
			window.draw(m_SelectPlayGameButtonRect);
		}

		else
		{
			window.draw(m_PlayGameButtonRect);
		}

		//Check Mouse rectangle with the options button
		if (m_mouseRect.getGlobalBounds().intersects(m_OptionsButtonRect.getGlobalBounds()))
		{
			window.draw(m_SelectOptionsButtonRect);
		}

		else
		{
			window.draw(m_OptionsButtonRect);
		}

		//Check Mouse rectangle with the credits button
		if (m_mouseRect.getGlobalBounds().intersects(m_CreditsButtonRect.getGlobalBounds()))
		{
			window.draw(m_SelectCreditsButtonRect);
		}

		else
		{
			window.draw(m_CreditsButtonRect);
		}

		//Check Mouse rectangle with the quit button
		if (m_mouseRect.getGlobalBounds().intersects(m_QuitButtonRect.getGlobalBounds()))
		{
			window.draw(m_SelectQuitButtonRect);
		}

		else
		{
			window.draw(m_QuitButtonRect);
		}
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
		//If the player isnt connected then show only the connected screen
		if (m_playerConnected == false)
		{
			window.draw(m_ConnectRectangle);
			//window.draw(m_CollisionConnectRect);
		}

		else if (m_playerConnected == true && m_playerReady == false)
		{
			window.draw(m_NotReadyRectangle);
			//window.draw(m_SaveNameRectangle);
			//window.draw(m_NameRectangle);
		}

		else if (m_playerConnected == true && m_playerReady == true)
		{
			window.draw(m_ReadyRectangle);
		}

		//window.draw(m_CollisionReadyRectangle);
		//window.draw(m_chatLobbyRect);
		//window.draw(m_connectRect);
		//Draw Chat String
	}
	break;

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
sf::RectangleShape SceneManager::GetConnectRectangle()
{
	return m_CollisionConnectRect;
}


