#include "../include/Command.hpp"

Command::Command(std::string prefix, std::string name, std::vector<std::string> params, std::string trailing)\
:_prefix(prefix), _name(name), _params(params), _trailing(trailing) {

}

Command::~Command() {

}

const std::string &Command::getPrefix() const {
	return (_prefix);
}

const std::string &Command::getName() const {
	return (_name);
}

const std::vector<std::string> &Command::getParams() const {
	return (_params);
}

const std::string &Command::getTrailing() const {
	return (_trailing);
}

Kick_cmd::Kick_cmd(std::string prefix, std::string name, std::vector<std::string> params, std::string trailing)\
: Command(prefix, name, params, trailing){

}

Kick_cmd::~Kick_cmd(){
	
}

void Kick_cmd::kick(Client client_id, Channel channel)
{
	channel.removeMember(client_id);
}

