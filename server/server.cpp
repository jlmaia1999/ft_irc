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
	while (_running)
	{
		int res = poll(&_fds[0], _fds.size(), -1);

		if(res == -1)
		{
			if (errno == EINTR)
				continue;
			throw std::runtime_error("Error:poll failed");
		}
		size_t i = _fds.size() - 1;
		while(i >= 1)
		{
			int cli_fd = _fds[i].fd;
			short revents = _fds[i].revents;
			if (revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				RemoveData(i);
				i--;
				continue;
			}
			if (revents & POLLIN)
			{
				ReceiveNewData(i);
				if(i >= _fds.size() || _fds[i].fd != cli_fd)
				{
					--i;
					continue;
				}
			}
			if (revents & POLLOUT)
				SendData(i);
			--i;
		}
		for (int j = 0; j < _Quiting.size(); j++)
			RemoveData(_Quiting[j]);
		_Quiting.clear();
		if (_fds[0].revents & POLLIN)
			AcceptNewClient();
	}
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
	_fds.push_back(NewPoll);
	std::cout << "Server listening on port " << _Port << std::endl;
}

void Server::ReceiveNewData(int i)
{
	char buff[512];
	memset(buff, 0, sizeof(buff));
	int cli_fd = _fds[i].fd;
	Client *cli = _clients[cli_fd];

	ssize_t bytes = recv(_fds[i].fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		RemoveData(i);
		return;
	}
	if (bytes >= 512)
	{
		std::cout << "Error: Input too long" << std::endl;
		cli->ft_getline();
		return ;
	}
	std::string data(buff, bytes);
	cli->addInput(data);
	while(cli->fullLine())
	{
		std::string line = cli->ft_getline();
		std::cout << "Message from " << cli->getNickname() << ": " << line <<std::endl;
		//call cmd function
	}
	if (cli->getIsQuit())
		_Quiting.push_back(i);
}

void Server::AcceptNewClient()
{
	while (_running)
	{
		sockaddr_in cli_adrr;
		socklen_t cli_len = sizeof(cli_adrr);

		int cli_fd = accept(_SocketFd, reinterpret_cast<sockaddr*>(&cli_adrr), &cli_len);
		if (cli_fd == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			if (errno = EINTR)
				continue;
			throw std::runtime_error("could not accept");
		}
		if (fcntl(cli_fd, F_SETFL, O_NONBLOCK) == -1)
		{
			close(cli_fd);
			std::cerr << "Error: fcntl failed" << std::endl;
			return;
		}
		char ip_buffer[INET_ADDRSTRLEN];
		const char *ip = inet_ntop(AF_INET, &cli_adrr.sin_addr, ip_buffer, sizeof(ip_buffer));
		if(ip = NULL)
		{
			close (cli_fd);
			std::cerr << "Error: inet_ntop failed" << std::endl;
			return ;
		}
		int cli_Port = htons(cli_adrr.sin_port);
		Client* client = new Client(cli_fd);
		_clients[cli_fd] = client;
		pollfd cli_Poll;
		cli_Poll.fd = cli_fd;
		cli_Poll.events = POLLIN;
		cli_Poll.revents = 0;
		_fds.push_back(cli_Poll);
		std::cout << "Client " << cli_fd << " has connected. ip = " << ip << ", port = " << cli_Port << std::endl;
	}
}

void Server::RemoveData(int i)
{
	std::cout << "Data removed" << std::endl;
}

void Server::SendData(int i)
{
	std::cout << "Data sent"<< std::endl;
}

void Server::SignalHandler(int signum)
{
	(void)signum;
	Server::Signal = true;
}


std::string Server::GetHostname()
{
	return _hostname;
}