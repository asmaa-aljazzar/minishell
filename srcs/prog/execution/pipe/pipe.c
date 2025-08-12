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
    pid_t pid;

    for (int i = 0; i < cmd_count; i++)
    {
        pid = waitpid(pids[i], &status, 0);
        if (pid == pids[cmd_count - 1])
        {
            if (WIFEXITED(status))
                ms->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                ms->exit_code = 128 + WTERMSIG(status);
        }
    }
}

static void setup_pipes_and_redirection(int pipes[][2], int idx, int cmd_count)
{
    // Redirect stdin to previous pipe read end if not first command
    if (idx > 0 && dup2(pipes[idx - 1][0], STDIN_FILENO) < 0)
    {
        perror("dup2 stdin");
        exit(EXIT_FAILURE);
    }

    // Redirect stdout to next pipe write end if not last command
    if (idx < cmd_count - 1 && dup2(pipes[idx][1], STDOUT_FILENO) < 0)
    {
        perror("dup2 stdout");
        exit(EXIT_FAILURE);
    }

    close_all_pipes(pipes, cmd_count - 1);
}

static void execute_command_in_child(t_minishell *ms, t_command *cmd)
{
    if (is_command_empty(cmd))
        exit(0);

    if (main_redirection(ms) != 0)
        exit(EXIT_FAILURE);

    if (is_builtin(cmd))
    {
        compare_commands(ms);
        exit(ms->exit_code);
    }
    else
    {
        execute_external_command(ms);
        // execve should not return if successful
        exit(EXIT_FAILURE);
    }
}

static void run_child(t_minishell *ms, t_command *cmd, int pipes[][2], int idx, int cmd_count)
{
    setup_signals_child();

    setup_pipes_and_redirection(pipes, idx, cmd_count);

    ms->cmd = cmd;

    execute_command_in_child(ms, cmd);
}

// --- Create all pipes for N commands: N-1 pipes ---
static int create_all_pipes(int pipes[][2], int pipe_count)
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

// --- Fork each child process for each command ---
static int fork_children(t_minishell *ms, int pipes[][2], pid_t *pids, int cmd_count)
{
    t_command *cmd = ms->cmd;

    for (int i = 0; i < cmd_count && cmd; i++, cmd = cmd->next)
    {
        pids[i] = fork();
        if (pids[i] < 0)
            return i; // Return how many forks succeeded before failure
        if (pids[i] == 0)
            run_child(ms, cmd, pipes, i, cmd_count);
    }
    return cmd_count;
}

// --- Parent closes pipes and waits for children ---
static void handle_parent_process(t_minishell *ms, int pipes[][2], pid_t *pids, int cmd_count)
{
    close_all_pipes(pipes, cmd_count - 1);
    wait_for_children(ms, pids, cmd_count);
}

// --- Allocate pipes and pids arrays ---
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

// --- Cleanup on fork failure ---
static void cleanup_on_fork_failure(t_minishell *ms, pid_t *pids, int forked, int pipes[][2], int pipe_count)
{
    ms->exit_code = EXIT_FAILURE;
    kill_children(pids, forked);
    for (int j = 0; j < forked; j++)
        waitpid(pids[j], NULL, 0);
    close_all_pipes(pipes, pipe_count);
    free(pids);
    free(pipes);
}

// --- Setup pipes, fork children ---
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
        return -1;
    }
    return 0;
}

// --- Main function to execute piped commands ---
void execute_piped_commands(t_minishell *ms, int cmd_count)
{
    if (cmd_count < 2) // no pipe, nothing to do here
        return;

    int (*pipes)[2] = NULL;
    pid_t *pids = NULL;

    if (setup_and_fork(ms, cmd_count, &pipes, &pids) < 0)
    {
        ms->exit_code = EXIT_FAILURE;
        return;
    }

    handle_parent_process(ms, pipes, pids, cmd_count);

    free(pipes);
    free(pids);
}
