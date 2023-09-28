/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:08:17 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 12:09:25 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDR_H
# define RDR_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"


/*
!RDR
*/
void	init_rdr(t_lexer tokens, t_main *main);
void	rdr_in(char **arr, t_main *main);
void	rdr_out(char **arr, t_main *main);
void	rdr_app(char **arr, t_main *main);
void	rdr_hd(t_token token, t_main *main, int fd);
int		open_hd(char *lim, bool quotes, t_main *main);
void	rdr_error(char *str, t_main *main, int options);


#endif
