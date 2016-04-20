#include "ExtraIncludes.h"
#include "MultiPlayer.h"
#include <vector>

using namespace std;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void Draw1(sf::RenderWindow &window);
	void Draw2(sf::RenderWindow &window);
	void Draw3(sf::RenderWindow &window);
	void Draw4(sf::RenderWindow &window);
	void Draw5(sf::RenderWindow &window);
	void Draw6(sf::RenderWindow &window);
	void Draw7(sf::RenderWindow &window);
	void Draw8(sf::RenderWindow &window);
	void Draw9(sf::RenderWindow &window);
	void Update(sf::Time time);
	void SetPlayersPosition(string playerID, sf::Vector2f position);
	void AddNewPlayer(string playerID, string name);
	MultiPlayer* FindWhichPlayerToUpdate(string playerIP);
	vector<MultiPlayer*> GetPlayers() { return m_Players; }

private:
	vector<MultiPlayer*> m_Players;
};
