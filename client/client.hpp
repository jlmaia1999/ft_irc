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
#include "../channel/channel.hpp"
#include "../commands/command.hpp"


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