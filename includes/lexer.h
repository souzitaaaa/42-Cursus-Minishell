/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:51:53 by joe               #+#    #+#             */
/*   Updated: 2023/10/13 18:13:54 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*
!ADD_TOKENS
*/
int		add_token(t_main *main, t_type token, char *str);

/*
!CREATE_NODES
*/
t_node	*create_n(t_main *main, t_type token, char *str);
t_node	*create_n_prev(t_main *main, t_type token, char **arr);

/*
!LEXER_UTILS
*/
void    remove_node(t_lexer *lexer, int index);
void    insert_node(t_lexer *lexer, t_node *new, int index);
void    print_tokens(t_lexer *tokens);
t_node *get_node(t_lexer tokens, int index_wanted);

/*
!LEXER.C
*/
void	lexer(t_main *main);

/*
!QUOTES_TREATMENT.C
*/
char	**quotes_treatment(t_quotes quotes, char *str, t_main *main);
t_node	*create_n_quotes(t_main *main, t_type token, int *i, char **result, bool expand);
int		add_token_quotes(t_main *main, t_type token, int *i, char **result, bool expand);
int		get_min(int a, int b);

/*
!JOIN_UTILS
*/
char	**ft_arrnl_strarrjoin(char	**arr1, char	*str, char	**arr2);
char	**ft_arrstrnl_arrjoin(char	**arr1, char	*str, char	**arr2);
char	**ft_arrstrarrjoin(char	**arr1, char	*str, char	**arr2);
char    *join_expanded(char *str, char *expanded, int len);

/*
!EXPAND.C
*/
char	*expand(t_main *main, char *cmp);
char	*expand_more(t_main *main, char *str);
void	check_expansion_arr(t_main *main, char **arr);
char	*check_expansion_str(t_main *main, char *str);

/*
!EXPAND_UTILS.C
*/
char    *ft_arr_to_str(char **arr, char *str);
bool    check_more_var(char *str, int i);
int     get_number_len(int n);
char	*expand_exitcode(t_main *main, char *str);
void	check_expansion(t_main *main, char **arr);
void	del_emptyline(char **arr);

/*
!LIST.C
*/
void		shift_index(t_lexer *stack);
void		put_head_node(t_lexer *stack, t_node *new);
t_node		*remove_head(t_lexer *stack);
void		insert_head(t_lexer *stack, t_node *new);
void		insert_last(t_lexer *stack, t_node *new);



#endif
