#include "ExtraIncludes.h"
#include "Player.h"
#include <vector>

using namespace std;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void Draw(sf::RenderWindow &window);
	void Update(sf::Time time);
	void SetPlayersPosition(string playerID, sf::Vector2f position);
	void AddNewPlayer(string playerID);
	vector<Player*> GetPlayers() { return m_Players; }

private:
	vector<Player*> m_Players;
};
