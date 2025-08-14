#include "minishell.h"

static int is_valid_identifier(const char *str);
static void update_or_add_env(t_minishell *minishell, char *name, char *value);
static void export_without_value(t_minishell *minishell, char *name);
static int has_valid_arguments(t_command *cmd);

static void print_invalid_identifier(const char *name, const char *value)
{
    ft_putstr_fd((char *)"minishell: export: `", STDERR_FILENO);
    ft_putstr_fd((char *)name, STDERR_FILENO);
    if (value)
    {
        ft_putstr_fd("=", STDERR_FILENO);
        ft_putstr_fd((char *)value, STDERR_FILENO);
    }
    ft_putstr_fd((char *)"': not a valid identifier\n", STDERR_FILENO);
}

static void process_assignment(t_minishell *shell, char *arg)
{
    char *equal_position = ft_strchr(arg, '=');
    char *name;
    char *value;

    *equal_position = '\0';
    name = arg;
    value = equal_position + 1;

    if (is_valid_identifier(name))
        update_or_add_env(shell, name, value);
    else
    {
        print_invalid_identifier(name, value);
        shell->exit_code = 1;
    }
    *equal_position = '=';
}

static void process_no_assignment(t_minishell *shell, char *arg)
{
    if (is_valid_identifier(arg))
        export_without_value(shell, arg);
    else
    {
        print_invalid_identifier(arg, NULL);
        shell->exit_code = 1;
    }
}

static void process_export_args(t_minishell *shell, t_command *cmd)
{
    int i = 1;

    while (cmd->argv[i])
    {
        if (!cmd->argv[i][0])
        {
            i++;
            continue;
        }
        if (ft_strchr(cmd->argv[i], '='))
            process_assignment(shell, cmd->argv[i]);
        else
            process_no_assignment(shell, cmd->argv[i]);
        i++;
    }
}

void export_builtin(t_minishell *shell)
{
    t_command *cmd = shell->cmd;

    if (!cmd || !cmd->argv || !cmd->argv[0])
    {
        shell->exit_code = 1;
        return;
    }
    shell->exit_code = 0;

    if (!cmd->argv[1] || !has_valid_arguments(cmd))
    {
        print_sorted_env(shell);
        return;
    }
    process_export_args(shell, cmd);
}

static int has_valid_arguments(t_command *cmd)
{
    int i = 1;

    while (cmd->argv[i])
    {
        if (cmd->argv[i][0] != '\0') // Found a non-empty argument
            return 1;
        i++;
    }
    return 0; // All arguments are empty
}

static int is_valid_identifier(const char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0;

    // First character must be letter or underscore
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;

    // Rest must be alphanumeric or underscore
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }

    return 1;
}
#include "minishell.h"

static void update_existing_env(t_minishell *shell, t_env *var, char *name, char *value)
{
    if (ft_strcmp(name, "SHLVL") == 0)
    {
        if (!is_positive_number(value))
        {
            value = "1";
        }
        if (ft_atoi(value) > 10)
        {
            ft_putstr_fd("./minishell: warning: shell level (1000) too high, resetting to '1'\n", 2);
            value = "1";
        }
        
    }
    if (var->value)
        free(var->value);
    var->value = ft_strdup(value);
    update_envp_array(shell, name, value);
}

static void add_new_env(t_minishell *shell, char *name, char *value)
{
    t_env *new_var;
    t_env *current;

    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;
    if (!new_var->name || !new_var->value)
    {
        free(new_var->name);
        free(new_var->value);
        free(new_var);
        return;
    }
    if (!shell->env)
        shell->env = new_var;
    else
    {
        current = shell->env;
        while (current->next)
            current = current->next;
        current->next = new_var;
    }
    update_envp_array(shell, name, value);
}

void update_or_add_env(t_minishell *shell, char *name, char *value)
{
    t_env *current;

    if (!shell || !name || !value)
        return;

    current = shell->env;
    while (current)
    {
        if (current->name && ft_strcmp(current->name, name) == 0)
        {
            update_existing_env(shell, current, name, value);
            return;
        }
        current = current->next;
    }
    add_new_env(shell, name, value);
}

#include "minishell.h"

static int env_variable_exists(t_minishell *shell, char *name)
{
    t_env *current = shell->env;

    while (current)
    {
        if (current->name && ft_strcmp(current->name, name) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

static void add_env_without_value(t_minishell *shell, char *name)
{
    t_env *new_var;
    t_env *current;

    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    new_var->name = ft_strdup(name);
    new_var->value = NULL;
    new_var->next = NULL;
    if (!new_var->name)
    {
        free(new_var);
        return;
    }
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

void export_without_value(t_minishell *shell, char *name)
{
    if (!shell || !name)
        return;

    if (env_variable_exists(shell, name))
        return;

    add_env_without_value(shell, name);
}
