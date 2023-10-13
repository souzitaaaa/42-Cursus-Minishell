/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/13 18:20:30 by dinoguei         ###   ########.fr       */
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

void    print_quotes(t_quotes *quotes)
{
	int count = 0;
	t_node_quotes  *aux = quotes->head;

				printf("\033[1;36m\t\t(Printing quotes)\033[0m\n");
	while (count++ < quotes->size)
	{
		printf("\033[1;34m[INDEX] \033[0m %i\n", aux->index);
		printf("\033[1;34m[TYPE]  \033[0m %c\n", aux->type);
		printf("\033[1;34m[START]  \033[0m %i\n", aux->start);
		printf("\033[1;34m[END]  \033[0m %i\n\n", aux->end);
		aux = aux->next;
	}
			printf("\033[1;36m\t\t(End printing quotes)\033[0m\n");
}
