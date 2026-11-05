#include "server.hpp"

Client::Client(): _fd(0), _ipadd(NULL){}

Client::~Client(){}

int Client::GetFd()
{
    return _fd;
}

void Client::SetFd(int fd)
{
    _fd = fd;
}

void Client::SetIpadd(std::string ipadd)
{
    _ipadd = ipadd;
}