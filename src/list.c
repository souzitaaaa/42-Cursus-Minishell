/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/17 21:12:46 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shift_index(t_lexer *stack)
{
	t_node	*element;

	stack->head->index = 0;
	element = stack->head->next;
	while (element != stack->head)
	{
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

void	put_head_node(t_lexer *stack, t_node *new)
{
	stack->head = new;
	new->next = stack->head;
	new->prev = stack->head;
}

t_node	*remove_head(t_lexer *stack)
{
	t_node	*temp;

	temp = stack->head;
	if (stack->size == 1)
		stack->head = NULL;
	else
	{
		stack->head->next->prev = stack->head->prev;
		stack->head->prev->next = stack->head->next;
		stack->head = stack->head->next;
		shift_index(stack);
	}
	stack->size--;
	return (temp);
}

void	insert_head(t_lexer *stack, t_node *new)
{
	if (stack->head == NULL)
		put_head_node(stack, new);
	else
	{
		new->next = stack->head;
		new->prev = stack->head->prev;
		stack->head->prev->next = new;
		stack->head->prev = new;
		stack->head = new;
	}
	shift_index(stack);
	stack->size++;
}

void	insert_last(t_lexer *stack, t_node *new)
{
	static int	index = 0;

	if (stack->head == NULL)
	{
		index = 0;
		put_head_node(stack, new);
	}
	else
	{
		index++;
		stack->head->prev->next = new;
		new->prev = stack->head->prev;
		new->next = stack->head;
		stack->head->prev = new;
	}
	new->index = index;
	stack->size++;
}
