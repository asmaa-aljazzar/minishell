

// //* ----------- [ Functions ] -----------
// //? [[[[[[[[[[[[[[[[[[[ Debug ]]]]]]]]]]]]]]]]]]]
// //! Debug functions
// void debug_Display_t_command(t_minishell *minishell);
// void debug_check_cmd_heredoc(t_command *cmd);
// void debug_print_env(t_minishell *shell);
// void debug_tokens(t_minishell *minishell);
// void debug_commands(t_minishell *minishell);
// //!

// //? [[[[[[[[[[ Main ]]]]]]]]]]]
// //*####
// void print_banner(void);

// // #### Do the first fork in the program.
// void main_fork(t_minishell *minishell);

// //Todo: write comments
// void main_redirection(t_minishell *shell);

// //*#### This the loop that make the shill working forever.
// //- Each line after prompt will enter this loop to get process.
// //- tokens -> commands pipeline -> execute
// void main_loop(t_minishell *minishell);
// //

// //? [[[[[[[[[[[ Signals ]]]]]]]]]]]
// //*#### Call signal handlers
// void handle_sigquit(int sig);
// void handle_sigint(int sig);
// void setup_signals_parent(void);
// void setup_signals_child(void);
// void setup_signals_heredoc(void);
// //? [[[[[[[[[[ Commands ]]]]]]]]]]]

// //*#### Loop over tokens array to count how many pipes in it.
// void count_pipe(t_minishell *minishell);
// int is_command_empty(t_command *cmd);
// void print_sorted_env(t_minishell *minishell); // Todo

// //*#### exit_command
// //- Handles the `exit` built-in logic.
// //- Only valid if "exit" is the first token.
// //- If no args: exits with 0.
// //- If one numeric arg: exits with (arg % 256).
// //- If one non-numeric arg: exits with 0.
// //- If more than one arg: prints error, does not exit.
// void exit_builtin(t_minishell *minishell);

// // Todo: add comments
// void pwd_builtin(t_minishell *shell);

// // Todo: add comments
// int is_builtin(t_command *cmd);

// // Todo: add comments
// void    cd_builtin(t_minishell *shell);

// // Todo: add comments
// void compare_commands(t_minishell *shell);

// void export_builtin(t_minishell *shell);
// void unset_builtin(t_minishell *shell);



// //? [[[[[[[[[[[[[[[ EXEC ]]]]]]]]]]]]]]]

// // Todo: add comments
// int exec_builtin(t_minishell *shell);

// // Todo: add comments
// int exec_command(t_minishell *shell);

// // Todo: add comments
// int is_builtin(t_command *cmd);

// //? [[[[[[[[[[[[[ Path ]]]]]]]]]]]]]

// // Todo: add comments
// // Todo: add comments
// char *already_path(char *cmd);
// // Todo: add comments
// char    *find_path(t_env *env);
// char    *find_cmd_path( char *cmd,char *path_env);
// char    *get_path(t_minishell *shell);
// int is_executable(char *path);
// char *join_path(const char *path, const char *cmd);

// //? [[[[[[[[[[[[[ Env ]]]]]]]]]]]]]

// //*#### Expand the tokens if they are not in single quotes.
// //- Use [ expand_variable ] function.
// //- Update the value of in tokens array.
// void expand_tokens(t_minishell *minishell);

// //*#### Expand specific variable in token:
// //- Search on dollar sign to handle it env.
// //- else it will will extract letters.
// char *expand_variable(t_minishell *minishell, char *token);

// //*#### Put letters in the in token string unless found a [ $ ]
// char *extract_literal(char *token, size_t *i);

// //*#### Handle what come after [ $ ].
// //- If it is ? then exit status, free itoa value.
// //- Else, it will extract variable value.
// void handle_dollar(t_minishell *minishell, char *token, size_t *i, char **result);

// //*#### Extract the name & value of the variable
// //*##### The variable can contain:
// //- letters
// //- numbers
// //- ( _ ) special character
// char *extract_var_value(t_minishell *minishell, char *token, size_t *i);

// //*#### Replace the old variable in $VAR format with:
// //- NAME=val format
// char *append_result(char *old_result, char *value);

