/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:31:23 by bberger           #+#    #+#             */
/*   Updated: 2024/01/15 16:54:52 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"


int main(void) {
    // std::cout << "Hello" << std::endl;

    // Create a socket
    // Bind the socket to an IP / port
    // Listen for incoming connections
    // Accept incoming connections and create a new threads for each one
    // Read from / write to the socket
    // Parse the request according to IRC protocol
    // Respond to the request
    // Handle errors and disconnections
    // Close the socket

	Server server;
	server.run();	

    return (0);
}
