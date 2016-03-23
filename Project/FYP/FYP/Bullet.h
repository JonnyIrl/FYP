#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Bullet
{
public:
	Bullet();
	~Bullet();
	Bullet(sf::Vector2f PlayerPosition, sf::Vector2f mousePos, int currentWeapon);
	bool LoadTexture();
	void Draw(sf::RenderWindow &window);
	void Update(sf::Time time);
	void CheckDeadBullets();
	void CheckBoundaryCollisions();
	void AssignBullets();
	bool Alive();

private:
	sf::Texture m_bulletTexture;
	sf::RectangleShape m_bulletRectangle;
	sf::Vector2f m_position;
	bool m_alive;
	float m_bulletAngle;
	float m_bulletSpeed;
	float m_sniperBulletSpeed;

	//Different Gun Bullets
	sf::Texture m_sniperTexture, m_miniGunTexture, m_deagleTexture, m_akTexture;
	sf::RectangleShape m_sniperRectangle, m_miniGunRectangle, m_deagleRectangle, m_akRectangle;
	AnimatedSprite m_sniperAnimation, m_miniGunAnimation;
	Animation m_sniperBulletAnimated, m_miniGunBulletAnimated;

	int m_currentWeapon = 1;
	const int M16 = 1;  int DEAGLE = 2; int SNIPER = 3; int MINIGUN = 4; int TRAP = 5; int AK = 6; int BOMB = 7;
};