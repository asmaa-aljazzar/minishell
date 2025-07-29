/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/29 12:41:37 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTSHELL_H
#define ANTSHELL_H

//* ----------- [ Includes ] -----------
#include "../libft/includes/libft.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>


//* ----------- [ Macros ] -----------
#define PROMPT "\033[33mminishell\033[32m$ \033[0m"
#define SIG_NONE 0
#define SIG_INT 130   // Ctrl+C (128 + 2)
#define SIG_QUIT 131  // Ctrl+\ (128 + 3)
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
    char **envp; // ["NAME=VAl"][...][...]
    int exit_code;
} t_minishell;

//* ----------- [ Functions ] -----------
//? [[[[[[[[[[[[[[[[[[[ Debug ]]]]]]]]]]]]]]]]]]]
//! Debug functions
void debug_Display_t_command(t_minishell *minishell);
void debug_check_cmd_heredoc(t_command *cmd);
//!

//? [[[[[[[[[[ Main ]]]]]]]]]]]
//*####
void print_banner(void);

// #### Do the first fork in the program.
void main_fork(t_minishell *minishell);

//Todo: write comments
void main_redirection(t_minishell *shell);

//*#### This the loop that make the shill working forever.
//- Each line after prompt will enter this loop to get process.
//- tokens -> commands pipeline -> execute
void main_loop(t_minishell *minishell);
//

//? [[[[[[[[[[[ Signals ]]]]]]]]]]]
//*#### Call signal handlers
void handle_sigquit(int sig);
void handle_sigint(int sig);
void setup_signals(void);

//? [[[[[[[[[[ Commands ]]]]]]]]]]]

//*#### Loop over tokens array to count how many pipes in it.
void count_pipe(t_minishell *minishell);

void print_sorted_env(t_minishell *minishell); // Todo

//*#### exit_command
//- Handles the `exit` built-in logic.
//- Only valid if "exit" is the first token.
//- If no args: exits with 0.
//- If one numeric arg: exits with (arg % 256).
//- If one non-numeric arg: exits with 0.
//- If more than one arg: prints error, does not exit.
void exit_builtin(t_minishell *minishell);

// Todo: add comments
void pwd_builtin(t_minishell *shell);

// Todo: add comments
int is_builtin(t_command *cmd);

// Todo: add comments
void    cd_builtin(t_minishell *shell);

// Todo: add comments
void compare_commands(t_minishell *shell);




//? [[[[[[[[[[[[[[[ EXEC ]]]]]]]]]]]]]]]

// Todo: add comments
int exec_builtin(t_minishell *shell);

// Todo: add comments
int exec_command(t_minishell *shell);

// Todo: add comments
int is_builtin(t_command *cmd);

//? [[[[[[[[[[[[[ Path ]]]]]]]]]]]]]

// Todo: add comments
// Todo: add comments
char *already_path(char *cmd);
// Todo: add comments
char    *find_path(t_env *env);
char    *find_cmd_path( char *cmd,char *path_env);
char    *get_path(t_minishell *shell);
int is_executable(char *path);
char *join_path(const char *path, const char *cmd);

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

//*#### Handle what come after [ $ ].
//- If it is ? then exit status, free itoa value.
//- Else, it will extract variable value.
void handle_dollar(t_minishell *minishell, char *token, size_t *i, char **result);

//*#### Extract the name & value of the variable
//*##### The variable can contain:
//- letters
//- numbers
//- ( _ ) special character
char *extract_var_value(t_minishell *minishell, char *token, size_t *i);

//*#### Replace the old variable in $VAR format with:
//- NAME=val format
char *append_result(char *old_result, char *value);

//*#### Get environment value from t_env struct by loop over its name
//- If not found → expand to empty string
char *get_env_value(t_env *env, const char *var);

//*#### Join the letteral with extracted value
void append_and_free(char **result, char *to_add);

//*#### Run [ env ] command.
// Print all environmen variables.
// With NAME=val format
void env_builtin(t_minishell *minishell);

// 
void export_builtin(t_minishell *minisell);

//
void unset_builtin(t_minishell *minisell);

