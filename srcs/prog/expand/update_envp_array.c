#include "minishell.h"

void update_envp_array(t_minishell *shell, char *name, char *value)
{
    char *new_entry;

    if (!name || !value)
        return;
    new_entry = build_envp_entry(name, value); // ["NAME=VAL"]
    if (!new_entry)
        return;
    if (!replace_existing_envp(shell, name, new_entry))
        append_envp(shell, new_entry);
}
