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
#include <assert.h>
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
void Analyze(char *, int);


int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "FYP");
	sf::Time frameTime;
	sf::Clock frameClock;
	sf::Clock akClock;
	sf::Clock summonClock;
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
			if (!hud.initScoreBoard)
			{
				vector<pair<string, int>> result = netcode.GetScores();
				hud.SetScore(result, player.GetName(), player.GetScore());
				hud.initScoreBoard = true;
			}

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

				else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Tab))
				{
					if (!hud.showScore)
					{
						hud.showScore = true;
					}

					else
					{
						hud.showScore = false;
					}
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//netcode.SendNewBullet(converted, player.GetWeapon());
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
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

								netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//netcode.SendNewBullet(converted, player.GetWeapon());
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room2Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//netcode.SendNewBullet(converted, player.GetWeapon());
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room3Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//netcode.SendNewBullet(converted, player.GetWeapon());
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room4Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room5Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room6Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								//player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room7Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								/*netcode.SendNewBullet(converted, player.GetWeapon());
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));*/
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);


							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room8Bullets.push_back(b);
								akClock.restart();

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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
							netcode.SendNewBullet(converted, player.GetWeapon());
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
								/*netcode.SendNewBullet(converted, player.GetWeapon());
								player.AddNewTrap(sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 10));*/
								player.SetTrapCoolDown(true);
							}
						}

						//AK
						if (player.GetWeapon() == 6)
						{
							player.SetEnergy(true, 4);
							if (converted.x > player.GetPosition().x && converted.y > player.GetPosition().y || converted.x > player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								netcode.SendNewBullet(converted, player.GetWeapon());
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 4, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
							}


							else if (converted.x < player.GetPosition().x && converted.y > player.GetPosition().y || converted.x < player.GetPosition().x && converted.y < player.GetPosition().y)
							{
								int countDown = 0;
								int timer = 0;
								//cout << "BEFORE WHILE = " << timer << endl;

								netcode.SendNewBullet(converted, player.GetWeapon());
								//cout << "TIMER++ = " << timer << endl;
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 22, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
								b = new Bullet(sf::Vector2f(player.GetPosition().x - 18, player.GetPosition().y + 28), converted, player.GetWeapon());
								Room9Bullets.push_back(b);
								akClock.restart();

							}

							soundManager.PlayAKShotSoundEffect();
						}
					}
				}break;