// //*#### Get environment value from t_env struct by loop over its name
// // - Loop ove t_env and search value by name. 
// // - If not found → expand to empty string.
// char *get_env_value(t_env *env, const char *var);

// //*#### Join the letteral with extracted value
// void append_and_free(char **result, char *to_add);

// //*#### Run [ env ] command.
// // Print all environmen variables.
// // With NAME=val format
// void env_builtin(t_minishell *minishell);

// // 
// void export_builtin(t_minishell *minisell);

// //
// void unset_builtin(t_minishell *minisell);

// //? [[[[[[[[[[[[[ Env - Word Splitting ]]]]]]]]]]]]]

// //*#### Split expanded variable content on whitespace
// //- Splits string on spaces, tabs, newlines
// //- Returns array of strings, NULL-terminated
// //- Returns NULL if input is empty or NULL
// char **split_on_whitespace(char *str);

// //*#### Check if character is whitespace
// //- Returns 1 for space, tab, newline
// //- Returns 0 otherwise
// int is_whitespace(char c);

// //*#### Count words in a string separated by whitespace
// //- Used to determine array size for splitting
// int count_words_in_string(char *str);

// //*#### Expand and split a single token
// //- Handles both expansion and word splitting
// //- Creates multiple tokens if expansion contains spaces
// void expand_and_split_token(t_minishell *ms, t_token *token, 
//                            t_token **new_tokens, int *new_count);

// //*#### Free array of strings
// //- Frees each string and the array itself
// void free_split_array(char **array);

// //*#### Estimate maximum tokens after expansion
// //- Conservative estimate for memory allocation
// int count_max_tokens_after_expansion(t_minishell *ms);

// //*#### Handle empty variable expansion cases
// //- Returns appropriate string for empty expansions
// //- Returns NULL if not an empty case
// char *handle_empty_expansion(char *token);

// //? [[[[[[[[[[[[ Free ]]]]]]]]]]]]]

// //*#### Exit the shell after free:
// //- Commands structure.
// //- Tokens array.
// //- Input string.
// //- Env Structure.
// //- Clear the history.
// //- Save exit status.
// void ft_exit(t_minishell *minishell, char *str, int status);

// //*#### Loop ove t_env structure elemnts
// //- free name
// //- free value
// //- free the current node
// void free_env(t_env *env);

// //*#### Loop over tokens array.
// //- Free the string inside the token.
// //- Free the token structure itself.
// //- Free the array of pointers.
// void free_tokens(t_token **arr);

// //*#### Free spicific token.
// void free_token(t_token *token);

// //*#### Free commands structure:
// //- Free argv array, not argv[i] strings.
// //- Free input_files and output_files with [ free_file_list ].
// //- It Does NOT free input_file or output_file — they point to token->word strings!
// void free_commands(t_minishell *minishell);

// //*#### Loop over & free the list of files names in commmands struct.
// void free_file_list(char **list);

// //*#### Without exit just free:
// //- commands struct.
// //- tokens arary.
// //- input string.
// void check_to_free(t_minishell *minishell);

// //*#### Free an 2D array.
// void free_2d(char **arr);

// //? [[[[[[[[[[[[[[ Init ]]]]]]]]]]]]]]]

// //*#### Initialize some of elements in the antshell structure.
// //- Initialize all pointers to NULL
// //- Initialize counters to 0
// //- Clear the buffer
// void init(t_minishell *minishell, char **environ);

// //*#### Parsing happened here in addition of some built in commands.
// // 1. Display the prompt.
// // 2. Read the input line into a buffer.
// // 3. Add this line to the history.
// // 4. Parsing the input.
// // 5. Split it into tokens.
// // 6. Move it into cmd structure.
// // 7. Run export unset commands.
// // 8. After Each initialize check for Null.
// // 9. exit if error occured
// //Todo: SHOULD change export & unset to wort on commands structure.
// void init_shell(t_minishell *minishell); // TODO: Split this function

// //*#### Converts system-provided environment variables (environ)
// //*#### Into a modifiable linked list (t_env) owned by minishell
// //- Loop over environ arrtibute.
// //- make head is new node if no nodes yet.
// //- other wise the tail->next will be the new node.
// t_env *init_env(t_minishell *minishell, char **env);

