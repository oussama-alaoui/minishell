/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:56 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/11 00:21:20 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_error(char *cmd, char *message, char *status)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	create_list_env("?", status, 0);
}

void	change_status(int status)
{
	char	*err;

	err = ft_itoa(status);
	create_list_env("?", err, 0);
	free(err);
}

void	cmd_not_found(int fd[], t_list *lst, char **env)
{
	(void)lst;
	close(fd[1]);
	g_info.sig = 1;
	if (lst->next)
		exec_cmd_pipe(fd[0], lst->next, env);
}

int	if_no_cmd(t_list *head, t_var var, char **env)
{
	if (head->cmd == NULL || head->cmd[0] == '\0')
	{
		close(head->in_fd);
		close(head->out_fd);
		if (head->next)
		{
			pipe(var.fd);
			close(var.fd[1]);
			exec_cmd_pipe(var.fd[0], head->next, env);
			close(var.fd[1]);
		}
		return (1);
	}
	return (0);
}

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
