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

//! Could delete 
//.h + debug folder
#include "debug.h"
//!

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
} t_command;

typedef struct s_minishell
{
    char *input;
    t_command *cmd;             // head of the linked list of commands
    int tokens_count;
    int pipe_count;
    t_token **tok;
    char buff[1024];
    t_env *env;
    int exit_code;
} t_minishell;

//* ----------- [ Functions ] -----------

//? [[[[[[[[[[ Main ]]]]]]]]]]]
// #### Do the first fork in the program
void main_fork(t_minishell *minishell);
void main_redirection(t_minishell *shell);

//? [[[[[[[[[[ Commands ]]]]]]]]]]]

//? [[[[[[[[[[[[[ Env ]]]]]]]]]]]]]

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
//- 	integer values
//- 	tokens array
void init(t_minishell *minishell);
//
//#### Display prompt, take an input, and initialize other structure elements.
//- It is also count the number of tokens
//- exit if error occured
void init_shell(t_minishell *minishell);

//? [[[[[[[[[[[[] Parsing ]]]]]]]]]]]]]
void tokenize_pipe_op(t_minishell *minishell, int *k, int *i);
//
//* #### while loop iterates over the linked list of commands in shell->cmd ###
//- processing input/output redirections for each command in the pipeline.
//- stdout -> with the file descriptor of the output file.
//- stdin -> with the file descriptor of the input file.
//void redirection(t_minishell *minishell);
void input_redirection(t_command *cmd);
void output_redirection(t_command *cmd);

void tokenize_redir_op1(t_minishell *minishell, int *k, int *i);
//
void tokenize_redir_op2(t_minishell *minishell, int *k, int *i);
//
void tokenize_quoted(t_minishell *minishell, int *k, int *i, int glued);
//
void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued);

//? [[[[[[[[[[ Redirection ]]]]]]]]]]]]
// #### loop over tokens array to check for redirections
// void redirection(t_minishell *minishell);

// //
//* ### execution one command 
//- Single command executed
//- check its builtin 
//- External command with path resolution
int exec_command(t_minishell *shell);
//int is_builtin(char *cmd);
//int exec_builtin(t_minishell *shell);
char **env_to_envp(t_env *env);

//* get path for command 
//- check if input is already path  and excutable
//- if not token path after : 
//- search the rigth path in token 
//- builds a string: dir + "/" + cmd
char    *get_path(t_minishell *shell);
char *already_path(char *cmd);
int is_executable(char *path);
char    *find_path(t_env *env);
char    *find_cmd_path(char *cmd, char *path_env);
char *join_path(const char *path, const char *cmd);

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
void init_commands(t_minishell *minishell);
void count_pipe(t_minishell *minishell);
void get_tokens(t_minishell *minishell);
// void init_tokens (t_minishell *minishell);
t_env *init_env(t_minishell *minishell, char **env);
void expand_tokens(t_minishell *minishell);
char *expand_variable(t_minishell *minishell, char *token);
void env_builtin(t_minishell *minishell);
void export_builtin(t_minishell *minisell);
void unset_builtin(t_minishell *minisell);
void print_sorted_env(t_minishell *minishell);
void tokens_to_commands(t_minishell *minishell);
void merge_words(t_minishell *ms);
int validate_commands(t_command *cmds);
#endif