#pragma endregion ROOM 9 KEY PRESS
				}

					//Update visual representation
					hud.SetEnergy(player.GetEnergy());

					if (Event.type == sf::Event::KeyPressed)
					{
						if (Event.key.code != sf::Keyboard::E && room.IsSummoning())
						{
							room.SetSummoning(false);
							room.SetTimer(4);
						}
					}


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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);

								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
										cout << "ITEM TAKEN = " << RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon() << endl;
										RandomLootManager::GetInstance()->randomChests.at(i)->SetItemTaken(true);
									}


								}
							}
						}

						//If the player is pressing "E"
						if (collisionManager.CheckRectangleCollision(room.GetInteractingRock(), player.GetShape()))
						{

							//Set the player to summoning a new skill
							room.SetSummoning(true);

							//Place rectangle above players head
							room.SetSummoningRectSize(player.GetPosition());
							cout << "Set new rectangle" << endl;
						}

						else
						{
							room.SetSummoning(false);
							room.SetTimer(4);
						}


					}


					if (player.IsMoving())
					{
						room.SetSummoning(false);
						room.SetTimer(4);
					}

					if (room.FinishedSummoning())
					{		
						int powerup = rand() % 3 + 1;

						player.ResetPowerUps();

						//Speed Up
						if (powerup == 1)
						{
							player.FAST_MOVEMENT = true;
							cout << "SPEED UP " << endl;
						}

						else if (powerup == 2)
						{
							player.FAST_MOVEMENT = true;
							cout << "SPEED UP " << endl;
						}

						else if (powerup == 3)
						{
							player.EXTRA_LIFE = true;
							cout << "EXTRA_LIFE " << endl;
						}

						room.SetSummoning(false);
						room.SetTimer(4);
						cout << "COUNTDOWN FINISHED" << endl;
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
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
									netcode.SendChestOpenUpdate(i);
									RandomLootManager::GetInstance()->randomChests.at(i)->SetActived(true);
								}

								else
								{
									if (!RandomLootManager::GetInstance()->randomChests.at(i)->IsItemTaken() && RandomLootManager::GetInstance()->randomChests.at(i)->IsOpen())
									{
										//assign the player the new weapon
										netcode.SendChestItemTakenUpdate(i);
										player.SetWeapon(RandomLootManager::GetInstance()->randomChests.at(i)->GetWeapon());
										hud.SetHighlight(hud.FindHighlight(player.GetWeapon()));
										hud.SetHighlight(player.GetWeapon());
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

			if (player.GetHealth() <= 0)
			{
				sf::Vector2f newPos = player.Respawn();
				if (player.GetHealth() != 100)
				{
					player.SetHealth(true, 100);
				}
				player.ResetPowerUps();
				netcode.m_killingspree = 0;
				player.ResetKillingSpree();
				player.IncreaseDeathCount();
				hud.SetHealth(player.GetHealth());
				player.SetRespawned(false);
				cout << "After Respawn room = " << player.GetRoom() << endl;
				netcode.SendRespawnMessage(newPos, player.GetRoom());
				cout << "After Sending Respawn room = " << player.GetRoom() << endl;
				hud.SetHealth(player.GetHealth());
				cout << "Before setting room = " << player.GetRoom() << endl;
				room.m_currentRoom = player.GetRoom();
			}


			netcode.pm.Update(frameTime);

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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room1Bullets.size(); j++)// at(i)->Room3Bullets)
					{
						if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->Alive())
						netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->Draw(window);
					}
				}

				netcode.pm.Draw1(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room2Bullets.size(); j++)// at(i)->Room3Bullets)
						{
								if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw2(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room3Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw3(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room4Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw4(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room5Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw5(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room6Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw6(window);

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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room7Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw7(window);

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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room8Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->Draw(window);							
						}
				}

				netcode.pm.Draw8(window);
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

				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room9Bullets.size(); j++)// at(i)->Room3Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->Alive())
								netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->Draw(window);						
						}
				}

				netcode.pm.Draw9(window);

			}
			break;
			}			

			#pragma endregion CHEST + BULLET DRAW SWITCH STATEMENT

			hud.Draw(window);

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

			//Multiplayer Bullets 1
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room1Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room1Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room1Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room1Bullets.end(), netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room1Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room2Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 2
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room2Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room2Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room2Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room2Bullets.end(), netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room2Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room2Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 3
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room3Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room3Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room3Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room3Bullets.end(), netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room3Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room3Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 4
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room4Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room4Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room4Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room4Bullets.end(), netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room4Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room3Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 5
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room5Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room5Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room5Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room5Bullets.end(), netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room5Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room3Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 6
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room6Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room6Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room6Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room6Bullets.end(), netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room6Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room6Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 7
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room7Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room7Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room7Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room7Bullets.end(), netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room7Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room7Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 8
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room8Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room8Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room8Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room8Bullets.end(), netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room8Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room8Bullets Deleted" << std::endl;
						break;

					}
				}
			}

			//Multiplayer Bullets 9
			for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
			{
				for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room9Bullets.size(); j++)// at(i)->Room3Bullets)
				{
					netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->Update(frameTime);

					if (!netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->Alive())
					{
						netcode.pm.GetPlayers().at(i)->Room9Bullets.erase(std::remove(netcode.pm.GetPlayers().at(i)->Room9Bullets.begin(), netcode.pm.GetPlayers().at(i)->Room9Bullets.end(), netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)), netcode.pm.GetPlayers().at(i)->Room9Bullets.end());
						//delete netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j);
						std::cout << "Room9Bullets Deleted" << std::endl;
						break;

					}
				}
			}

#pragma endregion DIFFERENT BULLET UPDATES


#pragma region Colllisions in Room 1

			if (player.GetRoom() == 0)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 0)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room1Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}


						//Check Players Collision with the multiplayers
						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room1Bullets.size(); j++)
						{
							if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}

										else
										{
											player.SetHealth(false, 40);
										}
										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}

										else
										{
											player.SetHealth(false, 15);
										}
										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}

										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room1Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end bullet alive if

						}//end if
					}
				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room1Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room1Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room1Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room1Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room1Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room1Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room1Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room1Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room1Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room1Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room1Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room1Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room1Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room1Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room1Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if


#pragma endregion Colllisions in Room 1

#pragma region Colllisions in Room 2

			if (player.GetRoom() == 1)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 1)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room2Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room2Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room2Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end bullet alive

						}//end for

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room2Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room2Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room2Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room2Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room2Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room2Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room2Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room2Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room2Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room2Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room2Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room2Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room2Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room2Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room2Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if

#pragma endregion Colllisions in Room 2
			
#pragma region Colllisions in Room 3

			if (player.GetRoom() == 2)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 2)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room3Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room3Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room3Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//bullet alive if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room3Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room3Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room3Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room3Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room3Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room3Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room3Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room3Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room3Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room3Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room3Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room3Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room3Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room3Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room3Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if