//? [[[[[[[[[[[[ Free ]]]]]]]]]]]]]

//*#### Exit the shell after free:
//- Commands structure.
//- Tokens array.
//- Input string.
//- Env Structure.
//- Clear the history.
//- Save exit status.
void ft_exit(t_minishell *minishell, char *str, int status);

//*#### Loop ove t_env structure elemnts
//- free name
//- free value
//- free the current node
void free_env(t_env *env);

//*#### Loop over tokens array.
//- Free the string inside the token.
//- Free the token structure itself.
//- Free the array of pointers.
void free_tokens(t_token **arr);

//*#### Free spicific token.
void free_token(t_token *token);

//*#### Free commands structure:
//- Free argv array, not argv[i] strings.
//- Free input_files and output_files with [ free_file_list ].
//- It Does NOT free input_file or output_file — they point to token->word strings!
void free_commands(t_minishell *minishell);

//*#### Loop over & free the list of files names in commmands struct.
void free_file_list(char **list);

//*#### Without exit just free:
//- commands struct.
//- tokens arary.
//- input string.
void check_to_free(t_minishell *minishell);

//*#### Free an 2D array.
void free_2d(char **arr);

//? [[[[[[[[[[[[[[ Init ]]]]]]]]]]]]]]]

//*#### Initialize some of elements in the antshell structure.
//- Initialize all pointers to NULL
//- Initialize counters to 0
//- Clear the buffer
void init(t_minishell *minishell);

//*#### Parsing happened here in addition of some built in commands.
// 1. Display the prompt.
// 2. Read the input line into a buffer.
// 3. Add this line to the history.
// 4. Parsing the input.
// 5. Split it into tokens.
// 6. Move it into cmd structure.
// 7. Run export unset commands.
// 8. After Each initialize check for Null.
// 9. exit if error occured
//Todo: SHOULD change export & unset to wort on commands structure.
void init_shell(t_minishell *minishell); // TODO: Split this function

//*#### Converts system-provided environment variables (environ)
//*#### Into a modifiable linked list (t_env) owned by minishell
//- Loop over environ arrtibute.
//- make head is new node if no nodes yet.
//- other wise the tail->next will be the new node.
t_env *init_env(t_minishell *minishell, char **env);

//*#### Initialize commands structure.
void init_commands(t_minishell *minishell);

//*#### A helper function for init commands.
//- Initialize a node in commands structure.
t_command *create_command(t_minishell *minishell);

//*#### initialize tokens for normal string, with glued flag.
void init_normal_token(t_minishell *ms, char *word, int glued, int *k);

//? [[[[[[[[[[[[ Parsing ]]]]]]]]]]]]]

//*#### Handle EOF from readline (Ctrl+D).
//- Detects if input is NULL (readline returned EOF).
//- Prints "exit", frees environment list, clears readline history.
//- Exits the shell cleanly.
void	handle_eof(t_minishell *minishell);

//*#### A helper function for [process_token]
//- Set pipe into tokens array.
void tokenize_pipe_op(t_minishell *minishell, int *k, int *i);

//*#### Tokenize input redirection symbols.
//- Detects and delegates to heredoc ('<<') or input file ('<') handlers.
//- If '>' is found instead, delegates to tokenize_output_redir.
void tokenize_input_redir(t_minishell *minishell, int *k, int *i);

//*#### Handle heredoc token ('<<').
//- Allocates a new token with word set to '<<'.
//- Sets type to INPUT_HEREDOC and qtype to QUOTE_NONE.
//- Increments token index and input index by 2.
void handle_heredoc_redir(t_minishell *minishell, int *k, int *i);

//*#### Handle input file redirection token ('<').
//- Allocates a new token with word set to '<'.
//- Sets type to INPUT_FILE and qtype to QUOTE_NONE.
//- Increments token index and input index by 1.
void handle_input_file_redir(t_minishell *minishell, int *k, int *i);

//*#### Tokenize output redirection operator.
//- Detects if the redirection is `>>` or `>`.
//- Calls the appropriate handler to tokenize it.
void tokenize_output_redir(t_minishell *minishell, int *k, int *i);

