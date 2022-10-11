/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:46 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/09 21:47:03 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_list *lst, t_var var, int intfd)
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
}

void	free_tableau_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
