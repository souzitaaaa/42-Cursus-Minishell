/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:49:31 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/10 16:01:15 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var *var_node(const char *var)
{
    t_var *new_node;
    
    new_node = (t_var *)malloc(sizeof(t_var));
    if (new_node == NULL) 
    {
        //ft_error();
        exit(0);
    }
    new_node->var = strdup(var);
    return (new_node);
}

void	put_head_node(t_env *env, t_var *var_new)
{
	env->head = var_new;
	var_new->next = env->head;
	var_new->prev = env->head;
}

void	add_var(t_env *env, t_var *var_new)
{
	static int	index = 0;

	if (env->head == NULL)
	{
		index = 0;
		put_head_node(env, var_new);
	}
	else
	{
		env->head->prev->next = var_new;
		var_new->prev = env->head->prev;
		var_new->next = env->head;
		env->head->prev = var_new;
	}
	var_new->index = index;
	env->size++;
}

void    list_var(t_env  *env, t_var *var)
{
    int     count;
    t_var   *aux;

    aux = (t_var *)malloc(sizeof(t_var));
    var = env->head;
    count = 0;
    while (count++ <= env->size)
    {
        aux = var_node(var);
        add_var(env, aux);
        var = var->next;
    }
}

void    print_var(t_env *env)
{
    t_var   *current;

    current = env->head;
    while (current != NULL)
    {
        printf("%s\n", current->var);
        current = current->next;
    }
}