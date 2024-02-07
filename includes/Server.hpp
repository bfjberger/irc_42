/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:28 by pvong             #+#    #+#             */
/*   Updated: 2024/02/06 23:06:22 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

#include "Client.hpp"
#include "Channel.hpp"
#include "Numeric_Replies.hpp"

typedef struct s_Message {

	std::string					prefix;
	std::string					command;

	std::vector<std::string>	params;

	// A function that returns a string from all the params

	bool	hasPrefix;
	bool	hasCommand;
	bool	error;
}	t_Message;

std::string	getParams(t_Message* msg, int index = 0);

#include "Bot.hpp"
#include "ACommand.hpp"

#include "Commands/Invite.hpp"
#include "Commands/Join.hpp"
#include "Commands/Kick.hpp"
#include "Commands/Kill.hpp"
#include "Commands/Mode.hpp"
#include "Commands/Nick.hpp"
#include "Commands/Oper.hpp"
#include "Commands/Part.hpp"
#include "Commands/Pass.hpp"
#include "Commands/Privmsg.hpp"
#include "Commands/Quit.hpp"
#include "Commands/Topic.hpp"
#include "Commands/User.hpp"

class Bot;

class ACommand;

class Server {

	private:
		struct sockaddr_in					_serverAddress;

		std::map<int, Client *>				_clients;
		std::map<std::string, ACommand *>	_commands;
		std::map<std::string, Channel *>	_channels;
		std::map<int, std::string>			_aggMessages;
		std::map<int, bool>					_aggMessagesStatus;
		int			_serverSocketFd;

		std::string	_port;
		std::string	_password;
		std::string	_version;
		std::string	_name;
		bool		_running;
		bool		_capStatus;

		std::pair<int, Bot*>		_bot;

	public:
		Server(const std::string port, const std::string password);
		~Server();

		//SERVER MANAGEMENT
		void	launch();
		int		createClientConnection(std::vector<pollfd>& pollfds, std::vector<pollfd>& newPollfds);
		int		handleExistingConnection(std::vector<pollfd>& pollfds, std::vector<pollfd>::iterator it);
		int		handlePollout(std::vector<pollfd>& pollfds, std::vector<pollfd>::iterator it);
		int		handlePollErr(std::vector<pollfd>& pollfds, std::vector<pollfd>::iterator it);
		void	handleMaxClient(int clientSocketFd);
		int		acceptSocket(int listenSocket);
		void	eraseClientFromMaps(int clientFd);
		void	run();

		//CLIENT
		void	addClient(int clientSocketFd, std::vector<pollfd>& pollfds);
		void	deleteClient(std::vector<pollfd>& pollfds, std::vector<pollfd>::iterator it);
		bool	isNick(std::string nick);

		//CHANNEL
		bool	isChannel(std::string channelName);
		void	addChannel(Channel* channel);
		void	removeChannel(std::string channelName);

		//GETTERS
		std::string const &getPass() const;

		const std::map<int, Client*>&	getClients() const;
		Client*							getClient(std::string nickname);

		const std::map<std::string, Channel*>&	getChannels() const;
		Channel*								getChannel(std::string channelName);

		Bot*	getBot() const;

		//PARSER
		t_Message*	parseCommands(std::string message, Client* client);
		void		parsePrefix(std::string& message, t_Message* msg, Client* client);
		void		fillUserInfo(std::map<int, Client *>::iterator &it, std::string message);
		void		splitMessage(std::vector<std::string> &cmds, std::string msg);
		void		parser(std::string message, int clientSocketFd);

		//EXECUTION
		void		execCommand(std::string message, Client* client);

/* ---------------------------- LINKS AND OTHERS ---------------------------- */
// link parsing: https://tools.ietf.org/html/rfc2812#section-2.3.1
// TODO: work on the commands
// link welcome: https://tools.ietf.org/html/rfc2812#section-5.1
// TODO: work on the replies -> RPL_WELCOME, RPL_YOURHOST, RPL_CREATED, RPL_MYINFO

// TODO: ADD the management of the channels (if not all done by the commands)

};

std::string	tmpFormatString(std::string msg);
void		trimString(std::string &str);

#endif //SERVER_HPP
