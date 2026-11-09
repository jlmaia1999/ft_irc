#pragma once

#include <iostream>
#include <vector> 
#include <cstring>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <poll.h> 
#include <csignal> 
#include <sstream>

class Client
{
	private:
		int _fd;
		std::string _ipadd;
	public:
		Client();
		~Client();
		int GetFd();
		void SetFd(int fd);
		void SetIpadd(std::string ipadd);
};

class Server
{
	private:
		std::vector<Client> _clients; //type is Client, switch once the class is created
		int	_Port;
		int	_SocketFd;
		static bool Signal;
		std::vector<struct pollfd> fds;

	public:
		Server();
		~Server();

		void ServerInit(int port);
		void ServerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);

		static void SignalHandler(int signum);
		void CloseFds();
		void ClearClients(int fd);
};