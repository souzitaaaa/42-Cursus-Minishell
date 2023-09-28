/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:36:59 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 11:50:25 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"

/*
!QUOTES.C
*/
int		check_quotes(char c, int quotes);
int		check_quotes_print(t_main *main);


/*
!QUOTES LIST.C
*/
void		shift_index_quotes(t_quotes *stack);
void		put_head_node_quotes(t_quotes *stack, t_node_quotes *new);//!INICIALIZAR ISSO "t_node_quotes" !!!!!!!!
t_node_quotes		*remove_head_quotes(t_quotes *stack);
void		insert_head_quotes(t_quotes *stack, t_node_quotes *new);
void		insert_last_quotes(t_quotes *stack, t_node_quotes *new);

#endif
