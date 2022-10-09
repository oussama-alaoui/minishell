
#include "../minishell.h"

void	closefd(int a, int b, int c, int d)
{
	if (a > -1)
		close(a);
	if (b > -1)
		close(b);
	if (c > -1)
		close(b);
	if (d > -1)
		close(d);
}

void	saveio(int fd[], int io_fd[])
{
	fd[0] = -1;
	fd[1] = -1;
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
}

void	restoreio(int io_fd[])
{
	dup2(io_fd[0], 0);
	dup2(io_fd[1], 1);
	close(io_fd[0]);
	close(io_fd[1]);
}

void	dup_fd(int intfd, int fd[], t_list *lst)
{
	if (intfd != -1)
	{
		dup2(intfd, 0);
		close(intfd);
	}
	if (lst->in_fd > 0)
	{
		dup2(lst->in_fd, 0);
		close(lst->in_fd);
	}
	if (lst->out_fd >= 0)
	{
		dup2(lst->out_fd, 1);
		close(lst->out_fd);
	}
	else if (lst->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}
