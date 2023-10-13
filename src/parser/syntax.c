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

//!redirects seguidos,  redirect e pipe por esta ordem -> ver com o diogo
bool    syntax_followed_rdrs(t_lexer tokens)
{
    t_node  *aux;
    int count = 0;

	aux = tokens.head;
	while (count++ < tokens.size - 1)
	{
		if ((aux->token.type == OUT || aux->token.type == IN
			|| aux->token.type == HEREDOC || aux->token.type == APPEND)
				&& (aux->next->token.type == OUT || aux->next->token.type == IN
					|| aux->next->token.type == HEREDOC || aux->next->token.type == APPEND))
		{
		    ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		    return (false);
		}
		aux = aux->next;
	}
	return (true);
}

//*pipes seguidos
bool    syntax_double_pipe(t_lexer tokens)
{
    t_node  *aux;
    int count = 0;

	aux = tokens.head;
	while (count++ < tokens.size - 1)
	{
		if (aux->token.type == PIPE && aux->next->token.type == PIPE)
		{
		    ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		    return (false);
		}
		aux = aux->next;
	}
	return (true);
}


//*Começar em pipe
bool    syntax_first_node(t_lexer tokens)
{
    t_node  *aux;

	aux = tokens.head;
	if (aux->token.type == PIPE)
	{
	    ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	    return (false);
	}
	return (true);
}

//*Acabar em pipe ou riderect
bool    syntax_last_node(t_lexer tokens)
{
    t_node  *aux;

	aux = tokens.head->prev;
	if ((aux->token.type != STRING && *aux->token.arr == 0) || aux->token.type == PIPE)
	{
	    ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
	    return (false);
	}
	return (true);
}

bool	syntax_analysis(t_lexer tokens)
{
    //printf("\033[1;33m\t\t\t[Syntax Analysis]\033[0m\n");
	if (syntax_first_node(tokens) == false)
        return (false);
    if (syntax_last_node(tokens) == false)
        return (false);
    if (syntax_double_pipe(tokens) == false)
        return (false);
	if (syntax_followed_rdrs(tokens) == false)
        return (false);
    return (true);
}
