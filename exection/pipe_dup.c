/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:37 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/12 00:12:34 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closefd(int a, int b, int c, int d)
{
	if (a > -1)
		close(a);
	if (b > -1)
		close(b);
	if (c > -1)
		close(b);
	if (d > -1)
		close(d);
}

void	saveio(int fd[], int io_fd[])
{
	fd[0] = -1;
	fd[1] = -1;
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
}

void	restoreio(int io_fd[])
{
	dup2(io_fd[0], 0);
	dup2(io_fd[1], 1);
	close(io_fd[0]);
	close(io_fd[1]);
}

void	dup_fd(int intfd, int fd[], t_list *lst)
{
	if (intfd != -1)
	{
		dup2(intfd, 0);
		close(intfd);
	}
	if (lst->in_fd > 0)
	{
		dup2(lst->in_fd, 0);
		close(lst->in_fd);
	}
	if (lst->out_fd >= 0)
	{
		dup2(lst->out_fd, 1);
		close(lst->out_fd);
	}
	else if (lst->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

void	exec_cmd_pipe(int intfd, t_list *lst, char **env)
{
	t_execvar	var;

	var.env = env;
	var.pid = 0;
	if (if_no_cmd(lst, var, env))
		return ;
	saveio(var.fd, var.io_fd);
	if (lst->next)
		pipe(var.fd);
	if (!check_builtin(lst))
		var.cmd = get_cmd_from_path(lst->cmd);
	if (!check_builtin(lst) && var.cmd == NULL)
		return (cmd_not_found(var.fd, lst, env));
	exec_cmd(lst, var, intfd);
	if (!check_builtin(lst))
		free(var.cmd);
	close(var.io_fd[0]);
	closefd(var.fd[1], var.io_fd[1], var.io_fd[0], intfd);
	if (!lst->next && wait_and_error(var.fd[0], lst))
		return ;
	exec_cmd_pipe(var.fd[0], lst->next, env);
}
