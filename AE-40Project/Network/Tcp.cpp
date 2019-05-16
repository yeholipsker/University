#include "stdafx.h"
#include "Tcp.h"

// Constructor
Tcp::Tcp(int portNo, const char * ipAddress)
{
	this->portNo = portNo;
	this->ipAddress = ipAddress;
	// Initialize the socket.
	this->mySocket = new MySocket();
	this->mySocket->initialize();
}

// The connect method.
void Tcp::connectToHost()
{
	// Address family Internet.
	this->addr.sin_family = AF_INET; 
	// Port to connect on.
	this->addr.sin_port = htons(this->portNo);
	inet_pton(AF_INET, this->ipAddress, &this->addr.sin_addr.s_addr);
	// Connection failed.
	if (connect(this->mySocket->getSocket(), (SOCKADDR *)&this->addr, sizeof(this->addr)) == SOCKET_ERROR)
	{
		std::cout << "couldn't connect. Error: " << WSAGetLastError() << std::endl;
		return;
	}
	else
	{
		return;
	}
}

// The bind & listen method.
void Tcp::bindAndListen()
{
	// Address family Internet.
	this->addr.sin_family = AF_INET;
	// Port to connect on.
	this->addr.sin_port = htons(this->portNo);
	// 0.0.0.0 for any.
	inet_pton(AF_INET, this->ipAddress, &this->addr.sin_addr.s_addr);
	// Binding failed.
	if (bind(this->mySocket->getSocket(), (LPSOCKADDR)&this->addr, sizeof(this->addr)) == SOCKET_ERROR)
	{
		std::cout << "failed at binding" << std::endl;
		closesocket(this->mySocket->getSocket());
		WSACleanup();
		return;
	}
	// Listening failed.
	if (listen(this->mySocket->getSocket(), SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "failed at listening" << std::endl;
		closesocket(this->mySocket->getSocket());
		WSACleanup();
		return;
	}
}

// Accept
SOCKET Tcp::acceptClients()
{
	return accept(this->mySocket->getSocket(), NULL, NULL);
}

// Destructor
Tcp::~Tcp() {
	this->mySocket->close();
	delete this->mySocket;
}
