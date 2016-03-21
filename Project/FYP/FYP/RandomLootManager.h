#include "ExtraIncludes.h"
#include <iostream>

using namespace std;

class RandomLootManager
{
public:
	RandomLootManager();
	~RandomLootManager();

	void GenerateRoom1Loot();
	void GenerateRoom2Loot();
	void GenerateRoom3Loot();
	void GenerateRoom4Loot();
	void GenerateRoom5Loot();
	void GenerateRoom6Loot();
	void GenerateRoom7Loot();
	void GenerateRoom8Loot();
	void GenerateRoom9Loot();

private:
	bool m_rareLoot1, m_rareLoot2, m_rareLoot3;
};

