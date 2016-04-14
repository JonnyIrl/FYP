#include "ExtraIncludes.h"
#include "SFML/Network.hpp"
#include <string>
using namespace std;

//ClientS will use Client to get IP Address's etc. 
class Client
{
public:
	Client(const string &IP, const string &Port);
	sf::IpAddress GetIPAddress(){ return m_IPAddress; }
	string GetName() { return m_Name; }
	bool GetConnected() { return m_connected; }
	void SetConnected(bool state) { m_connected = state; }

private:
	sf::IpAddress m_IPAddress;
	string m_Name;
	bool m_connected;
};
