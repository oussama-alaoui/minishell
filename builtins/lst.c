/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:42:51 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/11 02:12:12 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_list_env(char *key, char *value, int status)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value == NULL)
				return (1);
			if (status == 2)
				return (tmp->value = ft_strjoin(tmp->value, value), 1);
			free(tmp->value);
			return (tmp->value = ft_strdup(value), 1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstenv_(key, value);
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

int	key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		if (str[i] != '\'' || str[i] != '"')
			i++;
	return (i);
}

int	check_plus_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '\0')
			return (str[i] = '\0', 2);
		i++;
	}
	return (0);
}
