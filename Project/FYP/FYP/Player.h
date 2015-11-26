#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Player
{
public:
	Player();
	~Player();
	void Update(sf::Time time);
	sf::RectangleShape GetShape();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	void updateTex(sf::Texture texture);
	bool LoadTexture();
	void Draw(sf::RenderWindow& window);

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	bool m_alive;
	bool m_moving;
	sf::Sprite m_spr;
	sf::RectangleShape m_rect;
	sf::Texture m_pDownTexture;
	sf::Texture m_pUpTexture;
	sf::Texture m_pLeftTexture;
	sf::Texture m_pRightTexture;

	Animation m_playerLeftAnimation;
	Animation m_playerRightAnimation;
	Animation m_playerUpAnimation;
	Animation m_playerDownAnimation;
	AnimatedSprite m_playerAnimation;
};
