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
	sf::Clock akClock;
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
	std::vector<Bullet *> Room1Bullets;
	std::vector<Bullet *> Room2Bullets;
	std::vector<Bullet *> Room3Bullets;
	std::vector<Bullet *> Room4Bullets;
	std::vector<Bullet *> Room5Bullets;
	std::vector<Bullet *> Room6Bullets;
	std::vector<Bullet *> Room7Bullets;
	std::vector<Bullet *> Room8Bullets;
	std::vector<Bullet *> Room9Bullets;
	SoundManager soundManager = SoundManager();


	//Network 
	Netcode netcode = Netcode();
	netcode.PLAYERNAME = player.GetName();

	window.setFramerateLimit(60);

	sf::Thread thread(&Netcode::ReceivePacket, &netcode);

	RandomLootManager::GetInstance()->GenerateAllRoomsLoot();
	thread.launch();
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

#pragma region PLAY GAME CASE
		case sceneManager.PLAY_GAME:
		{
			frameTime = frameClock.restart();
			// Process events 
			sf::Event Event;

			int timer = akClock.getElapsedTime().asSeconds();
			while (window.pollEvent(Event))
			{
				// Close window : exit 
				if (Event.type == sf::Event::Closed)
					window.close();

				// Escape key : exit 
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
					window.close();

				//AK
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num1))
				{
					hud.SetHighlight(1);
					player.SetWeapon(6);
				}

				//DEAGLE
				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num2))
				{
					hud.SetHighlight(2);
					player.SetWeapon(2);
				}

				//SNIPER
				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num3))
				{
					hud.SetHighlight(3);
					player.SetWeapon(3);
				}

				//MINIGUN
				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num4))
				{
					hud.SetHighlight(4);
					player.SetWeapon(4);
				}

				//TRAP
				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num5))
				{
					hud.SetHighlight(5);
					player.SetWeapon(5);
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num6))
				{
					hud.SetHighlight(6);
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num7))
				{
					player.SetHealth(false, 10);
					hud.SetHealth(player.GetHealth());
					break;
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Y))
				{
					player.IncreaseDecreaseKillingSpress(true);
					break;
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::U))
				{
					player.IncreaseDecreaseKillingSpress(false);
					break;
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::I))
				{
					player.IncreaseDeathCount();
					break;
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::O))
				{
					soundManager.PlayKillingSpreeSoundEffect(6);
					break;
				}

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
				{
					soundManager.PlayKillingSpreeSoundEffect(7);
					break;
				}


				//Key Presses for each room, creating bullets etc.
				switch (room.m_currentRoom)
				{
					#pragma region ROOM 1 KEY PRESS
					//Top Left Room
				case room.ROOM1:
				{

					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room1Bullets.push_back(b);


							}
						

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;		
								cout << "BEFORE WHILE = " << timer << endl;

									cout << "TIMER++ = " << timer << endl;
									b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
									Room1Bullets.push_back(b);
									b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
									Room1Bullets.push_back(b);
									b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
									Room1Bullets.push_back(b);
									akClock.restart();								
							
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;

#pragma endregion ROOM 1 KEY PRESS

					#pragma region ROOM 2 KEY PRESS
				case room.ROOM2:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);
						 
						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 2 KEY PRESS

					#pragma region ROOM 3 KEY PRESS
				case room.ROOM3:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 3 KEY PRESS

					#pragma region ROOM 4 KEY PRESS
				case room.ROOM4:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 4 KEY PRESS

					#pragma region ROOM 5 KEY PRESS
				case room.ROOM5:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();

						}
					}
				}break;
