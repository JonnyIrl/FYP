#include "ExtraIncludes.h"
#include "PacketType.h"
#include "PlayerManager.h"
#include "SFML\Network.hpp"
#include <iostream>
#include <list>
using namespace std;

class Netcode
{
public:
	Netcode();
	void ConnectToServer(string id);
	void SendPacket();
	void UpdateChatWindow(list<string> messages);
	void Update();
	void ReceivePacket();
	void ReceiveServerMessageUpdate();
	string GetTypedMessage();
	void AppendChatMessage(string message);
	void SetName(string name) { m_NameText.setString(name); m_NameString = name; }
	void AddToName(string letter);
	string GetName() { return m_NameString; }
	void RemoveNameLetter() { m_NameString.pop_back(); SetName(m_NameString); }
	void RemoveChatLetter() { m_currentMessage.pop_back(); m_text.setString(m_currentMessage); }
	void ResetText();
	void Draw(sf::RenderWindow &window);
	bool GetConnected() { return m_connected; }
	string ConvertStringToCharArray(string name, int typeCommand);

	void ReceivePlayersPosition();

	string PLAYERNAME;


private:

	//Pre Game Lobby Variables
	sf::Font m_font;
	sf::Text m_text, m_chatLobbyText, m_NameText;
	string m_currentMessage, m_NameString;
	int m_messagesSent;
	list<string> m_historyMessages;
	sf::IpAddress m_ServerIPAddress;
	sf::UdpSocket m_socket;
	bool m_connected;
	bool m_receivedReply;
	sf::IpAddress m_ipAddress = sf::IpAddress::getLocalAddress();
	unsigned short m_serverPort = 5300;
	unsigned short m_personalPort = 5301;
	int retryCount = 0;
	bool running = true;
	PlayerManager pm = PlayerManager();
	sf::UdpSocket listener;
	char playerNameCharArray[1024];

};

