/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:42:51 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/04 22:51:17 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ft_envadd_back_(tmp);
	return (1);
}

t_list_env	*ft_lstenv_(char *key, char *value)
{
	t_list_env	*list;

	list = ft_calloc(sizeof(t_list_env));
	if (!list)
		return (NULL);
	if (value)
		list->value = ft_strdup(value);
	else
		list->value = NULL;
	list->key = ft_strdup(key);
	list->next = NULL;
	return (list);
}

void	ft_envadd_back_(t_list_env *new)
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
