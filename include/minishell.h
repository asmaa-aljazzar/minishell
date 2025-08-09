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
void increase_SHLVL_var(t_minishell *ms, t_env *env);

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

/**
 * @brief #### Get value of an env variable
 * @brief - Search env list for matching name
 * @brief - Return value if found
 * @brief - Return empty string if not found
 * @param env  Env linked list
 * @param var  Variable name to search
 * @return     Pointer to value string, or "" if not found
 */
char *get_env_value(t_env *env, const char *var);

/**
 * @brief #### Update value of an existing env variable
 * @brief - Search env list for matching name
 * @brief - Free old value and set new one
 * @brief - Update value in envp array
 * @param shell  Minishell context
 * @param name   Variable name
 * @param value  New value
 * @return       1 if updated, 0 if not found
 */
int update_existing_env_var(t_minishell *shell, char *name, char *value);

/**
 * @brief #### Create and add a new env variable
 * @brief - Allocate and assign name/value
 * @brief - If list empty, set as first node
 * @brief - Else, append to end of list
 * @brief - Update envp array
 * @param shell  Minishell context
 * @param name   Variable name
 * @param value  Variable value
 * @return       None
 */
void create_new_env_var(t_minishell *shell, char *name, char *value);

/**
 * @brief #### Update envp array with a variable
 * @brief - Build "NAME=VALUE" string
 * @brief - Replace if variable exists
 * @brief - Else, append new entry
 * @param shell  Minishell context
 * @param name   Variable name
 * @param value  Variable value
 * @return       None
 */
void update_envp_array(t_minishell *shell, char *name, char *value);

/**
 * @brief #### Append new entry to envp array
 * @brief - Count current entries
 * @brief - Allocate bigger array
 * @brief - Copy existing entries
 * @brief - Add new entry and NULL terminator
 * @brief - Free old array and replace
 * @param shell      Minishell context
 * @param new_entry  "NAME=VALUE" string to append
 * @return           None
 */
void append_envp(t_minishell *shell, char *new_entry);

/**
 * @brief #### Build "NAME=VALUE" string
 * @brief - Join name with '='
 * @brief - Append value to result
 * @param name   Variable name
 * @param value  Variable value
 * @return       Newly allocated "NAME=VALUE" string
 */
char *build_envp_entry(char *name, char *value);

/**
 * @brief #### Replace variable in envp array if it exists
 * @brief - Search for matching name followed by '='
 * @brief - Free old entry and set new one
 * @param shell      Minishell context
 * @param name       Variable name
 * @param new_entry  New "NAME=VALUE" string
 * @return           1 if replaced, 0 if not found
 */
int replace_existing_envp(t_minishell *shell, char *name, char *new_entry);

/**
 * @brief #### Update or create an env variable
 * @brief - If exists, update value
 * @brief - Else, create new variable
 * @param shell  Minishell context
 * @param name   Variable name
 * @param value  Variable value
 * @return       None
 */
void update_env_var(t_minishell *shell, char *name, char *value);

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

/**
 * @brief #### Exit minishell with cleanup
 * @brief - Print error message if provided
 * @brief - Free allocated resources (complex and simple)
 * @brief - Clear readline history
 * @brief - Set exit code and exit program
 * @param shell   Minishell context
 * @param msg     Error message (optional)
 * @param status  Exit status code
 * @return        Does not return
 */
void ft_exit(t_minishell *shell, char *msg, int status);

/**
 * @brief #### Free simple allocated resources
 * @brief - Free input string if allocated
 * @param shell  Minishell context
 * @return       None
 */
void free_simple_resources(t_minishell *shell);

/**
 * @brief #### Free complex allocated resources
 * @brief - Free commands, tokens, env linked list, and envp array
 * @brief - Set pointers to NULL after freeing
 * @param shell  Minishell context
 * @return       None
 */
void free_complex_resources(t_minishell *shell);

/**
 * @brief #### Free all command nodes and their resources
 * @brief - Free argv, input/output files and lists
 * @brief - Free each command node
 * @brief - Set command list head to NULL
 * @param minishell  Minishell context
 * @return           None
 */
void free_commands(t_minishell *minishell);

/**
 * @brief #### Free a NULL-terminated 2D string array
 * @brief - Free each string and set pointer to NULL
 * @brief - Free the array itself
 * @param arr  2D string array
 * @return     None
 */
void free_2d(char **arr);

/**
 * @brief #### Free token array and contained tokens
 * @brief - Free each token's word and token struct
 * @brief - Free the tokens array
 * @param tokens  Array of token pointers
 * @return        None
 */
void free_tokens(t_token **tokens);

/**
 * @brief #### Free entire env linked list
 * @brief - Free name and value of each node
 * @brief - Free each node itself
 * @param env  Head of env linked list
 * @return     None
 */
void free_env(t_env *env);

//? [ Minilib ]

/**
 * @brief #### Check if string is a positive number
 * @brief - Return 0 if NULL or empty string
 * @brief - Return 0 if any non-digit found
 * @brief - Return 1 if all digits
 * @param s  Input string
 * @return   1 if positive number, 0 otherwise
 */
int is_positive_number(const char *s); //? Done

//? [ Debug ]

//#### Print the environment variables array
void debug_print_envp_array(char **envp);

//#### Print the environment variables linked list
void debug_print_env_list(t_env *env);

# endif