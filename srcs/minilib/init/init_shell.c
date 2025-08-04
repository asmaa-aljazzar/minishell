
#include "minishell.h"

int validate_syntax(t_minishell *ms)
{
    int i;

    i = 0;
    while (ms->tok[i])
    {
        if (ms->tok[i]->type == OUTPUT_PIPE)
        {
            if (i == 0 || !ms->tok[i + 1] || ms->tok[i + 1]->type == OUTPUT_PIPE)
            {
                ft_putendl_fd("syntax error near unexpected token `|'", 2);
                return 0;
            }
        }
        // Check for redirections
        else if (ms->tok[i]->type == INPUT_FILE ||
                 ms->tok[i]->type == INPUT_HEREDOC ||
                 ms->tok[i]->type == OUTPUT_FILE ||
                 ms->tok[i]->type == OUTPUT_APPEND)
        {
            if (!ms->tok[i + 1] || ms->tok[i + 1]->type != INUPT_WORD) // Note: Fix the typo INUPT_WORD to INPUT_WORD in your enum
            {
                ft_putendl_fd("syntax error near unexpected token `newline'", 2);
                return 0;
            }
            i++;
        }
        i++;
    }
    return 1;
}

void init_shell(t_minishell *minishell)
{
    minishell->tok = NULL;
    minishell->tokens_count = 0;
    minishell->pipe_count = 0;
    minishell->input = readline(PROMPT);
    handle_eof(minishell);
    if (*minishell->input)
        add_history(minishell->input);
    if (!*minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
        return;
    }
    get_tokens(minishell);
    if (!minishell->tok)
    {
        ft_putendl_fd("Error: Failed to tokenize input", STDERR_FILENO);
        free(minishell->input);
        minishell->input = NULL;
        return;
    }
    if (!validate_syntax(minishell))
    {
        check_to_free(minishell);
        return;
    }
    count_pipe(minishell);
}
