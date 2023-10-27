/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:58:56 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/19 15:58:56 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Redirects vazios seguidos
bool	syntax_followed_rdrs(t_lexer tokens)
{
	t_node	*aux;
	int		count;

	count = 0;
	aux = tokens.head;
	while (count++ < tokens.size - 1)
	{
		if (is_emptyrdr(aux->token))
		{
			if (is_rdr(aux->next->token.type))
				error_syntax(get_token(aux->next->token.type));
			if (aux->next->token.type == PIPE)
				error_syntax("|");
			return (false);
		}
		aux = aux->next;
	}
	return (true);
}

//*pipes seguidos
bool	syntax_double_pipe(t_lexer tokens)
{
	t_node	*aux;
	int		count;

	count = 0;
	aux = tokens.head;
	while (count++ < tokens.size - 1)
	{
		if (aux->token.type == PIPE && aux->next->token.type == PIPE)
		{
			error_syntax("||");
			return (false);
		}
		aux = aux->next;
	}
	return (true);
}

//*Começar em pipe
bool	syntax_first_node(t_lexer tokens)
{
	t_node	*aux;

	aux = tokens.head;
	if (aux->token.type == PIPE)
	{
		error_syntax("|");
		return (false);
	}
	return (true);
}

//*Acabar em pipe ou riderect vazio
bool	syntax_last_node(t_lexer tokens)
{
	t_node	*aux;

	aux = tokens.head->prev;
	if (is_rdr(aux->token.type)
		&& (aux->token.arr == NULL))
	{
		error_syntax("newline");
		return (false);
	}
	if (aux->token.type == PIPE)
	{
		error_syntax("|");
		return (false);
	}
	return (true);
}

bool	syntax_analysis(t_lexer tokens)
{
	if (syntax_first_node(tokens) == false)
	{
		return (false);
	}
	if (syntax_double_pipe(tokens) == false)
	{
		return (false);
	}
	if (syntax_followed_rdrs(tokens) == false)
	{
		return (false);
	}
	if (syntax_last_node(tokens) == false)
	{
		return (false);
	}
	return (true);
}
