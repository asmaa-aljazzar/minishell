#include "minishell.h"


int process_token(t_minishell *ms, int *k, int *i)
{
    int glued = update_glued(ms, i, *k);
    if (glued == -1)
        return 0; // error or stop condition

    if (!select_tokenizer(ms, k, i, glued))
        return 0; // propagate tokenizer failure
    return 1;
}
