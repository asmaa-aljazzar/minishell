#include "minishell.h"

static const char *token_type_to_str(t_type type)
{
    if (type == T_WORD) return "WORD";
    if (type == PIPE) return "PIPE";
    if (type == T_INPUT) return "INPUT_FILE";
    if (type == T_HEREDOC) return "INPUT_HEREDOC";
    if (type == T_OUTPUT) return "OUTPUT_FILE";
    if (type == T_APPEND) return "OUTPUT_APPEND";
    if (type == T_FILE) return "FILE"; // For generic file tokens
    // Add others as needed
    return "UNKNOWN";
}

static const char *quote_type_to_str(t_quote q)
{
    if (q == QUOTE_NONE) return  "NO_QUOTE";
    if (q == QUOTE_SINGLE) return "SINGLE_QUOTE";
    if (q == QUOTE_DOUBLE) return "DOUBLE_QUOTE";
    return "UNKNOWN_QUOTE";
}

void debug_print_tokens(t_token **tokens)
{
    int i = 0;
    printf("---- Tokens debug ----\n");
    while (tokens[i])
    {
        printf("[%d] word='%s' | type=%s | qtype=%s | expanded=%d | glued=%d\n",
               i,
               tokens[i]->word ? tokens[i]->word : "(null)",
               token_type_to_str(tokens[i]->type),
               quote_type_to_str(tokens[i]->qtype),
               tokens[i]->expanded,
               tokens[i]->glued);
        i++;
    }
    printf("---- End of tokens ----\n");
}
