/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric_Replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:31:31 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 13:53:51 by kmorin           ###   ########.fr       */
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

#define USER_ID(user) (user->getNick() + "!" + user->getUserName() + "@" + user->getHostname())
#define RPL_WELCOME(nickname, host, user_id) (":" + host + " 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n") //001

#define MSG_START(client) (":localhost " + client + " ")

/* ************************************************************************** */
/*                             COMMAND RESPONSES                              */
/* ************************************************************************** */

#define RPL_NICKCHANGE(nickname) ("You're now known as " + nickname + "\r\n") //NICK

#define RPL_UMODEIS(client, string) (": localhost 221 " + client + " Your user mode is [" + string + "]\r\n") //221

#define RPL_AWAY() (": localhost 301" + "<nick> :<away message>\r\n") //301

#define RPL_CHANNELMODEIS(channel, mode) (": localhost 324 " + channel + " [" + mode + "]\r\n") //324

#define RPL_NOTOPIC(client, channel) (":localhost 331 " + client + " " + channel + " :No topic is set\r\n") //331

#define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " " + channel + " : " + topic + "\r\n") //332

#define RPL_INVITING(client, channel, nick) (":localhost 341 " + client + " " + channel + " " + nick + "\r\n") //341

#define RPL_BANLIST(client, channel, banid) (":localhost 367 " + client + " " + channel + " " + banid + "\r\n") //367

#define RPL_ENDOFBANLIST(client, channel) (":localhost 368 " + client + " " + channel + " :End of channel ban list\r\n") //368

#define RPL_MOTD(client, text) (":localhost 372 " + client + " " + ":- " + text + "\r\n") //372

#define RPL_MOTDSTART(client, server) (":localhost 375 " + client + " " + ":- " + server + " Message of the day - \r\n") //375

#define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " " + ":End of MOTD command\r\n") //376

#define RPL_YOUREOPER(client) (":localhost 381 " + client + " " + ":You are now an IRC operator\r\n") //381

/* ************************************************************************** */
/*                               ERRORS REPLIES                               */
/* ************************************************************************** */

#define ERR_NOSUCHNICK(client, nickname) (":localhost 401 " + client + " " + nickname + " :No such nick/channel\r\n") //401

#define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel\r\n") //403

#define ERR_CANNOTSENDTOCHAN(client, channel) (":localhost 404 " + client + " " + channel + " :Cannot send to channel\r\n") //404

#define ERR_TOOMANYCHANNELS(client, channel) (":localhost 405 " + client + " " + channel + " :You have joined too many channels\r\n") //405

#define ERR_TOOMANYTARGETS(client, target) (":localhost 407 " + client + " " + target + " :Duplicate recipients. No message delivered\r\n") //407

#define ERR_NORECIPIENT(client, command) (":localhost 411 " + client + " " + ":No recipient given (" + command + ")\r\n") //411

#define ERR_NOTEXTTOSEND(client) (":localhost 412 " + client + " " + ":No text to send\r\n") //412

#define ERR_NOTOPLEVEL(client, mask) (":localhost 413 " + client + " " + mask + " :No toplevel domain specified\r\n") //413

#define ERR_WILDTOPLEVEL(client, mask) (":localhost 414 " + client + " " + mask + " :Wildcard in toplevel domain\r\n") //414

#define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n") //421

#define ERR_NOMOTD(client) (":localhost 422 " + client + " " + ":MOTD File is missing\r\n") //422

#define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " " + ":No nickname given\r\n") //431

#define ERR_ERRONEUSNICKNAME(client, nick) (":localhost 432 " + client + " " + nick + " :Erroneous nickname\r\n") //432

#define ERR_NICKNAMEINUSE(client, nick) (":localhost 433 " + client + " " + nick + " :Nickname is already in use\r\n") //433

#define ERR_NICKCOLLISION(client, nick) (":localhost 436 " + client + " " + nick + " :Nickname collision KILL\r\n") //436

#define ERR_USERNOTINCHANNEL(client, nick, channel) (":locahost 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n") //441

#define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :You're not on that channel\r\n") //442

#define ERR_USERONCHANNEL(client, user, channel) (":localhost 443 " + client + " " + user + " " + channel + " :is already on channel\r\n") //443

#define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters\r\n") //461

#define ERR_ALREADYREGISTRED(client) (":localhost 462 " + client + " " + ":You may not reregister\r\n") //462

#define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " " + ":Password incorrect\r\n") //464

#define ERR_KEYSET(client, channel) (":localhost 467 " + client + " " + channel + " :Channel key already set\r\n") //467

#define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n") //471

#define ERR_UNKNOWNMODE(client, cara) (":localhost 472 " + client + " " + cara + " :is unknown mode char to me\r\n") //472

#define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + ":Cannot join channel (+i)\r\n") //473

#define ERR_BANNEDFROMCHAN(client, channel) (":localhost 474 " + client + " " + channel + ":Cannot join channel (+b)\r\n") //474

#define ERR_BADCHANNELKEY(client, channel) (":localhost 475 " + client + " " + channel + ":Cannot join channel (+k)\r\n") //475

#define ERR_NOPRIVILEGES(client) (":localhost 481 " + client + " " + ":Permission Denied- You're not an IRC operator\r\n") //481

#define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " " + channel + " :You're not channel operator\r\n") //482

#define ERR_CANTKILLSERVER(client) (":localhost 483 " + client + " " + ":You can't kill a server!\r\n") //483

#define ERR_RESTRICTED(client) (":localhost 484 " + client + " " + ":Your connection is restricted!\r\n") //484

#define ERR_NOOPERHOST(client) (":localhost 491 " + client + " " + ":No O-lines for your host\r\n") //491

#define ERR_UMODEUNKNOWNFLAG(client) (":localhost 501 " + client + " " + ":Unknown MODE flag\r\n") //501

#define ERR_USERSDONTMATCH(client) (":localhost 502 " + client + " " + ":Cant change mode for other users\r\n") //502

#endif //NUMERIC_REPLIES_HPP
