/*
===============================================================================
!                                LEXER / PARSER
===============================================================================

? Cases to Handle:
- Split by spaces
- Operators: | > < >> <<
- Quotes: single/double
- Escaped characters
- Env variables ($VAR)
- Command + args parsing

? Edge Cases:
- Unclosed quotes
- Multiple spaces/tabs
- Empty input
- Only operators
- Bad heredoc delimiter
- Mixed quotes and escapes

===============================================================================
!                              EXECUTION ENGINE
===============================================================================

? Cases to Handle:
- PATH resolution
- Absolute path
- Builtin dispatch
- Fork and execve
- Parent waits for child

? Edge Cases:
- Command not found
- Permission denied
- Invalid execve args
- Exiting with child status

===============================================================================
!                             REDIRECTIONS & PIPES
===============================================================================

? Cases to Handle:
- Single pipe |
- Multiple pipes
- > overwrite
- >> append
- < input file
- << heredoc

? Edge Cases:
- Missing file
- Permission error
- Consecutive pipes
- Invalid redirection syntax
- Empty heredoc

===============================================================================
!                                   BUILTINS
===============================================================================

? Cases to Handle:
- cd with path
- cd without path
- echo with/without -n
- exit with/without code
- export/unset vars
- env listing

? Edge Cases:
- cd non-existent dir
- cd permission denied
- export invalid identifier
- unset non-existent
- exit non-numeric
- echo with quotes

===============================================================================
!                             SIGNALS & ENVIRONMENT
===============================================================================

? Cases to Handle:
- SIGINT in parent (prompt)
- SIGINT in child (interrupt)
- SIGQUIT default/ignore
- Termios for canonical mode
- Env map handling

? Edge Cases:
- Multiple signals at once
- Reset termios on crash
- Leaking env variables

===============================================================================
!                               TESTING & CLEANUP
===============================================================================

? Cases to Handle:
- Valgrind clean
- Norminette pass
- Functional correctness
- Leak-free exit

? Edge Cases:
- Forgotten free on exit
- Double free
- Bad fd close
- Zombie child
- Invalid user input
- Race conditions in pipes

===============================================================================
*/

