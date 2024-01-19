/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:58:32 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/19 14:15:06 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ************************************************************************** */
/*                          CONSTRUCTOR - DESTRUCTOR                          */
/* ************************************************************************** */

Channel::Channel(const std::string& name) {

	_name = name;
	_topic = "";
	_password = "";
	userLimit = -1;
	i = false;
	t = false;
	k = false;
	o = false;
	l = false;
}

Channel::~Channel(void) {}

/* ************************************************************************** */
/*                                   GETTERS                                  */
/* ************************************************************************** */

std::string	Channel::getName(void) const {

	return (_name);
}

std::string	Channel::getTopic(void) const {

	return (_topic);
}

std::string	Channel::getPassword(void) const {

	return (_password);
}

/* ************************************************************************** */
/*                                   SETTERS                                  */
/* ************************************************************************** */

void	Channel::setName(std::string& name) {

	_name = name;
}

void	Channel::setTopic(std::string& topic) {

	_topic = topic;
}

void	Channel::setPassword(std::string& password) {

	_password = password;
}
