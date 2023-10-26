/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:01 by joe               #+#    #+#             */
/*   Updated: 2023/10/23 23:04:59 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
!PARSER
*/
void	parser(t_main *main);

/*
!SYNTAX
*/
bool	syntax_analysis(t_lexer tokens);

/*
!SYNTAX_UTILS
*/
char	*get_token(t_type type);
bool	is_rdr(t_type type);
bool	is_emptyrdr(t_token token);

/*
!CMDCAT
*/
void	cmdcat(t_lexer *tokens);

/*
!CMDCAT_UTILS
*/
int		find_first_cmd(t_node *aux, int size);
char	**copy_first_cmd(t_lexer tokens, int index);
t_node	*create_n_cmd(char **temp);
void	insert_temp(t_lexer *tokens, int index, char **temp);

//!AST
void	create_ast(t_lexer tokens, t_ast *ast);
//void	print_ast(t_ast ast);

//!AST_ULTIS
void	insert_l_left(t_leaf **leave, t_node *pipe);
void	insert_l_right(t_leaf **leave, t_node *pipe, t_lexer tokens);

//!AST_LIST
void	left_create_list_in(t_lexer *list_in, t_node *aux);
void	left_create_list_out(t_lexer *list_out, t_node *aux);
void	right_create_list_in(t_lexer *list_in, t_node *aux, t_lexer tokens);
void	right_create_list_out(t_lexer *list_out, t_node *aux, t_lexer tokens);

//!AST_LIST_UTILS
void	init_list_ast(t_lexer *list);
t_node	*node_dup(t_node *src);

//!LIST_END_NULL
void	shift_index_endnull(t_lexer *stack);
void	put_head_node_endnull(t_lexer *stack, t_node *new);
void	insert_head_endnull(t_lexer *stack, t_node *new);
void	insert_last_endnull(t_lexer *stack, t_node *new, int index);
//void    print_list_endnull(t_node *head);

#endif
