/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 12:45:00 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	init_quotes(t_quotes *quotes)
{
	quotes->head = NULL;
	quotes->size = 0;
	quotes->counter = 0;
}

void	ini_variables_quotes(t_variables_quotes *s_var_quotes)
{
	s_var_quotes->i = 0;
	s_var_quotes->quotes_analises = 0;
	s_var_quotes->open_quote_position = -1;
	s_var_quotes->open_quote_type = '\0';
	s_var_quotes->c = '\0';
}

void	init_ast(t_ast	*ast)
{
	ast->head = NULL;
	ast->counter = 0;
	ast->size = 0;
}

void	init_lexer(t_lexer *stack)
{
	stack->head = NULL;
	stack->size = 0;
}

void	init_env(t_env *stack)
{
	stack->head = NULL;
	stack->size = 0;
	stack->i = 0;
}
