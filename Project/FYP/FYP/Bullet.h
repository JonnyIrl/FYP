class Bullet
{
public:
	Bullet();
	~Bullet();
	Bullet(sf::Vector2f PlayerPosition, sf::Vector2f mousePos);
	bool LoadTexture();
	void Draw(sf::RenderWindow &window);
	void Update();
	void CheckDeadBullets();
	void CheckBoundaryCollisions();
	bool Alive();

private:
	sf::Texture m_bulletTexture;
	sf::RectangleShape m_bulletRectangle;
	sf::Vector2f m_position;
	bool m_alive;
	float m_bulletAngle;

};