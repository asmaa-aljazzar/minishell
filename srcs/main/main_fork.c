/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:18 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 17:25:27 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fork a child process in the main.
// Redirection in child.
// Compare the command in commands array to execute them
// Redirection in child.

void main_fork(t_minishell *shell)
{
    int pid;
    pid = fork ();
    if (pid == 0)
    {
        redirection(shell);
        // child_re(minishell);
        // compare_commands (minishell);
    }
    else
    {
        // parent_re(minishell);
        int status;
        waitpid(pid, &status, 0);
    }
}

