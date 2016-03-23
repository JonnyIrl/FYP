#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>
using namespace std;

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
	void LoadTextFile(string name);
	void AssignGunRectangles();
	int GetWeapon() { return currentWeapon; }
	void SetWeapon(int weapon) { currentWeapon = weapon; }
	string GetName(){ return m_Name; }

	//Get Animated Frames Textures
	Animation GetLeftAnimation() { return m_playerLeftAnimation; }
	Animation GetRightAnimation() { return m_playerRightAnimation; }
	Animation GetUpAnimation() { return m_playerUpAnimation; }
	Animation GetDownAnimation() { return m_playerDownAnimation; }
	AnimatedSprite GetAnimatedSprite() { return m_playerAnimation; }
	int GetDirection() { return m_dir; }


private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	string m_Name;
	bool m_alive;
	bool m_moving;
	float m_speed;
	int m_dir;
	sf::Sprite m_spr;
	sf::RectangleShape m_rect;
	sf::Texture m_pDownTexture;
	sf::Texture m_pUpTexture;
	sf::Texture m_pLeftTexture;
	sf::Texture m_pRightTexture;

	//Guns
	sf::Texture m_deagleLeftTexture, m_deagleRightTexture;
	sf::Texture m_sniperLeftTexture, m_sniperRightTexture;
	sf::Texture m_miniGunLeftTexture, m_miniGunRightTexture;

	sf::RectangleShape m_deagleLeftRectangle, m_deagleRightRectangle;
	sf::RectangleShape m_sniperLeftRectangle, m_sniperRightRectangle;
	sf::RectangleShape m_miniGunLeftRectangle, m_miniGunRightRectangle;
	//End Guns

	//Each Gun Variable
	int currentWeapon = 3;
	const int M16 = 1;  int DEAGLE = 2; int SNIPER = 3; int MINIGUN = 4; int TRAP = 5; int AK = 6; int BOMB = 7;
	


	Animation m_playerLeftAnimation;
	Animation m_playerRightAnimation;
	Animation m_playerUpAnimation;
	Animation m_playerDownAnimation;
	AnimatedSprite m_playerAnimation;
};
