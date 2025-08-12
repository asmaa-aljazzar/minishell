#include "minishell.h"

//*#### Counts environment variables in the linked list
int print_sorted_env_count(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}

//*#### Creates an array of env variable names, returns NULL on malloc failure
char **print_sorted_env_fill_names(t_env *env, int count)
{
    char **names;
    int i = 0;

    names = malloc(sizeof(char *) * count);
    if (!names)
        return NULL;

    while (env && i < count)
    {
        names[i] = env->name;
        env = env->next;
        i++;
    }
    return names;
}

//*#### Sorts the array of names alphabetically using bubble sort
void print_sorted_env_sort_names(char **names, int count)
{
    int i, j;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - 1 - i)
        {
            if (ft_strcmp(names[j], names[j + 1]) > 0)
            {
                char *temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

//*#### Prints environment variables in sorted order by matching names
void print_sorted_env_print(t_minishell *minishell, char **sorted_names, int count)
{
    int i;
    t_env *current;

    for (i = 0; i < count; i++)
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
    }
}

//*#### Controller function to print environment variables sorted by name
void print_sorted_env(t_minishell *minishell)
{
    int count;
    char **sorted_names;

    if (!minishell || !minishell->env)
        return;

    count = print_sorted_env_count(minishell->env);
    if (count == 0)
        return;

    sorted_names = print_sorted_env_fill_names(minishell->env, count);
    if (!sorted_names)
        return;

    print_sorted_env_sort_names(sorted_names, count);
    print_sorted_env_print(minishell, sorted_names, count);

    free(sorted_names);
}
