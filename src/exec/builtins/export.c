/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:47:44 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/06 20:18:15 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void swap_var(t_var *var1, t_var *var2)
{
	char	*temp;

	temp = ft_strdup(var1->var);
    free(var1->var);
    var1->var = ft_strdup(var2->var);
    free(var2->var);
    var2->var = temp;
}

void sort_ascii(t_main *main)
{
    int count = 0;
    t_var *current;

    current = main->env_list.head;
    while (count < main->env_list.size - 1)
    {
        if (ft_strcmp(current->var, current->next->var) > 0)
        {
            swap_var(current, current->next);
            count = 0;
            current = main->env_list.head;
        }
        else
        {
            count++;
            current = current->next;
        }
    }
}

void ft_export(t_env *env)
{
    t_var *current;
    t_main  aux;
    char *temp;
    
    aux.env_list = *env;
    current = env->head;
    env->i = 0;
    sort_ascii(&aux);
    while (env->i++ < env->size)
    {
        temp = ft_calloc(sizeof(char),ft_strclen(current->var, '=') + 2);
        ft_strlcpy(temp, current->var, ft_strclen(current->var, '=') + 2);
        ft_printf("declare -x %s", temp);
        free(temp);
        temp = ft_calloc(sizeof(char), ft_strlen(current->var) - ft_strclen(current->var, '=') + 1);
        ft_strlcpy(temp, current->var + ft_strclen(current->var, '=') + 1, ft_strlen(current->var) + 1);
        ft_printf("\"%s\"\n", temp);
        free(temp);
        current = current->next;
    }
}

void export(t_main *main, char **array, bool child)
{
    main->env_list.i = 1;
    if (array[1] == 0)
        ft_export(&main->env_list);
    else
    {
        while(array[main->env_list.i])
        {
            if (array[main->env_list.i][0] == '=') //fazer uma funcao que dá erro em: - + * = % ? / | \ ()
			{
				error_export(array, STDERR_FILENO);
                 if (child)
                    exit(2);
                set_exit_code(main, 2);
			}
			else
            {
                if (!ft_strchr(array[main->env_list.i], '='))
                {
					main->env_list.i++;
                    continue ;
                }
            if (modify_var(main, array[main->env_list.i]) == false)
               insert_var(main, array[main->env_list.i]);
            }
            main->env_list.i++;
        }
    }
    if (child)
        exit(0);
    set_exit_code(main, 0);
}
