#include "minishell.h"
void env_builtin(t_minishell *minishell)
{
    t_command *cmd = minishell->cmd;
    
    // If no arguments, print all environment variables
    if (cmd->argv[1] == NULL)
    {
        t_env *curr = minishell->env;
        while (curr)
        {
            if (curr->value)
                printf("%s=%s\n", curr->name, curr->value);
            curr = curr->next;
        }
        minishell->exit_code = 0;
        return;
    }
    
    // Save original command for path resolution
    t_command *original_cmd = minishell->cmd;
    
    // Temporarily modify cmd to point to the command we want to execute
    // Create a temporary command structure for path resolution
    t_command temp_cmd = {0};
    temp_cmd.argv = &cmd->argv[1]; // Skip "env", start from the actual command
    minishell->cmd = &temp_cmd;
    
    // Use your existing get_path function
    char *path = get_path(minishell);
    
    // Restore original command
    minishell->cmd = original_cmd;
    
    if (!path)
    {
        // Command not found
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        minishell->exit_code = 127;
        return;
    }
    
    // Fork to execute the command
    pid_t pid = fork();
    
    if (pid == -1)
    {
        // Fork failed
        ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
        free(path);
        minishell->exit_code = 1;
        return;
    }
    
    if (pid == 0)
    {
        // Child process
        // Skip "env" to get just the command and its arguments
        execve(path, &cmd->argv[1], minishell->envp);
        // If execve returns, there was an error
        exit(127);
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status))
            minishell->exit_code = WEXITSTATUS(status);
        else
            minishell->exit_code = 1;
        
        free(path);
    }
}