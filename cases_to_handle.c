/*
===============================================================================
!                                LEXER / PARSER
===============================================================================

? YOU must handle explicitly:
- Tokenize input by whitespace (spaces, tabs).
- Recognize and separate operators: |, <, >, >>, <<.
- Parse quotes: single (') literal, double (") with $ expansions.
- Preserve spaces inside quotes.
- Env var expansion ($VAR, $?) respecting quote rules.
- Reject or error on unclosed quotes.
- Reject or error on empty input or input with only operators.
- Reject bad heredoc delimiters.
- Handle nested/mixed quotes.
- Do not interpret backslash \ or semicolon ;.
- Build abstract syntax tree or linked command list.
- Identify pipelines and associate commands.
- Assign redirections to commands.
- Detect and reject invalid syntax (e.g. | |, cat <, etc.).

? Handled for you:
- None. Tokenizer/parser 100% your code.

===============================================================================
!                              EXECUTION ENGINE
===============================================================================

? YOU must handle explicitly:
- Locate executables via PATH or absolute path.
- Recognize and dispatch builtins internally.
- Fork processes.
- Setup pipes (pipe(), dup2()) for N commands.
- Handle redirections (<, >, >>, <<) before execve.
- Close unused file descriptors.
- Wait for all child processes to finish.
- Track last foreground exit status ($?).

? Edge cases:
- Command not found → print error.
- Permission denied → print error.
- Multiple pipes and redirections → chain correctly, last redirection wins.
- Missing files for redirection.
- Exit status propagation.

? Handled for you:
- OS runs execve, manages process scheduling.
- Syscalls pipe(), open(), dup2(), waitpid() provide low-level tools.

===============================================================================
!                             REDIRECTIONS & PIPES
===============================================================================

? YOU must handle explicitly:
- < : open file for reading; fail gracefully on error.
- > : truncate file for writing.
- >>: open file for appending.
- <<: heredoc:
    - prompt user until delimiter line.
    - do not add heredoc input to history.
    - handle Ctrl-C interrupt gracefully (abort heredoc).
- Setup pipe chains for multiple commands.
- Detect and error on consecutive pipes without command.
- Ensure pipe ends are closed properly.

? Handled for you:
- OS syscalls for open, close, pipe.
- errno reports file errors.

===============================================================================
!                                   BUILTINS
===============================================================================

? YOU must handle explicitly:
- echo [-n] [args...]
- cd [path | none]
- pwd (print working directory)
- export [VAR=VAL | none]
- unset [VAR]
- env (print environment)
- exit [status]

? Edge cases:
- cd to invalid or inaccessible directory → error message.
- export invalid identifiers → error message.
- exit with non-numeric status → error.
- echo with quoted arguments and multiple spaces preserved.
- unset non-existent vars → no error, silently ignore.

? Handled for you:
- None. All builtin logic must be written.

===============================================================================
!                             SIGNALS & ENVIRONMENT
===============================================================================

? YOU must handle explicitly:
- SIGINT (Ctrl-C):
    - Parent: print new prompt, reset input line.
    - Child: terminate immediately.
- SIGQUIT (Ctrl-\):
    - Parent: ignore.
    - Child: default behavior.
- Maintain global signal state variable (only one allowed).
- Reset terminal settings on exit or signal.
- Manage environment map internally for export/unset.
- Pass updated env map to execve.

? Edge cases:
- Interrupt heredoc on SIGINT cleanly.
- Handle multiple signals arriving closely.
- Avoid leaks in environment data structures.

? Handled for you:
- OS delivers signals.
- sigaction() syscall.

===============================================================================
!                               TERMINAL SETTINGS
===============================================================================

? YOU must handle explicitly:
- Disable echoing of Ctrl-C in prompt (canonical mode adjustments).
- Restore terminal settings on normal exit or crash.
- Protect against crash leaving terminal in inconsistent state.

? Handled for you:
- tcgetattr(), tcsetattr() syscalls.

===============================================================================
!                             MEMORY MANAGEMENT
===============================================================================

? YOU must handle explicitly:
- Free all allocated memory on normal and error exit.
- Free tokens, command structures, env map copies.
- Avoid double frees and use-after-frees.
- Handle leaks during error handling paths.

? Handled for you:
- None.

===============================================================================
!                               CTRL-D & EOF
===============================================================================

? YOU must handle explicitly:
- Exit shell cleanly when readline returns NULL (EOF / Ctrl-D).

? Handled for you:
- readline() returns NULL on EOF.

===============================================================================
!                               CTRL-\ (SIGQUIT)
===============================================================================

? YOU must handle explicitly:
- Ignore SIGQUIT in interactive parent shell.
- Do nothing special besides that.

? Handled for you:
- OS sends SIGQUIT signal.

===============================================================================
!                               NORMINETTE & MAKEFILE
===============================================================================

? YOU must handle explicitly:
- Conform to Norminette rules (function length, naming, header structure).
- Write Makefile with targets:
    - all (build executable)
    - clean (remove object files)
    - fclean (clean + remove executable)
    - re (fclean + all)
- Compile with flags: -Wall -Wextra -Werror.

? Handled for you:
- Norminette tool reports violations.
- Make program runs rules.

===============================================================================
!                                 SUMMARY TABLE
===============================================================================

Feature               | YOU must handle            | Handled for you
----------------------|----------------------------|-------------------------------
Prompt & readline     | Prompt, EOF exit           | History, line editing
Tokenization          | All tokenizing & parsing   | None
Quotes                | All quote parsing          | None
Env var expansion     | $VAR, $? replacements      | getenv()
Parser / AST          | Build command structure    | None
Execution             | fork, execve, dup2, wait   | execve runs, OS schedules
Redirections          | <, >, >>, heredoc logic    | open/close syscalls
Pipes                 | pipe fd setup, chaining    | pipe() syscall
Builtins              | All builtin commands       | None
Environment           | export, unset env map      | getenv() returns env
Signals               | sigaction handling         | OS delivers signals
Termios               | Modify terminal settings   | tcsetattr/tcgetattr syscalls
$?                    | Track last exit status     | waitpid returns code
Ctrl-D                | Exit shell on EOF          | readline returns NULL
Ctrl-\                | Ignore SIGQUIT in parent   | OS sends SIGQUIT
Memory management     | Free all allocated memory  | None
Norminette            | Follow rules strictly      | Norm tool checks
Makefile              | Write rules & flags        | make runs rules

===============================================================================
*/
