#pragma once
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>

// Socket implementation class.
class MySocket
{
public:
	// Constructor
	MySocket();
	// Initialize the socket.
	void initialize();
	// Getter
	SOCKET getSocket();
	// Close the socket.
	void close();
	// Destructor
	~MySocket();

private:
	// The socket.
	SOCKET mySocket;
	// Connection data.
	WSADATA wsadata;
};

