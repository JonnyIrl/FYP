#include "ExtraIncludes.h"
#include "Player.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Room.h"

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

				//Check if the player collides with the play game rectangle
				if (collisionManager.CheckRectangleCollision(player.GetShape(), sceneManager.GetCollisionPlayRect()))
					sceneManager.m_currentScene = sceneManager.PLAY_GAME;


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
				room.Draw(window);				
				player.Update(frameTime);


				//1 = top door i.e player walked through the bottom door.
				if (room.CheckToGoToNextRoom(player.GetShape()))
				{
					if(room.checkDoor == 1) player.SetPosition(room.SetTopDoor());
					if(room.checkDoor == 2) player.SetPosition(room.SetBottomDoor());
					if(room.checkDoor == 3) player.SetPosition(room.SetLeftDoor());
					if(room.checkDoor == 4)player.SetPosition(room.SetRightDoor());
				}

				player.Draw(window);				


				// Finally, display rendered frame on screen 
				window.display();
			}
			
			break;
		}


		
	} //loop back for next frame

	return EXIT_SUCCESS;
}