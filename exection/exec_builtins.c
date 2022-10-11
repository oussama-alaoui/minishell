/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:44:43 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/09 21:44:44 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtins(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		ft_echo(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		ft_export(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "env") == 0)
		ft_env(1);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
	{
		if (lst->args && lst->args[0] && lst->args[1])
			ft_cd(lst->args[1]);
		else
			ft_cd(NULL);
	}
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		ft_unset(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		ft_exit(lst->args + 1);
}
