#include "ExtraIncludes.h"
#include "MultiPlayer.h"
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
	MultiPlayer* FindWhichPlayerToUpdate(string playerIP);
	vector<MultiPlayer*> GetPlayers() { return m_Players; }

private:
	vector<MultiPlayer*> m_Players;
};
