/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:33:08 by eelmoham          #+#    #+#             */
/*   Updated: 2022/10/05 20:33:14 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_list *lst)
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

void	check_export_exec(t_list *lst)
{
	if (lst->next && lst->args + 1 == NULL)
		ft_export(lst->args + 1);
	else if (lst->next && lst->args + 1 != NULL)
		return ;
	else
		ft_export(lst->args + 1);
}

void	check_unset_exec(t_list *lst)
{
	if (lst->next && lst->args + 1 == NULL)
		ft_unset(lst->args + 1);
	else if (lst->next && lst->args + 1 != NULL)
		return ;
	else
		ft_unset(lst->args + 1);
}

void	check_exit_exec(t_list *lst)
{
	if (lst->next)
		return ;
	else
		built_in_exit(lst->args + 1);
}

void	exc_built_ins(t_list *lst)
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
		check_unset_exec(lst);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		check_exit_exec(lst);
}
