#include "ExtraIncludes.h"

class WeaponManager
{
public:

	//Current Weapon Player Has
	byte GetCurrentWeapon();
	void SetCurrentWeapon(byte gun);

	WeaponManager();
	~WeaponManager();

private:
	enum WEAPON : byte{ ASSAULT_RIFLE, BOMB, PISTOL, MACHINEGUN, NET, FLASHBANG };
	sf::Texture m_assaultRifleTexture, m_bombTexture, m_pistolTexture, m_machineGunTexture, m_netTexture, m_flashbangTexture;
	byte m_currentWeapon;
};
