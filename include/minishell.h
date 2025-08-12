#ifndef MINISHELL_H
#define MINISHELL_H

//* ----------- [ Includes ] -----------
#include <signal.h>
#include <asm-generic/signal-defs.h> //! may delete // my system don't recognize sa
#include "../libft/includes/libft.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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

typedef struct s_fd_backup
{
    int stdin_backup;
    int stdout_backup;
    int stderr_backup;
} t_fd_backup;

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
    int expanded; // 1 if expanded or 0
    // int is_environ
    int glued;     /* 1 → directly attached to previous char 0 → at least one white-space before it   */
} t_token;

typedef struct s_cd_path
{
    char *path;
    char *display_path;
    char *expanded_path;
}   t_cd_path;

//? “Can a command have both input redirection and input pipe?”
//! ✅ !No.
//* A command cannot simultaneously have both.

typedef struct s_command
{
    char **argv;       // ["cat"]
    int  *argv_expanded;//todo
    t_type input_type; // NONE / REDIR_IN / HEREDOC / PIPE_IN
    char *input_file; // the last redirection file
    t_type output_type; // NONE / REDIR_OUT / APPEND / PIPE_OUT
    char *output_file; // the last redirection file
    // int heredoc_fd;
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
    int skip_execution; // if no need to execute [error, not mandatory].
    int in_single_quote;
    int in_double_quote;
    int last_token_end;
} t_minishell;

//* ----------- [ Functions ] -----------

//? [ Main ] 

void main_loop (t_minishell *ms);
int main_redirection(t_minishell *ms);

//? [ Lexer & Tokenizer ]

void merge_words(t_minishell *minishell);
void advance_and_merge(t_minishell *minishell, t_token **orig, int *i, int k);
void merge_two_tokens(t_minishell *minishell, t_token *dst, t_token *src);
t_token *create_new_token(t_minishell *ms, const char *word, int did_expand);

/**
 * @brief #### Tokenize input string into tokens array
 * @brief - Allocate token array based on input length
 * @brief - Track single and double quote states
 * @brief - Use tokenizer selector for each character
 * @brief - Return 0 on syntax error, 1 on success
 * @param ms  Minishell context
 * @return    1 if tokenization succeeded, 0 on failure
 */
int get_tokens(t_minishell *minishell);

