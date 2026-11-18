#include "channel/channel.hpp"
#include "server/server.hpp"
#include "parsing/parsing.hpp"
#include "commands/command.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./server <port> <password>" << std::endl;
		return (1);
	}
	std::istringstream port(argv[1]);
	int port_num = 0;
	port >> port_num;
	std::cout << "Port: " << port_num << std::endl;
	IRCMessage message;
	std::string line = ":nick!user@host PRIVMSG #channel :Hello everyone\r\n";
	if (parsing::parseLine(line, message)) {
		std::cout << "Prefix: " << message.prefix << std::endl;
		std::cout << "Command: " << message.command << std::endl;
		for (std::vector<std::string>::size_type i = 0; i < message.params.size(); i++)
			std::cout << "Param " << i << ": " << message.params[i] << std::endl;
	}
	else
		std::cout << "Failed to parse line" << std::endl;
	Server ser(port_num, argv[2]);
	std::cout << "SERVER"<< std::endl;
	try
	{
		if (port_num <= 0 || port_num > 65535)
		{
			throw std::invalid_argument("Invalid port number");
		}
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		ser.ServerInit();
	}
	catch(const std::exception& e)
	{
		//ser.CloseFds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The server Closed" << std::endl;
}

// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 	{
// 		std::cerr << "Usage: ./server <port> <password>" << std::endl;
// 		return (1);
// 	}
// 	std::istringstream port(argv[1]);
// 	int port_num = 0;
// 	port >> port_num;
// 	std::cout << "Port: " << port_num << std::endl;
// 	Server ser(port_num, argv[2]);
// 	std::cout << "SERVER"<< std::endl;
// 	try
// 	{
		
// 		if (port_num <= 0 || port_num > 65535)
// 		{
// 			throw std::invalid_argument("Invalid port number");
// 		}
// 		signal(SIGINT, Server::SignalHandler);
// 		signal(SIGQUIT, Server::SignalHandler);
// 		ser.ServerInit();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		// ser.CloseFds();
// 		std::cerr << e.what() << std::endl;
// 	}
// 	std::cout << "The server Closed" << std::endl;
// }