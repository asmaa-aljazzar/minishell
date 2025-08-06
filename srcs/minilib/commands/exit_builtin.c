#include "minishell.h"

static int validate_exit_arg(char *arg);
static void handle_exit(t_minishell *minishell, int exit_code);

void exit_builtin(t_minishell *minishell)
{
    int arg_count = 0;
    int exit_code = 0;

    // Count arguments
    while (minishell->tok[arg_count])
        arg_count++;
    arg_count--; // Subtract 1 to exclude "exit" token

    printf("exit\n");

    // Case handling
    if (arg_count == 0)
    {
        // No arguments
        handle_exit(minishell, 0);
    }
    else if (arg_count == 1)
    {
        // One argument
        if (validate_exit_arg(minishell->tok[1]->word))
        {
            // Valid numeric argument
            exit_code = ft_atoi(minishell->tok[1]->word) % 256;
            handle_exit(minishell, exit_code);
        }
        else
        {
            // Invalid numeric argument
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", 
                    minishell->tok[1]->word);
            handle_exit(minishell, 2);
        }
    }
    else
    {
        // Multiple arguments
        if (validate_exit_arg(minishell->tok[1]->word))
        {
            // First argument is numeric, but too many arguments
            fprintf(stderr, "minishell: exit: too many arguments\n");
            minishell->exit_code = 1;
        }
        else
        {
            // First argument is not numeric
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", 
                    minishell->tok[1]->word);
            handle_exit(minishell, 2);
        }
    }
}

static int validate_exit_arg(char *arg)
{
    int i = 0;
    
    // Handle optional sign
    if (arg[i] == '+' || arg[i] == '-')
        i++;
    
    // Check if remaining characters are digits
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (0);
        i++;
    }
    
    return (1);
}

static void handle_exit(t_minishell *minishell, int exit_code)
{
    check_to_free(minishell);
    free_env(minishell->env);
    free_2d(minishell->envp);
    rl_clear_history();
    exit(exit_code);
}