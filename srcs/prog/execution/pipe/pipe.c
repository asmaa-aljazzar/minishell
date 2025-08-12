#include "minishell.h"

// Close all pipe file descriptors safely
static void close_all_pipes(int pipes[][2], int pipe_count)
{
    for (int i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

// Kill previously forked children in case of error to avoid zombies
static void kill_children(pid_t *pids, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (pids[i] > 0)
            kill(pids[i], SIGKILL);
    }
}

// Wait for all children and update exit status from last command
static void wait_for_children(t_minishell *ms, pid_t *pids, int cmd_count)
{
    int status;
    for (int i = 0; i < cmd_count; i++)
    {
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1)
        {
            if (WIFEXITED(status))
                ms->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                ms->exit_code = 128 + WTERMSIG(status);
        }
    }
}


// --- 4. Child process code ---
static void run_child(t_minishell *ms, t_command *cmd, int (*pipes)[2],
                      int cmd_index, int cmd_count)
{
    setup_signals_child();

    // Set up pipes
    if (cmd_index > 0 && dup2(pipes[cmd_index - 1][0], STDIN_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    if (cmd_index < cmd_count - 1 && dup2(pipes[cmd_index][1], STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close_all_pipes(pipes, cmd_count - 1);
    ms->cmd = cmd;

    if (is_command_empty(cmd))
        exit(0);

    if (main_redirection(ms) != 0)
        exit(EXIT_FAILURE);
    
    // Execute command
    if (is_builtin(cmd))
    {
        compare_commands(ms);
        exit(ms->exit_code);
    }
    else
    {
        // For external commands, execute directly
        execute_external_command(ms);
        // execute_external_command should not return
    }
    
    exit(EXIT_FAILURE); // Should never reach here
}
// --- 2. Create all pipes ---
static int create_all_pipes(int (*pipes)[2], int pipe_count)
{
    for (int i = 0; i < pipe_count; i++)
    {
        if (pipe(pipes[i]) < 0)
        {
            perror("pipe");
            close_all_pipes(pipes, i);
            return -1;
        }
    }
    return 0;
}

// --- 3. Fork children and execute commands ---
static int fork_children(t_minishell *ms, int (*pipes)[2], pid_t *pids, int cmd_count)
{
    t_command *cmd = ms->cmd;

    for (int i = 0; i < cmd_count && cmd; i++, cmd = cmd->next)
    {
        pids[i] = fork();
        if (pids[i] < 0)
            return i; // Number of successful forks before failure
        if (pids[i] == 0)
        {
            run_child(ms, cmd, pipes, i, cmd_count);
            // never returns
        }
    }
    return cmd_count; // all forks succeeded
}

// --- 5. Parent cleanup and wait ---
static void handle_parent_process(t_minishell *ms, int (*pipes)[2], pid_t *pids, int cmd_count)
{
    close_all_pipes(pipes, cmd_count - 1);
    wait_for_children(ms, pids, cmd_count);
}
// Allocates pipes and pids arrays; returns 0 or -1 on failure
static int allocate_resources(int cmd_count, int (**pipes)[2], pid_t **pids)
{

    *pipes = malloc(sizeof(int[2]) * (cmd_count - 1));
    *pids = malloc(sizeof(pid_t) * cmd_count);
    if (!*pipes || !*pids)
    {
        perror("malloc");
        free(*pipes);
        free(*pids);
        return -1;
    }
    return 0;
}

// Handles cleanup on fork failure: kills children, waits, closes pipes, frees memory
static void cleanup_on_fork_failure(t_minishell *ms, pid_t *pids, int forked, int (*pipes)[2], int pipe_count)
{
    ms->exit_code = EXIT_FAILURE;
    kill_children(pids, forked);
    for (int j = 0; j < forked; j++)
        waitpid(pids[j], NULL, 0);
    close_all_pipes(pipes, pipe_count);
    free(pids);
    free(pipes);
}
// Función auxiliar que se encarga de preparar recursos, crear pipes y forkear hijos.
// Retorna 0 en éxito, -1 en error.
static int setup_and_fork(t_minishell *ms, int cmd_count, int (**pipes)[2], pid_t **pids)
{
    if (allocate_resources(cmd_count, pipes, pids) < 0)
        return -1;
    if (create_all_pipes(*pipes, cmd_count - 1) < 0)
    {
        free(*pipes);
        free(*pids);
        return -1;
    }

    int forked = fork_children(ms, *pipes, *pids, cmd_count);
    if (forked < cmd_count)
    {
        cleanup_on_fork_failure(ms, *pids, forked, *pipes, cmd_count - 1);
        free(*pipes);
        free(*pids);
        return -1;
    }
    return 0;
}

// Función principal orquestadora
void execute_piped_commands(t_minishell *ms, int cmd_count)
{
    if (cmd_count < 2) // no pipe
        return;
    int (*pipes)[2]; // array of int[2] 

    pipes = NULL;
    pid_t *pids = NULL;
    if (setup_and_fork(ms, cmd_count, &pipes, &pids) < 0) //todo
    {
        ms->exit_code = EXIT_FAILURE;
        return;
    }
    handle_parent_process(ms, pipes, pids, cmd_count);//todo
    free(pipes);
    free(pids);
}
