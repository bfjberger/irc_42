/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:28 by pvong             #+#    #+#             */
/*   Updated: 2024/01/16 12:09:18 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <map>
#include <list>
#include <utility>

#define MAX_SOCKETS 10
#define PORT 8080

struct Message {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    std::string body;
};

class Server {
public:
    Server();
    ~Server();

    void run();
    Message parse_message(std::string message);

private:
    struct sockaddr_in _serverAddress;
    std::map<std::string, std::list<int> > _channels;
    std::map<int, std::string> _clients;
    int _serverSocket;
    static void *handle_client(void *clientSocket);


};

#endif
