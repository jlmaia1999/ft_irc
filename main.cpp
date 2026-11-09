#include "include/Parser.hpp"
#include "include/Command.hpp"
#include "include/Channel.hpp"
#include "server.hpp"
#include <iostream>

static void printCommand(const Command &command)
{
	std::cout << "name: " << command.getName() << std::endl;
	std::cout << "prefix: " << command.getPrefix() << std::endl;

	const std::vector<std::string> &params = command.getParams();
	for (std::size_t i = 0; i < params.size(); ++i)
		std::cout << "param[" << i << "]: " << params[i] << std::endl;

	std::cout << "trailing: " << command.getTrailing() << std::endl;
	std::cout << "--------------------" << std::endl;
}

int main()
{
	std::string remainder;
	std::vector<Command *> commands;
	Command *command;

	commands = Parser::parseBuffer(
		"NICK ali\r\nUSER ali 0 * :Alice\r\nJOIN #general\r\n",
		remainder
	);

	command = new Kick_cmd();

	for (std::size_t i = 0; i < commands.size(); ++i)
		printCommand(*(commands[i]));

	std::cout << "Remainder: [" << remainder << "]" << std::endl;

	commands = Parser::parseBuffer("PRIVMSG #general :hello", remainder);
	std::cout << "After incomplete command:" << std::endl;
	std::cout << "Remainder: [" << remainder << "]" << std::endl;

	commands = Parser::parseBuffer(" world\r\n", remainder);
	for (std::size_t i = 0; i < commands.size(); ++i)
		printCommand(commands[i]);


	return 0;
}

// int main(int argc, char **argv)
// {
//     if (argc != 3)
//     {
//         std::cerr << "Usage: ./server <port> <password>" << std::endl;
//         return (1);
//     }
//     Server ser;
//     std::cout << "SERVER"<< std::endl;
//     try
//     {
//         std::istringstream port(argv[1]);
//         int port_num;
//         if (!(port >> port_num) || port_num <= 0 || port_num > 65535)
//         {
//             throw std::invalid_argument("Invalid port number");
//         }
//         signal(SIGINT, Server::SignalHandler);
//         signal(SIGQUIT, Server::SignalHandler);
//         ser.ServerInit(port_num);
//     }
//     catch(const std::exception& e)
//     {
//         ser.CloseFds();
//         std::cerr << e.what() << std::endl;
//     }
//     std::cout << "The server Closed" << std::endl;
// }