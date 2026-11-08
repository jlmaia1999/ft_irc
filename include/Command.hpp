#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>

class Command
{
	private:
		std::string prefix;
		std::string name;
		std::vector<std::string> params;
		std::string trailing;
	public:
		Command(std::string prefix, std::string name, std::vector<std::string> params, std::string trailing);
		virtual ~Command() = 0;
		const std::string &getPrefix() const;
		const std::string &getName() const;
		const std::vector<std::string> &getParams() const;
		const std::string &getTrailing() const;
};

#endif