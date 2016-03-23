#include "Player.h"


Player::Player()
{
	m_position = sf::Vector2f(500, 500);
	m_rect.setSize(sf::Vector2f(46, 50));
	m_rect.setPosition(m_position);
	m_moving = false;

	//Load in the textures, and assign them to each animation.
	if (LoadTexture())
	{
		m_playerDownAnimation.setSpriteSheet(m_pDownTexture);
		m_playerDownAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerDownAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerDownAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerUpAnimation.setSpriteSheet(m_pUpTexture);
		m_playerUpAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerUpAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerUpAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerRightAnimation.setSpriteSheet(m_pRightTexture);
		m_playerRightAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerRightAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerRightAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerLeftAnimation.setSpriteSheet(m_pLeftTexture);
		m_playerLeftAnimation.addFrame(sf::IntRect(0, 0, 46, 50));
		m_playerLeftAnimation.addFrame(sf::IntRect(46, 0, 46, 50));
		m_playerLeftAnimation.addFrame(sf::IntRect(92, 0, 46, 50));

		m_playerAnimation = AnimatedSprite(sf::seconds(0.15f));
		m_playerAnimation.setAnimation(m_playerDownAnimation);

		LoadTextFile("Assets/Settings/name.txt");
		if (m_Name.size() <= 0)
		{
			m_Name = "PLAYER1";
		}

		m_speed = 5;

		AssignGunRectangles();
	}
}

void Player::AssignGunRectangles()
{
	//Deagle
	m_deagleLeftRectangle.setSize(sf::Vector2f(27, 16));
	m_deagleLeftRectangle.setTexture(&m_deagleLeftTexture);
	m_deagleRightRectangle.setSize(sf::Vector2f(27, 16));
	m_deagleRightRectangle.setTexture(&m_deagleRightTexture);

	//SNIPER
	m_sniperRightRectangle.setSize(sf::Vector2f(50, 13));
	m_sniperRightRectangle.setTexture(&m_sniperRightTexture);
	m_sniperLeftRectangle.setSize(sf::Vector2f(50, 13));
	m_sniperLeftRectangle.setTexture(&m_sniperLeftTexture);


	//MINIGUN
	m_miniGunRightRectangle.setSize(sf::Vector2f(55, 23));
	m_miniGunRightRectangle.setTexture(&m_miniGunRightTexture);
	m_miniGunLeftRectangle.setSize(sf::Vector2f(55, 23));
	m_miniGunLeftRectangle.setTexture(&m_miniGunLeftTexture);
}

bool Player::LoadTexture()
{
	if (!m_pDownTexture.loadFromFile("Assets/Player/pDown.png"))
		return false;

	if (!m_pUpTexture.loadFromFile("Assets/Player/pUp.png"))
		return false;

	if (!m_pRightTexture.loadFromFile("Assets/Player/pRight.png"))
		return false;

	if (!m_pLeftTexture.loadFromFile("Assets/Player/pLeft.png"))
		return false;

	//Guns Textures
	if (!m_deagleLeftTexture.loadFromFile("Assets/Guns/Deagle/leftDeagle.png"))
	{
		std::cout << "Couldnt load Deagle Texture" << endl;
		return false;
	}

	if (!m_deagleRightTexture.loadFromFile("Assets/Guns/Deagle/rightDeagle.png"))
	{
		std::cout << "Couldnt load Deagle Texture" << endl;
		return false;
	}

	if (!m_sniperLeftTexture.loadFromFile("Assets/Guns/Sniper/leftSniper.png"))
	{
		std::cout << "Couldnt load Sniper Texture" << endl;
		return false;
	}

	if (!m_sniperRightTexture.loadFromFile("Assets/Guns/Sniper/rightSniper.png"))
	{
		std::cout << "Couldnt load Sniper Texture" << endl;
		return false;
	}

	if (!m_miniGunLeftTexture.loadFromFile("Assets/Guns/MiniGun/leftMiniGun.png"))
	{
		std::cout << "Couldnt load MiniGun Texture" << endl;
		return false;
	}

	if (!m_miniGunRightTexture.loadFromFile("Assets/Guns/MiniGun/rightMiniGun.png"))
	{
		std::cout << "Couldnt load MiniGun Texture" << endl;
		return false;
	}

	else
	return true;
}

