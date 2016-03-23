#include "Chest.h"

Chest::Chest()
{

}

Chest::Chest(sf::Vector2f position, int randomItem, int roomNumber)
{
	if (LoadTexture())
	{
		m_position = position;

		//Set Sprite Sheet
		m_chestOpeningAnimation.setSpriteSheet(m_chestTexture);
		AddAnimationFrames();

		//Assign the Animated Sprite
		m_chestAnimation = AnimatedSprite(sf::seconds(0.03f));
		m_chestAnimation.setAnimation(m_chestOpeningAnimation);
		m_chestAnimation.setLooped(false);
		m_chestAnimation.setPosition(m_position);
		m_chestAnimation.setAnimation(m_chestOpeningAnimation);

		//Assign the rectangle
		m_chestRectangle.setSize(sf::Vector2f(42, 42));
		m_chestRectangle.setPosition(sf::Vector2f(m_position.x - 5, m_position.y - 5));
		//m_chestRectangle.setTexture(&m_chestTexture);

		m_isActivated = m_isOpen = m_isItemTaken = false;
		AssignRandomItem(randomItem);

		//Assign the display rectangle
		m_displayWindowRectangle.setSize(sf::Vector2f(40, 40));
		m_displayWindowRectangle.setPosition(sf::Vector2f(m_position.x - 4, m_position.y - 44));
		m_displayWindowRectangle.setTexture(&m_itemTexture);

		m_chestRoomNumber = roomNumber;
	}
}

bool Chest::AssignRandomItem(int randNumber)
{
	if (randNumber == 1 || randNumber == 2)
	{
		
		if (!m_AK47Texture.loadFromFile("Assets/Chest/ak47.png"))
		{
			std::cout << "Failed to load ak47 sprite" << std::endl;		
			return false;
		}

		else
		{
			m_itemWeapon = AK;
			m_itemTexture = m_AK47Texture;
			return true;
		}

	}

	else if (randNumber == 3 || randNumber == 4)
	{
		if (!m_DEAGLETexture.loadFromFile("Assets/Chest/deagle.png"))
		{
			std::cout << "Failed to load deagle sprite" << std::endl;
			return false;
		}

		else
		{
			m_itemWeapon = DEAGLE;
			m_itemTexture = m_DEAGLETexture;
			return true;
		}
	}

	else if (randNumber == 5 || randNumber == 6)
	{
		if (!m_SNIPERTexture.loadFromFile("Assets/Chest/sniper.png"))
		{
			std::cout << "Failed to load sniper sprite" << std::endl;
			return false;
		}

		else
		{
			m_itemWeapon = SNIPER;
			m_itemTexture = m_SNIPERTexture;
			return true;
		}
	}

	else if (randNumber == 7 || randNumber == 8)
	{
		if (!m_TRAPTexture.loadFromFile("Assets/Chest/trap.png"))
		{
			std::cout << "Failed to load trap sprite" << std::endl;
			return false;
		}

		else
		{
			m_itemWeapon = TRAP;
			m_itemTexture = m_TRAPTexture;
			return true;
		}
	}

	else if (randNumber == 8 || randNumber == 9)
	{
		if (!m_BOMBTexture.loadFromFile("Assets/Chest/bomb.png"))
		{
			std::cout << "Failed to load bomb sprite" << std::endl;
			return false;
		}

		else
		{
			m_itemWeapon = BOMB;
			m_itemTexture = m_BOMBTexture;
			return true;
		}
	}

	else if (randNumber == 10)
	{
		if (!m_MINIGUNTexture.loadFromFile("Assets/Chest/minigun.png"))
		{
			std::cout << "Failed to load minigun sprite" << std::endl;
			return false;
		}

		else
		{
			m_itemWeapon = MINIGUN;
			m_itemTexture = m_MINIGUNTexture;
			return true;
		}
	}
}

void Chest::AddAnimationFrames()
{
	//Using width and height makes changing images sizes easy
	int width = 32; int height = 32;

	//Add the 9 frames
	m_chestOpeningAnimation.addFrame(sf::IntRect(0, 0, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width, 0, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width * 2, 0, width, height));

	m_chestOpeningAnimation.addFrame(sf::IntRect(0, height, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width, height, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width * 2, height, width, height));

	m_chestOpeningAnimation.addFrame(sf::IntRect(0, height * 2, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width, height * 2, width, height));
	m_chestOpeningAnimation.addFrame(sf::IntRect(width * 2, height * 2, width, height));
}

void Chest::Update(sf::Time time)
{
	//If its activated but not open (i.e when to play the animation)
	if (IsActivated() && !IsOpen())
	{		
		m_chestAnimation.update(time);

		if (!m_chestAnimation.isPlaying())
		{
			m_isOpen = true;
			m_chestAnimation.setFrame(size_t(8));
		}
	}

	
}

bool Chest::CheckInRange(sf::RectangleShape &playerRect)
{
	if (m_chestRectangle.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
	{
		return true;
	}

	else
		return false;
}

void Chest::Draw(sf::RenderWindow &window)
{
	window.draw(m_chestAnimation);

	if (IsOpen() && !m_isItemTaken)
	{
		window.draw(m_displayWindowRectangle);
	}
}

bool Chest::LoadTexture()
{
	if (!m_chestTexture.loadFromFile("Assets/Chest/chest.png"))
	{
		std::cout << "Failed to load chest sprite" << std::endl;
		return false;
	}
	else
		return true;
}

Chest::~Chest()
{
}