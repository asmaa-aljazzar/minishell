// // main_fork.c - Updated
#include "minishell.h"
void main_fork(t_minishell *minishell)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        setup_signals_child();
        
        main_redirection(minishell);
                
        // Check if there's a command
        if (!minishell->cmd->argv || !minishell->cmd->argv[0])
        {
            exit(0);
        }
        else
        {
            compare_commands(minishell);
            exit(minishell->exit_code);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            minishell->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            minishell->exit_code = 128 + WTERMSIG(status);
    }
    else
    {
        perror("fork");
        minishell->exit_code = 1;
    }
}
// void main_fork(t_minishell *shell)
// {
//     int status;
//     pid_t pid;
//     t_command *cmd = shell->cmd;
    
//     if (!cmd || !cmd->argv || !cmd->argv[0])
//     {
//         shell->exit_code = 0;
//         return;
//     }
    
//     // Handle builtin commands in parent (except in pipeline)
//     if (is_builtin(cmd) && !cmd->next)
//     {
//         // Save original stdin/stdout
//         int saved_stdin = dup(STDIN_FILENO);
//         int saved_stdout = dup(STDOUT_FILENO);
        
//         // Check redirections first
//         if (!handle_redirection(shell))
//         {
//             shell->exit_code = 1;
//             return;
//         }
        
//         // Apply redirections for builtin
//         if (cmd->input_type == INPUT_FILE)
//             input_redirection(cmd);
//         if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
//             handle_output_redirection(cmd);
        
//         // Execute builtin
//         compare_commands(shell);
        
//         // Restore stdin/stdout
//         dup2(saved_stdin, STDIN_FILENO);
//         dup2(saved_stdout, STDOUT_FILENO);
//         close(saved_stdin);
//         close(saved_stdout);
        
//         return;
//     }
    
//     // Fork for external commands
//     pid = fork();
    
//     if (pid == -1)
//     {
//         ft_putstr_fd("minishell: ", STDERR_FILENO);
//         perror("fork");
//         shell->exit_code = EXIT_FAILURE;
//         return;
//     }
    
//     if (pid == 0) // Child process
//     {
//         setup_signals_child ();
//         // Setup redirections
//         main_redirection(shell);
        
//         // Execute command
//         compare_commands(shell);
        
//         // Should never reach here
//         exit(EXIT_FAILURE);
//     }
//     else // Parent process
//     {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status))
//             shell->exit_code = WEXITSTATUS(status);
//         else if (WIFSIGNALED(status))
//         {
//             shell->exit_code = 128 + WTERMSIG(status);
//             if (WTERMSIG(status) == SIGINT)
//                 ft_putstr_fd("\n", STDOUT_FILENO);
//         }
//     }
// }