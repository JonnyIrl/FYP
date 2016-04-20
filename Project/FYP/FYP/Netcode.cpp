#include "Netcode.h"

Netcode::Netcode()
{
	if (!m_font.loadFromFile("Assets/Pregame/font.ttf"))
	{
		std::cout << "Couldn't load FONT" << std::endl;
	}

	else
	{
		m_text.setPosition(sf::Vector2f(20, 666));
		m_text.setFont(m_font);
		m_text.setColor(sf::Color::White);

		m_chatLobbyText.setPosition(sf::Vector2f(20, 200));
		m_chatLobbyText.setFont(m_font);
		m_chatLobbyText.setColor(sf::Color::White);

		m_NameText.setPosition(sf::Vector2f(165, 110));
		m_NameText.setFont(m_font);
		m_NameText.setColor(sf::Color::White);

		m_connectedClientsText.setPosition(sf::Vector2f(900, 200));
		m_connectedClientsText.setFont(m_font);
		m_connectedClientsText.setColor(sf::Color::White);

		m_currentMessage = "";
		m_messagesSent = 0;
		m_connected = false;


		m_ServerIPAddress = "192.168.0.15";
		//m_ipAddress = "192.168.0.15";
		m_serverPort = 5300;
		m_personalPort = 5301;

		if (listener.bind(5301) == sf::Socket::Done)
		{
			cout << "Socket bound" << endl;
		}

		cout << "Personal IP = " << m_ipAddress.toString() << endl;

		//PLAYERNAME = playerName;
		cout << "Netcode Constructor Finished" << endl;
	}
}

string Netcode::ConvertStringToCharArray(string name, int typeCommand)
{	
	//Converts the name into a char array so you can remove 1 letter at a time etc.
	strncpy_s(playerNameCharArray, name.c_str(), sizeof(playerNameCharArray));
	playerNameCharArray[sizeof(playerNameCharArray) - 1] = 0;
	string str(playerNameCharArray);
	return str;
}

string Netcode::GetTypedMessage()
{
	return m_currentMessage;
}
void Netcode::AppendChatMessage(string message)
{
	m_currentMessage += message;
	m_text.setString(m_currentMessage);
}
void Netcode::ResetText()
{
	m_messagesSent = 0;
	m_historyMessages.push_back(m_currentMessage);
	m_currentMessage = "";
	AppendChatMessage("");
	m_messagesSent++;
}
void Netcode::SetPlayerAsClient(bool ready)
{
	clients.AddNewClient(m_ipAddress.getLocalAddress().toString(), PLAYERNAME, 1, ready);
	AddClientData(PLAYERNAME);
}

void Netcode::AddClientData(string name)
{
	m_connectedClientsString += name + "\n";
	m_connectedClientsText.setString(m_connectedClientsString);
}

//Network code
void Netcode::ConnectToServer(string id)
{
	if (!m_connected)
	{
		m_ipAddress = sf::IpAddress::getLocalAddress();
		cout << "Not Connected.. Attempting to connect.." << endl;
		cout << "Your IP = " << m_ipAddress.toString() << endl;
		sf::Packet packet;

		//Send the initial connection details that the server needs
					// PACKET TYPE           //PLAYER IP         //PLAYER NAME
		packet << INITIAL_CONNECT_DATA << m_ipAddress.toString() << id;

		//Send that packet to the server with the servers port
		sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
		if (status == sf::Socket::Done)
		{
			cout << "Connection Packet Sent" << endl;
			SetPlayerAsClient(false);
		}
	}
}

void Netcode::SendPlayerReady()
{
	sf::Packet packet;
	packet << PLAYER_READY_CHANGED << m_ipAddress.getLocalAddress().toString() << m_playerReady;
	cout << "READY = " << m_playerReady << endl;
	clients.GetVector().at(0)->SetReady(m_playerReady);
	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}

}

void Netcode::SendPacket()
{
	m_receivedReply = false;
	string message = m_currentMessage;

	sf::Packet packet;
	packet << GENERAL_MSG << m_ipAddress.getLocalAddress().toString() << message << m_NameString;
	cout << "NAME = " << m_NameString << endl;

	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}

	/*while (!m_receivedReply)
	{
		ReceivePacket();
	}*/
}

void Netcode::SetPlayerReady(bool state) 
{ 
	m_playerReady = state; 

}

