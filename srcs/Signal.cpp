/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:56:24 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:57:18 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "Server.hpp"

// void	handler_sigint(int i)
// {
// 	(void)i;
// 	if (g_signal == -1)
// 	{
// 		write(1, "\n", 1);
// 		g_signal = 130;
// 	}
// 	else
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// void	handler_sigquit(int i)
// {
// 	(void)i;
// 	if (g_signal == -1)
// 	{
// 		write(1, "Quit: 3\n", 8);
// 		g_signal = 131;
// 	}
// 	else
// 		rl_redisplay();
// }

// void	manage_sig() {

// 	struct sigaction	sig;

// 	sig.sa_handler = &handler_sigquit;
// 	if (sigaction(SIGINT, &sig, &data->sig_old) == -1)
// 		std::cout << COLOR("Error: sigint", RED);

// 	sig.sa_handler = &handler_sigquit;
// 	if (sigaction(SIGQUIT, &sig, &data->sig_old) == -1)
// 		std::cout << COLOR("Error: sigquit", RED);
// }
