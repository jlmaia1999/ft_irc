#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>
#include "Channel.hpp"

class Command
{
	private:
		std::string _prefix;
		std::string _name;
		std::vector<std::string> _params;
		std::string _trailing;
	public:
		Command(std::string prefix, std::string name, std::vector<std::string> params, std::string trailing);
		~Command();
		const std::string &getPrefix() const;
		const std::string &getName() const;
		const std::vector<std::string> &getParams() const;
		const std::string &getTrailing() const;
};

class Kick_cmd : public Command 
{
	public:
		void kick(Client client_id, Channel channel);
		Kick_cmd(std::string prefix, std::string name, std::vector<std::string> params, std::string trailing);
		~Kick_cmd();
};


#endif