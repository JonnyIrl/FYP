#include "Client.h"
#include <vector>
using namespace std;

class Clients
{
public:
	Clients();
	void AddNewClient(const string &IP, const string &Name, int count, bool ready);
	vector<sf::IpAddress> BroadcastToAllClients();
	vector<sf::IpAddress> BroadcastToEveryoneExceptClient(const string &IPAddress);
	sf::IpAddress FindWhoSentMessage(string &IP);
	int FindWhatNumberClientsWhoSentReadyIs(string &IP);
	bool CheckIfClientExists(const string &IPAddress);
	int Size() { return clientList.size(); }
	void Draw(sf::RenderWindow &window);
	vector<Client*> GetVector() { return clientList; }
	bool CheckIfClientsAllReady();

private:
	vector<Client*> clientList;
	
};
