#ifndef MINISHELL_H
#define MINISHELL_H

//* ----------- [ Includes ] -----------
#include <signal.h>
#include "../libft/includes/libft.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>



//* ----------- [ Macros ] -----------
#define PROMPT "\033[33mminishell\033[32m$ \033[0m"
#define SIG_NONE 0
#define SIG_INT 130   // Ctrl+C (128 + 2)
#define SIG_QUIT 131  // Ctrl+\ (128 + 3)

//* ----------- [ Global ] -----------
extern volatile sig_atomic_t g_signal_received;

//* ----------- [ enums ] -----------

// use to detect what kind of word in the tokens array
typedef enum e_quote
{
    QUOTE_NONE, // not qouted
    QUOTE_SINGLE, // 'some'
    QUOTE_DOUBLE, // "some"
    QUOTE_MIXED // not"some"'some'
} t_quote;

typedef enum e_type
{
    INPUT_NONE,
    INPUT_FILE, 
    INPUT_WORD,
    INPUT_HEREDOC,
    OUTPUT_NONE,
    OUTPUT_FILE,
    OUTPUT_APPEND,
    PIPE
} t_type;

//* ----------- [ Structures ] -----------
//
typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;

//? This is the array of tokens: we can create a custome arrays
typedef struct s_token
{
    char *word;    /* already without the surrounding quotes   */
    t_type type;   /* WORD | PIPE | REDIR_*                    */
    t_quote qtype; /* how it 'was' quoted  */
    // int is_environ
    int glued;     /* 1 → directly attached to previous char 0 → at least one white-space before it   */
} t_token;


//? “Can a command have both input redirection and input pipe?”
//! ✅ !No.
//* A command cannot simultaneously have both.

typedef struct s_command
{
    char **argv;       // ["cat"]
    t_type input_type; // NONE / REDIR_IN / HEREDOC / PIPE_IN
    char *input_file; // the last redirection file
    t_type output_type; // NONE / REDIR_OUT / APPEND / PIPE_OUT
    char *output_file; // the last redirection file
    int heredoc_fd;
    struct s_command *next; // Next command in pipe sequence
    char **input_files; // array of files before last one // todo: may need to fix
    char **output_files; // array of files berore last one // todo: may need to fix
} t_command;

typedef struct s_minishell
{
    char *input; // redline input string
    t_command *cmd; // commands linked list
    int tokens_count; // number of tokens
    t_token **tok; // tokens array
    int pipe_count; // how many [pipe/ commands] we have
    char buff[1024];
    t_env *env; // env vars linded list
    char **envp; // ["NAME=VAl"][...][...]
    int exit_code;
    int skip_execution; // if no need to execute [error, not mandatory]
} t_minishell;

//* ----------- [ Functions ] -----------
//? [ Main ]

//? [ Lexer & Tokenizer ]

//? [ Parser ]

//? [ Execution ]

//? [ Builtins ]

//? [ Signals ]

//? [ Expanssion ]
void increase_SHLVL_var(t_minishell *ms, t_env *env);  // todo: func inside 2

//? [ Errors ]


//?  [ Init ]
void init(t_minishell *ms, char **environ); // todo: func inside 1

//? [ Free ]

//? [ Minilib ]
int is_positive_number(const char *s); //? Done

# endif