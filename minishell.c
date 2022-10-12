/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:11:56 by oakoudad          #+#    #+#             */
/*   Updated: 2022/10/11 23:05:36 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	int	tmp;

	if (sig == 2 && g_var.sig)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	tmp = g_var.sig;
	if (g_var.heredoc == 1)
		g_var.sig = 1;
	if (sig == 2 && g_var.heredoc == 1 && tmp == 0)
	{
		write(1, "\n", 1);
		close(g_var.heredoc_fd);
		g_var.heredoc_fd = open(g_var.heredoc_file,
				O_RDONLY | O_WRONLY | O_TRUNC);
		close(g_var.heredoc_fd);
		exit(1);
	}
}

void	config(char **e)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;

	i = -1;
	g_var.env_lst = NULL;
	g_var.sig = 1;
	while (e[++i])
	{
		if (var_cmp("SHLVL", e[i]))
		{
			shlvl = ft_atoi(&e[i][6]) + 1;
			if (shlvl < 0)
				shlvl = 0;
			new_shlvl = ft_itoa(shlvl);
			e[i] = ft_strjoin(ft_strdup("SHLVL="), new_shlvl);
			free(new_shlvl);
		}
	}
	if (!search_var("SHLVL", e))
		create_list_env("SHLVL", "1", 1);
	if (!search_var("PATH", e))
		create_list_env("PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1);
}

void	my_void(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **env)
{
	char		*txt;

	my_void(ac, av);
	config(env);
	if (init_env(env) == 0)
		return (0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		rl_catch_signals = 0;
		txt = readline("Minishell$ ");
		if (txt == NULL)
			return (ft_putstr_fd(1, "exit\n"), 0);
		if (txt[0] == EOF)
		{
			free(txt);
			continue ;
		}
		add_history(txt);
		if (check_syntax(txt) == -1)
			return (0);
		free(txt);
		txt = NULL;
	}
}