void Netcode::ReceivePacket()
{
	bool quit = false;

	while (!quit)
	{
		sf::Packet packet;
		list<string> messages;
		bool replied = false;

		sf::Socket::Status status = listener.receive(packet, m_ipAddress, m_personalPort);

		//retryCount++;

		switch (status)
		{
		case sf::Socket::Error:

			break;
		case sf::Socket::Done:
			PacketType type;
			sf::Uint32 size;
			//unsigned short port;
			packet >> type;

			//If we get this far then we have got a message from the server so no need to open the packet up and check.
			if (type == SERVER_REPLY_MSG)
			{
				cout << "Got Server reply message!" << endl;
				m_connected = true;
				m_receivedReply = true;
				break;
			}

			//If we get this far then we have got a message from the server so no need to open the packet up and check.
			if (type == UPDATE_MSG)
			{
				cout << "Update Message" << endl;
				packet >> size;
				cout << "Size = " << size << endl;

				for (sf::Uint32 i = 0; i < size; ++i)
				{
					string item;
					packet >> item;
					messages.push_back(item);
				}

				cout << "Messages size = " << messages.size();
				//Update the chat window with the text.
				UpdateChatWindow(messages);
				cout << "Updated chat window" << endl;
				ResetText();
				cout << "Reset text" << endl;
				m_receivedReply = true;
				break;
			}

			if (type == NEW_PLAYER_CONNECTED)
			{
				string playerID;
				string playerIP;
				bool ready;

				packet >> playerID >> playerIP >> ready;
				cout << "New Player = " << playerID << " IP = " << playerIP << " Ready = " << ready << endl;

				//If the clients doesnt exist then add them..
				if (!clients.CheckIfClientExists(playerIP))
				{
					clients.AddNewClient(playerIP, playerID, clients.Size() + 1, ready);
					cout << "Added new client " << playerIP << " : " << playerID << endl;
					AddClientData(playerID);
					pm.AddNewPlayer(playerIP);
				}
				break;
			}

			if (type == PLAYER_READY_CHANGED)
			{
				string playerIP;
				bool ready;

				packet >> playerIP >> ready;
				cout << "READY Player = " << playerIP << " Ready = " << ready;

				//Need to change the clients ready to be whatever was sent across
				//FIND WHICH CLIENT SENT THE READY CHANGED		THEN SET THE READY BOOL TO WHATEVER THEY SENT
				clients.GetVector().at(clients.FindWhatNumberClientsWhoSentReadyIs(playerIP))->SetReady(ready);
				break;
			}

			if (type == PLAYER_POSITION_UPDATE)
			{
				string playerID;
				float xPos, yPos;
				int direction;
				packet >> playerID;
				packet >> xPos;
				packet >> yPos;
				packet >> direction;

				for (int i = 0; pm.GetPlayers().size(); i++)
				{
					if (pm.GetPlayers().at(i)->GetPlayerID() == playerID)
					{
						cout << "Found player.. setting position = " << xPos << " " << yPos << endl;
						cout << "Setting Direction = " << direction << endl;
						pm.GetPlayers().at(i)->SetPosition(sf::Vector2f(xPos, yPos));
						pm.GetPlayers().at(i)->SetDirection(direction);
						break;
					}
				}

				break;
			}

			if (type == BULLET_MESSAGE)
			{
				string playerID;
				float xPos, yPos;
				int gun;
				packet >> playerID;
				packet >> xPos;
				packet >> yPos;
				packet >> gun;

				for (int i = 0; pm.GetPlayers().size(); i++)
				{
					if (pm.GetPlayers().at(i)->GetPlayerID() == playerID)
					{
						cout << "Found player.. setting CONVERTED = " << xPos << " " << yPos << endl;
						cout << "Shooting Bullet" << endl;
						cout << "Gun = " << gun << endl;
						pm.GetPlayers().at(i)->ShootBullet(sf::Vector2f(xPos, yPos), gun);
						break;
					}
				}

				break;
			}

			if (type == RESPAWN_MESSAGE)
			{
				string playerID;
				float xPos, yPos;
				int room;
				packet >> playerID;
				packet >> xPos;
				packet >> yPos;
				packet >> room;

				for (int i = 0; pm.GetPlayers().size(); i++)
				{
					if (pm.GetPlayers().at(i)->GetPlayerID() == playerID)
					{
						cout << "Found player.. setting position = " << xPos << " " << yPos << endl;
						cout << "Setting Room = " << room << endl;
						pm.GetPlayers().at(i)->SetPosition(sf::Vector2f(xPos, yPos));
						pm.GetPlayers().at(i)->SetRoom(room);
						break;
					}
				}

				break;
			}

			if (type == ROOM_UPDATE)
			{
				string playerID;
				int room;
				packet >> playerID;
				packet >> room;

				for (int i = 0; pm.GetPlayers().size(); i++)
				{
					if (pm.GetPlayers().at(i)->GetPlayerID() == playerID)
					{
						cout << "Found player.. setting room = " << room << endl;
						cout << "Setting Room = " << room << endl;
						pm.GetPlayers().at(i)->SetRoom(room);
						break;
					}
				}

				break;
			}
		default:
			;
		}
	}
}