//*#### Handle `>` redirection.
//- Allocates a token for OUTPUT_FILE (overwrite mode).
//- Stores ">" in the word field.
//- Updates index to skip one '>'.
void handle_output_file_redir(t_minishell *minishell, int *k, int *i);

//*#### Handle `>>` redirection.
//- Allocates a token for OUTPUT_APPEND (append mode).
//- Stores ">>" in the word field.
//- Updates index to skip both '>' characters.
void handle_output_append_redir(t_minishell *minishell, int *k, int *i);

//*#### Tokenize quoted or normal string.
//- If current char is quote, reads quoted content and creates token.
//- Else, delegates to tokenize_normal_string.
//- Moves index forward past closing quote if found.
void tokenize_quoted(t_minishell *ms, int *k, int *i, int glued);

//*#### Create a token from quoted string.
//- Allocates a token and sets its word, quote type, and glue flag.
//- Frees the word and exits on allocation failure.
//- Increments token index.
void create_quoted_token(t_minishell *ms, int *k, char *word, char quote, int glued);

//*#### Read content inside a quoted string.
//- Increments index past the opening quote.
//- Reads until the matching closing quote.
//- Allocates and returns the quoted substring.
//- If unmatched quote is found, prints error and returns NULL.
char *read_quoted_content(t_minishell *ms, int *i, char quote);

//*#### A helper function for [process_token]
//- Set Strings That Not space or operation and not quoted into tokens array.
void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued);

//*#### A helper function for [ tokenize_normal_string ]
//- fill the value in a token after allocate
char *allocate_normal_word(t_minishell *ms, int start, int len);

//*#### Allocate and fill tokens array
//- Loop over input string.
//- Use process_tokens function.
//- Set last token as NULL.
//- Count number of commands.
void get_tokens(t_minishell *minishell);

//*#### This help to know if the token is glued to the other tokens 
//*#### Or there is at least one space.
//- Skip spaces, glued is 0 if space exist.
//- If input end then return.
//- Otherwise the tokens is glued.
//##### Then continue tokenizing & use glued value with:
//- tokenize_quoted.
//- tokenize_normal_string.
void process_token(t_minishell *minishell, int *k, int *i);

//*#### Merge consecutive glued WORD tokens.
//- Rewrites the tokens array in-place to condense glued WORDs.
//- For example: "HELLO"'$USER'"test" → one token: "HELLOasmaatest"
//- Uses two indexes: `i` to read, `k` to write.
//- Uses helper: `advance_and_merge` to absorb multiple glued tokens.
void merge_words(t_minishell *minishell);


//*#### Advance through glued WORD tokens and merge them into current token.
//- Loops while the next token is of type WORD, glued, and eligible to merge.
//- Uses `merge_two_tokens` to append and clean up.
void advance_and_merge (t_minishell *minishell, t_token **orig, int *i, int k);

//*#### Merge two tokens together.
//- Joins the `src` token's word to `dst` token's word.
//- Frees the original word in `dst` and free `src` token.
//- Used when consecutive glued WORD tokens are found.
void merge_two_tokens (t_minishell *minishell, t_token *dst, t_token *src);

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

//?[[[[[[[[[[[[[ Heredoc ]]]]]]]]]]]]
char *expand_heredoc_variables(t_minishell *shell, char *content);
char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand);
int create_heredoc_pipe(char *content);
int should_expand_heredoc(t_minishell *shell, char *delimiter);
int setup_heredoc_input(t_command *cmd);
int process_all_heredocs(t_minishell *shell);


//? [[[[[[[[[[ Redirection ]]]]]]]]]]]]
//Todo: add comments
int handell_redirection_output(t_minishell *shell);

//Todo: add comments
void output_redirection_append(t_command *cmd);

//Todo: add comments
void output_redirection_trunc(t_command *cmd);

//Todo: add comments
void handle_output_redirection(t_command *cmd);

//Todo: add comments
void input_redirection(t_command *cmd);

//Todo: add comments
int handell_redirection_input_herdoc(t_minishell *shell);

//Todo: add comments
int handell_redirection(t_minishell *shell);

#endif
