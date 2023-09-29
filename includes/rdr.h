/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:08:17 by joe               #+#    #+#             */
/*   Updated: 2023/09/29 12:37:31 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDR_H
# define RDR_H

# include "minishell.h"

/*
!INIT_RDR
*/
void	init_rdr(t_lexer tokens, t_main *main);

/*
!RDR_APP
*/
void	rdr_app(char **arr, t_main *main);

/*
!RDR_HD
*/
int		open_hd(char *lim, bool quotes, t_main *main);
void	rdr_hd(t_token token, t_main *main, int fd);

/*
!RDR_IN
*/
void	rdr_in(char **arr, t_main *main);

/*
!RDR_OUT
*/
void	rdr_out(char **arr, t_main *main);

/*
!RDR_ERROR
*/
void	rdr_error(char *str, t_main *main, int options);

#endif
