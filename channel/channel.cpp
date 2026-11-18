#include "channel.hpp"

Channel::Channel(Server *server, Client &client, std::string name) : _name(name), _hostname(""), _topic(""), _key("") {
	(void)server;
	_clients[&client] = true;
}

void Channel::addClient(Client &client) {
	if (!hasClient(client))
		_clients[&client] = false;
}

void Channel::remClient(Client &op_client, Client &client, std::string why) {
	(void)op_client;
	(void)why;
	std::map<Client *, bool>::iterator it = _clients.find(&client);
	if (it != _clients.end())
		_clients.erase(it);
}

Client *Channel::getClient(const std::string &name) {
	
}

void Channel::sendData(Client &client, std::string cmd, std::string msg) {

}

const std::string &Channel::getTopic() const {
	return _topic;
}

void Channel::setTopic(Client &client, std::string topic) {
	if (isOperator(client))
		_topic = topic;
}

bool Channel::hasClient(Client &client) const {
	return _clients.find(&client) != _clients.end();
}

bool Channel::isOperator(Client &client) const {
	std::map<Client *, bool>::const_iterator it = _clients.find(&client);
	if (it == _clients.end())
		return false;
	return it->second;
}

bool Channel::isEmpty() const {
	return _clients.empty();
}