int process_token(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Select and invoke tokenizer based on current char and quote state
 * @brief - Tokenize pipe '|' outside quotes
 * @brief - Tokenize input redirection '<' outside quotes
 * @brief - Tokenize output redirection '>' outside quotes
 * @brief - Tokenize quoted strings
 * @brief - Tokenize normal strings otherwise
 * @param ms     Minishell context
 * @param k      Pointer to token index
 * @param i      Pointer to input index
 * @param glued  Glue status flag
 * @return       1 on success, 0 on failure
 */
int select_tokenizer(t_minishell *ms, int *k, int *i, int glued); // todo func inside

/**
 * @brief #### Tokenize pipe '|' operator
 * @brief - Allocate token for pipe character
 * @brief - Set token word to "|"
 * @brief - Set token type to PIPE and quote type to none
 * @brief - Increment token and input indices
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void tokenize_pipe_op(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Tokenize input redirection operator
 * @brief - Detect single '<' or double '<<' for heredoc
 * @brief - Call appropriate handler for each case
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void tokenize_input_redir(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Handle heredoc input redirection '<<'
 * @brief - Allocate token for '<<'
 * @brief - Set token type to INPUT_HEREDOC and quote type to none
 * @brief - Increment token index and advance input index by 2
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void handle_heredoc_redir(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Handle single input redirection '<'
 * @brief - Allocate token for '<'
 * @brief - Set token type to INPUT_FILE and quote type to none
 * @brief - Increment token index and advance input index by 1
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void handle_input_file_redir(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Tokenize input redirection operator
 * @brief - Detect single '>' or double '>>' for heredoc
 * @brief - Call appropriate handler for each case
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void tokenize_output_redir(t_minishell *minishell, int *k, int *i); 

/**
 * @brief #### Handle output append redirection '>>'
 * @brief - Allocate token for '>>'
 * @brief - Set token type to OUTPUT_APPEND and quote type to none
 * @brief - Increment token index and advance input index by 2
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void handle_output_append_redir(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Handle single output redirection '>'
 * @brief - Allocate token for '>'
 * @brief - Set token type to OUTPUT_FILE and quote type to none
 * @brief - Increment token index and advance input index by 1
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index
 * @return           None
 */
void handle_output_file_redir(t_minishell *minishell, int *k, int *i);

/**
 * @brief #### Tokenize a quoted string
 * @brief - Save quote character
 * @brief - Read content inside quotes
 * @brief - Return 0 if unmatched quote (error)
 * @brief - Create quoted token with content and glue status
 * @brief - Advance input index past closing quote
 * @param ms     Minishell context
 * @param k      Pointer to token index
 * @param i      Pointer to input index
 * @param glued  Glue status flag
 * @return       1 on success, 0 on error
 */
int tokenize_quoted(t_minishell *ms, int *k, int *i, int glued); // todo func inside

/**
 * @brief #### Extract content inside matching quotes
 * @brief - Advance past opening quote
 * @brief - Search for closing quote, error if unmatched
 * @brief - Allocate and copy content between quotes
 * @param ms     Minishell context
 * @param i      Pointer to input index (updated)
 * @param quote  Quote character to match
 * @return       Allocated string inside quotes or NULL on error
 */
char *read_quoted_content(t_minishell *ms, int *i, char quote);

/**
 * @brief #### Create token from quoted word
 * @brief - Allocate token structure
 * @brief - Assign word and set token type to INPUT_WORD
 * @brief - Set quote type based on quote character
 * @brief - Set glued flag
 * @brief - Increment token index
 * @param ms     Minishell context
 * @param k      Pointer to token index
 * @param word   Quoted string content
 * @param quote  Quote character ('"' or '\'')
 * @param glued  Glue status flag
 * @return       None
 */
void create_quoted_token(t_minishell *ms, int *k, char *word, char quote, int glued);

/**
 * @brief #### Tokenize a normal (unquoted) string segment
 * @brief - Scan until delimiter or special char
 * @brief - Return if no characters scanned
 * @brief - Allocate substring for normal word
 * @brief - Create token with allocated word and glue status
 * @param minishell  Minishell context
 * @param k          Pointer to token index
 * @param i          Pointer to input index (updated)
 * @param glued      Glue status flag
 * @return           None
 */
void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued);

/**
 * @brief #### Allocate and copy normal word substring
 * @brief - Allocate memory for substring of given length
 * @brief - Copy substring from input starting at index
 * @param ms     Minishell context
 * @param start  Start index in input string
 * @param len    Length of substring
 * @return       Newly allocated substring
 */
char *allocate_normal_word(t_minishell *ms, int start, int len);

/**
 * @brief #### Create token for normal (unquoted) word
 * @brief - Allocate token structure
 * @brief - Assign word, set type to INPUT_WORD
 * @brief - Set quote type to none and initialize expanded flag
 * @brief - Set glue status
 * @brief - Increment token index
 * @param ms     Minishell context
 * @param word   Word string to assign
 * @param glued  Glue status flag
 * @param k      Pointer to token index
 * @return       None
 */
void fill_normal_token(t_minishell *ms, char *word, int glued, int *k);




//? [ Parser ]
void allocate_commands(t_minishell *ms);
void fill_argvs(t_minishell *ms);
void process_token_to_fill(t_minishell *ms, t_command **cmd, t_token *tok, int *arg_idx);
void argv_for_commands(t_minishell *minishell);
void allocate_argv(t_minishell *minishell, int *argc, t_command **cmd, int *i);
void if_output_files_append(t_minishell *minishell, t_token *token, t_command **cmd, int *i);
void if_output_pipe(t_token *token, t_command **cmd, int *argc);
void tokens_to_commands(t_minishell *minishell);
void if_input_files_heredoc(t_minishell *minishell, t_token *token, t_command **cmd, int *i);


