/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:28 by pvong             #+#    #+#             */
/*   Updated: 2024/01/18 14:45:01 by kmorin           ###   ########.fr       */
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
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <poll.h>

#define MAX_SOCKETS 10
#define ERR_MAX_CLIENTS "Error: maximum number of clients reached."
#define BUFF_SIZE 4096

class Server {
public:
    Server(const std::string port, const std::string password);
    ~Server();

    void run();
    void deleteClient(std::vector<pollfd> &pollfds, int clientSocketFd);

private:
    struct sockaddr_in _serverAddress;
    // std::map<std::string, std::list<int> > _channels;
    // std::map<int, std::string> _clients;
    int _serverSocketFd;
    std::string _port;
    std::string _password;


};

#endif
