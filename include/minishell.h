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
//todo: 1 from main.c
//? [ Main ] 

//? [ Lexer & Tokenizer ]

//? [ Parser ]

//? [ Execution ]

//? [ Builtins ]

//? [ Signals ]

//? [ Expanssion ]

/**
 * @brief #### Update 'SHLVL' value
 * @brief - Add `1` positive, 
 * @brief - Start from `1` if negative
 * @param ms   Minishell structure
 * @param env  Env linked list
 * @return     Nothing
 */
void increase_SHLVL_var(t_minishell *ms, t_env *env);  // todo: func inside 4
/**
 * @brief #### Create a new env node from a string
 * @brief - Find '=' separator in string
 * @brief - Extract name before '='
 * @brief - Duplicate value after '='
 * @brief - Allocate and assign node fields
 * @param ms       Minishell context (for error handling)
 * @param environ  Env variable string "NAME=VALUE"
 * @return         Pointer to new env node, or NULL if no '=' found
 */
t_env *create_env_node(t_minishell *minishell, char *environ);

/**
 * @brief #### Append a node to the env linked list
 * @brief - If list empty, set head to new node
 * @brief - Else, link new node after tail
 * @brief - Update tail to new node
 * @param new_node  Node to append
 * @param head      Pointer to head of list
 * @param tail      Pointer to tail of list
 * @return          None
 */
void append_env_node(t_env *new_node, t_env **head, t_env **tail);

//? [ Errors ]


//?  [ Init ]

/**
 * @brief #### Initialize minishell structure
 * @brief - Set initial NULL or zero values
 * @brief - Duplicate env array to envp
 * @brief - Create env linked list from environ
 * @brief - Clear buffer
 * @brief - Increase SHLVL by 1
 * @param ms       Minishell structure pointer
 * @param environ  Environment variables array
 * @return         None
 */
void init(t_minishell *ms, char **environ);

/**
 * @brief #### Create env linked list from environ array
 * @brief - Create node for each env variable
 * @brief - Append node to env list
 * @param minishell  Minishell context
 * @param environ    Environment variables array
 * @return           Head of env linked list
 */
t_env *init_env(t_minishell *minishell, char **environ);

//? [ Free ]

//? [ Minilib ]
int is_positive_number(const char *s); //? Done

# endif