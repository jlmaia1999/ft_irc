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
        signal(SIGINT, Server::SignalHandler);
        signal(SIGQUIT, Server::SignalHandler);
        ser.ServerInit(std::atoi(argv[1]));
    }
    catch(const std::exception& e)
    {
        ser.CloseFds();
        std::cerr << e.what() << std::endl;
    }
    std::cout << "The server Closed" << std::endl;

}