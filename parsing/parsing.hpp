#pragma once

#include <iostream>
#include <vector>
#include <cctype>

struct IRCMessage
{
	std::string prefix;
	std::string command;
	std::vector<std::string> params;
};

class parsing
{
	public:
		parsing();
		~parsing();
		static bool parseLine(const std::string &line, IRCMessage &message);
};