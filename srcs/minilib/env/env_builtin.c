
#include "minishell.h"

void env_builtin(t_minishell *minishell)
{
    t_env *curr = minishell->env;
    while (curr)
    {
        if (curr->value)
            printf("%s=%s\n", curr->name, curr->value);
        curr = curr->next;
    }
}
