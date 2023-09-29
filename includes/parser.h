/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:01 by joe               #+#    #+#             */
/*   Updated: 2023/09/29 12:43:39 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
!SYNTAX
*/
bool    syntax_analysis(t_main *main);

/*
!PARSER
*/
void	parser(t_main *main);
void	test_ast(t_lexer tokens, t_ast *ast);

/*
!CMDCAT
*/
void	cmdcat(t_lexer *tokens);

//!AST_ULTIS
void	insert_l_left(t_leave **leave, t_node *pipe);
void	insert_l_right(t_leave **leave, t_node *pipe, t_lexer tokens);

//!AST_LEXER
void	left_create_list_in(t_lexer *list_in, t_node *aux);
void	left_create_list_out(t_lexer *list_out, t_node *aux);
void	right_create_list_in(t_lexer *list_in, t_node *aux, t_lexer tokens);
void	right_create_list_out(t_lexer *list_out, t_node *aux, t_lexer tokens);

//!LIST_END_NULL
void	shift_index_endnull(t_lexer *stack);
void	put_head_node_endnull(t_lexer *stack, t_node *new);
void	insert_head_endnull(t_lexer *stack, t_node *new);
void	insert_last_endnull(t_lexer *stack, t_node *new, int index);
void    print_list_endnull(t_node *head);

#endif