// //*#### Initialize commands structure.
// void init_commands(t_minishell *minishell);

// //*#### A helper function for init commands.
// //- Initialize a node in commands structure.
// t_command *create_command(t_minishell *minishell);

// //*#### initialize tokens for normal string, with glued flag.
// void init_normal_token(t_minishell *ms, char *word, int glued, int *k);

// //? [[[[[[[[[[[[ Parsing ]]]]]]]]]]]]]

// //*#### Handle EOF from readline (Ctrl+D).
// //- Detects if input is NULL (readline returned EOF).
// //- Prints "exit", frees environment list, clears readline history.
// //- Exits the shell cleanly.
// void	handle_eof(t_minishell *minishell);

// //*#### A helper function for [process_token]
// //- Set pipe into tokens array.
// void tokenize_pipe_op(t_minishell *minishell, int *k, int *i);

// //*#### Tokenize input redirection symbols.
// //- Detects and delegates to heredoc ('<<') or input file ('<') handlers.
// //- If '>' is found instead, delegates to tokenize_output_redir.
// void tokenize_input_redir(t_minishell *minishell, int *k, int *i);

// //*#### Handle heredoc token ('<<').
// //- Allocates a new token with word set to '<<'.
// //- Sets type to INPUT_HEREDOC and qtype to QUOTE_NONE.
// //- Increments token index and input index by 2.
// void handle_heredoc_redir(t_minishell *minishell, int *k, int *i);

// //*#### Handle input file redirection token ('<').
// //- Allocates a new token with word set to '<'.
// //- Sets type to INPUT_FILE and qtype to QUOTE_NONE.
// //- Increments token index and input index by 1.
// void handle_input_file_redir(t_minishell *minishell, int *k, int *i);

// //*#### Tokenize output redirection operator.
// //- Detects if the redirection is `>>` or `>`.
// //- Calls the appropriate handler to tokenize it.
// void tokenize_output_redir(t_minishell *minishell, int *k, int *i);

// //*#### Handle `>` redirection.
// //- Allocates a token for `OUTPUT_FILE` (overwrite mode).
// //- Stores `>` in the word field.
// //- Updates index to skip one `>`.
// void handle_output_file_redir(t_minishell *minishell, int *k, int *i);

// //*#### Handle `>>` redirection.
// //- Allocates a token for `OUTPUT_APPEND` (append mode).
// //- Stores `>>` in the word field.
// //- Updates index to skip both `>` characters.
// void handle_output_append_redir(t_minishell *minishell, int *k, int *i);

// //*#### Tokenize quoted or normal string.
// //- If current char is quote, reads quoted content and creates token.
// //- Else, delegates to tokenize_normal_string.
// //- Moves index forward past closing quote if found.
// void tokenize_quoted(t_minishell *ms, int *k, int *i, int glued);

// //*#### Create a token from quoted string.
// //- Allocates a token and sets its word, quote type, and glue flag.
// //- Frees the word and exits on allocation failure.
// //- Increments token index.
// void create_quoted_token(t_minishell *ms, int *k, char *word, char quote, int glued);

// //*#### Read content inside a quoted string.
// //- Increments index past the opening quote.
// //- Reads until the matching closing quote.
// //- Allocates and returns the quoted substring.
// //- If unmatched quote is found, prints error and returns NULL.
// char *read_quoted_content(t_minishell *ms, int *i, char quote);

// //*#### A helper function for [process_token]
// //@brief Hold Set Strings That Not space or operation and not quoted into tokens array.
// //@param minishell
// //@return nothing
// void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued);

// //*#### A helper function for [ tokenize_normal_string ]
// //- fill the value in a token after allocate
// char *allocate_normal_word(t_minishell *ms, int start, int len);

// //*#### Allocate and fill tokens array
// //- Loop over input string.
// //- Use `process_tokens` function.
// //- Set last token as `NULL`.
// //- Count number of commands.
// void get_tokens(t_minishell *minishell);

