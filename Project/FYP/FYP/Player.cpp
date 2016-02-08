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
	}
}

bool Player::LoadTexture()
{
	if (!m_pDownTexture.loadFromFile("Assets/Player/pDown.png"))
		return false;

	if (!m_pUpTexture.loadFromFile("Assets/Player/pUp.png"))
		return false;

	if (!m_pRightTexture.loadFromFile("Assets/Player/pRightTest.png"))
		return false;

	if (!m_pLeftTexture.loadFromFile("Assets/Player/pLeftTest.png"))
		return false;

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
		m_position.y -= 0.05f;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_playerAnimation.getAnimation() != &m_playerDownAnimation)
		{
			m_playerAnimation.setAnimation(m_playerDownAnimation);			
		}
		m_playerAnimation.update(time);
		m_position.y += 0.05f;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (m_playerAnimation.getAnimation() != &m_playerLeftAnimation)
		{
			m_playerAnimation.setAnimation(m_playerLeftAnimation);
		}
		m_playerAnimation.update(time);
		m_position.x -= 0.05f;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (m_playerAnimation.getAnimation() != &m_playerRightAnimation)
		{
			m_playerAnimation.setAnimation(m_playerRightAnimation);
		}
		m_playerAnimation.update(time);
		m_position.x += 0.05f;
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