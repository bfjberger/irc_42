#include "./Commands/Dcc.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <fstream>


Dcc::Dcc(void){}
Dcc::~Dcc(void){}

void	Dcc::execute(Server* server, t_Message* msg, Client* client)
{
    (void) server;
    (void) msg;
    (void) client;



    if (msg->params[0] == "SEND")
    {
        struct sockaddr_in addr;
        int status;
        socklen_t len = sizeof(struct sockaddr_in);

        status = getsockname(client->getFd(), (struct sockaddr *)&addr, &len);

        char ip_str[INET_ADDRSTRLEN];
        uint16_t port = ntohs(addr.sin_port);

        inet_ntop(AF_INET, &addr, ip_str, INET_ADDRSTRLEN); //if error return null
        std::stringstream ss;
        ss << port;
        std::string strValue = ss.str();

        const char* filePath = msg->params[1].c_str();

    // Open the file in binary mode
        std::ifstream file(filePath, std::ios::binary);

        if (file.is_open()) 
        {
            // Determine the file size by seeking to the end
            file.seekg(0, std::ios::end);
            std::streampos fileSize = file.tellg();

            std::cout << "File size: " << fileSize << " bytes" << std::endl;

            // Close the file
            file.close();

            std::ostringstream oss;
            oss << fileSize;
            std::string fileSizeStr = oss.str();

        std::string dccSendMsg = ":" + client->getNick() + "!" + client->getUserName() + "@" + client->getHostname() + " PRIVMSG " 
        + msg->params[2] + " :DCC SEND" + msg->params[1] + ip_str + strValue + fileSizeStr;
        } 
        else 
        {
        std::cerr << "Error opening the file." << std::endl;
        }

    }
    if (msg->params[0] == "GET")
    {
        
    }
}

// arg 1 = send or get, arg 2 = file name, arg 3 = user name of target client
// :testK!~kmorin@67ad-8ab6-b0a4-3ff5-ce28.25.185.ip PRIVMSG bbr :DCC SEND test.txt 168560387 53036 2
// std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
// 		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
// 		return;

