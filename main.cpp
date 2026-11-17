#include "channel/channel.hpp"
#include "server/server.hpp"
#include "parsing/parsing.hpp"
#include <iostream>

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
// 	IRCMessage message;
// 	std::string line = ":nick!user@host PRIVMSG #channel :Hello everyone\r\n";
// 	if (parsing::parseLine(line, message)) {
// 		std::cout << "Prefix: " << message.prefix << std::endl;
// 		std::cout << "Command: " << message.command << std::endl;
// 		for (std::vector<std::string>::size_type i = 0; i < message.params.size(); i++)
// 			std::cout << "Param " << i << ": " << message.params[i] << std::endl;
// 	}
// 	else
// 		std::cout << "Failed to parse line" << std::endl;
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
// 		ser.CloseFds();
// 		std::cerr << e.what() << std::endl;
// 	}
// 	std::cout << "The server Closed" << std::endl;
// }

int main()
{
	std::vector<std::string> testLines;
	testLines.push_back("NICK mynickname");
	testLines.push_back(":nick!user@host PRIVMSG #channel :Hello everyone\r\n");
	testLines.push_back("JOIN #general");
	testLines.push_back("");
	testLines.push_back("   ");
	testLines.push_back("PASS secret");
	testLines.push_back("USER john 0 * :John Doe");
	testLines.push_back("NICK testuser\r\n");
	testLines.push_back("PART #channel :Leaving channel");
	testLines.push_back(":server 001 testuser :Welcome to IRC");
	testLines.push_back("MODE #channel +o testuser");
	testLines.push_back("PRIVMSG #channel :Hello with multiple words");
	testLines.push_back("NOTICE testuser :This is a notice");
	testLines.push_back("  JOIN   # spaced-channel  ");
	testLines.push_back("\tPING server.example.com");
	testLines.push_back(":irc.example.com PONG server.example.com");
	testLines.push_back("QUIT :Goodbye");
	testLines.push_back(":");
	for (std::vector<std::string>::size_type i = 0; i < testLines.size(); i++) {
		IRCMessage message;
		std::cout << "\nInput: [" << testLines[i] << "]" << std::endl;
		if (parsing::parseLine(testLines[i], message)) {
			std::cout << "Prefix: " << message.prefix << std::endl;
			std::cout << "Command: " << message.command << std::endl;
			for (std::vector<std::string>::size_type j = 0; j < message.params.size(); j++)
				std::cout << "Param " << j << ": " << message.params[j] << std::endl;
		}
		else
			std::cout << "Invalid line" << std::endl;
	}
	return (0);
}