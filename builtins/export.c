/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:30:03 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/05 19:33:27 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int key_len(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0' && str[i] != '=')
		if (str[i] != '\'' || str[i] != '"')
			i++;
	return (i);
}

char *get_key(char *str, int status)
{
	int     i;
	int     j;
	char    *key;

	i = key_len(str);
	key = ft_calloc(sizeof(char) * i);
	i = 0;
	j = 0;
	while(str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
			key[j++] = str[i++];
	}
	if (key[j - 1] == '+' && status > 0)
		key[j - 1] = '\0';
	else
		key[j] = '\0';
	return (key);
}

int valid_key(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_')
			|| (str[i] >= '0' && str[i] <= '9' && i > 0))
			i++;
		else if (str[i] == '+' && str[i + 1] == '\0')
			return (2);
		else
		{
			ft_putstr_fd(2, "minishell: export: ");
			ft_putstr_fd(2, str);
			ft_putstr_fd(2, ": not a valid identifier\n");
			return (0);
		}
	}
	return 1;
}

char *get_value(char *str)
{
	int     i;
	int     j;
	char    *value;

	i = key_len(str);
	j = ft_strlen(str) - i;
	if (j == 0)
		return (NULL);
	else
	{
		value = ft_calloc(sizeof(char) * j);
		j = 0;
		while(str[++i] != '\0' )
		{
			if (str[i] == '\'' || str[i] == '"')
				continue;
			else
				value[j++] = str[i];
		}
		value[j] = '\0';
		return (value);
	}
}

int init_env(char **var)
{
	int i;
	char *key;
	char *val;

	i = -1;        
	while (var[++i])
	{
		if (valid_key(get_key(var[i], 0)))
		{
			key = get_key(var[i], 1);
			val = get_value(var[i]);
			if (create_list_env(key, val, valid_key(get_key(var[i], 0))) == 0)
				return (0);
		}
	}
	return (1);
}

void ft_export(char **var)
{
	create_list_env("?", "0", 0);
	if (!var || !var[0])
		ft_env(0);
	init_env(var);
}

