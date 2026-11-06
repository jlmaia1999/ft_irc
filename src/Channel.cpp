#include "../include/Channel.hpp"

Channel::Channel(const std::string &name) : _name(name) {}

const std::string &Channel::getName() const {
	return _name;
}

void Channel::addMember(int client_id) {
	_members.insert(client_id);
}

void Channel::removeMember(int client_id) {
	_members.erase(client_id);
	_operators.erase(client_id);
}

bool Channel::hasMember(int client_id) const {
	return _members.find(client_id) != _members.end();
}

bool Channel::empty() const {
	return _members.empty();
}