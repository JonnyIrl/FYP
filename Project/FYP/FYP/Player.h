#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>
#include <list>

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
	int GetHealth() { return m_health; }
	void SetHealth(bool increase, int amount) 
	{
		if (increase)
		{
			m_health += amount;
		}

		else
			m_health -= amount;
	}
	int GetEnergy() { return m_energy; }
	void SetEnergy(bool increase, int amount)
	{
		if (increase)
		{
			m_energy += amount;
		}

		else
			m_energy -= amount;
	}
	void AddNewTrap(sf::Vector2f position);
	void SetTrapCoolDown(bool state){ countDownTrap = state; }
	bool GetTrapCoolDown() { return countDownTrap; }


private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	string m_Name;
	bool m_alive;
	bool m_moving;
	float m_speed;
	float m_bulletDelay;
	int m_health;
	int m_energy;
	int m_dir;
	int trapCoolDown;
	bool countDownTrap;
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
	sf::Texture m_AK47LeftTexture, m_AK47RightTexture;
	sf::Texture m_trapTexture;

	sf::RectangleShape m_deagleLeftRectangle, m_deagleRightRectangle;
	sf::RectangleShape m_sniperLeftRectangle, m_sniperRightRectangle;
	sf::RectangleShape m_miniGunLeftRectangle, m_miniGunRightRectangle;
	sf::RectangleShape m_AK47LeftRectangle, m_AK47RightRectangle;
	sf::RectangleShape m_trapRectangle;
	sf::RectangleShape m_blankRectangle;
	list<sf::RectangleShape> m_TrapRectangles;
	//End Guns

	//Each Gun Variable
	int currentWeapon = 6;
	const int M16 = 1;  int DEAGLE = 2; int SNIPER = 3; int MINIGUN = 4; int TRAP = 5; int AK47 = 6; int BOMB = 7;
	

	//Clock for count downs
	sf::Clock trapClock;

	//Text for count down display
	sf::Text trapCDText;
	//Font
	sf::Font trapFont;

	Animation m_playerLeftAnimation;
	Animation m_playerRightAnimation;
	Animation m_playerUpAnimation;
	Animation m_playerDownAnimation;
	AnimatedSprite m_playerAnimation;
};
