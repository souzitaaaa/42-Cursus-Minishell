/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:15 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/17 21:12:56 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_lexer *stack)
{
	t_node	*element;
	t_node	*temp;
	int		counter;

	if (stack->head == NULL)
		return ;
	element = stack->head;
	counter = 0;
	while (counter++ < stack->size)
	{
		temp = element;
		element = element->next;
		free(temp);
	}
	stack->head = NULL;
	stack->size = 0;
}

void	free_env(t_env *stack)
{
	t_var	*element;
	t_var	*temp;
	int		counter;

	if (stack->head == NULL)
		return ;
	element = stack->head;
	counter = 0;
	while (counter++ < stack->size)
	{
		temp = element;
		element = element->next;
		free(temp);
	}
	stack->head = NULL;
	stack->size = 0;
}
