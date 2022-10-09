#include "../minishell.h"

void	printf_error(char *cmd, char *message, char *status)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	create_list("?", status);
}

void	change_status(int status)
{
	char	*err;

	err = ft_itoa(status);
	create_list("?", err);
	free(err);
}

void	cmd_not_found(int fd[], t_list *lst, char **env)
{
	close(fd[1]);
	g_info.sig = 1;
	if (lst->next)
		exec_cmd_pipe(fd[0], lst->next, env);
}

int	if_no_cmd(t_list *head, char **env, t_var	var)
{
	if (head->cmd == NULL || head->cmd[0] == '\0')
	{
		close(head->in_fd);
		close(head->out_fd);
		if (head->next)
		{
			pipe(var.fd);
			close(var.fd[1]);
			exec_cmd_pipe(var.fd[0], head->next, env);
			close(var.fd[1]);
		}
		return (1);
	}
	return (0);
}