// //*#### This help to know if the token is glued to the other tokens 
// //*#### Or there is at least one space.
// //- Skip spaces, glued is 0 if space exist.
// //- If input end then return.
// //- Otherwise the tokens is glued.
// //##### Then continue tokenizing & use glued value with:
// //- tokenize_quoted.
// //- tokenize_normal_string.
// void process_token(t_minishell *minishell, int *k, int *i);

// //*#### Merge consecutive glued WORD tokens.
// //- Rewrites the tokens array in-place to condense glued WORDs.
// //- For example: "HELLO"'$USER'"test" → one token: "HELLOasmaatest"
// //- Uses two indexes: `i` to read, `k` to write.
// //- Uses helper: `advance_and_merge` to absorb multiple glued tokens.
// void merge_words(t_minishell *minishell);


// //*#### Advance through glued WORD tokens and merge them into current token.
// //- Loops while the next token is of type WORD, glued, and eligible to merge.
// //- Uses `merge_two_tokens` to append and clean up.
// void advance_and_merge (t_minishell *minishell, t_token **orig, int *i, int k);

// //*#### Merge two tokens together.
// //- Joins the `src` token's word to `dst` token's word.
// //- Frees the original word in `dst` and free `src` token.
// //- Used when consecutive glued WORD tokens are found.
// void merge_two_tokens (t_minishell *minishell, t_token *dst, t_token *src);

// //*#### Allocate argv for all commands
// void argv_for_commands(t_minishell *minishell);

// //*#### Allocate argv for current command (+1 for NULL).
// void allocate_argv(t_minishell *minishell, int *argc, t_command **cmd, int *i);

// //*#### Convert the tokens array into commands linked list.
// //- Separate [ files names ] [ type of operation ] [ command and its argv ].
// void tokens_to_commands(t_minishell *minishell);

// //*#### A helper function for [ tekens_to_commands ] function.
// //- Close current argv.
// //- Move to next command.
// void if_outputPipe(t_token *token, t_command **cmd, int *argc);

// //*#### A helper function for [ tekens_to_commands ] function
// // Check if command [ has_more_redirections ] to add into [ Input ] files.
// // Add last file into [ Input ] file with file type enum.
// void if_input_filesHeredoc(t_minishell *minishell, t_token *token, t_command **cmd, int *i);

// //*#### A helper function for [ tekens_to_commands ] function
// // Check if command [ has_more_redirections ] to add into [ Output ] files.
// // Add last file into [ Output ] file with file type enum.
// void if_output_filesAppend(t_minishell *minishell, t_token *token, t_command **cmd, int *i);

// //*#### Add the new file name into its list in cmd struct.
// // - Free the old Array.
// // - return the new list.
// char **add_to_list(char **old_list, char *value);

// //*#### Check if there is more than one I/O redirections in the command:
// //- return 1 when true .
// //- return 0 otherwise. 
// int has_more_redirections(t_token **tokens, int start_index, t_type t1, t_type t2);

// //?[[[[[[[[[[[[[ Heredoc ]]]]]]]]]]]]

// //*#### This will process [ Form commands struct ]:
// //- Discarded heredocs.
// //- Final heredoc.
// int process_all_heredocs(t_minishell *shell);

// //*#### Processes heredocs that not the final input
// // - Loop over all input files in the command
// // - For each heredoc, determines if has var expand or not
// // - Reads the heredoc content, free it immediately (not used)
// // - If reading fails, set `exit_code` to `1` and returns `0` (error)
// // - Return `1` on successful process all heredocs (even if discarded)
// int process_discarded_heredocs(t_minishell *minishell, t_command *cmd);



// //*#### Check if the delimiter should expand variables
// // - Loop over the tokens array tokens to find matched delimiter
// // - Return `1` if delimiter is not single quote
// // - Return `0` if found and it is single quote (no expansion)
// // - Defaults to `1` (expand) if delimiter is not found in tokens
// int should_expand_heredoc(t_minishell *shell, char *delimiter);

// int process_final_heredoc(t_minishell *shell, t_command *cmd);

// //*#### Read content from [ stdin ] until delimiter
// // - Uses `read_until_delimiter` to collect heredoc input
// // - If `should_expand` is true, expand input
// // - Free the original content if expanded, return the processed string
// // - Returns NULL when fail to read, otherwise returns heredoc content
// char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand);

