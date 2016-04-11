#include "Netcode.h"

Netcode::Netcode()
{

	if (!m_font.loadFromFile("Assets/Pregame/font.ttf"))
	{
		std::cout << "Couldn't load FONT" << std::endl;
	}

	else
	{
		m_text.setPosition(sf::Vector2f(100, 600));
		m_text.setFont(m_font);
		m_text.setColor(sf::Color::White);

		m_chatLobbyText.setPosition(sf::Vector2f(100, 165));
		m_chatLobbyText.setFont(m_font);
		m_chatLobbyText.setColor(sf::Color::White);

		m_currentMessage = "";
		m_messagesSent = 0;
		m_connected = false;


		m_ServerIPAddress = "192.168.0.15";
		m_serverPort = 5300;
		m_personalPort = 5301;

		//PLAYERNAME = playerName;
		cout << "Netcode Constructor Finished" << endl;
	}
}

string Netcode::GetTypedMessage()
{
	return m_currentMessage;
}
void Netcode::SetChatMessage(string message)
{
	m_messagesSent++;
	m_currentMessage += message;
	m_text.setString(m_currentMessage);
}
void Netcode::ResetText()
{
	m_messagesSent = 0;
	m_historyMessages.push_back(m_currentMessage);
	m_currentMessage = "";
	SetChatMessage("");
	m_messagesSent++;
}

//Network code
void Netcode::ConnectToServer(string id)
{
	if (!m_connected)
	{
		cout << "Not Connected.. Attempting to connect.." << endl;
		sf::IpAddress ip = "192.168.0.15";
		m_ipAddress = "192.168.0.15";
		sf::Packet packet;

		cout << "BEFORE PACKING = " << "192.168.0.15" << endl;
		//Send the initial connection details that the server needs
		packet << INITIAL_CONNECT_DATA << "192.168.0.15" << id;

		cout << "AFTER PACKING = " << "192.168.0.15" << endl;

		//Send that packet to the server with the servers port
		sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
		if (status == sf::Socket::Done)
		{
			cout << "Connection Packet Sent" << endl;
			cout << "AFTER SENDING = " << "192.168.0.15" << endl;
		}

		while (!m_receivedReply)
		{
			//cout << "Waiting for a reply now..." << endl;
			//ReceivePacket();
			m_receivedReply = true;
			cout << "Got Reply from the server.. \n Now Connected to the server!" << endl << endl;
		}
	}
}

void Netcode::SendPacket()
{
	m_receivedReply = false;
	string message = m_currentMessage;

	sf::Packet packet;
	packet << GENERAL_MSG << "192.168.0.15" << message << PLAYERNAME;

	sf::Socket::Status status = m_socket.send(packet, m_ServerIPAddress, m_serverPort);
	switch (status)
	{
	case sf::Socket::Done:
		cout << "Message Sent" << endl;
		//PacketType type;
		//packet >> type;
		
		//if (type == GENERAL_MSG)
		//{
			//cout << "Message Sent, waiting for a reply now. " << endl;
			//std::string msg;
			//packet >> msg >> PLAYERNAME;
			//packet.clear();
		//}
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

void Netcode::ReceivePacket()
{
	bool quit = false;
	while (!quit)
	{
		sf::Packet packet;
		list<string> messages;
		//m_ipAddress = "192.168.0.15";
		sf::Socket::Status status = m_socket.receive(packet, m_ipAddress, m_personalPort);
		retryCount++;

		switch (status)
		{
		case sf::Socket::Done:
			PacketType type;
			sf::Uint32 size;
			//unsigned short port;
			packet >> type;

			//If we get this far then we have got a message from the server so no need to open the packet up and check.
			if (type == SERVER_REPLY_MSG)
			{
				m_receivedReply = true;
				break;
			}

			//If we get this far then we have got a message from the server so no need to open the packet up and check.
			//if (type == SERVER_REPLY_MSG)
			//{
			//	/*std::string msg;
			//	packet >> msg;
			//	std::cout << "Server: " << msg << "\n";
			//	retryCount = 0;*/
			//	m_receivedReply = true;
			//	break;
			//}

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

			if (type == PLAYER_POSITION_UPDATE)
			{
				string playerID;
				float xPos, yPos;
				packet >> playerID;
				packet >> xPos;
				packet >> yPos;

				for (int i = 0; pm.GetPlayers().size(); i++)
				{
					if (pm.GetPlayers().at(i)->GetPlayerID() == playerID)
					{
						pm.GetPlayers().at(i)->SetPosition(sf::Vector2f(xPos, yPos));
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
	//ReceivePacket();
}
void Netcode::Draw(sf::RenderWindow& window)
{
	window.draw(m_text);
	window.draw(m_chatLobbyText);
}