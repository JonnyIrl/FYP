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

float CollisionManager::GetMagnitude(sf::Vector2f vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

int CollisionManager::GetDotProduct(sf::Vector2f vec1, sf::Vector2f vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y));
}

float CollisionManager::GetCosAngle(float mag1, float mag2, int length)
{
	return (length / (mag1 * mag2));
}

float CollisionManager::InverseAngle(float angle)
{
	return acos(angle);
}

float CollisionManager::RadsToDegrees(float angle)
{
	return ((angle * 180) / M_PI);
}