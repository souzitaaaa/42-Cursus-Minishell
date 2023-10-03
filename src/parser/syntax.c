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
//*pipes seguidos

//*Começar em pipe
bool    syntax_first_node(t_lexer tokens)
{
    t_node  *aux;

	aux = tokens.head;
	if (aux->token.type == PIPE)
	{
	    printf("minishell: syntax error near unexpected token `|'\n");
	    return (false);
	}
	//printf("syntax on tthe out is right\n");
	return (true);
}

//*Acabar em pipe ou riderect
bool    syntax_last_node(t_lexer tokens)
{
    t_node  *aux;

	aux = tokens.head->prev;
	if ((aux->token.type != STRING && *aux->token.arr == 0) || aux->token.type == PIPE)
	{
	    printf("minishell: syntax error near unexpected token 'newline'\n");
	    return (false);
	}
	//printf("syntax on tthe out is right\n");
	return (true);
}

bool	syntax_analysis(t_lexer tokens)
{
    //printf("\033[1;33m\t\t\t[Syntax Analysis]\033[0m\n");
	if (syntax_first_node(tokens) == false)
        return (false);
    if (syntax_last_node(tokens) == false)
        return (false);
    return (true);
}
