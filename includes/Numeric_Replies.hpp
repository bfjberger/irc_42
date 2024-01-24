/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric_Replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:31:31 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 15:47:36 by kmorin           ###   ########.fr       */
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

/* ************************************************************************** */
/*                             COMMAND RESPONSES                              */
/* ************************************************************************** */

#define RPL_UMODEIS() ("<user mode string>\r\n") //221

#define RPL_AWAY() ("<nick> :<away message>\r\n") //301

#define RPL_CHANNELMODEIS() ("<channel> <mode> <mode params>\r\n") //324

#define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n") //331

#define RPL_TOPIC(channel, topic) (channel + " : " + topic + "\r\n") //332

#define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n") //341

#define RPL_BANLIST(channel, banid) (channel + " " + banid + "\r\n") //367

#define RPL_ENDOFBANLIST(channel) (channel + " :End of channel ban list\r\n") //368

#define RPL_MOTD(text) (":- " + text + "\r\n") //372

#define RPL_MOTDSTART(server) (":- " + server + " Message of the day - \r\n") //375

#define RPL_ENDOFMOTD() (":End of MOTD command\r\n") //376

#define RPL_YOUREOPER() (":You are now an IRC operator\r\n") //381

/* ************************************************************************** */
/*                               ERRORS REPLIES                               */
/* ************************************************************************** */

#define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel\r\n") //401

#define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel\r\n") //403

#define ERR_CANNOTSENDTOCHAN(channel) (channel + " :Cannot send to channel\r\n") //404

#define ERR_TOOMANYCHANNELS(channel) (channel + " :You have joined too many channels\r\n") //405

#define ERR_TOOMANYTARGETS(target) (target + " :Duplicate recipients. No message delivered\r\n") //407

#define ERR_NORECIPIENT(command) (":No recipient given (" + command + ")\r\n") //411

#define ERR_NOTEXTTOSEND() (":No text to send\r\n") //412

#define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified\r\n") //413

#define ERR_WILDTOPLEVEL(mask) (mask + " :Wildcard in toplevel domain\r\n") //414

#define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n") //421

#define ERR_NOMOTD() (":MOTD File is missing\r\n") //422

#define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters\r\n") //461

#define ERR_ALREADYREGISTRED() (":You may not reregister\r\n") //462

#define ERR_NONICKNAMEGIVEN() (":No nickname given\r\n") //431

#define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneus nickname\r\n") //432

#define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n") //433

#define ERR_NICKCOLLISION(nick) (nick + " :Nickname collision KILL\r\n") //436

#define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n") //442

#define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel\r\n") //443

#define ERR_PASSWDMISMATCH() (":Password incorrect\r\n") //464

#define ERR_KEYSET(channel) (channel + " :Channel key already set\r\n") //467

#define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n") //471

#define ERR_UNKNOWNMODE(char) (char + " :is unknown mode char to me\r\n") //472

#define ERR_INVITEONLYCHAN(channel) (channel + ":Cannot join channel (+i)\r\n") //473

#define ERR_BANNEDFROMCHAN(channel) (channel + ":Cannot join channel (+b)\r\n") //474

#define ERR_BADCHANNELKEY(channel) (channel + ":Cannot join channel (+k)\r\n") //475

#define ERR_NOPRIVILEGES() (":Permission Denied- You're not an IRC operator\r\n") //481

#define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n") //482

#define ERR_CANTKILLSERVER() (":You can't kill a server!\r\n") //483

#define ERR_RESTRICTED() (":Your connection is restricted!\r\n") //484

#define ERR_NOOPERHOST() (":No O-lines for your host\r\n") //491

#define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag\r\n") //501

#define ERR_USERSDONTMATCH() (":Cant change mode for other users\r\n") //502

#endif //NUMERIC_REPLIES_HPP
