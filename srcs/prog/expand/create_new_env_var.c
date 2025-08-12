#include "minishell.h"
static t_env *allocate_env_var(const char *name, const char *value)
{
    t_env *new_var;

	new_var = malloc(sizeof(t_env));
    if (!new_var)
    {
        ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
        return NULL;
    }
    new_var->name = ft_strdup(name);
    if (!new_var->name)
    {
        free(new_var);
        return NULL;
    }
    new_var->value = ft_strdup(value);
    if (!new_var->value)
    {
        free(new_var->name);
        free(new_var);
        return NULL;
    }
    new_var->next = NULL;
    return new_var;
}

static void append_env_var(t_minishell *shell, t_env *new_var)
{
    t_env *current;

    if (!shell->env)
        shell->env = new_var;
    else
    {
        current = shell->env;
        while (current->next)
            current = current->next;
        current->next = new_var;
    }
}

int create_new_env_var(t_minishell *shell, char *name, char *value)
{
    t_env *new_var = allocate_env_var(name, value);
    if (!new_var)
        return 0;

    append_env_var(shell, new_var);

    if (!update_envp_array(shell, name, value))
        return 0;

    return 1;
}

