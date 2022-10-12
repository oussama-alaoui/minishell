/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:11:12 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/04 21:07:06 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(void)
{
	char	*home;
	char	*tmp;

	home = get_env_value("HOME");
	if (home == NULL || *home == 0)
		return ("");
	tmp = ft_strdup(home);
	return (tmp);
}
