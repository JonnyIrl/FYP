#include "ExtraIncludes.h"
#include "Player.h"

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "FYP");
	sf::Time frameTime;
	sf::Clock frameClock;
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//Create the Player.
	Player player = Player();


	// Start game loop 
	while (window.isOpen())
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
	} //loop back for next frame

	return EXIT_SUCCESS;
}