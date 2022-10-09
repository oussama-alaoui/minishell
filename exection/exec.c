#include "../minishell.h"

int	wait_and_error(int fd, t_list	*head)
{
	int	z;
	int	status;

	z = 0;
	close(fd);
	while (z < g_info.count_pipes && g_info.count_pipes)
	{
		wait(&status);
		if (WIFEXITED(status) && z == 0)
		{
			g_info.errorstatus = WEXITSTATUS(status);
			if (head->error == 0)
				change_status(g_info.errorstatus);
		}
		if (WIFSIGNALED(status) && z == 0)
		{
			g_info.errorstatus = WTERMSIG(status) + 128;
			if (g_info.errorstatus == 131)
				write(2, "Quit: 3\n", 8);
			change_status(g_info.errorstatus);
		}
		z++;
	}
	g_info.sig = 1;
	return (1);
}

int		exec_cmd(t_list *lst, t_var var, int intfd)
{
	int	status;

	if (g_info.count_pipes > 1 || !check_builtin(lst))
		var.pid = fork();
	if (var.pid == -1)
		kill(wait(&status), 9);
	else if (var.pid == 0)
	{
		g_info.sig = 0;
		dup_fd(intfd, var.fd, lst);
		if (check_builtin(lst) == 0)
		{
			close(var.io_fd[0]);
			closefd(var.fd[0], var.io_fd[1], var.io_fd[0], -1);
			signal(SIGQUIT, exit);
			execve(var.cmd, lst->args, var.env);
		}
		else
		{
			exec_builtins(lst);
			restoreio(var.io_fd);
			if (g_info.count_pipes > 1)
				exit(0);
		}
	}
	return (1);
}

void	exec_cmd_pipe(int intfd, t_list *lst, char **env)
{
	t_var	var;

	var.env = NULL;
	if (ft_strcmp("cat", lst->cmd) != 0)
		var.env = env;
	var.pid = 0;
	if (lst == NULL || if_no_cmd(lst, env, var))
		return ;
	saveio(var.fd, var.io_fd);
	if (lst->next)
		pipe(var.fd);
	if (!check_builtin(lst))
		var.cmd = get_cmd_from_path(lst->cmd);
	if (!check_builtin(lst) && var.cmd == NULL)
		return (cmd_not_found(var.fd, lst, env));
	g_info.sig = 1;
	if (exec_cmd(lst, var, intfd) == 0)
		return ;
	if (!check_builtin(lst))
		free(var.cmd);
	close(var.io_fd[0]);
	closefd(var.fd[1], var.io_fd[1], var.io_fd[0], intfd);
	if (!lst->next && wait_and_error(var.fd[0], lst))
		return ;
	exec_cmd_pipe(var.fd[0], lst->next, env);
}

void	exec(t_list *lst)
{
	char	**env;
	int		i;

	env = prepare_env();
	exec_cmd_pipe(-1, lst, env);
	i = 0;
	if (env)
	{
		while (env[i])
		{
			myfree(env[i]);
			i++;
		}
		myfree(env);
	}
}
