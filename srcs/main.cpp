/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:31:23 by bberger           #+#    #+#             */
/*   Updated: 2024/01/25 10:30:01 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"


bool g_server_running = true;

static void	signalHandler(int signal) {

	std::cout << COLOR(" :Signal ", CYAN) << signal << COLOR(" received. Exiting...", CYAN) << std::endl;
	g_server_running = false;
}

int main(int ac, char **av) {

	// Create a socket
	// Bind the socket to an IP / port
	// Listen for incoming connections
	// Accept incoming connections and create a new threads for each one
	// Read from / write to the socket
	// Parse the request according to IRC protocol
	// Respond to the request
	// Handle errors and disconnections
	// Close the socket

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
		try {
			Server server(av[1], av[2]);
			server.run();

		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cout<<"port must be between 0 and 65535"<<std::endl;
		return (2);
	}

	return (0);
}
