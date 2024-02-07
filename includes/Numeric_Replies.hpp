/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric_Replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:31:31 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/07 15:47:02 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

/*
	Generated after the execution of IRC commands following certain conditions

	RPL -> command responses
	ERR -> error replies
*/

#define USER_ID(user) (user->getNick() + "!" + user->getUserName() + "@" + user->getAddress())
#define RPL_WELCOME(nickname, host, user_id) (":" + host + " 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n") //001

#define MSG_START(client) (":localhost " + client + " ")

/* ************************************************************************** */
/*                             COMMAND RESPONSES                              */
/* ************************************************************************** */

// JOIN RPL
#define RPL_JOIN(client, channel) (":" + USER_ID(client) + " JOIN " + channel + "\r\n") //JOIN
#define RPL_ENDOFNAMES(address, client, channel) (":" + address + " 366 " + client + " " + channel + " :End of /NAMES list\r\n") //366
#define RPL_NAMREPLY(address, client, channel, nickname) (":" + address + " 353 " + client + " = " + channel + " :" + nickname + "\r\n") //353

// PART
#define RPL_PART(client, channel, reason) (":" + USER_ID(client) + " PART " + channel + " " + (reason.empty() ? "." : reason ) + "\r\n")

// PING
#define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n") // PONG

#define RPL_PING(user_id, token) (user_id + " PING " + token + "\r\n") // PING

#define RPL_PRIVMSG(nickname, message) (":localhost " + nickname + ": " + message + "\r\n") // PRIVMSG

#define RPL_NICKCHANGE(nickname) ("You're now known as " + nickname + "\r\n") //NICK

#define RPL_NICK(client, nick) (":" + USER_ID(client) + " NICK " + nick + "\r\n") // NICK

#define RPL_UMODEIS(address, client, string) (":" + address + " 221 " + client + " " + string + "\r\n") //221

#define RPL_CHANNELMODEIS(address, client, channel, mode) (":" + address + " 324 " + client + " " + channel + " " + mode + "\r\n") //324

#define RPL_NOTOPIC(address, client, channel) (":" + address + " 331 " + client + " " + channel + " :No topic is set\r\n") //331

#define RPL_TOPIC(address, client, channel, topic) (":" + address + " 332 " + client + " " + channel + " :" + topic + "\r\n") //332

#define RPL_INVITING(address, client, channel, nick) (":" + address + " 341 " + nick + " " + client + " " + channel + "\r\n") //341

#define RPL_BANLIST(address, client, channel, banid) (":" + address + " 367 " + client + " " + channel + " " + banid + "\r\n") //367

#define RPL_ENDOFBANLIST(address, client, channel) (":" + address + " 368 " + client + " " + channel + " :End of channel ban list\r\n") //368

#define RPL_MOTD(address, client, text) (":" + address + " 372 " + client + " :- " + text + "\r\n") //372

#define RPL_MOTDSTART(address, client, server) (":" + address + " 375 " + client + " :- " + server + " Message of the day - \r\n") //375

#define RPL_ENDOFMOTD(address, client) (":" + address + " 376 " + client + " :End of MOTD command\r\n") //376

#define RPL_YOUREOPER(address, client) (":" + address + " 381 " + client + " :You are now an IRC operator\r\n") //381

/* ************************************************************************** */
/*                               ERRORS REPLIES                               */
/* ************************************************************************** */

#define ERR_NOSUCHNICK(address, client, nickname) (":" + address + " 401 " + client + " " + nickname + " :No such nick/channel\r\n") //401

#define ERR_NOSUCHCHANNEL(address, client, channel) (":" + address + " 403 " + client + " " + channel + " :No such channel\r\n") //403

#define ERR_CANNOTSENDTOCHAN(address, client, channel) (":" + address + " 404 " + client + " " + channel + " :Cannot send to channel\r\n") //404

#define ERR_TOOMANYCHANNELS(address, client, channel) (":" + address + " 405 " + client + " " + channel + " :You have joined too many channels\r\n") //405

#define ERR_TOOMANYTARGETS(address, client, target) (":" + address + " 407 " + client + " " + target + " :Duplicate recipients. No message delivered\r\n") //407

