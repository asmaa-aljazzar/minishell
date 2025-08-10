#include "minishell.h"

int tokenize_quoted(t_minishell *ms, int *k, int *i, int glued)
{
    char quote = ms->input[*i];

    // Toggle quote state ON
    if (quote == '\'')
        ms->in_single_quote = 1;
    else if (quote == '"')
        ms->in_double_quote = 1;

    char *word = read_quoted_content(ms, i, quote);
    if (!word)
        return 0;

    create_quoted_token(ms, k, word, quote, glued);

    (*i)++; // Move past closing quote

    // Toggle quote state OFF
    if (quote == '\'')
        ms->in_single_quote = 0;
    else if (quote == '"')
        ms->in_double_quote = 0;

    ms->last_token_end = *i - 1; // Index of closing quote

    return 1;
}
