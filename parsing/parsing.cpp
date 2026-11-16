#include "parsing.hpp"

parsing::parsing() {}

parsing::~parsing() {}

bool parsing::parseLine(const std::string &line, IRCMessage &message) {
	std::string input = line;
	std::string::size_type pos = 0;
	message.prefix.clear();
	message.command.clear();
	message.params.clear();
	if (!input.empty() && input[input.size() - 1] == '\n')
		input.erase(input.size() - 1);
	if (!input.empty() && input[input.size() - 1] == '\r')
		input.erase(input.size() - 1);
	while (pos < input.size() && (input[pos] == ' ' || input[pos] == '\t'))
		pos++;
	if (pos == input.size())
		return false;
	if (input[pos] == ':') {
		pos++;
		std::string::size_type prefixStart = pos;
		while (pos < input.size() && input[pos] != ' ' && input[pos] != '\t')
			pos++;
		message.prefix = input.substr(prefixStart, pos - prefixStart);
	}
	while (pos < input.size() && input[pos] == ' ' || input[pos] == '\t')
		pos++;
	if (pos == input.size())
		return false;
	std::string::size_type commandStart = pos;
	while (pos < input.size() && input[pos] != ' ' && input[pos] != '\t')
		pos++;
	message.command = input.substr(commandStart, pos - commandStart);
	for (std::string::size_type i = 0; i < message.command.size(); i++)
		message.command[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(message.command[i])));
	while (pos < input.size()) {
		while (pos < input.size() && (input[pos] == ' ' || input[pos] == '\t'))
			pos++;
		if (pos == input.size())
			break;
		if (input[pos] == ':') {
			message.params.push_back(input.substr(pos + 1));
			break;
		}
		std::string::size_type parameterStart = pos;
		while (pos < input.size() && input[pos] != ' ' && input[pos] != '\t')
			pos++;
		message.params.push_back(input.substr(parameterStart, pos - parameterStart));
	}
	return true;
}