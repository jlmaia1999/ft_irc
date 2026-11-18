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

class Server;

class Client
{
	private:
		std::string _username;
		std::string _nickname;
		std::string _hostname;
		std::string _fullname;
		std::string _realname;
		int _socket;
		bool _Password;
		bool _userset;
		bool _nickset;
		bool _isRegistered;
		bool _isQuit;
		bool _isWelcome;

		std::string _input;
		std::string _output;
		
	public:
		Client(int socket);
		Client &operator=(const Client &other);
		~Client();
		int GetSocket() const;
		void setPassword();
		void setIsRegistered();
		void setIsQuit();
		void setIsWelcome();

		std::string getUsername() const;
		std::string getNickname() const;
		std::string getHostname() const;
		std::string getFullname() const;
		std::string getRealname() const;
		bool getIsRegistered() const;
		bool getIsQuit() const;
		bool getIsWelcome() const;


		void cmd_nick(std::string nickname);
		void cmd_user(std::string username, std::string hostname, std::string realname);

		void addInput(const std::string &data);
		bool fullLine() const;

		void addOutput(const std::string &data);
		bool pendOutput() const;
		const std::string &getOutput() const;
		void RemoveOutput(std::string::size_type size);
		std::string ft_getline();
};