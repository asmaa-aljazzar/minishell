/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:19 by aaljazza          #+#    #+#             */
/*   Updated: 2025/08/01 18:45:22 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// signals.c

#include "minishell.h"

int g_signal_received = SIG_NONE;

void handle_sigint(int sig)
{
    (void)sig;
    g_signal_received = SIG_INT;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int sig)
{
    (void)sig;
    // g_signal_received = SIG_QUIT;
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}