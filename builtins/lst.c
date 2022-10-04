/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:36:38 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/04 21:37:09 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_envadd_back(t_list_env *new)
{
	t_list_env	*t;

	t = g_info.env_lst;
	if (t == NULL)
	{
		g_info.env_lst = new;
		return ;
	}
	while (t->next)
		t = t->next;
	t->next = new;
}

int	create_list_env(char *name, char *value, int status)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			if (value == NULL)
				return (1);
			if (status == 2)
			{
				tmp->value  = ft_strjoin(tmp->value, value);
				return (1);
			}
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstenv(name, value);
	if (!tmp)
		return (0);
	if (tmp->key[0] == '?' && tmp->key[1] == '\0')
		tmp->status = 0;
	else
		tmp->status = 1;
	ft_envadd_back(tmp);
	return (1);
}

int	ft_lstsize(t_list_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}