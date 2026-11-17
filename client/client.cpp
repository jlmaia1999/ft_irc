#include "server.hpp"

Client::Client(int socket):
	_username(""),
	_nickname(""),
	_hostname(""),
	_fullname(""),
	_realname(""),
	_socket(socket),
	_userset(false),
	_nickset(false)
{}

Client::~Client()
{
	if (_socket != -1)
		close(_socket);
}

int Client::GetSocket() const
{
	return _socket;
}

void Client::cmd_nick(std::string nickname)
{
	_nickname = nickname;
	_nickset = true;
}

void Client::cmd_user(std::string username, std::string hostname, std::string realname)
{
	_username = username;
	_hostname = hostname;
	_realname = realname;
	_userset = true;
}

void Client::setPassword()
{
	_Password = true;
}

void Client::setIsRegistered()
{
	if (_nickset && _userset && _Password)
		_isRegistered = true;
}

void Client::setIsQuit()
{
	_isQuit = true;
}

void Client::setIsWelcome()
{
	_fullname = _nickname + "!" + _username + "@" + _hostname;
	_isWelcome = true;
}

std::string Client::getUsername() const
{
	return _username;
}

std::string Client::getNickname() const
{
	return _nickname;
}

std::string Client::getHostname() const
{
	return _hostname;
}

std::string Client::getFullname() const
{
	return _fullname;
}

std::string Client::getRealname() const
{
	return _realname;
}

bool Client::getIsRegistered() const
{
	return _isRegistered;
}

bool Client::getIsQuit() const
{
	return _isQuit;
}

bool Client::getIsWelcome() const
{
	return _isWelcome;
}