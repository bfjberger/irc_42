/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:31:23 by bberger           #+#    #+#             */
/*   Updated: 2024/02/06 13:40:05 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"


bool g_server_running = true;

static void	signalHandler(int signal) {

	std::cout << COLOR(" :Signal ", CYAN) << signal << COLOR(" received. Exiting...", CYAN) << std::endl;
	g_server_running = false;
}

int main(int ac, char **av) 
{
	signal(SIGINT, signalHandler);

	if (ac != 3) {
		std::cout << "Usage: ./ft_irc [port] [password]" << std::endl;
		return (1);
	}
	std::string port=av[1];

	if (port.find_first_not_of("0123456789", 0) != port.npos)
	{
		std::cout << "error port must be a number" << std::endl;
			return (1);
	}

	if (std::atoi(av[1]) >= 0 && std::atoi(av[1]) <= 65535)
	{
		Server server(av[1], av[2]);
		server.run();
	}
	else
	{
		std::cout<<"port must be between 0 and 65535"<<std::endl;
		return (2);
	}

	return (0);
}
