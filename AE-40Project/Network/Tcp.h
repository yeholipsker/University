#pragma once
#include "MySocket.h"

// Tcp implementation class.
class Tcp
{
public:
	// Constructor
	Tcp(int portNo, const char* ipAddress);
	// Connect
	void connectToHost();
	// Bind & listen.
	void bindAndListen();
	// Accept
	SOCKET acceptClients();
	// Destructor
	~Tcp();

private:
	SOCKADDR_IN addr;
	int portNo; 
	const char* ipAddress;
	MySocket * mySocket;
};

