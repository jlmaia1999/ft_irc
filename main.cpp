#include "include/Parser.hpp"
#include "include/Command.hpp"
#include "include/Channel.hpp"
#include <iostream>

// int main()
// {
// 	Parser parser;
// 	std::string remainder;
// 	std::vector<Command> commands;
// 	commands = Parser::parseBuffer("NICK ali\r\nUSER ali 0 * :Alice", remainder);
// 	commands = Parser::parseBuffer(" Smith\r\nJOIN #general\r\n", remainder
// );
// 	for (std::size_t i = 0; i < commands.size(); ++i) {
// 		std::cout << "command " << i << ":" << std::endl;
// 		std::cout << "name: " << commands[i].name << std::endl;
// 		for (std::size_t j = 0; j < commands[i].params.size(); ++j)
// 			std::cout << "param[" << j << "]: "
// 				<< commands[i].params[j] << std::endl;
// 		if (!commands[i].trailing.empty())
// 			std::cout << "trailing: "
// 				<< commands[i].trailing << std::endl;
// 		std::cout << std::endl;
// 	}
// 	return 0;
// }

int main()
{
	Channel channel("#general");
	std::cout << channel.getName()<< std::endl << "Initially empty: " << channel.empty() << std::endl;
	channel.addMember(1);
	channel.addMember(2);
	std::cout << "Client 1 joined: " << channel.hasMember(1) << std::endl;
	std::cout << "Client 2 joined: " << channel.hasMember(2) << std::endl;
	std::cout << "Client 3 joined: " << channel.hasMember(3) << std::endl;
	channel.removeMember(1);
	std::cout << "Client 1 after PART: " << channel.hasMember(1) << std::endl;
	std::cout << "Client 2 still present: " << channel.hasMember(2) << std::endl;
	channel.removeMember(2);
	std::cout << "Empty after everyone leaves: " << channel.empty() << std::endl;
	return 0;
}