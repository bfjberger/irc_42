/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:43:18 by pvong             #+#    #+#             */
/*   Updated: 2024/01/18 17:52:06 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

#include "ft_irc.hpp"

// Define replies for server-client communication
// https://tools.ietf.org/html/rfc2812#section-5

/* -------------------------- 5.1 Command responses ------------------------- */
//        001    RPL_WELCOME
//               "Welcome to the Internet Relay Network
//                <nick>!<user>@<host>"
//        002    RPL_YOURHOST
//               "Your host is <servername>, running version <ver>"
//        003    RPL_CREATED
//               "This server was created <date>"
//        004    RPL_MYINFO
//               "<servername> <version> <available user modes>
//                <available channel modes>
/* -------------------------------------------------------------------------- */

// TODO: Macros for replies


#endif // REPLIES_HPP