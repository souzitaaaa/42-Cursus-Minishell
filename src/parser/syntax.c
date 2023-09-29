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

bool    syntax_last_node(t_lexer *lexer)
{
    int count = 0;
    t_node  *aux = lexer->head;

	while (count++ < lexer->size)
		aux = aux->next;
	if (aux->token.type != STRING && ft_arrlen(aux->token.arr) == 0)
	{
	    //printf("bash: syntax error near unexpected token 'newline'\n");
	    return (false);
	}
	//printf("syntax on tthe out is right\n");
	return (true);
}

bool    syntax_analysis(t_main *main)
{
    //printf("\033[1;33m\t\t\t[Syntax Analysis]\033[0m\n");
    if (syntax_last_node(&main->tokens) == false)
        return (false);
    return (true);
}
