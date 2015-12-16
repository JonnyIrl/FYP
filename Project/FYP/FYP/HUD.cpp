#include "ExtraIncludes.h"
#include "HUD.h"


//Constructor
HUD::HUD()
{
	if (LoadTexture())
	{
		m_hudRectangle.setSize(sf::Vector2f(300, 100));
		m_hudRectangle.setTexture(&m_hudTexture);
		m_hudRectangle.setPosition(sf::Vector2f(0, 620));
	}
}

bool HUD::LoadTexture()
{
	if (!m_hudTexture.loadFromFile("Assets/HUD/HUD.png"))
		return false;
	
	return true;
}

void HUD::Draw(sf::RenderWindow &window)
{
	window.draw(m_hudRectangle);
}