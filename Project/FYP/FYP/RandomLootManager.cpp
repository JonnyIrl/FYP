#include "RandomLootManager.h"


static bool instanceFlag = false;
static RandomLootManager* instance = NULL;

RandomLootManager::RandomLootManager()
{

}

RandomLootManager * RandomLootManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new RandomLootManager();
		instanceFlag = true;
	}
	return instance;
}

void RandomLootManager::AddNewChest(Chest * chest)
{
	randomChests.push_back(chest);
}

RandomLootManager::~RandomLootManager()
{
}


void RandomLootManager::Draw(sf::RenderWindow &window)
{
	for each (Chest* c in randomChests)
	{
		c->Draw(window);
	}
}

void RandomLootManager::Update(sf::Time time)
{
	for each (Chest* c in randomChests)
	{
		c->Update(time);
	}
}

void RandomLootManager::GenerateAllRoomsLoot()
{
	srand(time(NULL));
	GenerateRoom1Loot();
	GenerateRoom2Loot();
	GenerateRoom3Loot();
	GenerateRoom4Loot();
	GenerateRoom5Loot();
	GenerateRoom6Loot();
	GenerateRoom7Loot();
	GenerateRoom8Loot();
	GenerateRoom9Loot();
}
void RandomLootManager::GenerateRoom1Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 1);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom2Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 2);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom3Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 3);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom4Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 4);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom5Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 5);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom6Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 6);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom7Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 7);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom8Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 8);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom9Loot()
{
	for (int i = 0; i < (m_amountOfRandoms / 9); i++)
	{
		int xPos = rand() % (maxX - minX) + minX;
		int yPos = rand() % (maxY - minY) + minY;
		int loot = rand() % 10 + 1;
		Chest* chest = new Chest(sf::Vector2f(xPos, yPos), loot, 9);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}