// //*#### Reads from stdin until delimiter
// // - Initialize heredoc content as an empty string.
// // - Uses `readline("> ")` will prompt to user.
// // - Each line processed by `process_heredoc_readline`, 
// //   append it or stop reading
// // - Loop break if delimiter found (`should_break`) 
// //   or on read failure
// // - Returns content or NULL on failure
// char *read_until_delimiter(char *delimiter);

// //*#### Processes a single line read from heredoc input
// // - Resets `g_signal_received` to SIG_NONE and clear `should_break`.
// // - If (`SIG_INT`) is detected, free line and content, return NULL
// // - If line is NULL (EOF), print a warning and sets `should_break = 1`
// // - If the line matche delimiter, free the line and sets `should_break = 1`
// // - Otherwise, appends line to content
// // - Always free the input line before return
// char *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break);

// //*#### Expands an env var found in heredoc content
// // - current index on `$`, `i++` to start reading the variable name.
// // - get variable name from content using `extract_var_name`.
// // - get value from the t_env using `get_env_value`.
// // - If variable value is NULL, appends empty string;
// //   otherwise, appends variable value.
// // - Free the extracted variable name.
// // - Returns the updated result string.
// char *expand_env_var(t_minishell *shell, char *content, char *result, int *i);

// //*#### Expand var in heredoc content
// // - Returns empty string if input is NULL
// // - Loop over each character in the content
// // - On `$`, checks if it's (`$?`) or a valid env var
// //     - `$?` → replaced last exit code.
// //     - `$VAR` or `$_` → replaced using env var.
// //     - Otherwise `$` is literal.
// // - Appends to `result`, character by character or expanded
// // - Returns the fully expanded result string
// char *expand_heredoc_variables(t_minishell *shell, char *content);

// //*#### Expands the `$?` special variable.
// // - Converts `shell->exit_code` to string using `ft_itoa`
// // - Appends the result to the string
// // - Free the temporary string after use
// // - increase `i` by 2 to skip  `$?`
// // - Returns the updated result string
// char *expand_exit_code(t_minishell *shell, char *result, int *i);

// //*#### Appends single char to the result string
// // - Converts the character to a null-terminated string
// // - Uses `append_to_result` to concatenate the
// //   char with the exist string
// // - Return the newly allocated concatenated string
// char *append_single_char(char *result, char c);

// //*#### Concatenate 2 strings togather
// // - Uses `ft_strjoin`.
// // - Free `temp` buffer.
// // - Return concatenated string.
// char *append_to_result(char *result, char *to_append);

// //*#### Extract the var name from the string next to $.
// // - Loop over the `characters`, `numbers` or `_`.
// // - Returns the string.
// char *extract_var_name(char *str, int *index);

// //*#### Display warning when heredoc ends due to EOF
// //*#### before the expected delimiter
// // - Informs the user that the heredoc was not properly closed
// // - Outputs the expected `delimiter` that was not found
// // - Writes the message to standard error (file descriptor 2)
// void print_eof_warning(char *delimiter);

// //*#### check if the line content is delimiter
// // - `ft_strncmp` for compare character.
// // - Must be exact the same length with the delimiter.
// int is_delimiter_line(char *line, char *delimiter);

// //*#### Appends line + newline to heredoc content
// // - Concatenates `line` to the existing `content`
// // - Then adds a newline character (`\n`) to the result
// // - Free the old `content` after each concatenation
// // - Returns the new constructed string
// char *append_line_to_content(char *content, char *line);

// //*#### create_heredoc_pipe
// //- Creates a pipe and writes the given heredoc content into its write end.
// //- If content is non-empty, it writes the full string to the pipe.
// //- Closes the write end after writing.
// //- On success: returns the read end of the pipe.
// //- On failure (pipe or write error): closes both ends and returns -1.
// int create_heredoc_pipe(char *content);

// //*#### Checks if the command expects heredoc input and if heredoc content exists.
// //- Creates a pipe containing the heredoc content using `create_heredoc_pipe`.
// //- Redirects standard input `stdin` to the pipe’s read end using dup2.
// //- Close original pipe descriptor after duplicate.
// //- Returns `1` on successful setup, `0` otherwise.
// int setup_heredoc_input(t_command *cmd);


