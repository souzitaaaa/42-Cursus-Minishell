/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:57:34 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 11:58:45 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"


/*
!EXTRA_TOKENS.C
*/
void	search_extra_tokens(t_main *main, int *i);
bool	special_chr(char c);


/*
!INPUT_TOKENS.C
*/
void    search_input_tokens(t_main *main, int *i, char *str);
void    get_rdr_in(t_main *main, int *i, t_type token, char *fd);


/*
!OUTPUT_TOKENS.C
*/
void    search_output_tokens(t_main *main, int *i, char *str);
bool    is_space(char c);
int     get_fd_rdr(t_main *main, int *i);


#endif