#include "../builtins.h"

void print_env()
{
    t_list_env *tmp;

    tmp = g_info.env_lst;
    while (tmp)
    {
        if (tmp->status == 1)
            if(tmp->value != NULL)
                printf("%s=\"%s\"\n",tmp->key, tmp->value);
        tmp = tmp->next;
    }
    
}

void print_export_env()
{
    t_list_env *tmp;

    tmp = g_info.env_lst;
    while (tmp)
    {
        if (tmp->status == 1)
        {
            if(tmp->value != NULL)
                printf("declare -x %s=\"%s\"\n",tmp->key, tmp->value);
            else
                printf("declare -x %s\n",tmp->key);
        }
        tmp = tmp->next;
    }
}

void ft_env (int type)
{
    if (type == 1)
        return (print_env());
    else
        return (print_export_env());
}
