#include "minishell.h"

static int is_valid_identifier(const char *str);
static void remove_from_env_list(t_minishell *shell, const char *name);
static void remove_from_envp_array(t_minishell *shell, const char *name);

void unset_builtin(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    int i = 1;

    shell->exit_code = 0;

    if (!cmd->argv[1])
        return;

    while (cmd->argv[i])
    {
        if (is_valid_identifier(cmd->argv[i]))
        {
            remove_from_env_list(shell, cmd->argv[i]);
            remove_from_envp_array(shell, cmd->argv[i]);
        }
        // Invalid identifiers are silently ignored, no error message
        i++;
    }
}

static void remove_from_env_list(t_minishell *shell, const char *name)
{
    t_env *current = shell->env;
    t_env *prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                shell->env = current->next;

            free(current->name);
            if (current->value)
                free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

static void remove_from_envp_array(t_minishell *shell, const char *name)
{
    char **new_envp;
    int count = 0;
    int i, j;
    int name_len = ft_strlen(name);

    if (!shell->envp)
        return;

    while (shell->envp[count])
        count++;

    if (count == 0)
        return;

    new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return;

    i = 0;
    j = 0;
    while (i < count)
    {
        if (!(ft_strncmp(shell->envp[i], name, name_len) == 0 &&
              shell->envp[i][name_len] == '='))
        {
            new_envp[j++] = shell->envp[i];
        }
        else
        {
            free(shell->envp[i]);
        }
        i++;
    }
    new_envp[j] = NULL;

    free(shell->envp);
    shell->envp = new_envp;
}

static int is_valid_identifier(const char *str)
{
    int i;

    if (!str || str[0] == '\0')
        return 0;

    if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;

    for (i = 1; str[i]; i++)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    return 1;
}
