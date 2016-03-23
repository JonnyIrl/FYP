#include "ExtraIncludes.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <iostream>

using namespace std;

class Chest
{
public:
	Chest();
	Chest(sf::Vector2f position, int randomItem, int roomNumber);
	~Chest();


	bool IsOpen() { return m_isOpen; }
	void SetOpen(bool state) { m_isOpen = state; }
	bool IsActivated() { return m_isActivated; }
	bool IsItemTaken() { return m_isItemTaken; }
	void SetItemTaken(bool state) { m_isItemTaken = state; }
	void SetActived(bool state) { m_isActivated = state; }
	int GetRoomNumber() { return m_chestRoomNumber; }
	int GetWeapon() { return m_itemWeapon; }
	bool LoadTexture();
	void AddAnimationFrames();
	void Update(sf::Time time);
	bool CheckInRange(sf::RectangleShape &playerRect);
	void Draw(sf::RenderWindow &window);
	bool AssignRandomItem(int randNumber);
	sf::Vector2f GetPosition() { return m_position; }
	int m_chestRoomNumber;

private:
	bool m_isOpen;
	bool m_isActivated;
	bool m_isItemTaken;
	
	sf::RectangleShape m_chestRectangle;
	sf::RectangleShape m_displayWindowRectangle;
	sf::RectangleShape m_itemRectangle;
	sf::Texture m_chestTexture;
	sf::Texture m_displayWindowTexture;
	sf::Texture m_itemTexture;
	sf::Texture m_AK47Texture, m_SNIPERTexture, m_BOMBTexture, m_TRAPTexture, m_DEAGLETexture, m_MINIGUNTexture;
	sf::Vector2f m_position;
	AnimatedSprite m_chestAnimation;
	Animation m_chestOpeningAnimation;
	int m_itemWeapon = 1;

	const int M16 = 1;  int DEAGLE = 2; int SNIPER = 3; int MINIGUN = 4; int TRAP = 5; int AK = 6; int BOMB = 7;

};
