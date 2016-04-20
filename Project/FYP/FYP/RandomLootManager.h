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

	void GenerateRoom1Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom2Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom3Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom4Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom5Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom6Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom7Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom8Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateRoom9Loot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	void GenerateAllRoomsLoot(vector<float> xPos, vector<float> yPos, vector<float> loot);
	vector<Chest*> randomChests;
	void Update(sf::Time time);
	void Draw(sf::RenderWindow &window);

private:
	bool m_rareLoot1, m_rareLoot2, m_rareLoot3;
	int m_amountOfRandoms = 18;
	int minX = 200; int maxX = 1000;
	int minY = 150; int maxY = 600;
};

