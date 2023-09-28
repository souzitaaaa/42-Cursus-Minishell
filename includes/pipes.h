/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:10:32 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 12:11:18 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"


//!PIPES
void		pipex(t_ast *ast, t_main *main);
t_ast_node	*get_beg(t_ast *ast);
void		write_to_pipe(int *fd, char **cmd, t_main *main);
void		pipe_read_and_write(int *fd, int *next_fd, char **cmd, t_main *main);
void		read_from_pipe(int *fd, char **cmd, t_main *main);


#endif