#pragma endregion Colllisions in Room 3

#pragma region Colllisions in Room 4

			if (player.GetRoom() == 3)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 3)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room4Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room4Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room4Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room4Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room4Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room4Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room4Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room4Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room4Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room4Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room4Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room4Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room4Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room4Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room4Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room4Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room4Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room4Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************


			}//end if

#pragma endregion Colllisions in Room 4

#pragma region Colllisions in Room 5
		
			if (player.GetRoom() == 4)
			{

				if (room.CheckStatueCollision(player.GetShape()))
				{
					//Collided with top rectangle
					if (room.checkStatue == 1)
					{
						player.SetPosition(sf::Vector2f(player.GetPosition().x, room.GetSummonerRectangleTop().getPosition().y - player.GetShape().getGlobalBounds().height));
						cout << "Collided with the top wall" << endl;
					}

					//Collided with bot rectangle
					if (room.checkStatue == 2)
					{
						player.SetPosition(sf::Vector2f(player.GetPosition().x, room.GetSummonerRectangleBot().getPosition().y + room.GetSummonerRectangleBot().getGlobalBounds().height));
						cout << "Collided with the bot wall" << endl;
					}

					//Collided with left rectangle
					if (room.checkStatue == 3)
					{
						player.SetPosition(sf::Vector2f(room.GetSummonerRectangleLeft().getPosition().x - player.GetShape().getGlobalBounds().width, player.GetPosition().y));
						cout << "Collided with the left wall" << endl;
					}

					//Collided with right rectangle
					if (room.checkStatue == 4)
					{
						player.SetPosition(sf::Vector2f(room.GetSummonerRectangleRight().getPosition().x + room.GetSummonerRectangleRight().getGlobalBounds().width, player.GetPosition().y));
						cout << "Collided with the right wall" << endl;
					}
				}


				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 4)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room5Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room5Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{

							if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room5Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room5Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room5Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room5Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room5Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room5Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room5Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room5Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room5Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room5Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room5Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room5Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room5Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room5Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room5Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room5Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if

#pragma endregion Colllisions in Room 5

#pragma region Colllisions in Room 6

			if (player.GetRoom() == 5)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 5)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room6Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room6Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);
										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room6Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room6Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room6Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room6Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room6Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room6Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room6Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room6Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room6Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room6Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room6Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room6Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room6Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room6Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room6Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room6Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if

#pragma endregion Colllisions in Room 6

#pragma region Colllisions in Room 7

			if (player.GetRoom() == 6)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 6)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room7Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room7Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room7Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for
				
				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room7Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room7Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room7Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room7Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room7Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room7Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room7Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room7Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room7Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room7Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room7Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room7Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room7Bullets.at(k)->Alive())
									{
										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room7Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room7Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************


			}//end if

#pragma endregion Colllisions in Room 7

#pragma region Colllisions in Room 8

			if (player.GetRoom() == 7)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 7)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room8Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room8Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room8Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room8Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room8Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room8Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room8Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room8Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room8Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room8Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room8Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room8Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room8Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room8Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room8Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room8Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room8Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room8Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************

			}//end if

#pragma endregion Colllisions in Room 8

