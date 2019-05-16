#include "stdafx.h"
#include "MySocket.h"

// Constructor
MySocket::MySocket() { }

// Initialize the socket.
void MySocket::initialize()
{
	// Make sure everything is good.
	if (WSAStartup(MAKEWORD(2, 2), &this->wsadata)) {
		std::cout << "something went wrong with winsock startup" << std::endl;
	}
	if (this->wsadata.wVersion != 0x0202) {
		WSACleanup();
		std::cout << "this is not winsock version 2!" << std::endl;
	}
	this->mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->mySocket == INVALID_SOCKET){
		WSACleanup();
		std::cout << "Failed at socket" << std::endl;
	}
}

// Getter
SOCKET MySocket::getSocket()
{
	return this->mySocket;
}

// Close the socket.
void MySocket::close()
{
	closesocket(this->mySocket);
	WSACleanup();
}

// Destructor
MySocket::~MySocket() { }
