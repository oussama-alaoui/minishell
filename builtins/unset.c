/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:00:13 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/07 17:30:04 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **args)
{
	int			i;
	t_list_env	*tmp;
	t_list_env	*prev;

	i = -1;
	while (args[++i])
	{
		if (!valid_key(args[i], 0))
			return ;
		tmp = g_info.env_lst;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, args[i]) == 0)
			{
				if (prev == NULL)
					g_info.env_lst = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