#pragma region Colllisions in Room 9

			if (player.GetRoom() == 8)
			{
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					if (netcode.pm.GetPlayers().at(i)->GetRoomNumber() == 8)
					{
						//Check players bullet vs the enemy players
						for each (Bullet* b in Room9Bullets)
						{
							if (collisionManager.CheckRectangleCollision(b->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape()))
							{
								b->SetAliveFalse();
								cout << "Hit enemy" << endl;
								break;
							}
						}

						for (int j = 0; j < netcode.pm.GetPlayers().at(i)->Room9Bullets.size(); j++)//(Bullet* b in netcode.pm.GetPlayers().at(i)->Room1Bullets)
						{
							if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->Alive())
							{
								//If the player is colliding with the other players bullet..
								if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->GetShape(), player.GetShape()))
								{
									//Reduce the players health
									//SNIPER
									if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->GetWeapon() == 3)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 20);
										}
										else
										player.SetHealth(false, 40);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->SetAliveFalse();
										break;
									}

									//AK
									else if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->GetWeapon() == 6)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 10);
										}
										else
										player.SetHealth(false, 15);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Deagle
									else if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->GetWeapon() == 2)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 15);
										}
										else
										player.SetHealth(false, 25);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->SetAliveFalse();
										break;
									}

									//Minigun
									else if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->GetWeapon() == 4)
									{
										if (player.EXTRA_LIFE)
										{
											player.SetHealth(false, 5);
										}
										else
										player.SetHealth(false, 10);

										hud.SetHealth(player.GetHealth());
										if (player.GetHealth() <= 0)
										{
											netcode.SendKillConfirmed(netcode.pm.GetPlayers().at(i)->GetPlayerID());
										}
										netcode.pm.GetPlayers().at(i)->Room9Bullets.at(j)->SetAliveFalse();
										break;
									}

								}//end if

							}//end for

						}//end bullet if

					}//end if

				}//end for

				//**************************** MULTIPLAYER COLLISIONS ********************
				//Collision that checks between the multiplayer and the other multiplayer
				//CHECK I AGAINST J
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room9Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room9Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(0)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

						else
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(i)->Room9Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(i)->Room9Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(j)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(i)->Room9Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}

					}
				}

				//CHECK J AGAINST I
				for (int i = 0; i < netcode.pm.GetPlayers().size(); i++)
				{
					for (int j = 1; j < netcode.pm.GetPlayers().size(); j++)
					{
						if (i == netcode.pm.GetPlayers().size() - 1)
						{
							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room9Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(0)->Room9Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(0)->Room9Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(0)->Room9Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(0)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(0)->Room9Bullets.at(k)->SetAliveFalse();
										}
									}
								}
							}
						}

						else
						{

							for (int k = 0; k < netcode.pm.GetPlayers().at(j)->Room9Bullets.size(); k++)
							{
								//Check the bullet is alive first to stop vector issues
								//Check Player I'S Bullets K's off of player J's body
								if (netcode.pm.GetPlayers().at(j)->Room9Bullets.size() > 0)
								{
									if (netcode.pm.GetPlayers().at(j)->Room9Bullets.at(k)->Alive())
									{

										if (collisionManager.CheckRectangleCollision(netcode.pm.GetPlayers().at(j)->Room9Bullets.at(k)->GetShape(), netcode.pm.GetPlayers().at(i)->GetShape())
											&& netcode.pm.GetPlayers().at(j)->GetRoom() == netcode.pm.GetPlayers().at(i)->GetRoom())
										{
											netcode.pm.GetPlayers().at(j)->Room9Bullets.at(k)->SetAliveFalse();
										}
									}
								}

							}
						}
					}
				}
				//**********************************************************************************************


			}//end if

#pragma endregion Colllisions in Room 9

			//Check to update the scores
			if (netcode.UpdateScore())
			{
				player.SetScore(netcode.GetScore());
				vector<pair<string, int>> result = netcode.GetScores();
				hud.SetScore(result, player.GetName(), player.GetScore());
				netcode.SetUpdateScore(false);
				player.SetKillingSpree(netcode.m_killingspree);
				cout << "Updated Scores!!" << endl;
			}

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

#pragma region CheckToGoToNextRoom

			//1 = top door i.e player walked through the bottom door.
			//Used to check which room to go into next.
			if (room.CheckToGoToNextRoom(player.GetShape()))
			{
				if (room.checkDoor == 1)
				{
					player.SetPosition(room.SetTopDoor());					
				}
				if (room.checkDoor == 2)
				{
					player.SetPosition(room.SetBottomDoor());
				}
				if (room.checkDoor == 3) 
				{
					player.SetPosition(room.SetLeftDoor());
				}

				if (room.checkDoor == 4)
				{
					player.SetPosition(room.SetRightDoor());
				}
			
				player.SetRoom(room.m_currentRoom);
				netcode.SendRoomUpdate(room.m_currentRoom);
			}

