#include "include/Parser.hpp"
#include "include/Command.hpp"
#include <iostream>

int main()
{
	std::string msg1 = "NICK alice\r\n";
	std::string msg2 = "USER alice 0 * :Alice Smith\r\n";

	Command c1 = Parser::parseLine(msg1);
	Command c2 = Parser::parseLine(msg2);

	std::cout << "c1 name: " << c1.name << std::endl;
	std::cout << "c1 param: " << c1.params[0] << std::endl;
	std::cout << std::endl;
	std::cout << "c2 name: " << c2.name << std::endl;
	std::cout << "c2 param: " << c2.params[0] << std::endl;
	std::cout << "c2 trailing: " << c2.trailing << std::endl;

	return 0;
}