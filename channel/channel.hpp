#pragma once

#include <iostream>
#include <vector> 
#include <cstring>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <poll.h> 
#include <csignal> 
#include <sstream>

#include "../client/client.hpp"
#include "../server/server.hpp"
#include "../commands/command.hpp"

class Channel
{
    std::string _name;
    std::string _hostname;
    std::string _topic;
    std::string _key;
    std::vector<Client *> _client;
    std::vector<Client *> _op_clients;
    std::vector<Client *> _invited_clients;

    
};