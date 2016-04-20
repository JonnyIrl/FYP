#include "ExtraIncludes.h"
#include "PacketType.h"
#include "PlayerManager.h"
#include "SFML\Network.hpp"
#include "Clients.h"
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
	void Draw1(sf::RenderWindow &window);
	void Draw2(sf::RenderWindow &window);
	void Draw3(sf::RenderWindow &window);
	void Draw4(sf::RenderWindow &window);
	void Draw5(sf::RenderWindow &window);
	void Draw6(sf::RenderWindow &window);
	void Draw7(sf::RenderWindow &window);
	bool GetConnected() { return m_connected; }
	string ConvertStringToCharArray(string name, int typeCommand);
	void AddClientData(string name);
	bool GetPlayerReady() { return m_playerReady; }
	void SetPlayerReady(bool state);
	void SendPlayerReady();
	void SendPlayersPosition(sf::Vector2f position, int direction);
	void SetPlayerAsClient(bool ready);
	void SendNewBullet(sf::Vector2f position, int gun);
	void SendRespawnMessage(sf::Vector2f position, int direction);
	void SendRoomUpdate(int room);

	void ReceivePlayersPosition();
	int playerToUpdate = 0;

	string PLAYERNAME;
	Clients GetClients() { return clients; }
	bool CheckPlayersAllReady();
	PlayerManager pm = PlayerManager();

private:

	//Pre Game Lobby Variables
	sf::Font m_font;
	sf::Text m_text, m_chatLobbyText, m_NameText, m_connectedClientsText;
	string m_currentMessage, m_NameString, m_connectedClientsString;
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
	sf::UdpSocket listener;
	char playerNameCharArray[1024];
	Clients clients = Clients();
	bool m_playerReady = false;
	bool m_everyoneReady = false;
};

