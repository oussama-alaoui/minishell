/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:26:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/05 23:23:35 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t size)
{
	void		*p;

	p = malloc(size);
	if (!p)
	{
		printf("no space lift\n");
		exit(30);
		return (0);
	}
	return (p);
}
