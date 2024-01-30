/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:09 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 13:52:07 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>

#include "Color.hpp"

#define FAILURE -1
#define SUCCESS 1
#define BREAK 2
#define CONTINUE 3
#define RETURN 4

#define MAX_SOCKETS 10
#define ERR_MAX_CLIENTS "Error: maximum number of clients reached."
#define BUFF_SIZE 4096

extern bool g_server_running;

#endif //FT_IRC_HPP
