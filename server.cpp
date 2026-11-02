#pragma once

#include <iostream>
#include <vector>
#include <poll.h>

class server
{
	private:
		std::vector<int> _clients; //type is Client, switch once the class is created
		int	_Port;
		int	ScocketFd;
		static bool Signal;
		std::vector<struct pollfd> fds;

		public:
			server();
			~server();
};