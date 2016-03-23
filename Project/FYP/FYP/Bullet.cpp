#include "ExtraIncludes.h"
#include "Bullet.h"
#include <math.h>

Bullet::Bullet()
{
	m_alive = false;
}

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f mousePos, int currentWeapon)
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
		m_bulletSpeed = 8;
		m_sniperBulletSpeed = 11;
		m_currentWeapon = currentWeapon;
		AssignBullets();
	}
}

bool Bullet::LoadTexture()
{
	if (!m_bulletTexture.loadFromFile("Assets/Bullet/assaultRifleBullet.png"))
		return false;

	if (!m_sniperTexture.loadFromFile("Assets/Bullet/Sniper/bullet.png"))
	{
		std::cout << "Cant load sniper animation" << std::endl;
		return false;
	}

	if (!m_miniGunTexture.loadFromFile("Assets/Bullet/MiniGun/bullet.png"))
	{
		std::cout << "Cant load minigun animation" << std::endl;
		return false;
	}

	if (!m_deagleTexture.loadFromFile("Assets/Bullet/Deagle/bullet.png"))
	{
		std::cout << "Cant load deagle bullet" << std::endl;
		return false;
	}

	return true;
}

void Bullet::AssignBullets()
{
	m_sniperRectangle.setSize(sf::Vector2f(24, 29));
	m_sniperRectangle.setTexture(&m_sniperTexture);

	m_sniperBulletAnimated.setSpriteSheet(m_sniperTexture);

	//Using width and height makes changing images sizes easy
	int width = 24; int height = 29;

	//Add the 12 frames
	m_sniperBulletAnimated.addFrame(sf::IntRect(0, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 2, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 3, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 4, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 5, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 6, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 7, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 8, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 9, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 10, 0, width, height));
	m_sniperBulletAnimated.addFrame(sf::IntRect(width * 11, 0, width, height));

	m_sniperAnimation = AnimatedSprite(sf::seconds(0.03f));
	m_sniperAnimation.setAnimation(m_sniperBulletAnimated);

	//MINIGUN
	m_miniGunBulletAnimated.setSpriteSheet(m_miniGunTexture);

	width = 40; height = 40;
	//Add the 12 frames
	m_miniGunBulletAnimated.addFrame(sf::IntRect(0, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 2, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 3, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 4, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 5, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 6, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 7, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 8, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 9, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 10, 0, width, height));
	m_miniGunBulletAnimated.addFrame(sf::IntRect(width * 11, 0, width, height));

	m_miniGunAnimation = AnimatedSprite(sf::seconds(0.01f));
	m_miniGunAnimation.setAnimation(m_miniGunBulletAnimated);
	m_miniGunAnimation.setPosition(sf::Vector2f(m_miniGunRectangle.getPosition().x, m_miniGunRectangle.getPosition().y));


}

void Bullet::CheckDeadBullets()
{
	if (!m_alive)
	{
		
	}
}

void Bullet::Update(sf::Time time)
{

	CheckBoundaryCollisions();

	if (m_alive)
	{
		if (m_currentWeapon == SNIPER)
		{
			if (m_bulletRectangle.getTexture() != &m_sniperTexture)
			{
				m_bulletRectangle.setTexture(&m_sniperTexture);
				m_bulletRectangle.setSize(sf::Vector2f(24, 29));
			}

			m_sniperAnimation.update(time);
			m_sniperAnimation.setPosition(m_bulletRectangle.getPosition());

			m_position.x += std::cos(m_bulletAngle * (M_PI / 180))* m_sniperBulletSpeed;
			m_position.y += std::sin(m_bulletAngle * (M_PI / 180))* m_sniperBulletSpeed;
			m_bulletRectangle.setPosition(m_position);

		}

		else if (m_currentWeapon == MINIGUN)
		{
			if (m_bulletRectangle.getTexture() != &m_miniGunTexture)
			{
				m_bulletRectangle.setTexture(&m_miniGunTexture);
				m_bulletRectangle.setSize(sf::Vector2f(40, 40));
			}

			m_miniGunAnimation.update(time);
			m_miniGunAnimation.setPosition(m_bulletRectangle.getPosition());

			m_position.x += std::cos(m_bulletAngle * (M_PI / 180))* m_bulletSpeed;
			m_position.y += std::sin(m_bulletAngle * (M_PI / 180))* m_bulletSpeed;
			m_bulletRectangle.setPosition(m_position);

		}

		else if (m_currentWeapon == DEAGLE)
		{
			if (m_bulletRectangle.getTexture() != &m_deagleTexture)
			{
				m_bulletRectangle.setSize(sf::Vector2f(14, 15));
				m_bulletRectangle.setTexture(&m_deagleTexture);			
			}

			m_position.x += std::cos(m_bulletAngle * (M_PI / 180))* m_sniperBulletSpeed;
			m_position.y += std::sin(m_bulletAngle * (M_PI / 180))* m_sniperBulletSpeed;
			m_bulletRectangle.setPosition(m_position);

		}

		else if (m_currentWeapon == AK)
		{
			if (m_bulletRectangle.getTexture() != &m_deagleTexture)
			{
				m_bulletRectangle.setSize(sf::Vector2f(14, 15));
				m_bulletRectangle.setTexture(&m_deagleTexture);
			}

			m_position.x += std::cos(m_bulletAngle * (M_PI / 180))* m_bulletSpeed;
			m_position.y += std::sin(m_bulletAngle * (M_PI / 180))* m_bulletSpeed;
			m_bulletRectangle.setPosition(m_position);

		}

	}

}

void Bullet::Draw(sf::RenderWindow &window)
{
	if (m_alive)
	{
		//window.draw(m_bulletRectangle);

		if (m_currentWeapon == SNIPER)
		{
			window.draw(m_sniperAnimation);
		}

		if (m_currentWeapon == MINIGUN)
		{
			window.draw(m_miniGunAnimation);
		}

		if (m_currentWeapon == DEAGLE || m_currentWeapon == AK)
		{
			window.draw(m_bulletRectangle);
		}
	}
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