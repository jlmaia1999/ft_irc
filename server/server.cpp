#include "server.hpp"
bool Server::Signal = false;

Server::Server(int port, std::string password):
	_running(false),
	_hostname("127.0.0.1"),
	_Port(port),
	_Password(password),
	_SocketFd(-1),
	_clients(),
	_channels(){}

Server::~Server()
{
	if (_SocketFd != -1)
		close(_SocketFd);
}

void Server::ServerInit()
{
	_running = true;
	ServerSocket();
	
}

void Server::ServerSocket()
{
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET;
	add.sin_port = htons(_Port);
	add.sin_addr.s_addr = INADDR_ANY;

	_SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(_SocketFd == -1)
		throw(std::runtime_error("failed to create socket"));
	int en = 1;
	if(setsockopt(_SocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("failed to set option (SO_REUSADRR) on socket"));
	if(fcntl(_SocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("failed to set option (O_NONBLOCK) on socket"));
	if(bind(_SocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("failed to bind socket"));
	if (listen(_SocketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() failed"));
	
	NewPoll.fd = _SocketFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
	std::cout << "Server listening on port " << _Port << std::endl;
}

void Server::run()
{
	while (Server::Signal == false)
	{
		int res = (poll(&fds[0], fds.size(), -1) == -1);
		if (res = -1)
			throw(std::runtime_error("poll() failed"));
		for (size_t i = 0; i < fds.size(); i++)
		{
			int clientsfd = fds[i].fd;
			int revents = fds[i].revents;
			if (revents & (POLL_ERR | POLL_HUP | POLLNVAL))
			{
				RemoveData(i);
				i--;
				continue;
			}
			if (revents & POLLIN)
			{
				ReceiveNewData(i);
				if (i >= fds.size() || fds[i].fd != clientsfd)
				{
					i--;
					continue;
				}
			}
			if (revents & POLLOUT)
				SendData(i);
			i--;
		}
		if (fds[0].revents & POLLIN)
			AcceptNewClient();
	}
	CloseFds();
}

void Server::CloseFds()
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		std::cout <<"Client <" << _clients[i].GetFd() << "> Disconnected" << std::endl;
		close(_clients[i].GetFd());
	}
	if (_SocketFd != -1)
	{
		std::cout << "Server <" << _SocketFd << "> Disconnected" << std::endl;
		close(_SocketFd);
	}
}

void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client: " << fd << " has Disconected" << std::endl;
		ClearClients(fd);
		close(fd);
	}
}

void Server::AcceptNewClient()
{
	Client cli;
	struct sockaddr_in cli_add;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cli_add);

	int incofd = accept(_SocketFd, (sockaddr *)&(cli_add), &len);
	if(incofd == -1)
	{
		std::cout << "accept() failed"<<std::endl;
		return;
	}
	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
		return;
	}

	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	cli.SetFd(incofd);
	cli.SetIpadd(inet_ntoa(cli_add.sin_addr));
	_clients.push_back(cli);
	fds.push_back(NewPoll);
}

void Server::SignalHandler(int signum)
{
	(void)signum;
	Server::Signal = true;
}

void Server::ClearClients(int fd)
{
	for(size_t i = 0; i < fds.size(); i++)	
	{
		if (fds[i].fd == fd)
		{
			fds.erase(fds.begin() + i);
			break;
		}
	}
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if(_clients[i].GetFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

std::string Server::GetHostname()
{
	return _hostname;
}