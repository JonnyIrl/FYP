class HUD
{
public:
	HUD();
	bool LoadTexture();
	void Draw(sf::RenderWindow &window);

private:
	sf::Texture m_hudTexture;
	sf::RectangleShape m_hudRectangle;
};
