/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:51:53 by joe               #+#    #+#             */
/*   Updated: 2023/10/02 15:23:04 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*
!ADD_TOKENS
*/
int		add_token(t_main *main, t_type token, int *i, char *str);
int     add_prev_token(t_main *main, int *i, char *str);

/*
!CREATE_NODES
*/
t_node	*create_n(t_main *main, t_type token, int *i, char *str);
t_node	*create_n_prev(t_main *main, t_type token, char **arr);

/*
!LEXER_UTILS
*/
void    remove_node(t_lexer *lexer, int index);
void    insert_node(t_lexer *lexer, t_node *new, int index);
void    print_tokens(t_lexer *tokens);
t_node	*find_node(t_lexer tokens, int index);
int		find_last_hd(t_lexer tokens);

/*
!LEXER.C
*/
void	lexer(t_main *main);

/*
!QUOTES_TREATMENT.C
*/
void    quotes_treatment(t_main *main, int *i, int start);
int     add_token_quotes(t_main *main, t_type token, int *i, char *str, bool expand);

/*
!TOKEN.C
*/
t_node	*create_n(t_main *main, t_type token, int *i, char *str);
int		add_token(t_main *main, t_type token, int *i, char *str);
int     add_prev_token(t_main *main, int *i, char *str);
char	*expand(t_main *main, char *cmp);
void	check_expansion(t_main *main, char **arr);
t_node *get_node_index(t_lexer *tokens, int index_wanted);

/*
!LIST.C
*/
void		shift_index(t_lexer *stack);
void		put_head_node(t_lexer *stack, t_node *new);
t_node		*remove_head(t_lexer *stack);
void		insert_head(t_lexer *stack, t_node *new);
void		insert_last(t_lexer *stack, t_node *new);


#endif
