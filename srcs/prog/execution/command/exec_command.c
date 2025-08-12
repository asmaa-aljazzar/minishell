#include "minishell.h"

// Returns 1 if command argv is empty or all whitespace
// This checks all args to be empty strings or whitespace only
static int is_command_empty_all(t_command *cmd)
{
    if (!cmd || !cmd->argv)
        return 1;

    for (int i = 0; cmd->argv[i]; i++)
    {
        char *arg = cmd->argv[i];
        while (*arg && (*arg == ' ' || *arg == '\t' || *arg == '\n'))
            arg++;
        if (*arg != '\0')
            return 0; // found non-empty arg
    }
    return 1;
}
static int check_null_argv(t_command *cmd, t_minishell *ms)
{
    if (!cmd || !cmd->argv)
    {
        ms->exit_code = 127;
        return -1;
    }
    return 0;
}

static int check_empty_argv(t_command *cmd, t_minishell *ms)
{
    if (!cmd->argv[0])
    {
        ms->exit_code = 0;
        return 1;
    }
    return 0;
}

static int check_first_arg_empty(t_command *cmd, t_minishell *ms)
{
    if (cmd->argv[0][0] == '\0')
    {
        if (cmd->argv_expanded && cmd->argv_expanded[0] == 0)
        {
            ft_putstr_fd("minishell: : command not found\n", STDERR_FILENO);
            ms->exit_code = 127;
            return -1;
        }
        else
        {
            ms->exit_code = 0;
            return 1;
        }
    }
    return 0;
}

static int check_all_args_empty(t_command *cmd, t_minishell *ms)
{
    if (is_command_empty_all(cmd))
    {
        ms->exit_code = 0;
        return 1;
    }
    return 0;
}

static int validate_command(t_command *cmd, t_minishell *ms)
{
    int ret;

    ret = check_null_argv(cmd, ms);
    if (ret != 0)
        return ret;

    ret = check_empty_argv(cmd, ms);
    if (ret != 0)
        return ret;

    ret = check_first_arg_empty(cmd, ms);
    if (ret != 0)
        return ret;

    ret = check_all_args_empty(cmd, ms);
    if (ret != 0)
        return ret;

    return 0;
}


static int handle_redirections()
{
    // redir_status = handle_redirection(ms);
    int redir_status = 0;

    if (redir_status != 0)
    {
        if (redir_status > 0)
            return 1; // redirection-only success
        return -1;    // redirection error
    }
    return 0;
}

static int handle_builtin(t_minishell *ms)
{
    if (is_builtin(ms->cmd))
    {
        compare_commands(ms);
        return 1; // builtin handled
    }
    return 0;
}

int exec_command(t_minishell *ms)
{
    int ret;
    ret = validate_command(ms->cmd, ms);
    if (ret != 0)
        return (ret == 1) ? 0 : -1;
    ret = handle_redirections();
    if (ret != 0)
        return ret == 1 ? 0 : -1;
    if (!ms->envp)
    {
        ms->exit_code = 1;
        return -1;
    }
    if (handle_builtin(ms))
        return 0;
    // execute_external_command(ms);
    return -1;
}
