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
		bool _running;

		std::vector<Client> _clients;
		std::vector<int> _channels; // Placeholder for channel management
		std::vector<struct pollfd> fds;

		std::string _hostname;
		int	_Port;
		std::string _Password;
		int	_SocketFd;
		static bool Signal;

	public:
		Server(int port, std::string password);
		~Server();

		void ServerInit();
		void ServerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);

		static void SignalHandler(int signum);
		void CloseFds();
		void ClearClients(int fd);
};