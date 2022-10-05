/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:04:04 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/05 19:43:04 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char		*pwd;
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(1, pwd);
		ft_putstr_fd(1, "\n");
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
