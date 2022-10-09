/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:10:44 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/06 17:33:59 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env()
{
	t_list_env *tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (tmp->status == 1)
			if(tmp->value != NULL)
			{
				ft_putstr_fd(1, tmp->key);
				ft_putstr_fd(1, "=");
				ft_putstr_fd(1, tmp->value);
				ft_putstr_fd(1, "\n");
			}
		tmp = tmp->next;
	}
	
}

void print_export_env()
{
	t_list_env *tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (tmp->status == 1)
		{
			if(tmp->value != NULL)
			{
				ft_putstr_fd(1, "declare -x ");
				ft_putstr_fd(1, tmp->key);
				ft_putstr_fd(1, "=");
				ft_putstr_fd(1, tmp->value);
				ft_putstr_fd(1, "\n");
			}
			else
			{
				ft_putstr_fd(1, "declare -x ");
				ft_putstr_fd(1, tmp->key);
				ft_putstr_fd(1, "\n");
			}
		}
		tmp = tmp->next;
	}
}

void ft_env(int type)
{
	if (type == 1)
		return (print_env());
	else
		return (print_export_env());
}
