/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:31:23 by bberger           #+#    #+#             */
/*   Updated: 2024/01/17 15:04:10 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"


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

    if (ac != 3) {
        std::cout << "Usage: ./ft_irc [port] [password]" << std::endl;
        return (1); 
    }

	Server server(av[1], av[2]);
    try {
        server.run();	

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return (0);
}
