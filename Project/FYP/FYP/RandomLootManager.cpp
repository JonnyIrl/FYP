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

void RandomLootManager::GenerateAllRoomsLoot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	srand(time(NULL));
	GenerateRoom1Loot(xPos, yPos, loot);
	GenerateRoom2Loot(xPos, yPos, loot);
	GenerateRoom3Loot(xPos, yPos, loot);
	GenerateRoom4Loot(xPos, yPos, loot);
	GenerateRoom5Loot(xPos, yPos, loot);
	GenerateRoom6Loot(xPos, yPos, loot);
	GenerateRoom7Loot(xPos, yPos, loot);
	GenerateRoom8Loot(xPos, yPos, loot);
	GenerateRoom9Loot(xPos, yPos, loot);
}
void RandomLootManager::GenerateRoom1Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 0; i < 2; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 1);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom2Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 2; i < 4; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 2);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom3Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 4; i < 6; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 3);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom4Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 6; i < 8; i++)
	{

		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 4);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom5Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 8; i < 10; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 5);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom6Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 10; i < 12; i++)
	{

		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 6);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom7Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 12; i < 14; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 7);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom8Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 14; i < 16; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 8);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}
void RandomLootManager::GenerateRoom9Loot(vector<float> xPos, vector<float> yPos, vector<float> loot)
{
	for (int i = 16; i < 18; i++)
	{
		Chest* chest = new Chest(sf::Vector2f(xPos.at(i), yPos.at(i)), loot.at(i), 9);
		RandomLootManager::GetInstance()->AddNewChest(chest);
	}
}