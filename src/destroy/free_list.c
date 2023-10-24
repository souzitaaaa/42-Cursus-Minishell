/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:10:51 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 15:15:50 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_quotes(t_quotes *stack)
{
	t_node_quotes	*element;
	t_node_quotes	*temp;
	int				counter;

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

void	free_lexer(t_lexer *stack)
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
		ft_free_array(&element->token.arr);
		temp = element;
		element = element->next;
		free(temp);
	}
	stack->head = NULL;
	stack->size = 0;
}

void	free_list(t_node **head)
{
	t_node	*element;
	t_node	*temp;

	if (*head == NULL)
		return ;
	element = *head;
	while (element != NULL)
	{
		temp = element;
		element = element->next;
		free(temp);
	}
	*head = NULL;
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
		ft_free_str(&element->var);
		temp = element;
		element = element->next;
		free(temp);
	}
	stack->head = NULL;
	stack->size = 0;
}
