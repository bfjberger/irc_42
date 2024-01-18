/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:23 by pvong             #+#    #+#             */
/*   Updated: 2024/01/18 17:51:53 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

class Client {

public:
    Client(int fd);
    Client();
    ~Client();

    // Getters
    int getFd() const;
    std::string getNick() const;
    std::string getUserName() const;
    std::string getRealName() const;
    bool hasReceivedInfo() const;
    bool isLogged() const;

    // Setters
    void setNick(std::string nick);
    void setUserName(std::string userName);
    void setRealName(std::string realName);
    void setLogged(bool isLogged);
    void setReceivedInfo(bool receivedInfo);

    // TODO: Not Implemented yet
    void logIn();

    // Helpers function
    void printInfo() const;



private:
    int _fd;
    std::string _nick;
    std::string _userName;
    std::string _realName;
    bool _receivedInfo;
    bool _isLogged;
};

#endif // CLIENT_HPP
