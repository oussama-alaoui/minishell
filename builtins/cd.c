/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:10:38 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/06 19:01:23 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(char *key)
{
	t_list_env *tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int ft_chdir(char *path)
{
	char *pwd;
	char *oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL && path[0] == '.' && path[1] == '\0')
		return (perror("cd: error retrieving current directory: getcwd: cannot access parent directories"), 1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd(2, "Minishell: cd: ");
		ft_putstr_fd(2, path);
		perror("\1");
		return (1);
	}
	else
	{
		create_list_env("OLDPWD", oldpwd, 1);
		free(oldpwd);
	}
	pwd = getcwd(NULL, 0);
	create_list_env("PWD", pwd, 1);
	free(pwd);
	return (0);
}

void ft_cd(char *path)
{
	create_list_env("?", "0", 1);
	if (path == NULL)
	{
		if (ft_chdir(get_env_value("HOME")) == -1) 
			ft_putstr_fd(2, "cd: HOME not set\n");
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		if (get_env_value("OLDPWD") == NULL || ft_chdir(get_env_value("OLDPWD")) == -1)
			ft_putstr_fd(2, "cd: OLDPWD not set\n");
		else
		{
			ft_putstr_fd(1, getcwd(NULL, 0));
			ft_putstr_fd(1, "\n");
		}
	}
	else
		if (ft_chdir(path) == -1)
			perror("Minishell : ");
}
