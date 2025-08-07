#include "minishell.h"
// execute_pipeline.c
#include "minishell.h"

// execute_pipeline.c
#include "minishell.h"

void execute_pipeline(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    int cmd_count = 0;
    
    // Count commands in pipeline
    while (cmd)
    {
        cmd_count++;
        cmd = cmd->next;
    }
    
    if (cmd_count == 0)
        return;
    
    if (cmd_count == 1)
    {
        // Single command case - empty check is handled in main_fork
        main_fork(shell);
        return;
    }
    
    // Multi-command pipeline
    execute_piped_commands(shell, cmd_count);
}

// Add this to srcs/minilib/pipe/pipe.c
void execute_piped_commands(t_minishell *shell, int cmd_count)
{
    int (*pipes)[2] = malloc(sizeof(int[2]) * (cmd_count - 1));
    pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
    int i;
    t_command *cmd;
    
    if (!pipes || !pids)
    {
        ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
        shell->exit_code = EXIT_FAILURE;
        free(pipes);
        free(pids);
        return;
    }
    
    // Create all pipes
    i = 0;
    while (i < cmd_count - 1)
    {
        if (pipe(pipes[i]) < 0)
        {
            ft_putstr_fd("minishell: pipe failed\n", STDERR_FILENO);
            shell->exit_code = EXIT_FAILURE;
            close_all_pipes(pipes, i);
            free(pipes);
            free(pids);
            return;
        }
        i++;
    }
    
    // Fork all children
    cmd = shell->cmd;
    i = 0;
    while (i < cmd_count && cmd)
    {
        pids[i] = fork();
        
        if (pids[i] < 0)
        {
            ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
            shell->exit_code = EXIT_FAILURE;
            close_all_pipes(pipes, cmd_count - 1);
            free(pipes);
            free(pids);
            return;
        }
        
        if (pids[i] == 0)
        {
            setup_signals_child();
            
            // Set up pipes
            if (i > 0)  // Not first command
                dup2(pipes[i - 1][0], STDIN_FILENO);
            
            if (i < cmd_count - 1)  // Not last command
                dup2(pipes[i][1], STDOUT_FILENO);
            
            // Close all pipes
            close_all_pipes(pipes, cmd_count - 1);
            
            // Update shell->cmd to current command
            shell->cmd = cmd;
            
            // Check if command is empty
            if (is_command_empty(cmd))
            {
                // Empty command in pipeline - exit successfully
                exit(0);
            }
            
            // Handle redirections
            main_redirection(shell);
            
            // Execute command
            compare_commands(shell);
            
            // If builtin, exit with status
            if (is_builtin(cmd))
                exit(shell->exit_code);
            
            // Should never reach here for external commands
            exit(EXIT_FAILURE);
        }
        
        cmd = cmd->next;
        i++;
    }
    
    // Parent: close all pipes and wait
    close_all_pipes(pipes, cmd_count - 1);
    wait_for_children(shell, pids, cmd_count);
    
    free(pipes);
    free(pids);
}
#include "minishell.h"
// execute_piped_commands.c
#include "minishell.h"

// void execute_piped_commands(t_minishell *shell, int cmd_count)
// {
//     int (*pipes)[2] = malloc(sizeof(int[2]) * (cmd_count - 1));
//     pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
//     int i;
//     t_command *cmd;
    
//     if (!pipes || !pids)
//     {
//         ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
//         shell->exit_code = EXIT_FAILURE;
//         free(pipes);
//         free(pids);
//         return;
//     }
    
//     // Create all pipes
//     i = 0;
//     while (i < cmd_count - 1)
//     {
//         if (pipe(pipes[i]) < 0)
//         {
//             ft_putstr_fd("minishell: pipe failed\n", STDERR_FILENO);
//             shell->exit_code = EXIT_FAILURE;
//             close_all_pipes(pipes, i);
//             free(pipes);
//             free(pids);
//             return;
//         }
//         i++;
//     }
    
//     // Fork all children
//     cmd = shell->cmd;
//     i = 0;
//     while (i < cmd_count && cmd)
//     {
//         pids[i] = fork();
        
//         if (pids[i] < 0)
//         {
//             ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
//             shell->exit_code = EXIT_FAILURE;
//             close_all_pipes(pipes, cmd_count - 1);
//             free(pipes);
//             free(pids);
//             return;
//         }
        
//         if (pids[i] == 0)
//         {
//             setup_signals_child ();
//             // Set up pipes
//             if (i > 0)  // Not first command
//                 dup2(pipes[i - 1][0], STDIN_FILENO);
            
//             if (i < cmd_count - 1)  // Not last command
//                 dup2(pipes[i][1], STDOUT_FILENO);
            
//             // Close all pipes
//             close_all_pipes(pipes, cmd_count - 1);
            
            
//             // Update shell->cmd to current command
//             shell->cmd = cmd;
//             // Handle redirections
//             main_redirection(shell);
            
//             // Execute command
//             compare_commands(shell);
            
//             // If builtin, exit with status
//             if (is_builtin(cmd))
//                 exit(shell->exit_code);
            
//             // Should never reach here for external commands
//             exit(EXIT_FAILURE);
//         }
        
//         cmd = cmd->next;
//         i++;
//     }
    
//     // Parent: close all pipes and wait
//     close_all_pipes(pipes, cmd_count - 1);
//     wait_for_children(shell, pids, cmd_count);
    
//     free(pipes);
//     free(pids);
// }



// pipe_helpers.c
#include "minishell.h"

void close_all_pipes(int pipes[][2], int pipe_count)
{
    int i = 0;
    
    while (i < pipe_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void wait_for_children(t_minishell *shell, pid_t *pids, int cmd_count)
{
    int i = 0;
    int status;
    
    while (i < cmd_count)
    {
        waitpid(pids[i], &status, 0);
        
        // Last command's status becomes shell's exit code
        if (i == cmd_count - 1)
        {
            if (WIFEXITED(status))
                shell->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->exit_code = 128 + WTERMSIG(status);
        }
        i++;
    }
}
