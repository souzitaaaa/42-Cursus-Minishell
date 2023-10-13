/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:02:07 by joe               #+#    #+#             */
/*   Updated: 2023/10/04 13:31:48 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"

/*
!QUOTES.C
*/
void	create_quotes_node(t_quotes *quotes, int open_quote_type, int open_quote_position, int i);
int		check_quotes(char c, int quotes);
int		check_quotes_print(t_main *main);

/*
!QUOTES_SUBSTR
*/
void	quotes_substr(t_quotes *quotes, char *str);

/*
!QUOTES LIST.C
*/
void		shift_index_quotes(t_quotes *stack);
void		put_head_node_quotes(t_quotes *stack, t_node_quotes *new);
t_node_quotes		*remove_head_quotes(t_quotes *stack);
void		insert_head_quotes(t_quotes *stack, t_node_quotes *new);
void		insert_last_quotes(t_quotes *stack, t_node_quotes *new);
void    print_quotes(t_quotes *quotes);


#endif