void Player::LoadTextFile(string name)
{
	ifstream file(name);
	string str;
	while (getline(file, str))
	{
		m_Name = str;
	}
}

void Player::Update(sf::Time time)
{	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (m_playerAnimation.getAnimation() != &m_playerUpAnimation)
		{
			m_playerAnimation.setAnimation(m_playerUpAnimation);
		}
		m_playerAnimation.update(time);
		//m_position.y -= 0.05f;
		m_position.y -= m_speed;
		m_dir = 1;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_playerAnimation.getAnimation() != &m_playerDownAnimation)
		{
			m_playerAnimation.setAnimation(m_playerDownAnimation);			
		}
		m_playerAnimation.update(time);
		m_position.y += m_speed;
		m_dir = 2;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (m_playerAnimation.getAnimation() != &m_playerLeftAnimation)
		{
			m_playerAnimation.setAnimation(m_playerLeftAnimation);
		}
		m_playerAnimation.update(time);
		m_position.x -= m_speed;
		m_dir = 3;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (m_playerAnimation.getAnimation() != &m_playerRightAnimation)
		{
			m_playerAnimation.setAnimation(m_playerRightAnimation);
		}
		m_playerAnimation.update(time);
		m_position.x += m_speed;
		m_dir = 4;
	}

	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//m_velocity.x = 0;
		//m_velocity.y = 0;
	}

	//m_position += m_velocity;	
	m_playerAnimation.setPosition(m_position);
	m_rect.setPosition(m_position);

}

void Player::Draw(sf::RenderWindow &window)
{	
	
	window.draw(m_playerAnimation);

	if (currentWeapon == DEAGLE)
	{
		if ((m_playerAnimation.getAnimation() == &m_playerRightAnimation))
		{
			m_deagleRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 28));
			window.draw(m_deagleRightRectangle);
		}

		else if ((m_playerAnimation.getAnimation() == &m_playerLeftAnimation))
		{
			m_deagleLeftRectangle.setPosition(sf::Vector2f((m_position.x), m_position.y + 28));
			window.draw(m_deagleLeftRectangle);
		}
	}

	else if (currentWeapon == SNIPER)
	{
		if ((m_playerAnimation.getAnimation() == &m_playerRightAnimation))
		{
			m_sniperRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 28));
			window.draw(m_sniperRightRectangle);
		}

		else if ((m_playerAnimation.getAnimation() == &m_playerLeftAnimation))
		{
			m_sniperLeftRectangle.setPosition(sf::Vector2f((m_position.x - 15), m_position.y + 28));
			window.draw(m_sniperLeftRectangle);
		}
	}

	else if (currentWeapon == MINIGUN)
	{
		if ((m_playerAnimation.getAnimation() == &m_playerRightAnimation))
		{
			m_miniGunRightRectangle.setPosition(sf::Vector2f((m_position.x + 17), m_position.y + 20));
			window.draw(m_miniGunRightRectangle);
		}

		else if ((m_playerAnimation.getAnimation() == &m_playerLeftAnimation))
		{
			m_miniGunLeftRectangle.setPosition(sf::Vector2f((m_position.x - 27), m_position.y + 20));
			window.draw(m_miniGunLeftRectangle);
		}
	}

}

void Player::updateTex(sf::Texture texture)
{ //creates a copy of your texture you pass

	m_rect.setTexture(&texture); //actually takes the address of your texture 
}

sf::RectangleShape Player::GetShape()
{
	return m_rect;
}

sf::Vector2f Player::GetPosition()
{
	return m_position;
}

void Player::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

//Destructor
Player::~Player()
{
}