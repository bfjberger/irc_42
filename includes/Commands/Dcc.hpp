#pragma once
#ifndef DCC_HPP
#define DCC_HPP

#include "ACommand.hpp"

class Dcc : public ACommand {

	public:
		Dcc(void);
		~Dcc(void);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //DCC_HPP

