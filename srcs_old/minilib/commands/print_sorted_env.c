#include "minishell.h"

void print_sorted_env(t_minishell *minishell)
{
    t_env *current;
    char **sorted_names;
    int count = 0;
    int i, j;

    if (!minishell || !minishell->env)
        return;

    current = minishell->env;

    // Count environment variables
    while (current)
    {
        count++;
        current = current->next;
    }

    if (count == 0)
        return;

    // Create array for sorting names
    sorted_names = malloc(sizeof(char *) * count);
    if (!sorted_names)
        return;

    // Fill array with names
    current = minishell->env;
    i = 0;
    while (current && i < count)
    {
        sorted_names[i] = current->name;
        current = current->next;
        i++;
    }

    // Bubble sort using while
    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - 1 - i)
        {
            if (ft_strcmp(sorted_names[j], sorted_names[j + 1]) > 0)
            {
                char *temp = sorted_names[j];
                sorted_names[j] = sorted_names[j + 1];
                sorted_names[j + 1] = temp;
            }
            j++;
        }
        i++;
    }

    // Print sorted environment
    i = 0;
    while (i < count)
    {
        current = minishell->env;
        while (current)
        {
            if (ft_strcmp(current->name, sorted_names[i]) == 0)
            {
                ft_putstr_fd("declare -x ", STDOUT_FILENO);
                ft_putstr_fd(current->name, STDOUT_FILENO);

                if (current->value)
                {
                    ft_putstr_fd("=\"", STDOUT_FILENO);
                    ft_putstr_fd(current->value, STDOUT_FILENO);
                    ft_putstr_fd("\"", STDOUT_FILENO);
                }

                ft_putstr_fd("\n", STDOUT_FILENO);
                break;
            }
            current = current->next;
        }
        i++;
    }

    free(sorted_names);
}
