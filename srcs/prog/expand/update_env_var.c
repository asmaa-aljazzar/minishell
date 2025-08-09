#include "minishell.h"

void update_env_var(t_minishell *shell, char *name, char *value)
{
    if (!name || !value)
        return;
    if (!update_existing_env_var(shell, name, value))
        create_new_env_var(shell, name, value);
}
