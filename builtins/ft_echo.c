#include "../builtins.h"

int skip_arg(char *str)
{
	int	y;
	int	status;

	y = 1;
	status = 0;
	if (str[0] == '-')
	{
		// exit(0);
		while (str[y])
		{
			if (str[y] != 'n')
			{
				status = 0;
				return (status);
			}
			else
				status = 1;
			y++;
		}
	}
	return (status);
}

void	ft_echo(char **var)
{
	int	y;
	int	status;

	y = 0;
	status = 0;
    if (var && var[0])
    {
        while (var[y])
			if (!skip_arg(var[y++]))
                break;
		status = skip_arg(var[y - 2]);
		y++;
        while (var[y])
        {
            printf("%s", var[y]);
            if (var[y + 1] != NULL)
				printf(" ");
            y++;
        }
		if (status == 0)
			printf("\n");
    }
    else
        printf("\n");
}
