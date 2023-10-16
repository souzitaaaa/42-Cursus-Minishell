/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/16 16:23:46 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    insert_var_exp(t_main *main, char *str)
{
    t_var   *aux;
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	ft_strccpy(temp, str, '=');
	if (!ft_isnbr(temp))
	{
    	aux = var_node(str);
		add_var(&main->export_list, aux, -1);
	}
}

void    insert_var_env(t_main *main, char *str)
{
    t_var   *aux;
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	ft_strccpy(temp, str, '=');
	if (!ft_isnbr(temp))
	{
    	aux = var_node(str);
		add_var(&main->env_list, aux, -1);
	}
}

void	put_head_var(t_env *env, t_var *new)
{
	env->head = new;
	new->next = env->head;
	new->prev = env->head;
}

bool	modify_var(t_env *list, char *str)
{
    t_var   *current;
    int     count;
	char	*temp;

	count = 0;
    current = list->head;
    while (count++ < list->size)
    {
        if (ft_strncmp(str, current->var, ft_strclen(str, '=')) == 0)
        {
			temp = ft_strdup(str);
    		free(current->var);
    		current->var = temp;
    		return (true);
		}
        current = current->next;
    }
    return (false);
}

void	copy_exp(t_main *main)
{
	t_var	*aux;
	t_var	*new;

	main->export_list.i = 0;
	aux = main->env_list.head;
	while (main->export_list.i < main->env_list.size)
	{
		new = var_node(aux->var);
		add_var(&main->export_list, new, -1);
		main->export_list.i++;
		aux = aux->next;
	}
	if (main->prev == NULL)
	{
		new = var_node("OLDPWD");
		add_var(&main->export_list, new, -1);
	}
}