#pragma endregion CheckToGoToNextRoom

			//Check if the player has moved...
			if (player.IsMoving())
			{
				if (!room.CheckBoundingCollisions(player.GetShape()))
				{
					netcode.SendPlayersPosition(player.GetPosition(), player.GetDirection());
					player.SetMovingFalse();
				}
			}


			if (netcode.m_chestOpenUpdate)
			{
				RandomLootManager::GetInstance()->randomChests.at(netcode.chestIndex)->SetActived(true);
				netcode.chestIndex = 0;
				netcode.m_chestOpenUpdate = false;
			}

			if (netcode.m_checkItemTakenUpdate)
			{
				RandomLootManager::GetInstance()->randomChests.at(netcode.chestIndex)->SetItemTaken(true);
				netcode.chestIndex = 0;
				netcode.m_checkItemTakenUpdate = false;
			}

			if (netcode.m_checkGameOver)
			{
				hud.initScoreBoard = false;
				sceneManager.m_currentScene = sceneManager.GAME_OVER;
				hud.initScoreBoard = false;
				netcode.m_checkGameOver = false;
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
						if (sceneManager.IsPlayerConnected())
						{
							netcode.SetName(player.GetName());
						}
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

					//Check if the chest update is true
					if (netcode.ChestUpdate())
					{
						//Pass all 3 vectors to the random loot manager
						RandomLootManager::GetInstance()->GenerateAllRoomsLoot(netcode.m_Xpositions, netcode.m_Ypositions, netcode.m_lootType);
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


			//Check if all the players are ready... then start the game
			if (netcode.CheckPlayersAllReady())
			{
				netcode.SendGameStarted();
				sceneManager.m_currentScene = sceneManager.PLAY_GAME;
			}

			netcode.Update();
			sceneManager.Draw(window);
			netcode.Draw1(window, sceneManager.IsPlayerConnected());

			// Finally, display rendered frame on screen 
			window.display();
		}
#pragma endregion LOBBY TEXT NETCODE
		break;
		

		case sceneManager.GAME_OVER:
		{

			sf::Event Event;
			while (window.pollEvent(Event))
			{
				// Close window : exit 
				if (Event.type == sf::Event::Closed)
					window.close();

				// Escape key : exit 
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
					window.close();

			}

			if (!hud.initScoreBoard)
			{
				vector<pair<string, int>> result = netcode.GetScores();
				hud.SetScore(result, player.GetName(), player.GetScore());
				hud.initScoreBoard = true;
			}

			hud.gameOver = true;
			//prepare frame
			window.clear();

			hud.showScore = true;
			hud.Draw(window);

			// Finally, display rendered frame on screen 
			window.display();
		}
		break;


		case sceneManager.TUTORIAL:
		{
			frameTime = frameClock.restart();
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
					sf::Vector2i mousepos = sf::Mouse::getPosition(window);
					sf::Vector2f converted = window.mapPixelToCoords(mousepos);
					sf::RectangleShape mouseRect;
					mouseRect.setSize(sf::Vector2f(1, 1));
					mouseRect.setPosition(converted);

					if (collisionManager.CheckRectangleCollision(sceneManager.backRectangle, mouseRect))
					{
						sceneManager.tutorialPage--;
						std::cout << "CLICKED ON THE back button" << std::endl;
						
					}

					if (collisionManager.CheckRectangleCollision(sceneManager.nextRectangle, mouseRect))
					{
						sceneManager.tutorialPage++;
						cout << "Count = " << sceneManager.tutorialPage << endl;
						std::cout << "CLICKED ON THE next button" << std::endl;
						break;
					}
					
				}

			}



			if (sceneManager.tutorialPage >= 8)
				sceneManager.m_currentScene = sceneManager.MENU;

			if (sceneManager.tutorialPage <= 0)
				sceneManager.m_currentScene = sceneManager.MENU;

			sf::Vector2i mousepos = sf::Mouse::getPosition(window);
			sf::Vector2f converted = window.mapPixelToCoords(mousepos);
			sf::RectangleShape mouseRect;
			mouseRect.setSize(sf::Vector2f(1, 1));
			mouseRect.setPosition(converted);



			//Check Collision with the NEXT RECTANGLE
			if (collisionManager.CheckRectangleCollision(sceneManager.nextRectangle, mouseRect))
			{
				if (sceneManager.nextRectangle.getTexture() != &sceneManager.selectNextTexture)
				{
					sceneManager.nextRectangle.setTexture(&sceneManager.selectNextTexture);
				}
			}

			else
			{
				if (sceneManager.nextRectangle.getTexture() != &sceneManager.nextTexture)
				{
					sceneManager.nextRectangle.setTexture(&sceneManager.nextTexture);
				}
			}

			if (collisionManager.CheckRectangleCollision(sceneManager.backRectangle, mouseRect))
			{
				if (sceneManager.backRectangle.getTexture() != &sceneManager.selectBackTexture)
				{
					sceneManager.backRectangle.setTexture(&sceneManager.selectBackTexture);
				}
			}

			else
			{
				if (sceneManager.backRectangle.getTexture() != &sceneManager.backTexture)
				{
					sceneManager.backRectangle.setTexture(&sceneManager.backTexture);
				}
			}

			//prepare frame
			window.clear();


			sceneManager.ChangeBackground(Event, frameTime);
			sceneManager.Draw(window);

			// Finally, display rendered frame on screen 
			window.display();
		}
		break;

	} //loop back for next frame
	}
	return EXIT_SUCCESS;
}


void Analyze(char *string, int length)
{
	assert(string != NULL);     /* cannot be NULL */
	assert(*string != '\0');    /* cannot be empty */
	assert(length > 0);         /* must be positive */
}