// //? [[[[[[[[[[ Redirection ]]]]]]]]]]]]
// //? [[[[[[[[[[ Redirection ]]]]]]]]]]]]

// //*#### Validate all redirections before execution
// //- Checks if all input files exist and are readable
// //- Checks if all output files can be created/written
// //- Returns 1 on success, 0 on failure
// int handle_redirection(t_minishell *shell);

// //*#### Handle input file redirection
// //- Opens input file and redirects stdin
// //- Exits with error if file cannot be opened
// void input_redirection(t_command *cmd);

// //*#### Handle output file redirection
// //- Opens output file with appropriate flags (truncate/append)
// //- Redirects stdout to the file
// //- Exits with error if file cannot be opened
// void handle_output_redirection(t_command *cmd);

// // Remove the duplicate/misspelled prototypes:
// // int handell_redirection_output(t_minishell *shell);
// // void output_redirection_append(t_command *cmd);
// // void output_redirection_trunc(t_command *cmd);
// // int handell_redirection_input_herdoc(t_minishell *shell);
// // int handell_redirection(t_minishell *shell);

// //? [[[[[[[[[ Pipe ]]]]]]]]]

// //*#### Main pipeline execution function
// //- Determines if single command or pipeline
// //- Delegates to main_fork for single commands
// //- Delegates to execute_piped_commands for pipelines
// void execute_pipeline(t_minishell *shell);

// //*#### Execute multiple commands connected by pipes
// //- Creates pipes for inter-process communication
// //- Forks child processes for each command
// //- Sets up proper pipe connections
// //- Waits for all children to complete
// void execute_piped_commands(t_minishell *shell, int cmd_count);

// //*#### Close all pipe file descriptors
// //- Loops through all pipes and closes both read and write ends
// //- Used by parent after forking all children
// void close_all_pipes(int pipes[][2], int pipe_count);

// //*#### Setup pipe connections for child process
// //- Redirects stdin from previous pipe (if not first command)
// //- Redirects stdout to next pipe (if not last command)
// //- Closes all pipe file descriptors in child
// void setup_child_pipes(int pipes[][2], int cmd_index, int cmd_count);

// //*#### Wait for all child processes and set exit code
// //- Waits for each child process to complete
// //- Sets shell exit code to last command's exit status
// void wait_for_children(t_minishell *shell, pid_t *pids, int cmd_count);

// //*#### Check if command has no arguments
// //- Returns 1 if command is empty or has no argv
// //- Returns 0 otherwise
// int is_empty_command(t_command *cmd);

// // //*#### Validate pipeline syntax
// // //- Checks for consecutive pipes
// // //- Checks for pipe at end of input
// // //- Sets appropriate error messages and exit codes
// // //- Returns 0 on error, 1 on success
// // int validate_pipeline(t_minishell *minishell);

// //*#### Check for empty commands in pipeline
// //- Detects empty commands between pipes
// //- Sets syntax error and exit code
// void handle_empty_commands(t_minishell *shell);

// //? [[[[[[[[[ Command Execution ]]]]]]]]]

// //*#### Execute external commands
// //- Finds command in PATH or uses absolute path
// //- Executes with execve
// //- Handles command not found and permission errors
// void execute_external_command(t_minishell *shell);


// //? [[[[[[[[[ Builtin Commands ]]]]]]]]]

// //*#### Echo builtin implementation
// //- Handles -n flag for no newline
// //- Prints all arguments with spaces
// void echo_builtin(t_minishell *shell);

// //*#### Update environment variable
// //- Updates existing variable or creates new one
// //- Used by cd_builtin for PWD/OLDPWD
// void update_env_var(t_minishell *shell, char *name, char *value);

// void update_envp_array(t_minishell *shell, char *name, char *value);

// //[[[[[[[[Minilib]]]]]]]]

// int is_positive_number(const char *s);

// //[[[[[[[[expand]]]]]]]]

// void increase_SHLVL_var(t_minishell *ms, t_env *env);

// # endif