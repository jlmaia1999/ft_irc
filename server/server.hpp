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
#include <map>

class Client;

class Channel;

class Server
{
	private:
		bool _running;
		int	_SocketFd;
		int	_Port;
		std::string _Password;
		std::string _hostname;
		std::vector<struct pollfd> fds;
		std::vector<Client> _clients;
		std::vector<int> _channels; // Placeholder for channel management
		std::map<std::string, int> _commands; //command not created yet, int is supposed to be (command *)

		static bool Signal;

	public:
		Server(int port, std::string password);
		~Server();

		void ServerInit();
		void ServerSocket();
		void run();
		void AcceptNewClient();
		void ReceiveNewData(int fd);
		void RemoveData(int i);
		void RemoveChannel(Channel &channel);
		void RemoveClientChannels(Client &client);
		void shutdown();

		static void SignalHandler(int signum);
		void CloseFds();
		void ClearClients(int fd);

		Client *get_client(int client_fd);
		Client *get_client(std::string nickname);
		Channel *get_channel(std::string name);
};