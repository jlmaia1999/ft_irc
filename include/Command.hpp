#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>

class Command
{
	public:
		std::string prefix;
		std::string name;
		std::vector<std::string> params;
		std::string trailing;
};

#endif