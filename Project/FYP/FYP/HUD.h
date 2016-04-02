class HUD
{
public:
	HUD();
	bool LoadTexture();
	void Draw(sf::RenderWindow &window);
	void SetHighlight(int slotNumber);
	void SetHealth(int healthNumber);
	void SetEnergy(int enermyNumber);
	bool countDown = false;

private:
	sf::Texture m_hud1Texture;
	sf::Texture m_hud2Texture;
	sf::Texture m_hud3Texture;
	sf::Texture m_hud4Texture;
	sf::Texture m_hud5Texture;
	sf::Texture m_hud6Texture;

	sf::Texture m_blankTexture;

	sf::Texture m_health1Texture;
	sf::Texture m_health2Texture;
	sf::Texture m_health3Texture;
	sf::Texture m_health4Texture;
	sf::Texture m_health5Texture;
	sf::Texture m_health6Texture;
	sf::Texture m_health7Texture;
	sf::Texture m_health8Texture;
	sf::Texture m_health9Texture;
	sf::Texture m_health10Texture;

	sf::Texture m_energyBarTexture;

	sf::RectangleShape m_healthRectangle;
	sf::RectangleShape m_hudRectangle;
	sf::RectangleShape m_energyBarRectangle;
	sf::RectangleShape m_blankRectangle;
};
