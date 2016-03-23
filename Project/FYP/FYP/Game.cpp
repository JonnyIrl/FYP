#include "ExtraIncludes.h"
#include "Player.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Room.h"
#include "HUD.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "Netcode.h"
#include "RandomLootManager.h"
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

	//Network 
	Netcode netcode = Netcode();
	netcode.PLAYERNAME = player.GetName();
	window.setFramerateLimit(60);

	RandomLootManager::GetInstance()->GenerateAllRoomsLoot();
	//Chest chest = Chest(sf::Vector2f(300, 300), 3);
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
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				sceneManager.ChangeBackground(Event, frameTime);
			}

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
			sceneManager.ChangeBackground(Event,frameTime);
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

					//SNIPER
					if (player.GetWeapon() == 3)
					{
						
						if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
						{
							b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
							bullets.push_back(b);
						}

						else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
						{
							b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
							bullets.push_back(b);
						}
					}

					//MINIGUN
					if (player.GetWeapon() == 4)
					{

						if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
						{
							b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
							bullets.push_back(b);
						}

						else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
						{
							b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
							bullets.push_back(b);
						}
					}
				}


				switch (room.m_currentRoom)
				{
					//Top Left Room
				case room.ROOM1:
				{

					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 0; i < 2; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}
				}
				break;

				//Top Middle Room
				case room.ROOM2:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 2; i < 4; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}
				}
				break;

				//Top Right Room
				case room.ROOM3:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 4; i < 6; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}
				}
				break;

				//Middle Left Room
				case room.ROOM4:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 6; i < 8; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}				
				}
				break;

				//Middle Room
				case room.ROOM5:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 8; i < 10; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}

				}
				break;

				//Middle Right Room
				case room.ROOM6:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 10; i < 12; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}

				}
				break;

				//Bottom Left Room
				case room.ROOM7:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 12; i < 14; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}

					}

				}
				break;

				//Bottom Middle Room
				case room.ROOM8:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 14; i < 16; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}

				}
				break;

				//Bottom Right Room
				case room.ROOM9:
				{
					if (Event.key.code == sf::Keyboard::E)
					{
						for (int i = 16; i < 18; i++)
						{
							if (RandomLootManager::GetInstance()->randomChests.at(i)->CheckInRange(player.GetShape()))
							{
								if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsActivated())
								{
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}
					}

				}
				break;
				}
			
			}//END KEYBOARD EVENTS

			//prepare frame
			window.clear();

			//draw frame items			
			room.Draw(window);
			//RandomLootManager::GetInstance()->Draw(window);
			//RandomLootManager::GetInstance()->Update(frameTime);
			player.Update(frameTime);
			hud.Draw(window);

			switch (room.m_currentRoom)
			{
				//Top Left Room
			case room.ROOM1:
			{
				for (int i = 0; i < 2; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}
			}
			break;

			//Top Middle Room
			case room.ROOM2:
			{
				for (int i = 2; i < 4; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}
			}
			break;

			//Top Right Room
			case room.ROOM3:
			{
				for (int i = 4; i < 6; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}
			}
			break;

			//Middle Left Room
			case room.ROOM4:
			{
				for (int i = 6; i < 8; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;

			//Middle Room
			case room.ROOM5:
			{
				for (int i = 8; i < 10; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;

			//Middle Right Room
			case room.ROOM6:
			{
				for (int i = 10; i < 12; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;

			//Bottom Left Room
			case room.ROOM7:
			{
				for (int i = 12; i < 14; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;

			//Bottom Middle Room
			case room.ROOM8:
			{
				for (int i = 14; i < 16; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;

			//Bottom Right Room
			case room.ROOM9:
			{
				for (int i = 16; i < 18; i++)
				{
					RandomLootManager::GetInstance()->randomChests.at(i)->Draw(window);
					RandomLootManager::GetInstance()->randomChests.at(i)->Update(frameTime);
				}

			}
			break;
			}


			for each (Bullet* bullet in bullets)
			{
				bullet->Update(frameTime);
				bullet->Draw(window);

				if (!bullet->Alive())
				{
					bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
					delete bullet;
					std::cout << "Bullet Deleted" << std::endl;
					break;

				}
			}

			if (room.CheckBoundingCollisions(player.GetShape()))
			{
				//1 = top || 2 = bottom || 3 = left || 4 = right
				if (room.checkWall == 1) player.SetPosition(sf::Vector2f(player.GetPosition().x, room.SetTopWall().y));
				if (room.checkWall == 2) player.SetPosition(sf::Vector2f(player.GetPosition().x, room.SetBottomWall().y));
				if (room.checkWall == 3) player.SetPosition(sf::Vector2f(room.SetLeftWall().x, player.GetPosition().y));
				if (room.checkWall == 4) player.SetPosition(sf::Vector2f(room.SetRightWall().x, player.GetPosition().y));
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


			//chest.Draw(window);
			//chest.Update(frameTime);


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
					if (Event.text.unicode != 13)
					{
						if (Event.text.unicode < 128)
						{
							string charEntered;
							charEntered = static_cast<char>(Event.text.unicode);
							netcode.SetChatMessage(charEntered);
						}
					}

					//If the player presses Enter key
					else if (Event.text.unicode == 13)
					{
						netcode.SendPacket();
						netcode.ResetText();
					}
				}

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
					sf::RectangleShape mouseRect;
					mouseRect.setSize(sf::Vector2f(1, 1));
					mouseRect.setPosition(converted);

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetSendRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW
						netcode.SendPacket();
						netcode.ResetText();
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetConnectRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW
						netcode.ConnectToServer();
					}
				}
			}

			//prepare frame
			window.clear();

			netcode.Update();
			sceneManager.Draw(window);
			netcode.Draw(window);

			// Finally, display rendered frame on screen 
			window.display();
		}

		break;
		}


		
	} //loop back for next frame

	return EXIT_SUCCESS;
}