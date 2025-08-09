
#include "minishell.h"

void free_env(t_env *env)
{
    t_env *current = env;
    t_env *next;

    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}