#define ERR_NORECIPIENT(address, client, command) (":" + address + " 411 " + client + " :No recipient given (" + command + ")\r\n") //411

#define ERR_NOTEXTTOSEND(address, client) (":" + address + " 412 " + client + " :No text to send\r\n") //412

#define ERR_NOTOPLEVEL(address, client, mask) (":" + address + " 413 " + client + " " + mask + " :No toplevel domain specified\r\n") //413

#define ERR_WILDTOPLEVEL(address, client, mask) (":" + address + " 414 " + client + " " + mask + " :Wildcard in toplevel domain\r\n") //414

#define ERR_UNKNOWNCOMMAND(address, client, command) (":" + address + " 421 " + client + " " + command + " :Unknown command\r\n") //421

#define ERR_NOMOTD(address, client) (":" + address + " 422 " + client + " :MOTD File is missing\r\n") //422

#define ERR_NONICKNAMEGIVEN(address, client) (":" + address + " 431 " + client + " :No nickname given\r\n") //431

#define ERR_ERRONEUSNICKNAME(address, client, nick) (":" + address + " 432 " + client + " " + nick + " :Erroneous nickname\r\n") //432

#define ERR_NICKNAMEINUSE(address, client, nick) (":" + address + " 433 " + client + " " + nick + " :Nickname is already in use\r\n") //433

#define ERR_NICKCOLLISION(address, client, nick) (":" + address + " 436 " + client + " " + nick + " :Nickname collision KILL\r\n") //436

#define ERR_USERNOTINCHANNEL(address, client, nick, channel) (":" + address + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n") //441

#define ERR_NOTONCHANNEL(address, client, channel) (":" + address + " 442 " + client + " " + channel + " :You're not on that channel\r\n") //442

#define ERR_USERONCHANNEL(address, client, user, channel) (":" + address + " 443 " + client + " " + user + " " + channel + " :is already on channel\r\n") //443

#define ERR_NEEDMOREPARAMS(address, client, command) (":" + address + " 461 " + client + " " + command + " :Not enough parameters\r\n") //461

#define ERR_ALREADYREGISTRED(address, client) (":" + address + " 462 " + client + " :You may not reregister\r\n") //462

#define ERR_PASSWDMISMATCH(address, client) (":" + address + " 464 " + client + " :Password incorrect\r\n") //464

#define ERR_KEYSET(address, client, channel) (":" + address + " 467 " + client + " " + channel + " :Channel key already set\r\n") //467

#define ERR_CHANNELISFULL(address, client, channel) (":" + address + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n") //471

#define ERR_UNKNOWNMODE(address, client, cara) (":" + address + " 472 " + client + " " + cara + " :is unknown mode char to me\r\n") //472

#define ERR_INVITEONLYCHAN(address, client, channel) (":" + address + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n") //473

#define ERR_BANNEDFROMCHAN(address, client, channel) (":" + address + " 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n") //474

#define ERR_BADCHANNELKEY(address, client, channel) (":" + address + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n") //475

#define ERR_NOPRIVILEGES(address, client) (":" + address + " 481 " + client + " :Permission Denied- You're not an IRC operator\r\n") //481

#define ERR_CHANOPRIVSNEEDED(address, client, channel) (":" + address + " 482 " + client + " " + channel + " :You're not channel operator\r\n") //482

#define ERR_CANTKILLSERVER(address, client) (":" + address + " 483 " + client + " :You can't kill a server!\r\n") //483

#define ERR_RESTRICTED(address, client) (":" + address + " 484 " + client + " :Your connection is restricted!\r\n") //484

#define ERR_NOOPERHOST(address, client) (":" + address + " 491 " + client + " :No O-lines for your host\r\n") //491

#define ERR_UMODEUNKNOWNFLAG(address, client) (":" + address + " 501 " + client + " :Unknown MODE flag\r\n") //501

#define ERR_USERSDONTMATCH(address, client) (":" + address + " 502 " + client + " :Cant change mode for other users\r\n") //502

#endif //NUMERIC_REPLIES_HPP
