#include "ExtraIncludes.h"
#include "Chest.h"
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <vector>

using namespace std;

class RandomLootManager
{
public:
	RandomLootManager();
	static RandomLootManager* GetInstance();
	void AddNewChest(Chest* chest);
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
	void GenerateAllRoomsLoot();
	vector<Chest*> randomChests;
	void Update(sf::Time time);
	void Draw(sf::RenderWindow &window);

private:
	bool m_rareLoot1, m_rareLoot2, m_rareLoot3;
	int m_amountOfRandoms = 18;
	int minX = 200; int maxX = 1000;
	int minY = 150; int maxY = 600;
};

