/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:48:04 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/20 20:23:52 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	shift_index_env(t_env *stack)
{
	t_var	*element;
	int	counter;

	counter = 0;
	printf("size: %d\n", stack->size);
	stack->head->index = 0;
	printf("head: %s\n", stack->head->var);
	element = stack->head->next;
	printf("element: %s\n", element->var);
	while (counter++ < stack->size - 1)
	{
		printf("element in loop: %s\n", element->var);
		//ft_printf("encontramos o loop??\n");
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

void    remove_var(t_env *env, int index)
{
	t_var   *current;
    t_var	*rem;
	
    current = env->head;
    env->i = 0;
    if (env->size == 1)
	{
		env->head = NULL;
		env->size--;
	}
    else
    {
		ft_printf("index: %d\n", index);
        while (env->i++ < index - 1)
        {
			ft_printf("ENCONTRAMOS O LOOP\n");
            current = current->next;
        }
		/*if(current->next)
		{
			rem = current->next;
			current->next = rem->next;
			if (current->next)
				current->next->prev = current;
				
		}*/
		//ft_printf("current: %s\n", current->var);
		//ft_printf("current prev: %s\n", current->prev->var);
		//ft_printf("current next: %s\n", current->next->var);
        current->next->prev = current->prev;
        current->prev->next = current->next;
    	env->size--;
        if (index == 0)
            env->head = current->next;
        shift_index_env(env);
		ft_printf("sai do shift_index\n");
    }
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

int	unset_env(t_main *main, char *str)
{
	int		count = 0;
	int		index;
	t_var	*aux = main->env_list.head;
	
	while (count++ < main->env_list.size)
	{
		//ft_printf("loop env\n");
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			index = aux->index;
			ft_printf("index unset_var: %d\n", aux->index);
			remove_var(&main->env_list, aux->index);
			ft_printf("loop env 1\n");
			//aux = find_var(main->env_list, index);
			return(index);
		}
		aux = aux->next;
	}
	ft_printf("loop 2\n");
	index = main->env_list.size;
	return (index);
}

void	unset_exp(t_main *main, char *str)
{
	int		count = 0;
	int		index;
	t_var	*aux = main->export_list.head;

	while (count++ < main->export_list.size)
	{
		ft_printf("loop\n");
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			index = aux->index;
			remove_var(&main->export_list, aux->index);
			//aux = find_var(main->export_list, index);
			return ;
		}
		aux = aux->next;
	}
}

void	unset(t_main *main, char *str, bool child)
{
	unset_env(main, str);
	unset_exp(main, str);
	if (child)
        exit(0);
    set_exit_code(main, 0);
}