//? [ Execution ]
void execute_piped_commands(t_minishell *ms, int cmd_count);
void compare_commands(t_minishell *shell);
int exec_builtin(t_minishell *shell);
void execute_single_command(t_minishell *ms);
int is_command_empty(t_command *cmd);
void execute_external_command(t_minishell *shell);
int prepare_command_processing(t_minishell *ms);
void execute_commands(t_minishell *ms);

//? [Heredoc]
/* heredoc utils */
char    *append_line_to_content(char *content, char *line);
char    *append_single_char(char *result, char c);
char    *append_to_result(char *result, char *to_append);
int     create_heredoc_pipe(char *content);
char    *expand_env_var(t_minishell *shell, char *content, char *result, int *i);
char    *expand_exit_code(t_minishell *shell, char *result, int *i);
char    *expand_heredoc_variables(t_minishell *shell, char *content);
char    *extract_var_name(char *str, int *index);
int     is_delimiter_line(char *line, char *delimiter);
void    print_eof_warning(char *delimiter);
int handle_redirection(t_minishell *shell);
int input_redirection(t_command *cmd);
int handle_output_redirection(t_command *cmd);

/* heredoc main processing */
int     process_all_heredocs(t_minishell *minishell);
int     process_discarded_heredocs(t_minishell *minishell, t_command *cmd);
int     process_final_heredoc(t_minishell *shell, t_command *cmd);
char    *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break);
char    *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand);
char    *read_until_delimiter(char *delimiter);
int     setup_heredoc_input(t_command *cmd);
int     should_expand_heredoc(t_minishell *shell, char *delimiter);

//? [ Builtins ]
void cd_builtin(t_minishell *shell);
void echo_builtin(t_minishell *shell);
void env_builtin(t_minishell *shell);
void exit_builtin(t_minishell *shell);
void export_builtin(t_minishell *shell);
void pwd_builtin(t_minishell *shell);
void unset_builtin(t_minishell *shell);

//? [ PATH]
#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include "minishell.h"

// Returns strdup'ed path if cmd already contains '/' and is executable, else NULL
char *already_path(char *cmd);

// Searches PATH env string for executable cmd, returns malloc'ed full path or NULL
char *find_cmd_path(char *cmd, char *path_env);

// Retrieves PATH environment variable value string from env linked list (no strdup)
char *find_path(t_env *env);

// Top-level function to get full command path (already absolute or resolved from PATH)
char *get_path(t_minishell *shell);

// Checks if given path is executable by current user
int is_executable(char *path);

// Concatenates directory path and cmd into a full path string
char *join_path(const char *path, const char *cmd);

#endif


//? [ Signals ]

//? [ Expanssion ]
char *expand_variable(t_minishell *ms, char *token);
char *extract_literal(char *token, size_t *i);
void handle_dollar(t_minishell *ms, char *token, size_t *i, char **result);
char *extract_var_value(t_minishell *ms, char *token, size_t *i);
char *handle_empty_expansion(char *token);
void expand_tokens(t_minishell *ms);
void expand_and_split_token(t_minishell *ms, t_token *token,
                            t_token **new_tokens, int *new_count);
void handle_unquoted_token(t_minishell *ms, t_token *token, char *expanded,
                                  t_token **new_tokens, int *new_count, int did_expand);
void handle_single_quoted_token(t_token *token, t_token **new_tokens, int *new_count);
void handle_double_quoted_token(t_token *token, char *expanded,
                                       t_token **new_tokens, int *new_count, int did_expand);
