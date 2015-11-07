#include "ExtraIncludes.h"
#include "Player.h"
#include "SceneManager.h"
#include "CollisionManager.h"

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
	


	// Start game loop 
	while (window.isOpen())
	{
		switch (sceneManager.m_currentScene)
		{
			case sceneManager.MENU:
			{
				frameTime = frameClock.restart();
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
					sceneManager.AnimationToPlay(2);

				//Check the player off the Credits door
				else if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetCreditsRectangle()))
					sceneManager.AnimationToPlay(3);


				// Finally, display rendered frame on screen 
				window.display();
			}
			break;

			case sceneManager.OPTIONS:
			{

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


				}

				//prepare frame
				window.clear();

				//draw frame items
				player.Update(frameTime);
				player.Draw(window);


				// Finally, display rendered frame on screen 
				window.display();
			}
			
			break;
		}


		
	} //loop back for next frame

	return EXIT_SUCCESS;
}