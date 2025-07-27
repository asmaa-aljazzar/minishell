/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:19 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/27 16:34:10 by aaljazza         ###   ########.fr       */
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
    if (!isatty(0))
        return;
    rl_redisplay();
}

// During normal operation, do nothing
// During command execution, will print "Quit: 3"
void handle_sigquit(int sig)
{
    (void)sig;
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}