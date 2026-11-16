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
        std::string _username;
        std::string _nickname;
        std::string _hostname;
        std::string _fullname;
        std::string _realname;
		int _socket;
        bool _userset;
        bool _nickset;

        std::string _input;
        std::string _output;
		
	public:
		Client();
		~Client();
		int GetFd();
		void SetFd(int fd);
		void SetIpadd(std::string ipadd);
};