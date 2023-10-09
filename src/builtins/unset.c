/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/04 14:57:41 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	unset_env(t_main *main, char *str)
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
			return(index);
		}
		aux = aux->next;
	}
	index = main->env_list.size;
	return (index);
}

void	unset_exp(t_main *main, char *str)
{
	int		count = 0;
	t_var	*aux = main->export_list.head;

	while (count++ < main->export_list.size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			remove_var(&main->export_list, aux->index);
			return ;
		}
		aux = aux->next;
	}
}

void	unset(t_main *main, char **array, bool child)
{
	int		i;
	int exit_code;
    int error;

	i = 1;
	exit_code = 0;
	while (array[i]  != NULL)
	{
		error = validations_ch(array[i], STDERR_FILENO, array[0]);
        if(error)
        {
			exit_code = error;
			i++;
			continue ;
		}
		unset_env(main, array[i]);
		unset_exp(main, array[i]);
		i++;
	}
	if (child)
        exit(exit_code);
    set_exit_code(main, exit_code);
}

