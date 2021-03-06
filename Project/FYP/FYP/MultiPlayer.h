#pragma once
#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>
#include <list>
#include "Bullet.h"

using namespace std;

class MultiPlayer
{
public:
	MultiPlayer();
	~MultiPlayer();
	void UpdateRoom1(sf::Time time);
	void UpdateRoom2(sf::Time time);
	void UpdateRoom3(sf::Time time);
	void UpdateRoom4(sf::Time time);
	void UpdateRoom5(sf::Time time);
	void UpdateRoom6(sf::Time time);
	void UpdateRoom7(sf::Time time);
	void UpdateRoom8(sf::Time time);
	void UpdateRoom9(sf::Time time);
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
	bool CheckKillSoundEffect();
	bool CheckDeathStreakOver();
	int GetKillingSpree() { return m_killingSpree; }
	void ResetKillingSpree() { m_killingSpree = 0; }
	void IncreaseDecreaseKillingSpress(bool state);
	void IncreaseDeathCount() { m_deathsWithoutKill++; cout << "Death total = " << m_deathsWithoutKill; }
	bool CreateAKBullet();
	string GetPlayerID() { return m_PlayerID; }
	string GetPlayerName() { return m_Name; }
	void SetPlayerID(string ID) { m_PlayerID = ID; }
	void SetName(string name) { m_Name = name; }
	int GetRoom() { return m_currentRoom; }
	void SetRoom(int roomNum) { m_currentRoom = roomNum; }
	void SetDirection(int direction) { m_dir = direction; }
	int FindWhichRoomToUpdate();
	int GetRoomNumber() { return m_currentRoom; }
	int GetScore() { return m_score; }
	void SetHealthFull() { m_health = 100; }

	void ShootAKBullet(sf::Vector2f converted);
	void ShootSNIPERBullet(sf::Vector2f converted);
	void ShootTRAPBullet(sf::Vector2f converted);
	void ShootBullet(sf::Vector2f converted, int gun);
	void IncreaseScore() { m_score++; }


	std::vector<Bullet *> Room1Bullets;
	std::vector<Bullet *> Room2Bullets;
	std::vector<Bullet *> Room3Bullets;
	std::vector<Bullet *> Room4Bullets;
	std::vector<Bullet *> Room5Bullets;
	std::vector<Bullet *> Room6Bullets;
	std::vector<Bullet *> Room7Bullets;
	std::vector<Bullet *> Room8Bullets;
	std::vector<Bullet *> Room9Bullets;

	bool UpdatePlayerRoom = false;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	string m_Name;
	string m_PlayerID;
	bool m_alive;
	bool m_moving;
	float m_speed;
	float m_bulletDelay;
	int m_health;
	int m_score = 0;
	int m_energy;
	int m_dir;
	int m_killingSpree;
	int m_deathsWithoutKill;
	int trapCoolDown;
	bool countDownTrap;
	int m_currentRoom = 0;
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
	const int m_AKDelay = 2;
	int m_AKCountDown;

	//Clock for count downs
	sf::Clock trapClock;
	sf::Clock soundEffectClock;
	float soundEffectCountDown;

	//Text for count down display
	sf::Text trapCDText;
	//Font
	sf::Font trapFont;

	Animation m_playerLeftAnimation;
	Animation m_playerRightAnimation;
	Animation m_playerUpAnimation;
	Animation m_playerDownAnimation;
	AnimatedSprite m_playerAnimation;

	Bullet* b;
};

#endif
