#include "WeaponManager.h"


WeaponManager::WeaponManager()
{
	m_currentWeapon = ASSAULT_RIFLE;
}

byte WeaponManager::GetCurrentWeapon()
{
	return m_currentWeapon;
}

void WeaponManager::SetCurrentWeapon(byte weapon)
{
	m_currentWeapon = weapon;
}

WeaponManager::~WeaponManager()
{
}