/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:46 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/11 20:27:43 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_execve(t_execvar var, t_list *lst)
{
	close(var.io_fd[0]);
	closefd(var.fd[0], var.io_fd[1], var.io_fd[0], -1);
	signal(SIGQUIT, exit);
	execve(var.cmd, lst->args, var.env);
}

void	exec_builtin(t_execvar var, t_list *lst)
{
	exec_builtins(lst);
	restoreio(var.io_fd);
	if (g_var.count_pipes > 1)
		exit(0);
}

void	exec_cmd(t_list *lst, t_execvar var, int intfd)
{
	int	status;

	g_var.sig = 0;
	if (g_var.count_pipes > 1 || !check_builtin(lst))
		var.pid = fork();
	if (var.pid == -1)
		kill(wait(&status), 9);
	else if (var.pid == 0)
	{
		dup_fd(intfd, var.fd, lst);
		if (check_builtin(lst) == 0)
			exec_execve(var, lst);
		else
			exec_builtin(var, lst);
	}
}

void	exec(t_list *lst)
{
	char	**env;
	int		i;

	env = prepare_env();
	exec_cmd_pipe(-1, lst, env);
	g_var.sig = 1;
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
