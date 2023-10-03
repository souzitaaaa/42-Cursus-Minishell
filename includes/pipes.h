/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:10:32 by joe               #+#    #+#             */
/*   Updated: 2023/10/01 18:38:59 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

/*
!PIPES
*/
void		pipex(t_ast *ast, t_main *main);

/*
!PIPES_UTIL
*/
t_ast_node	*get_beg(t_ast *ast);
void		write_to_pipe(int *fd, t_leaf *cmd, t_main *main);
void		pipe_read_and_write(int *fd, int *next_fd, t_leaf *cmd, t_main *main);
void		read_from_pipe(int *fd, t_leaf *cmd, t_main *main);

/*
!RDR_IMPUT
*/
void	ft_redirect_in(t_node	*head, t_main *main, t_hd hd);
void	exec_hd_p(t_ast *ast, t_main *main);

/*
!RDR_OUTPUT
*/
void	ft_redirect_out(t_node	*head, t_main *main);

#endif
