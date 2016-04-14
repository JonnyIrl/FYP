#include "Client.h"
#include <vector>
using namespace std;

class Clients
{
public:
	Clients();
	void AddNewClient(const string &IP, const string &Name);
	vector<sf::IpAddress> BroadcastToAllClients();
	vector<sf::IpAddress> BroadcastToEveryoneExceptClient(const string &IPAddress);
	sf::IpAddress FindWhoSentMessage(string &IP);
	bool CheckIfClientExists(const string &IPAddress);

private:
	vector<Client*> clientList;
};