void handle_first_split_token(t_token *token, const char *word, int did_expand,
                                     t_token **new_tokens, int *new_count);

                            /**
 * @brief #### Update 'SHLVL' value
 * @brief - Add `1` positive, 
 * @brief - Start from `1` if negative
 * @param ms   Minishell structure
 * @param env  Env linked list
 * @return     Nothing
 */
int	increase_SHLVL_var(t_minishell *ms, t_env *env);

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
int create_new_env_var(t_minishell *shell, char *name, char *value);


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
int update_envp_array(t_minishell *shell, char *name, char *value);


/**
 * @brief #### Append new entry to envp array
 * @brief - Count current entries
 * @brief - Allocate bigger array
 * @brief - Copy existing entries
 * @brief - Add new entry and NULL terminator
 * @brief - Free old array and replace
 * @param shell      Minishell context
 * @param new_entry  "NAME=VALUE" string to append
 * @return 0 on failure
 *  1     success     
 */
int append_envp(t_minishell *shell, char *new_entry);

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
int update_env_var(t_minishell *shell, char *name, char *value);


//? [ Errors ]

int validate_syntax(t_minishell *ms);
int check_pipe_syntax(t_minishell *ms, int i);
int check_redirection_syntax(t_minishell *ms, int *i);

//?  [ Init ]

t_command *init_command(t_minishell *ms);
char **init_split_array(char *str, int *word_count);

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


void init_shell(t_minishell *minishell); // todo func inside

//? [ Free ]

void free_split_array(char **array);

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

void check_to_free(t_minishell *minishell);

void free_token(t_token *token);


//? [ Minilib ]
int is_builtin(t_command *cmd);
int update_glued(t_minishell *ms, int *i, int token_index);
void count_pipe(t_minishell *minishell);
int count_max_tokens_after_expansion(t_minishell *ms);
char *append_result(char *old_result, char *value);
void append_and_free(char **result, char *to_add);
int count_words_in_string(char *str);
char *extract_word(char *str, int *index);
char **split_on_whitespace(char *str);
int is_whitespace(char c);
void copy_token_to_argvs(t_minishell *ms, t_command *cmd, t_token *tok, int arg_idx);
char **add_to_list(char **old_list, char *value);
int has_more_redirections(t_token **tokens, int start_index, t_type t1, t_type t2);
void print_sorted_env(t_minishell *minishell);

/**
 * @brief #### Check if string is a positive number
 * @brief - Return 0 if NULL or empty string
 * @brief - Return 0 if any non-digit found
 * @brief - Return 1 if all digits
 * @param s  Input string
 * @return   1 if positive number, 0 otherwise
 */
int is_positive_number(const char *s); //? Done

/**
 * @brief #### Print ASCII banner in two parts
 * @brief - Part 1: Top half of banner
 * @brief - Part 2: Bottom half of banner
 * @brief - Use print_slowly for gradual output
 * @return None
 */
void print_banner(void);

/**
 * @brief #### Print string slowly to stdout
 * @brief - Write one character at a time
 * @brief - Delay between each character
 * @param line  String to print
 * @return      None
 */
void print_slowly(const char *line);

/**
 * @brief #### Handle EOF (Ctrl+D) in minishell
 * @brief - If no input, print "exit"
 * @brief - Free env list and envp array
 * @brief - Clear readline history
 * @brief - Exit program
 * @param minishell  Minishell context
 * @return           None
 */
void	handle_eof(t_minishell *minishell);

//? [ Signals ]
void setup_signals_parent(void);
void setup_signals_child(void);
void setup_signals_readline(void);
void setup_signals_heredoc(void);
void setup_signals_execution(void);
void sigint_handler(int sig);

//? [ Debug ]

void debug_command(const t_command *cmd);

//#### Print the environment variables array
void debug_print_envp_array(char **envp);

//#### Print the environment variables linked list
void debug_print_env_list(t_env *env);

// Print the tokens array
void debug_print_tokens(t_token **tokens);
//hala edition
void handlequit(int sig);
void handle_c(int sig);
void setup_sig_exc(int sig, void(*handler)(int));
# endif