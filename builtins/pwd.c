/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:04:04 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/10 22:13:55 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

char	*get_current_dir(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	return (strdup(buf));
}

void	ft_pwd(void)
{
	char		*pwd;
	t_list_env	*tmp;

	tmp = g_var.env_lst;
	pwd = get_current_dir();
	if (pwd)
	{
		ft_putstr_fd(1, pwd);
		ft_putstr_fd(1, "\n");
		free(pwd);
	}
	else
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
			{
				ft_putstr_fd(1, tmp->value);
				ft_putstr_fd(1, "\n");
				break ;
			}
			tmp = tmp->next;
		}
	}
}
