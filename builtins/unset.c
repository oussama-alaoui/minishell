/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:00:13 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/09 21:51:26 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstremove(t_list_env *to_remove)
{
	t_list_env	*tmp;

	if (g_info.env_lst == to_remove)
	{
		g_info.env_lst = to_remove->next;
		free(to_remove->key);
		free(to_remove->value);
		free(to_remove);
		return ;
	}
	tmp = g_info.env_lst;
	while (tmp->next != to_remove)
		tmp = tmp->next;
	tmp->next = to_remove->next;
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}

void	ft_unset(char **args)
{
	int			i;
	t_list_env	*tmp;

	i = -1;
	while (args[++i])
	{
		if (!valid_key(args[i], 0))
			return ;
		tmp = g_info.env_lst;
		while (tmp)
		{
			if (ft_strcmp(args[i], tmp->key) == 0)
			{
				ft_lstremove(tmp);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
