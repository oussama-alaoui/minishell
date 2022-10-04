#include "../builtins.h"


void	*ft_calloc(size_t size)
{
	void		*p;

	p = malloc(size);
	if (!p)
	{
		exit(30);
		return (0);
	}
	return (p);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	if (len == 0)
	{
		str = ft_calloc(sizeof(char) * 1);
		str[0] = 0;
		return (str);
	}
	str = ft_calloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	// printf("s1: \n");
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;

	// printf("s2: %d of : %s\n", a[i] - b[i], s1);
	return (a[i] - b[i]);
}

void	ft_putstr_fd(int fd, char *s)
{
	if (fd == 2)
		create_list_env("?", "258", 0);
	write(fd, s, ft_strlen(s));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (*s1 == '\0')
		s1 = ft_strdup("");
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	// free(s1);
	return (str);
}

void	print_error(char *cmd, char *message, char *status)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	create_list_env("?", status, 1);
}