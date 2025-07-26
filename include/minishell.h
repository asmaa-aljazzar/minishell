/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/03 00:35:30 by aaljazza        ####  ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTSHELL_H
#define ANTSHELL_H

//* ----------- [ Includes ] -----------
#include "../libft/includes/libft.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>


//* ----------- [ Macros ] -----------
#define PROMPT "\033[33mminishell\033[32m$ \033[0m"
// extern char **environ;

//* ----------- [ enums ] -----------
// Todo: use this every error appear
typedef enum e_error_code 
{
    ERR_NONE = 0,                // No error
    ERR_SYNTAX_UNMATCHED_QUOTE,  // Unmatched quote in input
    // ERR_SYNTAX_NEAR_EOL,         // Syntax error near end of line/input
    ERR_MEMORY_ALLOCATION,       // malloc/calloc failed
    ERR_COMMAND_NOT_FOUND,       // command not found
    ERR_PERMISSION_DENIED,       // permission error
    ERR_EXPORT_INVALID,          // invalid export argument
    ERR_UNSET_INVALID,           // invalid unset argument
    ERR_ENV_NOT_FOUND,           // environment variable not found
    ERR_EXECVE_FAILED,           // execve system call failed
    ERR_PIPE_FAILED,             // pipe system call failed
    ERR_FORK_FAILED,             // fork system call failed
    ERR_DUP2_FAILED,             // dup2 system call failed
    ERR_SIGNAL_HANDLING,         // signal handling error
} t_error_code;

// Todo: May add this to code later
// typedef struct s_error 
// {
//     t_error_code code;
//     char *message;
// } t_error;

// use to detect what kind of word in the tokens array
typedef enum e_quote
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE,
    QUOTE_MIXED
} t_quote;

typedef enum e_type
{
    INPUT_NONE,
    INPUT_FILE,
    INPUT_PIPE,
    INUPT_WORD,
    INPUT_END, //? May delete
    INPUT_HEREDOC,
    OUTPUT_NONE,
    OUTPUT_FILE,
    OUTPUT_APPEND,
    OUTPUT_PIPE
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
    int glued;     /* 1 → directly attached to previous char 0 → at least one white-space before it   */
} t_token;


//? “Can a command have both input redirection and input pipe?”
//! ✅ !No.
//* A command cannot simultaneously have both.

typedef struct s_command
{
    char **argv;       // ["cat"]
    t_type input_type; // NONE / REDIR_IN / HEREDOC / PIPE_IN
    char *input_file;
    t_type output_type; // NONE / REDIR_OUT / APPEND / PIPE_OUT
    char *output_file;
    struct s_command *next; // Next command in pipe sequence
    char **input_files;
    char **output_files;
} t_command;

typedef struct s_minishell
{
    char *input;
    t_command *cmd;
    int tokens_count;
    int pipe_count;
    t_token **tok;
    char buff[1024];
    t_env *env;
    int exit_code;
} t_minishell;

//* ----------- [ Functions ] -----------

//! Debug functions
void debug_Display_t_command(t_minishell *minishell);
//!

//? [[[[[[[[[[ Main ]]]]]]]]]]]

// #### Do the first fork in the program.
void main_fork(t_minishell *minishell);
//
//#### This the loop that make the shill working forever.
//- Each line after prompt will enter this loop to get process.
//- tokens -> commands pipeline -> execute
void main_loop(t_minishell *minishell);
//

//? [[[[[[[[[[ Commands ]]]]]]]]]]]

//*#### Loop over tokens array to count how many pipes in it.
void count_pipe(t_minishell *minishell);
//
void print_sorted_env(t_minishell *minishell); // Todo
//*#### Run exit command
// - Free the shell
// - Clear the history
// - Exit the shell
void exit_command(t_minishell *minishell);

//? [[[[[[[[[[[[[ Env ]]]]]]]]]]]]]