void Netcode::ReceiveServerMessageUpdate()
{

	//sf::Packet packet;
	//sf::Socket::Status status = m_socket.receive(packet, m_ipAddress, m_port);
	//list<string> messages;
	//switch (status)
	//{
	//case sf::Socket::Done:
	//	PacketType type;
	//	sf::Uint32 size;
	//	packet >> type;
	//	packet >> size;

	//	//If we get this far then we have got a message from the server so no need to open the packet up and check.
	//	if (type == UPDATE_MSG)
	//	{
	//		for (sf::Uint32 i = 0; i < size; ++i)
	//		{
	//			string item;
	//			packet >> item;
	//			messages.push_back(item);
	//		}
	//		//Update the chat window with the text.
	//		UpdateChatWindow(messages);
	//		m_receivedReply = true;
	//	}
	//	break;
	//default:
	//	;
	//}

}

void Netcode::AddToName(string letter)
{
	m_NameString += letter;
	SetName(m_NameString);
}

void Netcode::UpdateChatWindow(list<string> messages)
{
	string message = "";
	for (list<string>::const_iterator i = messages.begin(); i != messages.end(); ++i)
	{
		//printf("%s\n", i->c_str());
		//cout << "Messages = " << i->c_str() << endl;
		message += i->c_str();
		message += "\n";
	}
	m_chatLobbyText.setString(message);
}

void Netcode::Update()
{
	//ReceiveServerMessageUpdate();
}

void Netcode::Draw1(sf::RenderWindow& window)
{
	
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw2(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw3(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw4(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw5(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw6(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

void Netcode::Draw7(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_NameText);
	window.draw(m_chatLobbyText);
	window.draw(m_connectedClientsText);
	clients.Draw(window);
}

bool Netcode::CheckPlayersAllReady()
{
	if (clients.Size() >= 1 && clients.CheckIfClientsAllReady())
	{
		return true;
	}

	else
		return false;
}

void Netcode::SendPlayersPosition(sf::Vector2f position, int direction)
{
	sf::Packet packet;
	packet << PLAYER_POSITION_UPDATE << m_ipAddress.getLocalAddress().toString() << position.x << position.y << direction;
	cout << "POSITION = " << position.x << " " <<  position.y << " Direction = " << direction<< endl;
	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}
}

void Netcode::SendNewBullet(sf::Vector2f position, int gun)
{
	sf::Packet packet;
	packet << BULLET_MESSAGE << m_ipAddress.getLocalAddress().toString() << position.x << position.y << gun;
	cout << "POSITION = " << position.x << " " << position.y << " GUN = " << gun << endl;
	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Bullet Fired packet Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}
}

void Netcode::SendRespawnMessage(sf::Vector2f position, int room)
{
	sf::Packet packet;
	packet << RESPAWN_MESSAGE << m_ipAddress.getLocalAddress().toString() << position.x << position.y << room;
	cout << "RESPAWN POSITION = " << position.x << " " << position.y << " room = " << room << endl;
	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}
}

void Netcode::SendRoomUpdate(int room)
{
	sf::Packet packet;
	packet << ROOM_UPDATE << m_ipAddress.getLocalAddress().toString() << room;
	cout << "ROOM_UPDATE = " << " room = " << room << endl;
	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		break;

	case sf::Socket::Disconnected:
		std::cout << " has been disconnected\n";
		break;

	default:
		;
	}
}
