/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:01:44 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/10 02:37:06 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char *str)
{
	write(2, "minishell: export: `", 21);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	create_list_env("?", "1", 0);
	return (0);
}
