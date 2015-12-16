#include "ExtraIncludes.h"
#include "Bullet.h"
#include <math.h>

Bullet::Bullet()
{
	m_alive = false;
}

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	if (LoadTexture())
	{
		//Get and Set the angle to make turret face the mouse position
		float deltaX = mousePos.x -(playerPos.x);	//Moves turret to centre
		float deltaY = mousePos.y -(playerPos.y);	//Moves turret to centre

		m_bulletAngle = atan2(deltaY, deltaX) * 180.0 / M_PI;	//gets angle in degrees
		m_bulletRectangle.setSize(sf::Vector2f(10, 10));
		m_bulletRectangle.setTexture(&m_bulletTexture);
		//m_bulletRectangle.setRotation(m_bulletAngle);
		m_alive = true;
		m_position = playerPos;
		m_bulletRectangle.setPosition(playerPos);
	}
}

bool Bullet::LoadTexture()
{
	if (!m_bulletTexture.loadFromFile("Assets/Bullet/assaultRifleBullet.png"))
		return false;

	return true;
}

void Bullet::CheckDeadBullets()
{
	if (!m_alive)
	{
		
	}
}

void Bullet::Update()
{
	
	CheckBoundaryCollisions();

	if (m_alive)
	{
		m_position.x += std::cos(m_bulletAngle * (M_PI / 180) )* 0.2f;
		m_position.y += std::sin(m_bulletAngle * (M_PI / 180) )* 0.2f;
		m_bulletRectangle.setPosition(m_position);
	}

}

void Bullet::Draw(sf::RenderWindow &window)
{
	if (m_alive)
	window.draw(m_bulletRectangle);
}

bool Bullet::Alive()
{
	return m_alive;
}

void Bullet::CheckBoundaryCollisions()
{
	//Only check the right side for collision if the bullet is greater than 1100
	if (m_position.x >= 1200){ m_alive = false; }

	if (m_position.x <= 60){ m_alive = false; }

	if (m_position.y <= 60){ m_alive = false; }

	if (m_position.y >= 650){ m_alive = false; }

}

Bullet::~Bullet()
{
	//delete &m_bulletRectangle;
	//delete &m_bulletTexture;
	//delete &m_alive;
	//delete &m_position;
}