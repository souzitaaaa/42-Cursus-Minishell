/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_end_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:33:53 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/28 10:33:53 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shift_index_endnull(t_lexer *stack)
{
	t_node	*element;

	stack->head->index = 0;
	element = stack->head->next;
	while (element != NULL)
	{
		element->index = element->prev->index + 1;
		element = element->next;
	}
}

void	put_head_node_endnull(t_lexer *stack, t_node *new)
{
	stack->head = new;
	new->next = NULL;
	new->prev = NULL;
}

void	insert_head_endnull(t_lexer *stack, t_node *new)
{
	if (stack->head == NULL)
		put_head_node_endnull(stack, new);
	else
	{
		new->next = stack->head;
		new->prev = NULL;
		//stack->head->prev->next = new;
		stack->head->prev = new;
		stack->head = new;
	}
	stack->size++;
}

void	insert_last_endnull(t_lexer *stack, t_node *new, int index)
{
	t_node *aux;

	aux = stack->head;
	if (stack->head == NULL)
		put_head_node_endnull(stack, new);
	else
	{
		new->next = NULL;
		while(aux->next)
			aux = aux->next;
		//stack->head->prev->next = new;
		aux->next = new;
		new->prev = aux;
	}
	if(index == -1)
		new->index = stack->size;
	else
		new->index = index;
	stack->size++;
}

void    print_list_endnull(t_node *head)
{
	t_node  *aux = head;

				printf("\033[1;32m\t\t(Printing tokens)\033[0m\n");
    while(aux != NULL)
	{
		printf("\033[1;34m[INDEX] \033[0m %i\n", aux->index);
		printf("\033[1;34m[TYPE]  \033[0m %c\n", aux->token.type);
		printf("\033[1;34m[ARR] \033[0m \n");
		print_arr(aux->token.arr);
		printf("\033[1;34m[QUOTES HEREDOC]  \033[0m %i\n\n", aux->token.quotes);
		aux = aux->next;
        //if(aux == head)
          //  break ;
	}
			printf("\033[1;32m\t\t(End printing tokens)\033[0m\n");
}
