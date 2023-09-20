/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/20 20:22:18 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isnbr(const char *str)
{
	if (ft_strlen(str) > 11)
		return(0);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return(0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return(0);
		str++;
	}
	return(1);
}
void    insert_var(t_main *main, char *str, bool exp)
{
    t_var   *aux;
	char	*temp;
	
	temp = ft_calloc(sizeof(char), ft_strclen(str, '=') + 1);
	ft_strccpy(temp, str, '=');
	if (!ft_isnbr(temp))
	{
    	aux = var_node(str);
		if (exp)
			add_var(&main->export_list, aux, -1);
		else
		{
			add_var(&main->export_list, aux, -1);
			add_var(&main->env_list, aux, -1);
		}
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
	
	if(index == env->size)
	{
		add_var(env, node, -1);
		//print_var(*env);
		return ;
	}
    current = env->head;
    env->i = 0;
    if (env->head == NULL)
	{
        put_head_var(env, node);
		env->size++;
	}
    else
    {
        while (env->i++ < index)
        {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
    	env->size++;
        if (index == 0)
            env->head = node;
        shift_index_env(env);
    }
	//print_var(*env);
}
bool    modify_var(t_main *main, char *str, bool exp)
{
    t_var   *current;
    t_var   *aux;
    int     count;
	int		index;

	count = 0;
    current = main->env_list.head;
    while (count++ < main->env_list.size)
    {
        if (ft_strncmp(str, current->var, ft_strclen(str, '=')) == 0)
        {
			if(!exp)
			{
				index = current->index;
				remove_var(&main->export_list, current->index);
            	remove_var(&main->env_list, current->index);	
				aux = var_node(str);
				add_index_var(&main->export_list, aux, index);
            	add_index_var(&main->env_list, aux, index);
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
