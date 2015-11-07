#include "CollisionManager.h"

using namespace std;

CollisionManager::CollisionManager()
{
	cout << "Finished Collision Manager Constructor" << endl;
}

//Method to check collision between 2 rectangles.
bool CollisionManager::CheckRectangleCollision(sf::RectangleShape entity1, sf::RectangleShape entity2)
{
	if (entity1.getGlobalBounds().intersects(entity2.getGlobalBounds()))
		return true;

	else
		return false;
}