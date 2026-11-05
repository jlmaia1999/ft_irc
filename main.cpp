#include "include/Parser.hpp"
#include "include/Command.hpp"
#include <iostream>

int main()
{
	std::string raw = "NICK alice\r\nUSER alice 0 * :Alice Smith\r\nJOIN #general\r\n";
	std::vector<Command> commands = Parser::parseBuffer(raw);
	for (std::size_t i = 0; i < commands.size(); ++i) {
		std::cout << "command " << i << ":" << std::endl;
		std::cout << "name: " << commands[i].name << std::endl;
		for (std::size_t j = 0; j < commands[i].params.size(); ++j)
			std::cout << "param[" << j << "]: " << commands[i].params[j] << std::endl;
		if (!commands[i].trailing.empty())
			std::cout << "trailing: " << commands[i].trailing << std::endl;
		std::cout << std::endl;
	}
	return 0;
}