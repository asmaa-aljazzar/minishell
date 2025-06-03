#ifndef  TOKEN_H
# define TOKEN_H

//***[ Structures ]***


typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_HEREDOC,
    TOKEN_SINGLE_QUOTED_STRING,
    TOKEN_DOUBLE_QUOTED_STRING,
    TOKEN_EOF
} t_token_type;

// Node for each token
typedef struct s_token{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;
// t_token *create_token(t_token_type type, const char *value);
// void *tokens_init(t_token_type type);

#endif