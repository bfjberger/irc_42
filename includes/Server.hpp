/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:28 by pvong             #+#    #+#             */
/*   Updated: 2024/01/23 15:44:16 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

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

#include "ft_irc.hpp"
#include "Client.hpp"
#include "Numeric_Replies.hpp"

#define MAX_SOCKETS 10
#define ERR_MAX_CLIENTS "Error: maximum number of clients reached."
#define BUFF_SIZE 4096

typedef struct s_Message {

	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;

	bool	hasPrefix;
	bool	hasCommand;
	bool	wrongPrefix;
	// std::string	name;
	// std::string	message;
}	t_Message;

#include "ACommand.hpp"

class ACommand;

// #include "Commands/Join.hpp"
// #include "Commands/Kick.hpp"
// #include "Commands/Kill.hpp"
// #include "Commands/Mode.hpp"
// #include "Commands/Nick.hpp"
// #include "Commands/Oper.hpp"
// #include "Commands/Part.hpp"
// #include "Commands/Pass.hpp"
// #include "Commands/Privmsg.hpp"
// #include "Commands/Quit.hpp"
// #include "Commands/Topic.hpp"
// #include "Commands/User.hpp"


class Server {

	private:
		struct sockaddr_in			_serverAddress;
		std::map<const int, Client *>	_clients;

		std::map<std::string, ACommand *> _commands;

		int			_serverSocketFd;

		std::string	_port;
		std::string	_password;
		std::string	_version;
		std::string	_name;

	public:
		Server(const std::string port, const std::string password);
		~Server();

		//SERVER MANAGEMENT
		void	deleteClient(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it);
		void	handleMaxClient(int clientSocketFd);
		void	addClient(int clientSocketFd, std::vector<pollfd> &pollfds);
		int		acceptSocket(int listenSocket);
		void	run();

		//GETTER
		std::string const &getPass() const;

		//PARSER
		t_Message*	parseCommands(std::string message, Client* client);
		void		parsePrefix(std::string& message, t_Message* msg, Client* client);
		void		fillUserInfo(std::map<const int, Client *> &clients, int clientSocketFd, std::string message);
		void		splitMessage(std::vector<std::string> &cmds, std::string msg);
		void		parser(std::string message, int clientSocketFd);

		//EXECUTION
		void		execCommand(t_Message* msg, Client* client);

/* ------------------------------ REGISTRATION ------------------------------ */
// TODO: work on the parsing to get the user info -> NICK, USER
// link parsing: https://tools.ietf.org/html/rfc2812#section-2.3.1
// TODO: work on the commands, PASS, NICK, USER -> RPL_WELCOME
// link welcome: https://tools.ietf.org/html/rfc2812#section-5.1
// TODO: work on the replies -> RPL_WELCOME, RPL_YOURHOST, RPL_CREATED, RPL_MYINFO

// TODO: ADD a map of channels

};

#include "Commands/Invite.hpp"

#endif
