#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include "Command.hpp"

class Parser
{
	private:
		
	public:
		Parser();
		~Parser();
		static Command parseLine(const std::string &line);
};

#endif