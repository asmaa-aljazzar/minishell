/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:18 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 16:10:35 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fork a child process in the main.
// Redirection in child.
// Compare the command in commands array to execute them
void main_fork(t_minishell *shell)
{
    int status;
    pid_t pid;
    
    pid = fork();
    
    if (pid == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror("fork");
        shell->exit_code = EXIT_FAILURE;
        return;
    }
    
    if (pid == 0) // Child process
    {
        main_redirection(shell);
        compare_commands(shell);
        // If we get here, execution failed
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror("execution failed");
        exit(EXIT_FAILURE);
    }
    else
    { // Parent process
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_code = WEXITSTATUS(status);
        // else if (WIFSIGNALED(status)){
        //     shell->exit_code = 128 + WTERMSIG(status);
        //     if (WTERMSIG(status) == SIGINT)
        //         ft_putstr_fd("\n", STDERR_FILENO);
        // }
    }
}

