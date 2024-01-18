/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberger <bberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:31:23 by bberger           #+#    #+#             */
/*   Updated: 2024/01/18 15:12:43 by bberger          ###   ########.fr       */
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
    std::string port=av[1];
   
    if (port.find_first_not_of("0123456789", 0) != port.npos)
    {
        std::cout << "error port must be a number" << std::endl;
            return (1);
    }
 
    if (std::atoi(av[1]) >= 0 && std::atoi(av[1]) <= 65535)
    {
	    Server server(av[1], av[2]);
        try {
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

