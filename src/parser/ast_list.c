/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:45:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/23 22:45:20 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	left_create_list_in(t_lexer *list_in, t_node *aux)
{
	t_node	*new_node;

	init_list_ast(list_in);
	while (1)
	{
		if (aux->token.type == IN || aux->token.type == HEREDOC)
		{
			new_node = node_dup(aux);
			insert_head_endnull(list_in, new_node);
		}
		if (aux->index == 0)
			break ;
		aux = aux->prev;
	}
	if (list_in->head != NULL)
		shift_index_endnull(list_in);
}

void	left_create_list_out(t_lexer *list_out, t_node *aux)
{
	t_node	*new_node;

	init_list_ast(list_out);
	while (1)
	{
		if (aux->token.type == OUT || aux->token.type == APPEND)
		{
			new_node = node_dup(aux);
			insert_head_endnull(list_out, new_node);
		}
		if (aux->index == 0)
			break ;
		aux = aux->prev;
	}
	if (list_out->head != NULL)
		shift_index_endnull(list_out);
}

void	right_create_list_in(t_lexer *list_in, t_node *aux, t_lexer tokens)
{
	int		counter;
	t_node	*new_node;

	init_list_ast(list_in);
	counter = 0;
	while (aux->token.type != PIPE && aux != tokens.head)
	{
		if (aux->token.type == IN || aux->token.type == HEREDOC)
		{
			new_node = node_dup(aux);
			insert_last_endnull(list_in, new_node, counter);
			counter++;
		}
		aux = aux->next;
	}
}

void	right_create_list_out(t_lexer *list_out, t_node *aux, t_lexer tokens)
{
	int		counter;
	t_node	*new_node;

	init_list_ast(list_out);
	counter = 0;
	while (aux->token.type != PIPE && aux != tokens.head)
	{
		if (aux->token.type == OUT || aux->token.type == APPEND)
		{
			new_node = node_dup(aux);
			insert_last_endnull(list_out, new_node, counter);
			counter++;
		}
		aux = aux->next;
	}
}
