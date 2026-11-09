#include "../include/Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

Command Parser::parseLine(const std::string &line) {
	std::string prefix;
	std::string name;
	std::vector<std::string> params;
	std::string trailing;
	std::string input = line;
	while (!input.empty() && (input[input.size() - 1] == '\n' || input[input.size() - 1] == '\r'))
		input.erase(input.size() - 1, 1);
	if (input.empty())
		Command(prefix, name, params, trailing);
	if (!input.empty() && input[0] == ':') {
		std::string::size_type pos = input.find(' ');
		if (pos == std::string::npos)
			Command(prefix, name, params, trailing);
		prefix = input.substr(1, pos - 1);
		input = input.substr(pos + 1);
	}
	while (!input.empty() && input[0] == ' ')
		input.erase(0, 1);
	if (input.empty())
		Command(prefix, name, params, trailing);
	std::string::size_type pos = input.find(' ');
	if (pos == std::string::npos) {
		name = input;
		Command(prefix, name, params, trailing);
	}
	name = input.substr(0, pos);
	input = input.substr(pos + 1);
	while (!input.empty()) {
		while (!input.empty() && input[0] == ' ')
			input.erase(0, 1);
		if (input.empty())
			break;
		if (input[0] == ':') {
			trailing = input.substr(1);
			break ;
		}
		pos = input.find(' ');
		if (pos == std::string::npos) {
			params.push_back(input);
			break;
		}
		params.push_back(input.substr(0, pos));
		input = input.substr(pos + 1);
	}
	return Command(prefix, name, params, trailing);
}

std::vector<Command> Parser::parseBuffer(const std::string &buffer, std::string &remainder) {
	std::vector<Command> cmds;
	remainder += buffer;
	std::string::size_type pos;
	while ((pos = remainder.find("\r\n")) != std::string::npos) {
		std::string line = remainder.substr(0, pos);
		remainder.erase(0, pos + 2);
		if (!line.empty())
			cmds.push_back(parseLine(line));
	}
	return cmds;
}
