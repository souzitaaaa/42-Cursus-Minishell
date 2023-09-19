/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:10 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	shift_index_env(t_env *stack)
{
	t_var	*element;

	stack->head->index = 0;
	element = stack->head->next;
	while (element != stack->head)
	{
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

void    remove_var(t_env *env, int index)
{
	t_var   *current;
    
    current = env->head;
    env->i = 0;
    if (env->size == 1)
		env->head = NULL;
    else
    {
        while (env->i++ < index)
        {
            current = current->next;
        }
            current->next->prev = current->prev;
            current->prev->next = current->next;
            if (index == 0)
                env->head = current->next;
            shift_index_env(env);
    }
    env->size--;
    free(current);
}
t_var	*find_var(t_env env, int index)
{
	int	counter;
	t_var *aux;

	counter = 0;
	aux = env.head;
	while(counter++ < index)
		aux = aux->next;
	return (aux);
}

void	unset(t_main *main, char *str, bool child)
{
	int		count = 0;
	int		index;
	t_var	*aux = main->env_list.head;

	while (count++ < main->env_list.size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			index = aux->index;
			remove_var(&main->env_list, aux->index);
			aux = find_var(main->env_list, index);
		}
		aux = aux->next;
	}
	if (child)
        exit(0);
    set_exit_code(main, 0);
}
