/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric_Replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:31:31 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/19 11:54:48 by pvong            ###   ########.fr       */
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

/* ************************************************************************** */
/*                             COMMAND RESPONSES                              */
/* ************************************************************************** */

#define RPL_UMODEIS "<user mode string>" //221

#define RPL_AWAY "<nick> :<away message>" //301

#define RPL_CHANNELMODEIS "<channel> <mode> <mode params>" //324

#define RPL_NOTOPIC(channel) (channel + " :No topic is set\r\n") //331

#define RPL_TOPIC(channel, topic) (channel + " : " + topic + "\r\n") //332

#define RPL_INVITING(channel, nick) (channel + " " + nick + "\r\n") //341

#define RPL_BANLIST(channel, banid) (channel + " " + banid + "\r\n") //367

#define RPL_ENDOFBANLIST(channel) (channel + " :End of channel ban list\r\n") //368

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

#define ERR_WILDTOPLEVEL(maks) (mask + " :Wildcard in toplevel domain\r\n") //414

#define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters\r\n") //461

#define ERR_ALREADYREGISTRED() (":You may not reregister") //462

#define ERR_NONICKNAMEGIVEN() (":No nickname given") //431

#define ERR_ERRONEUSNICKNAME(nick) (nick + " :Erroneus nickname\r\n") //432

#define ERR_NICKNAMEINUSE(nick) (nick + " :Nickname is already in use\r\n") //433

#define ERR_NICKCOLLISION(nick) (nick + " :Nickname collision KILL\r\n") //436

#define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel\r\n") //442

#define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel\r\n") //443

#define ERR_KEYSET(channel) (channel + " :Channel key already set\r\n") //467

#define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)\r\n") //471

#define ERR_UNKNOWNMODE(char) (char + " :is unknown mode char to me\r\n") //472

#define ERR_INVITEONLYCHAN(channel) (channel + ":Cannot join channel (+i)\r\n") //473

#define ERR_BANNEDFROMCHAN(channel) (channel + ":Cannot join channel (+b)\r\n") //474

#define ERR_BADCHANNELKEY(channel) (channel + ":Cannot join channel (+k)\r\n") //475

#define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator\r\n") //482

#define ERR_UMODEUNKNOWNFLAG() (":Unknown MODE flag\r\n") //501

#define ERR_USERSDONTMATCH() (":Cant change mode for other users\r\n") //502

#endif
