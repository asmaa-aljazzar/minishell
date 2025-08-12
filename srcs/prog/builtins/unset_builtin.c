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

#include "minishell.h"

static int count_envp(char **envp)
{
    int count = 0;
    if (!envp)
        return 0;
    while (envp[count])
        count++;
    return count;
}

static int is_name_match(const char *env_str, const char *name)
{
    int name_len = ft_strlen(name);
    return (ft_strncmp(env_str, name, name_len) == 0 && env_str[name_len] == '=');
}

static void copy_envp_except_name(char **old_envp, char **new_envp, const char *name)
{
    int i = 0;
    int j = 0;

    while (old_envp[i])
    {
        if (!is_name_match(old_envp[i], name))
            new_envp[j++] = old_envp[i];
        else
            free(old_envp[i]);
        i++;
    }
    new_envp[j] = NULL;
}

void remove_from_envp_array(t_minishell *shell, const char *name)
{
    int count = count_envp(shell->envp);
    char **new_envp;

    if (count == 0)
        return;

    new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return;

    copy_envp_except_name(shell->envp, new_envp, name);

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
