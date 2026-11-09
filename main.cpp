#include "server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./server <port> <password>" << std::endl;
        return (1);
    }
    Server ser;
    std::cout << "SERVER"<< std::endl;
    try
    {
        std::istringstream port(argv[1]);
        int port_num;
        if (!(port >> port_num) || port_num <= 0 || port_num > 65535)
        {
            throw std::invalid_argument("Invalid port number");
        }
        signal(SIGINT, Server::SignalHandler);
        signal(SIGQUIT, Server::SignalHandler);
        ser.ServerInit(port_num);
    }
    catch(const std::exception& e)
    {
        ser.CloseFds();
        std::cerr << e.what() << std::endl;
    }
    std::cout << "The server Closed" << std::endl;
}