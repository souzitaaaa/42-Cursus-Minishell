/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/07 16:18:43 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    insert_var(t_main *main, char *str, bool exp)
{
    t_var   *aux;

    aux = var_node(str);
	if (exp)
    	add_var(&main->export_list, aux);
	else
	{
		add_var(&main->export_list, aux);
		add_var(&main->env_list, aux);
	}
}
void	put_head_var(t_env *env, t_var *new)
{
	env->head = new;
	new->next = env->head;
	new->prev = env->head;
}

void    add_index_var(t_env *env, t_var *node, int index)
{
    t_var   *current;

    current = env->head;
    env->i = 0;
    if (env->head == NULL)
        put_head_var(env, node);
    else
    {
        while (env->i++ < index)
        {
            current = current->next;
        }
        node->next = current;
        node->prev = current->next;
        current->prev->next = node;
        current->prev = node;
        if (index == 0)
            env->head = node;
        shift_index_env(env);
    }
    env->size--;
}

bool    modify_var(t_main *main, char *str, bool exp)
{
    t_var   *current;
    t_var   *aux;
    int     count = 0;

    current = main->env_list.head;
    while (count++ < main->env_list.size)
    {
        if (ft_strncmp(str, current->var, ft_strclen(str, '=')) == 0)
        {
			if (exp)
				remove_var(&main->export_list, current->index);
			else
			{
				remove_var(&main->export_list, current->index);
            	remove_var(&main->env_list, current->index);
			}
			aux = var_node(str);
			if (exp)
				add_index_var(&main->export_list, aux, current->index);
			else
			{
				add_index_var(&main->export_list, aux, current->index);
            	add_index_var(&main->env_list, aux, current->index);
			}
            return (true);
        }
        current = current->next;
    }
    return (false);
}

void	copy_exp(t_main *main)
{
    t_var  *aux;
	t_var	*new;
	
	main->export_list.i = 0;
	aux = main->env_list.head;
    while (main->export_list.i < main->env_list.size)
    {
		new = var_node(aux->var);
        add_var(&main->export_list, new);
        main->export_list.i++;
		aux = aux->next;
    }
	if (main->prev == NULL)
	{
		new = var_node("OLDPWD");
		add_var(&main->export_list, new);
	}
}
