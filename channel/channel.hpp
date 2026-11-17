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

#include "../client/client.hpp"
#include "../server/server.hpp"
#include "../commands/command.hpp"

class Channel
{
	private:
		std::string _name;
		std::string _hostname;
		std::string _topic;
		std::string _key;
		std::map<Client*, bool> _client;
		std::vector<Client *> _invited_clients;
	public:
		Channel(Server *server, Client &client, std::string name);
		void addClient(Client &client);
		void remClient(Client &op_client, Client &client, std::string why);
		void getClient(std::string name);
		void sendData(Client &client, std::string cmd, std::string msg);
		void getTopic();
		void setTopic(Client &client, std::string topic);
};