#pragma endregion ROOM 5 KEY PRESS

					#pragma region ROOM 6 KEY PRESS
				case room.ROOM6:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 6 KEY PRESS

					#pragma region ROOM 7 KEY PRESS
				case room.ROOM7:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 7 KEY PRESS

					#pragma region ROOM 8 KEY PRESS
				case room.ROOM8:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 8 KEY PRESS

					#pragma region ROOM 9 KEY PRESS
				case room.ROOM9:
				{
					if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
					{
						// left click...
						sf::Vector2i mousepos = sf::Mouse::getPosition(window);
						sf::Vector2f converted = window.mapPixelToCoords(mousepos);

						//SNIPER
						if (player.GetWeapon() == 3)
						{
							player.SetEnergy(true, 15);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							//Play SFX
							soundManager.PlaySniperShotSoundEffect();
						}

						//MINIGUN
						if (player.GetWeapon() == 4)
						{
							player.SetEnergy(true, 2);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}
						}

						//DEAGLE
						if (player.GetWeapon() == 2)
						{
							player.SetEnergy(true, 8);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}
						}

						//TRAP
						if (player.GetWeapon() == 5)
						{
							//If the trap is not on cool down..
							if (!player.GetTrapCoolDown())
							{
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{

								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 9 KEY PRESS
				}

					//Update visual representation
					hud.SetEnergy(player.GetEnergy());

				

				#pragma region UPDATE FOR EVERY ROOM
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
				#pragma endregion UPDATE FOR EVERY ROOM

			
			}//END KEYBOARD EVENTS

			//prepare frame
			window.clear();

			//draw frame items			
			room.Draw(window);
			player.Update(frameTime);
			hud.Draw(window);


			#pragma region CHEST + BULLET DRAW SWITCH STATEMENT
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

				for each (Bullet* bullet in Room1Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room2Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room3Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room4Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room5Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room6Bullets)
				{
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room7Bullets)
				{
					bullet->Draw(window);
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


				for each (Bullet* bullet in Room8Bullets)
				{					
					bullet->Draw(window);
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

				for each (Bullet* bullet in Room9Bullets)
				{
					bullet->Draw(window);
				}

			}
			break;
			}			

			#pragma endregion CHEST + BULLET DRAW SWITCH STATEMENT

			#pragma region DIFFERENT BULLET UPDATES
			
			//Bullets 1
			for each (Bullet* bullet in Room1Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room1Bullets.erase(std::remove(Room1Bullets.begin(), Room1Bullets.end(), bullet), Room1Bullets.end());
					delete bullet;
					std::cout << "Room 1 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 2
			for each (Bullet* bullet in Room2Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room2Bullets.erase(std::remove(Room2Bullets.begin(), Room2Bullets.end(), bullet), Room2Bullets.end());
					delete bullet;
					std::cout << " Room 2 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 3
			for each (Bullet* bullet in Room3Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room3Bullets.erase(std::remove(Room3Bullets.begin(), Room3Bullets.end(), bullet), Room3Bullets.end());
					delete bullet;
					std::cout << "Room 3 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 4
			for each (Bullet* bullet in Room4Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room4Bullets.erase(std::remove(Room4Bullets.begin(), Room4Bullets.end(), bullet), Room4Bullets.end());
					delete bullet;
					std::cout << "Room 4 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 5
			for each (Bullet* bullet in Room5Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room5Bullets.erase(std::remove(Room5Bullets.begin(), Room5Bullets.end(), bullet), Room5Bullets.end());
					delete bullet;
					std::cout << "Room 5 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 6
			for each (Bullet* bullet in Room6Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room6Bullets.erase(std::remove(Room6Bullets.begin(), Room6Bullets.end(), bullet), Room6Bullets.end());
					delete bullet;
					std::cout << "Room 6 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 7 
			for each (Bullet* bullet in Room7Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room7Bullets.erase(std::remove(Room7Bullets.begin(), Room7Bullets.end(), bullet), Room7Bullets.end());
					delete bullet;
					std::cout << "Room 7 Bullet Deleted" << std::endl;
					break;

				}
			}

			//Bullets 8
			for each (Bullet* bullet in Room8Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room8Bullets.erase(std::remove(Room8Bullets.begin(), Room8Bullets.end(), bullet), Room8Bullets.end());
					delete bullet;
					std::cout << "Room 8 Bullet Deleted" << std::endl;
					break;

				}
			}

			//BULLETS 9
			for each (Bullet* bullet in Room9Bullets)
			{
				bullet->Update(frameTime);

				if (!bullet->Alive())
				{
					Room9Bullets.erase(std::remove(Room9Bullets.begin(), Room9Bullets.end(), bullet), Room9Bullets.end());
					delete bullet;
					std::cout << "Room 9 Bullet Deleted" << std::endl;
					break;

				}
			}

			#pragma endregion DIFFERENT BULLET UPDATES

			//Check which killing spree sound effect to play

			//If true then play the sound for the amount of kills the player had.
			if (player.CheckKillSoundEffect())
			{
				soundManager.PlayKillingSpreeSoundEffect(player.GetKillingSpree());
				player.ResetKillingSpree();
			}

			if (player.CheckDeathStreakOver())
			{
				soundManager.PlayComebackKillSoundEffect();
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

			hud.countDown = player.GetTrapCoolDown();

			player.Draw(window);
			// Finally, display rendered frame on screen 
			window.display();
		}

		break;

#pragma endregion PLAY GAME CASE

#pragma region LOBBY TEXT NETCODE
		case sceneManager.LOBBY:
		{
			frameTime = frameClock.restart();

			// Process events 
			sf::Event Event;
			while (window.pollEvent(Event))
			{
				if (sceneManager.IsPlayerConnected())
				{
					//Detect when text is entered
					if (Event.type == sf::Event::TextEntered)
					{
						if (Event.text.unicode != 13 && Event.text.unicode != 8)
						{							

							if (Event.text.unicode < 128)
							{
								string charEntered;
								charEntered = static_cast<char>(Event.text.unicode);

								if (sceneManager.GetPlayerChangingName())
								{
									netcode.AddToName(charEntered);
								}			

								else
								{
									netcode.AppendChatMessage(charEntered);
								}
							}
						}

						//If the player presses Enter key
						else if (Event.text.unicode == 13)
						{
							netcode.SendPacket();
							//netcode.ResetText();
						}

						//BACK SPACE
						else if (Event.text.unicode == 8)
						{
							//If the player wants to change thir name
							if (sceneManager.GetPlayerChangingName())
							{
								if (netcode.GetName().size() > 0)
								{
									netcode.RemoveNameLetter();
								}
							}

							else
							{
								if (netcode.GetTypedMessage().size() > 0)
								{
									netcode.RemoveChatLetter();
								}
							}
						}
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

					//Only check collision with send button if the player is actually connected..
					if (sceneManager.IsPlayerConnected())
					{
						if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetSendRectangle()))
						{
							//SEND MESSAGE INTO CHAT WINDOW
							netcode.SendPacket();
							netcode.ResetText();
						}
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetConnectRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW						
						netcode.ConnectToServer(player.GetPlayerID());
						netcode.SetName(player.GetName());
					}

					//If a click is anywhere except the save name rectangle then set changing to false;
					if (!collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetNameRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW						
						sceneManager.SetPlayerChangingName(false);
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetNameRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW						
						sceneManager.SetPlayerChangingName(true);
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetSaveNameRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW						
						sceneManager.SetPlayerChangingName(false);
						netcode.SetName(netcode.GetName());
					}

					if (collisionManager.CheckRectangleCollision(mouseRect, sceneManager.GetReadyRectangle()))
					{
						//SEND MESSAGE INTO CHAT WINDOW						
						if (netcode.GetPlayerReady())
						{
							netcode.SetPlayerReady(false);
							sceneManager.SetPlayerReady(false);
							netcode.SendPlayerReady();
						}

						else
						{
							netcode.SetPlayerReady(true);
							sceneManager.SetPlayerReady(true);
							netcode.SendPlayerReady();
						}
					}

				}
			}

			//prepare frame
			window.clear();
			if (!sceneManager.IsPlayerConnected() && netcode.GetConnected())
			{
				sceneManager.SetPlayerConnected(true);
				cout << "Player has been set to connected!" << endl;
			}

			netcode.Update();
			sceneManager.Draw(window);
			netcode.Draw(window);

			// Finally, display rendered frame on screen 
			window.display();
		}
#pragma endregion LOBBY TEXT NETCODE

		break;
		}


		
	} //loop back for next frame

	return EXIT_SUCCESS;
}