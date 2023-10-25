/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:51:53 by joe               #+#    #+#             */
/*   Updated: 2023/10/25 11:16:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*
!ADD_TOKENS.C
*/
int		add_token(t_main *main, t_type token, char *str);
t_node	*create_n(t_main *main, t_type token, char *str);
char	**quotes_split(char *str, t_main *main, t_type token, bool *quote_hd);

/*
!EXPAND_UTILS.C
*/
bool	check_more_var(char *str, int i);
int	get_number_len(int n);
char	*expand_exitcode(t_main *main, char *str);
char	*ft_arr_to_str(char **arr, char *str);

/*
!EXPAND_UTILS2.C
*/
void    del_emptyline_while(char **arr, int *j);
void	del_emptyline(char **arr);
void	check_expansion_arr(t_main *main, char **arr);
char	*check_expansion_str(t_main *main, char *str);

/*
!EXPAND.C
*/
char	*expand(t_main *main, char *cmp);
char	*expand_more(t_main *main, char *str);
char	*expand_var(t_main *main, char *str, int i);

/*
!JOIN_UTILS.C
*/
char	**ft_arrnl_strarrjoin(char	**arr1, char	*str, char	**arr2);
char	**ft_arrstrnl_arrjoin(char	**arr1, char	*str, char	**arr2);
char	**ft_arrstrarrjoin(char	**arr1, char	*str, char	**arr2);
char    *join_expanded(char *str, char *expanded, int len);

/*
!LEXER_UTILS.C
*/
void	remove_node(t_lexer *lexer, int index, bool ft_free);
void    insert_node(t_lexer *lexer, t_node *new, int index);
void    print_tokens(t_lexer *tokens);
t_node *get_node(t_lexer tokens, int index_wanted);
bool	special_chr(char c);

/*
!LEXER.C
*/
void	lexer(t_main *main);
void search_tokens(t_main *main, int *i);

/*
!LIST.C
*/
void		shift_index(t_lexer *stack);
void		put_head_node(t_lexer *stack, t_node *new);
t_node		*remove_head(t_lexer *stack);
void		insert_head(t_lexer *stack, t_node *new);
void		insert_last(t_lexer *stack, t_node *new);

/*
!QUOTES_TREATMENT.C
*/
char	**out_of_quotes(char *str, int start, int len, t_main *main);
char	**check_join(t_join join, char before, char after);
char	**ft_quotes(t_node_quotes *aux, char *str, t_main *main, bool first);
char	**quotes_treatment(t_quotes quotes, char *str, t_main *main);

/*
!QUOTES_UTILS.C
*/
char	**str_to_arr(char *str);

#endif
