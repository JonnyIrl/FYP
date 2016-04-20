#include "ExtraIncludes.h"
#include <cmath>
#include <math.h>

class CollisionManager
{
public:
	CollisionManager();
	bool CheckRectangleCollision(sf::RectangleShape entity1, sf::RectangleShape entity2);
	float GetMagnitude(sf::Vector2f vect);
	int GetDotProduct(sf::Vector2f vec1, sf::Vector2f vec2);
	float GetCosAngle(float mag1, float mag2, int length);
	float InverseAngle(float angle);
	float RadsToDegrees(float angle);

private:

};

