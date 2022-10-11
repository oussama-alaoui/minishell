/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:30:03 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/11 02:12:15 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	int		i;
	int		j;
	char	*key;

	i = key_len(str);
	key = ft_calloc(sizeof(char) * i + 1);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
			key[j++] = str[i++];
	}
	key[j] = '\0';
	return (key);
}

int	valid_key(char *str, int type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')
			|| (str[i] >= '0' && str[i] <= '9' && i > 0))
			i++;
		else if (str[i] == '+' && str[i + 1] == '\0')
			return (2);
		else
		{	
			if (type)
				ft_putstr_fd(2, "minishell: export: ");
			else
				ft_putstr_fd(2, "minishell: unset: ");
			ft_putstr_fd(2, ft_strdup(str));
			ft_putstr_fd(2, ": not a valid identifier\n");
			return (0);
		}
	}
	return (1);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = key_len(str);
	j = ft_strlen(str) - i;
	if (j == 0)
		return (NULL);
	else
	{
		value = ft_calloc(sizeof(char) * j + 1);
		j = 0;
		while (str[++i] != '\0' )
		{
			if (str[i] == '\'' || str[i] == '"')
				continue ;
			if (str[i] == ' ' && str[i + 1] == ' ')
				continue ;
			else
				value[j++] = str[i];
		}
		value[j] = '\0';
		return (value);
	}
}

int	init_env(char **var)
{
	int		i;
	char	*key;
	char	*val;

	i = -1;
	while (var[++i])
	{
		key = get_key(var[i]);
		if (valid_key(key, 1))
		{
			val = get_value(var[i]);
			if (create_list_env(key, val, check_plus_arg(key)) == 0)
				return (0);
			free(key);
			free(val);
		}
		else
			free(key);
	}
	return (1);
}

void	ft_export(char **var)
{
	create_list_env("?", "0", 0);
	if (!var || !var[0])
		ft_env(0);
	init_env(var);
}
