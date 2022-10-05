/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:06:07 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/05 19:23:04 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int skip_arg(char *str)
{
	int	y;
	int	status;

	y = 0;
	status = 0;
	if (str[0] == '-')
	{
		while (str[++y])
		{
			if (str[y] != 'n')
				return (status = 0, status);
			else
				status = 1;
		}
	}
	return (status);
}

void	ft_echo(char **var)
{
	int	y;
	int	status;

	y = -1;
	status = 0;
    if (var && var[0])
    {
		while (skip_arg(var[++y]))
			status = skip_arg(var[y]);
        while (var[y])
        {
            ft_putstr_fd(2, var[y]);
            if (var[y + 1] != NULL)
				ft_putstr_fd(1, " ");
			y++;
        }
		if (status == 0)
			ft_putstr_fd(1, "\n");
    }
    else
        ft_putstr_fd(1, "\n");
}
