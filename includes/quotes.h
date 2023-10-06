/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:02:07 by joe               #+#    #+#             */
/*   Updated: 2023/10/06 13:05:57 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"

/*
!QUOTES.C
*/
int		check_quotes(char c, int quotes);
int		check_quotes_print(t_main *main);
char *remove_empty_quotes(char *prompt);

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
