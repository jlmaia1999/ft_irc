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
#include <cerrno>
#include <sstream>
#include <map>
#include "../commands/command.hpp"

class Client;
class Command;
class Channel;

class Server
{
	private:
		bool _running;
		int	_SocketFd;
		int	_Port;
		std::string _Password;
		std::string _hostname;
		std::vector<struct pollfd> _fds;
		std::map<int, Client*> _clients;
		std::vector<int> _Quiting;
		std::map<std::string, Channel &> _channels;
		std::map<std::string, Command *> _commands;

		static bool Signal;

	public:
		Server(int port, std::string password);
		~Server();

		void ServerInit();
		void ServerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);
		void RemoveData(int i);
		void SendData(int i);
		// void RemoveChannel(Channel &channel);
		// void RemoveClientChannels(Client &client);
		// void shutdown();
		// void cmd_pass(Client &client, const std::vector<std::string>& params);
		std::string GetHostname();

		static void SignalHandler(int signum);
		void CloseFds();
		void ClearClients(int fd);

		Client *get_client(int client_fd);
		Client *get_client(std::string nickname);
		Channel *get_channel(std::string name);
};