//*#### Expand the tokens if they are not in single quotes.
//- Use [ expand_variable ] function.
//- Update the value of in tokens array.
void expand_tokens(t_minishell *minishell);
//*#### Expand specific variable in token:
//- Search on dollar sign to handle it env.
//- else it will will extract letters.
char *expand_variable(t_minishell *minishell, char *token);
//*#### Put letters in the in token string unless found a [ $ ]
char *extract_literal(char *token, size_t *i);
void handle_dollar(t_minishell *minishell, char *token, size_t *i, char **result);
char *extract_var_value(t_minishell *minishell, char *token, size_t *i);
char *append_result(char *old_result, char *value);
char *get_env_value(t_env *env, const char *var);
void append_and_free(char **result, char *to_add);
void env_builtin(t_minishell *minishell);
//
void export_builtin(t_minishell *minisell);
//
void unset_builtin(t_minishell *minisell);

//? [[[[[[[[[[[[ Free ]]]]]]]]]]]]]
void ft_exit(t_minishell *minishell, char *str, int status);
//
void free_2d(char **arr);
//
void free_env(t_env *env);
//
void free_tokens(t_token **arr);
//
void free_commands(t_minishell *minishell);
//
void check_to_free(t_minishell *minishell);

//? [[[[[[[[[[[[[[ Init ]]]]]]]]]]]]]]]

//#### Initialize some of elements in the antshell structure.
//- Initialize all pointers to NULL
//- Initialize counters to 0
//- Clear the buffer
void init(t_minishell *minishell);

//#### Display prompt, take an input, and initialize other structure elements.
//- It is also count the number of tokens
//- exit if error occured
void init_shell(t_minishell *minishell);

//#### Converts system-provided environment variables (environ)
//#### into a modifiable linked list (t_env) owned by minishell
t_env *init_env(t_minishell *minishell, char **env);
//
void init_commands(t_minishell *minishell);

//? [[[[[[[[[[[[ Parsing ]]]]]]]]]]]]]
void tokenize_pipe_op(t_minishell *minishell, int *k, int *i);
//
void tokenize_redir_op1(t_minishell *minishell, int *k, int *i);
//
void tokenize_redir_op2(t_minishell *minishell, int *k, int *i);
//
void tokenize_quoted(t_minishell *minishell, int *k, int *i, int glued);
//
void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued);
//
void get_tokens(t_minishell *minishell);
//
void merge_words(t_minishell *ms);
//*#### Allocate argv for all commands
void argv_for_commands(t_minishell *minishell);
//*#### Allocate argv for current command (+1 for NULL).
void allocate_argv(t_minishell *minishell, int *argc, t_command **cmd, int *i);
//*#### Convert the tokens array into commands linked list.
//- Separate [ files names ] [ type of operation ] [ command and its argv ].
void tokens_to_commands(t_minishell *minishell);
//*#### A helper function for [ tekens_to_commands ] function.
//- Close current argv.
//- Move to next command.
void if_outputPipe(t_token *token, t_command **cmd, int *argc);
//*#### A helper function for [ tekens_to_commands ] function
// Check if command [ has_more_redirections ] to add into [ Input ] files.
// Add last file into [ Input ] file with file type enum.
void if_input_filesHeredoc(t_minishell *minishell, t_token *token, t_command **cmd, int *i);
//*#### A helper function for [ tekens_to_commands ] function
// Check if command [ has_more_redirections ] to add into [ Output ] files.
// Add last file into [ Output ] file with file type enum.
void if_output_filesAppend(t_minishell *minishell, t_token *token, t_command **cmd, int *i);
//*#### Add the new file name into its list in cmd struct.
// - Free the old Array.
// - return the new list.
char **add_to_list(char **old_list, char *value);
//*#### Check if there is more than one I/O redirections in the command:
//- return 1 when true .
//- return 0 otherwise. 
int has_more_redirections(t_token **tokens, int start_index, t_type t1, t_type t2);

//? [[[[[[[[[[ Redirection ]]]]]]]]]]]]
// #### loop over tokens array to check for redirections
// void redirection(t_minishell *minishell);
// //
// void redir_compare1(t_minishell *minishell);
// void redir_compare2(t_minishell *minishell);
// void child_re(t_minishell *minishell);
// void parent_re(t_minishell *minishell);
// void call_echo(t_minishell *minishell, int op);
// void call_pwd(t_minishell *minishell);
// void call_env(t_minishell *minishell);
//
//
// void compare_commands (t_minishell *minishell);
//
// #### 1. free all allocated memore
// - Commands array
// - Tokens array
// - Input String
// #### 2. Exit from the program if the input is [ exit ]
#endif
