#include "ExtraIncludes.h"
#include "Player.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Room.h"
#include "HUD.h"
#include "Bullet.h"
#include "SoundManager.h"

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "FYP");
	sf::Time frameTime;
	sf::Clock frameClock;
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//Create the Player.
	Player player = Player();
	//Create the SceneManager
	SceneManager sceneManager = SceneManager();
	//Create the Collision Manager
	CollisionManager collisionManager = CollisionManager();
	//Create the Room
	Room room = Room();
	HUD hud = HUD();
	Bullet* b;
	std::vector<Bullet *> bullets;
	SoundManager soundManager = SoundManager();

	// Start game loop 
	while (window.isOpen())
	{
		switch (sceneManager.m_currentScene)
		{
		case sceneManager.MENU:
		{
			frameTime = frameClock.restart();
			sceneManager.currentMaster = soundManager.MasterVolume();
			soundManager.PlayMenuMusic();
			//prepare frame
			window.clear();
			sceneManager.Draw(window);
			sceneManager.ChangeBackground(frameTime);
			player.Update(frameTime);
			player.Draw(window);


			//Collision Checks
			//Check the player off of the play game door
			if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetPlayRectangle()))
				sceneManager.AnimationToPlay(1);

			//Check the player off the options door
			else if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetOptionsRectangle()))
			{
				sceneManager.AnimationToPlay(2);
				sceneManager.m_currentScene = sceneManager.OPTIONS;
			}

			//Check the player off the Credits door
			else if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetCreditsRectangle()))
				sceneManager.AnimationToPlay(3);

			//Check if the player collides with the play game rectangle
			if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetCollisionPlayRect()))
				sceneManager.m_currentScene = sceneManager.PLAY_GAME;


			// Finally, display rendered frame on screen 
			window.display();
		}
		break;

		case sceneManager.OPTIONS:
		{
			frameTime = frameClock.restart();
			// Process events 
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
				{
					// left click...

					sf::Vector2i mousepos = sf::Mouse::getPosition(window);
					sf::Vector2f converted = window.mapPixelToCoords(mousepos);
					sf::RectangleShape mouseRect;
					mouseRect.setSize(sf::Vector2f(1, 1));
					mouseRect.setPosition(converted);



					//Check Collision with the SOUND EFFECTS PLUS RECTANGLE
					if (collisionManager.CheckRectangleCollision(sceneManager.GetSFXPlusRect(), mouseRect))
					{
						if (sceneManager.currentSfx != 4 && sceneManager.currentSfx < 4)
						{
							sceneManager.currentSfx++;

						}
						std::cout << "CLICKED ON THE SFX PLUS" << std::endl;
					}

					if (collisionManager.CheckRectangleCollision(sceneManager.GetSFXMinusRect(), mouseRect))
					{
						if (sceneManager.currentSfx != 1 && sceneManager.currentSfx > 0)
						{
							sceneManager.currentSfx--;
						}
						std::cout << "CLICKED ON THE SFX MINUS" << std::endl;
					}

					if (collisionManager.CheckRectangleCollision(sceneManager.GetMasterPlusRect(), mouseRect))
					{
						if (sceneManager.currentMaster != 4 && sceneManager.currentMaster < 4)
						{
							sceneManager.currentMaster++;
							soundManager.newMasterVolume = sceneManager.currentMaster;
							soundManager.CheckAudio(sceneManager.currentMaster);
						}
						std::cout << "CLICKED ON THE MASTER PLUS" << std::endl;
					}

					if (collisionManager.CheckRectangleCollision(sceneManager.GetMasterMinusRect(), mouseRect))
					{
						if (sceneManager.currentMaster != 1 && sceneManager.currentMaster > 0)
						{
							sceneManager.currentMaster--;
							soundManager.newMasterVolume = sceneManager.currentMaster;
							soundManager.CheckAudio(sceneManager.currentMaster);
						}
						std::cout << "CLICKED ON THE MASTER MINUS" << std::endl;
					}

					if (collisionManager.CheckRectangleCollision(sceneManager.GetConfirmRectangle(), mouseRect))
					{
						std::cout << "CLICKED ON THE CONFIRMED" << std::endl;
						soundManager.WriteToTextFile();
						player.SetPosition(sf::Vector2f(640, 330));
						if (soundManager.newMasterVolume != 1 || soundManager.newMasterVolume != 2 || soundManager.newMasterVolume != 3 || soundManager.newMasterVolume != 4)
						{
							soundManager.newMasterVolume = soundManager.MasterVolume();
						}
						soundManager.LoadTextFile("Assets/Settings/settings.txt");
						sceneManager.m_currentScene = sceneManager.MENU;
					}


				}
			}
			//prepare frame
			window.clear();
			sceneManager.Draw(window);
			sceneManager.ChangeBackground(frameTime);
			// Finally, display rendered frame on screen 
			window.display();
		}
		break;

		case sceneManager.PLAY_GAME:
		{
			frameTime = frameClock.restart();
			// Process events 
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				// Close window : exit 
				if (Event.type == sf::Event::Closed)
					window.close();

				// Escape key : exit 
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
					window.close();

				if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
				{
					// left click...
					sf::Vector2i mousepos = sf::Mouse::getPosition(window);
					sf::Vector2f converted = window.mapPixelToCoords(mousepos);
					b = new Bullet(sf::Vector2f(player.GetPosition().x + 25, player.GetPosition().y + 25), converted);
					bullets.push_back(b);
				}



			}

			//prepare frame
			window.clear();

			//draw frame items
			room.Draw(window);
			player.Update(frameTime);
			hud.Draw(window);


			for each (Bullet* bullet in bullets)
			{
				bullet->Update();
				bullet->Draw(window);

				if (!bullet->Alive())
				{
					bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
					delete bullet;
					std::cout << "Bullet Deleted" << std::endl;
					break;

				}
			}


			//1 = top door i.e player walked through the bottom door.
			//Used to check which room to go into next.
			if (room.CheckToGoToNextRoom(player.GetShape()))
			{
				if (room.checkDoor == 1) player.SetPosition(room.SetTopDoor());
				if (room.checkDoor == 2) player.SetPosition(room.SetBottomDoor());
				if (room.checkDoor == 3) player.SetPosition(room.SetLeftDoor());
				if (room.checkDoor == 4)player.SetPosition(room.SetRightDoor());
			}

			if (room.CheckBoundingCollisions(player.GetShape()))
			{
				//1 = top || 2 = bottom || 3 = left || 4 = right
				if (room.checkWall == 1) player.SetPosition(sf::Vector2f(player.GetPosition().x, room.SetTopWall().y));
				if (room.checkWall == 2) player.SetPosition(sf::Vector2f(player.GetPosition().x, room.SetBottomWall().y));
				if (room.checkWall == 3) player.SetPosition(sf::Vector2f(room.SetLeftWall().x, player.GetPosition().y));
				if (room.checkWall == 4) player.SetPosition(sf::Vector2f(room.SetRightWall().x, player.GetPosition().y));
			}



			player.Draw(window);
			// Finally, display rendered frame on screen 
			window.display();
		}

		break;

		case sceneManager.LOBBY:
		{
			frameTime = frameClock.restart();
			// Process events 
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				//Detect when text is entered
				if (Event.type == sf::Event::TextEntered)
				{
					if (Event.text.unicode < 128)
					{
							string charEntered;
							charEntered = static_cast<char>(Event.text.unicode);
							sceneManager.SetChatMessage(charEntered);				
					}
				}

				// Close window : exit 
				if (Event.type == sf::Event::Closed)
					window.close();

				// Escape key : exit 
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
					window.close();

				//If the player presses enter send the message
				if (Event.key.code == sf::Keyboard::Return)
				{
					sceneManager.ResetText();
				}

				if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
				{
					// left click...
					sf::Vector2i mousepos = sf::Mouse::getPosition(window);
					sf::Vector2f converted = window.mapPixelToCoords(mousepos);
					sf::RectangleShape mouseRect;
					mouseRect.setSize(sf::Vector2f(1, 1));
					mouseRect.setPosition(converted);

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetSendRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW
						sceneManager.SendPacket();
						sceneManager.ResetText();						
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetConnectRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW
						sceneManager.ConnectToServer();
					}
				}
			}

			//prepare frame
			window.clear();

			sceneManager.Draw(window);

			// Finally, display rendered frame on screen 
			window.display();
		}

		break;
		}


		
	} //loop back for next frame

	return EXIT_SUCCESS;
}