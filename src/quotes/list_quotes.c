/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-da <jcruz-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/20 16:26:14 by jcruz-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	shift_index_quotes(t_quotes *stack)
{
	t_node_quotes	*element;

	stack->head->index = 0;
	element = stack->head->next;
	while (element != stack->head)
	{
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

void	put_head_node_quotes(t_quotes *stack, t_node_quotes *new)
{
	stack->head = new;
	new->next = stack->head;
	new->prev = stack->head;
}

t_node_quotes	*remove_head_quotes(t_quotes *stack)
{
	t_node_quotes	*temp;

	temp = stack->head;
	if (stack->size == 1)
		stack->head = NULL;
	else
	{
		stack->head->next->prev = stack->head->prev;
		stack->head->prev->next = stack->head->next;
		stack->head = stack->head->next;
		shift_index_quotes(stack);
	}
	stack->size--;
	return (temp);
}

void	insert_head_quotes(t_quotes *stack, t_node_quotes *new)
{
	if (stack->head == NULL)
		put_head_node_quotes(stack, new);
	else
	{
		new->next = stack->head;
		new->prev = stack->head->prev;
		stack->head->prev->next = new;
		stack->head->prev = new;
		stack->head = new;
	}
	shift_index_quotes(stack);
	stack->size++;
}

void	insert_last_quotes(t_quotes *stack, t_node_quotes *new)
{
	if (stack->head == NULL)
		put_head_node_quotes(stack, new);
	else
	{
		stack->head->prev->next = new;
		new->prev = stack->head->prev;
		new->next = stack->head;
		stack->head->prev = new;
	}
	stack->size++;
}
