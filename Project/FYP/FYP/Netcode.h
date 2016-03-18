#include "ExtraIncludes.h"
#include "PacketType.h"
#include "SFML\Network.hpp"
#include <iostream>
#include <list>
using namespace std;

class Netcode
{
public:
	Netcode();
	void ConnectToServer();
	void SendPacket();
	void UpdateChatWindow(list<string> messages);
	void Update();
	void ReceivePacket();
	void ReceiveServerMessageUpdate();
	string GetTypedMessage();
	void SetChatMessage(string message);
	void ResetText();
	void Draw(sf::RenderWindow &window);
	string PLAYERNAME;


private:

	//Pre Game Lobby Variables
	sf::Font m_font;
	sf::Text m_text, m_chatLobbyText;
	string m_currentMessage;
	int m_messagesSent;
	list<string> m_historyMessages;
	sf::IpAddress m_ServerIPAddress;
	sf::UdpSocket m_socket;
	bool m_connected;
	bool m_receivedReply;
	sf::IpAddress m_ipAddress = "192.168.0.50";
	unsigned short m_serverPort = 5300;
	unsigned short m_personalPort = 5301;
	int retryCount = 0;

};

