#include "Clients.h"

Clients::Clients()
{

}

void Clients::AddNewClient(const string &IP, const string &Name)
{
	clientList.push_back(new Client(IP, Name));
}

bool Clients::CheckIfClientExists(const string &IPAddress)
{
	bool found = false;
	for (int i = 0; i < clientList.size(); i++)
	{
		//Check if the current clients IP is the one listed, if it is then dont add it to the vector
		if (clientList.at(i)->GetIPAddress().toString().find(IPAddress) != string::npos)
		{
			found = true;
		}
	}

	return found;
}

sf::IpAddress Clients::FindWhoSentMessage(string &IP)
{
	for (int i = 0; i < clientList.size(); i++)
	{
		//Check if the current clients IP is the one listed, if it is then dont add it to the vector
		if (clientList.at(i)->GetIPAddress().toString().find(IP) != string::npos)
		{
			return clientList.at(i)->GetIPAddress();
		}
	}
}