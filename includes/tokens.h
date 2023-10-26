/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:19:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 15:38:34 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

/*
!EXTRA_TOKENS.C
*/
void	search_extra_tokens(t_main *main, int *i);
bool	check_index_quotes(t_main *main, int *i);

/*
!OUTPUT_TOKENS.C
*/
t_type	t_type(t_main *main, int *i, int index);
void	search_output_tokens(t_main *main, int *i);
bool	is_space(char c);
int		get_fd_rdr(t_main *main, int *i);

/*
!INPUT_TOKENS.C
*/
void	search_input_tokens(t_main *main, int *i);
void	get_rdr_in(t_main *main, int *i, t_type token);

bool	check_valid_fd(char *str);

#endif
