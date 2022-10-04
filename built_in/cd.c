/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalaoui- <oalaoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:10:38 by oalaoui-          #+#    #+#             */
/*   Updated: 2022/10/04 21:43:04 by oalaoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(char *key)
{
    t_list_env *tmp;

    tmp = g_info.env_lst;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

int ft_chdir(char *path)
{
    char *pwd;
    char *oldpwd;

    oldpwd = getcwd(NULL, 0);
    if (chdir(path) == -1)
    {
        printf("cd: %s: No such file or directory\n", path);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (oldpwd)
    {
        create_list_env("OLDPWD", oldpwd, 1);
        free(oldpwd);
    }
    create_list_env("PWD", pwd, 1);
    free(pwd);
    return (0);
}

void ft_cd(char *path)
{
    create_list_env("?", "0", 1);
    if (path == NULL)
    {
        if (ft_chdir(getenv("HOME")) == -1)
            printf("cd: HOME not set\n");
    }
    else if (ft_strcmp(path, "-") == 0)
    {
        if (ft_chdir(getenv("OLDPWD")) == -1)
            printf("cd: OLDPWD not set\n");
        else
            printf("%s\n", getenv("OLDPWD"));
    }
    else
        if (ft_chdir(path) == -1)
            perror("Minishell : ");
}
