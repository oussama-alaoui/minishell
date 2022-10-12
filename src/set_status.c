/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:45:22 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/10 02:47:25 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_status(int type)
{
	char	**oldpwd;

	if (type == 1)
	{
		oldpwd = ft_calloc(sizeof(char *) * 2);
		oldpwd[0] = ft_strdup("OLDPWD");
		oldpwd[1] = NULL;
		ft_unset(oldpwd);
		free(oldpwd[0]);
		free(oldpwd);
	}
	create_list_env("?", "0", 0);
	return (type);
}
